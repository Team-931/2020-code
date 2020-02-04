/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "RobotContainer.h"

using namespace constants::RobotContainer;

RobotContainer::RobotContainer() : m_autonomousCommand(&Drive), JoystickDrive(JoystickDriveID), JoystickOperate(JoystickOperateID) {
  // Initialize all of your commands and subsystems here

  // Configure the button bindings
  ConfigureButtonBindings();
}

void RobotContainer::ConfigureButtonBindings() {
  // Configure your button bindings here
}

frc2::Command* RobotContainer::GetAutonomousCommand() {
  // An example command will be run in autonomous
  return &m_autonomousCommand;
}

int RobotContainer::SpecificColor(){
  return 0;//0 means no color yet
  //on WPI look for Game Data Details for more iformation about getting color

}
