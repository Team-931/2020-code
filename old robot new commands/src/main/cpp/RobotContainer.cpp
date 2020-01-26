/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "RobotContainer.h"
# include <frc2/command/RunCommand.h>

RobotContainer::RobotContainer() : simpleAutoCommand(&driveSystem) {
  // Initialize all of your commands and subsystems here

  // Configure the button bindings
  ConfigureButtonBindings();
  typedef frc::GenericHID JS;
  driveSystem.SetDefaultCommand(frc2::RunCommand(
    [this]{driveSystem.SetXYTwist(
      driveStick.GetY(JS::kRightHand),
      driveStick.GetX(JS::kRightHand),
      driveStick.GetX(JS::kLeftHand));},
     &driveSystem));
}

void RobotContainer::ConfigureButtonBindings() {
  // Configure your button bindings here
}

frc2::Command* RobotContainer::GetAutonomousCommand() {
  // An example command will be run in autonomous
  return &simpleAutoCommand;
}
