/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include "AnalogEncoder.h"
#include <frc/Talon.h>
#include <frc/controller/PIDController.h>
#include <frc/controller/ProfiledPIDController.h>
#include <frc/kinematics/SwerveModuleState.h>
#include <wpi/math>

template <typename TurnCtrl> class SwerveModule {
 public:
  SwerveModule(int driveMotorChannel, int turningMotorChannel, int encChannel);
  frc::SwerveModuleState GetState() const;
  void SetDesiredState(const frc::SwerveModuleState& state);

 private:
  static constexpr double kWheelRadius = 0.0508;
  static constexpr int kEncoderResolution = 5;

  static constexpr auto kModuleMaxAngularVelocity =
      wpi::math::pi * 1_rad_per_s;  // radians per second
  static constexpr auto kModuleMaxAngularAcceleration =
      wpi::math::pi * 2_rad_per_s / 1_s;  // radians per second^2

  frc::Talon m_driveMotor;
  TurnCtrl m_turningMotor;

  frc::Encoder m_driveEncoder{0, 1};
  AnalogEncoder m_turningEncoder;

  frc2::PIDController m_drivePIDController{1.0, 0, 0};
  frc::ProfiledPIDController<units::radians> m_turningPIDController{
      1.0,
      0.0,
      0.0,
      {kModuleMaxAngularVelocity, kModuleMaxAngularAcceleration}};
};
