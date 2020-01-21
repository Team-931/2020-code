/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/AnalogGyro.h>
#include <ctre/Phoenix.h>
#include <frc/geometry/Translation2d.h>
#include <frc/kinematics/SwerveDriveKinematics.h>
#include <frc/kinematics/SwerveDriveOdometry.h>
#include <wpi/math>

#include "SwerveModule.cpp"

/**
 * Represents a swerve drive style drivetrain.
 */
class Drivetrain {
 public:
  Drivetrain() { m_gyro.Reset(); }

  /**
   * Get the robot angle as a Rotation2d.
   */
  frc::Rotation2d GetAngle() const {
    // Negating the angle because WPILib Gyros are CW positive.
    return frc::Rotation2d(units::degree_t(-m_gyro.GetAngle()));
  }

  void Drive(units::meters_per_second_t xSpeed,
             units::meters_per_second_t ySpeed, units::radians_per_second_t rot,
             bool fieldRelative);
  void UpdateOdometry();

  static constexpr units::meters_per_second_t kMaxSpeed =
      3.0_mps;  // 3 meters per second
  static constexpr units::radians_per_second_t kMaxAngularSpeed{
      wpi::math::pi};  // 1/2 rotation per second

 private:
  frc::Translation2d m_frontLeftLocation{+0.35_m, +0.31_m};
  frc::Translation2d m_frontRightLocation{+0.35_m, -0.31_m};
  frc::Translation2d m_backLeftLocation{-0.35_m, +0.31_m};
  frc::Translation2d m_backRightLocation{-0.35_m, -0.31_m};

  SwerveModule<WPI_VictorSPX> m_frontLeft{1, 40,3};
  SwerveModule<WPI_VictorSPX> m_frontRight{3, 41, 0};
  SwerveModule<WPI_TalonSRX> m_backLeft{0, 12, 2};
  SwerveModule<WPI_TalonSRX> m_backRight{2, 31, 1};

  frc::AnalogGyro m_gyro{0};

  frc::SwerveDriveKinematics<4> m_kinematics{
      m_frontLeftLocation, m_frontRightLocation, m_backLeftLocation,
      m_backRightLocation};

  frc::SwerveDriveOdometry<4> m_odometry{m_kinematics, GetAngle()};
};
