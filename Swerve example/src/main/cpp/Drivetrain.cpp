/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Drivetrain.h"
# include <frc/shuffleboard/Shuffleboard.h>

void Drivetrain::SetPIDs() {
  frc::ShuffleboardTab & tab = frc::Shuffleboard::GetTab("PID");
  tab.Add("Front Left",  m_frontLeft.GetTurningPID());
  tab.Add("Front Right",  m_frontRight.GetTurningPID());
  tab.Add("Rear Left",  m_backLeft.GetTurningPID());
  tab.Add("Rear Right",  m_backRight.GetTurningPID());
}
void Drivetrain::Drive(units::meters_per_second_t xSpeed,
                       units::meters_per_second_t ySpeed,
                       units::radians_per_second_t rot, bool fieldRelative) {
  auto states = m_kinematics.ToSwerveModuleStates(
      fieldRelative ? frc::ChassisSpeeds::FromFieldRelativeSpeeds(
                          xSpeed, ySpeed, rot, GetAngle())
                    : frc::ChassisSpeeds{xSpeed, ySpeed, rot});

  m_kinematics.NormalizeWheelSpeeds(&states, kMaxSpeed);

  auto [fl, fr, bl, br] = states;

  m_frontLeft.SetDesiredState(fl);
  m_frontRight.SetDesiredState(fr);
  m_backLeft.SetDesiredState(bl);
  m_backRight.SetDesiredState(br);
}

void Drivetrain::UpdateOdometry() {
  m_odometry.Update(GetAngle(), m_frontLeft.GetState(), m_frontRight.GetState(),
                    m_backLeft.GetState(), m_backRight.GetState());
}
