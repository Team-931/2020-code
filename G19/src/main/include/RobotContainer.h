/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc2/command/Command.h>
# include <frc/smartdashboard/SendableChooser.h>

#include "commands/ExampleCommand.h"
#include "subsystems/drivetrain.h"
#include "subsystems/climber.h"
#include "subsystems/WOFSpinner.h"
#include "subsystems/shooter.h"
#include "subsystems/Cowl.h"
#include <frc/Joystick.h>

/**
 * This class is where the bulk of the robot should be declared.  Since
 * Command-based is a "declarative" paradigm, very little robot logic should
 * actually be handled in the {@link Robot} periodic methods (other than the
 * scheduler calls).  Instead, the structure of the robot (including subsystems,
 * commands, and button mappings) should be declared here.
 */
class RobotContainer {
 public:
  RobotContainer();

  frc2::Command* GetAutonomousCommand();

 private:
 frc::SendableChooser<char> AutonomousDashboard;
  // The robot's subsystems and commands are defined here...
  drivetrain Drive;
  climber Climb;
  WOFSpinner Wheel;
  shooter Gun;
  Cowl GunRoof;
  ExampleCommand m_autonomousCommand;
  frc::Joystick JoystickDrive;
  frc::Joystick JoystickOperate;
  
  void ConfigureButtonBindings();

  void Hopperclimber(int position); 

  uint32_t SpecificColor();//This is for getting the specific color form the feild
  void CheckScoreColor(); // call SpecificColor() and use the result
  void RotateForCount(); // turns WOFSpinner 3.5 times
  bool RotateForColor(); // turns WOFSpinner to the right color
  uint32_t Color2Score = 0, Color2Find = 0, ColorFound = 0;
};
