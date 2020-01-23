/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "SwerveModule.h"

#include <frc/AnalogInput.h>
#include <frc/geometry/Rotation2d.h>
#include <wpi/math>
#include <frc/SmartDashboard/SmartDashboard.h>

template <typename TurnCtrl> SwerveModule<TurnCtrl>::SwerveModule(int driveMotorChannel,
                           int turningMotorChannel, int encChannel)
    : m_driveMotor(driveMotorChannel), m_turningMotor(turningMotorChannel),  m_turningEncoder(new frc::AnalogInput (encChannel)) {
  // Set the distance per pulse for the drive encoder. We can simply use the
  // distance traveled for one rotation of the wheel divided by the encoder
  // resolution.
  m_driveEncoder.SetDistancePerPulse(2 * wpi::math::pi * kWheelRadius /
                                     kEncoderResolution);

  // Set the distance (in this case, angle) per pulse for the turning encoder.
  // This is the the angle through an entire rotation (2 * wpi::math::pi)
  // divided by the encoder resolution.
  m_turningEncoder.SetDistancePerRotation(2 * wpi::math::pi / kEncoderResolution);

  // Limit the PID Controller's input range between 0 and 2*pi and set the input
  // to be continuous.
  m_turningPIDController.EnableContinuousInput(-units::radian_t(/*wpi::math::pi*/0),
                                               2*units::radian_t(wpi::math::pi));
  
  frc::SmartDashboard::PutData(&m_turningPIDController);
  m_turningPIDController.SetP((turningMotorChannel >= 40) ? .0625 : 1);           //!! Kludge warning !!
}

template <typename TurnCtrl> frc::SwerveModuleState SwerveModule<TurnCtrl>::GetState() const {
  return {units::meters_per_second_t{m_driveEncoder.GetRate()},
          frc::Rotation2d(units::radian_t(m_turningEncoder.Get()))};
}

template <typename TurnCtrl> void SwerveModule<TurnCtrl>::SetDesiredState(const frc::SwerveModuleState& state) {
  // Calculate the drive output from the drive PID controller.
  const auto driveOutput = m_drivePIDController.Calculate(
      m_driveEncoder.GetRate(), state.speed.to<double>());

  // Calculate the turning motor output from the turning PID controller.
  const auto turnOutput = m_turningPIDController.Calculate(
      units::radian_t(m_turningEncoder.Get()), state.angle.Radians());

  // Set the motor outputs.
  m_driveMotor.Set(driveOutput);
  m_turningMotor.Set(turnOutput);
}

template class SwerveModule<WPI_TalonSRX>;
template class SwerveModule<WPI_VictorSPX>;
