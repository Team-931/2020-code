/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

# pragma once

# include <string>

# include <frc/TimedRobot.h>
# include <ctre/Phoenix.h>
# include <frc/SpeedControllerGroup.h>
# include <frc/drive/DifferentialDrive.h>
# include <rev/ColorSensorV3.h>
# include <frc/XboxController.h>
# include <frc/smartdashboard/SendableChooser.h>

class Robot : public frc::TimedRobot {
 public:
  void RobotInit() override;
  void RobotPeriodic() override;
  void AutonomousInit() override;
  void AutonomousPeriodic() override;
  void TeleopInit() override;
  void TeleopPeriodic() override;
  void TestPeriodic() override;

 private:
 //auto stuff
  frc::SendableChooser<std::string> m_chooser;
  const std::string kAutoNameDefault = "Default";
  const std::string kAutoNameCustom = "My Auto";
  std::string m_autoSelected;
  // Robot drive system
  ::WPI_TalonSRX leftMotor{3};
  ::WPI_TalonSRX rightMotor{1};
  ::WPI_TalonSRX leftMotor2{4};
  ::WPI_TalonSRX rightMotor2{2};
  frc::SpeedControllerGroup right {rightMotor, rightMotor2};
  frc::SpeedControllerGroup left {leftMotor, leftMotor2};
  frc::DifferentialDrive robotDrive{left, right};
  //color sense stuff
  rev::ColorSensorV3 colorEye{frc::I2C::Port::kOnboard};
  std::vector <double> savedReds;
  std::vector <double> savedGreens;
  std::vector <double> savedBlues;
  frc::XboxController driveStick{0};
};
