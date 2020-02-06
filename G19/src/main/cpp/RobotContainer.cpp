/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "RobotContainer.h"
# include <frc2/command/button/JoystickButton.h>
# include <frc/DriverStation.h>
# include <frc/smartdashboard/SmartDashboard.h>
# include <cmath>
#include <frc2/command/RunCommand.h>

using namespace constants::RobotContainer;

RobotContainer::RobotContainer() : m_autonomousCommand(&Drive), JoystickDrive(JoystickDriveID), JoystickOperate(JoystickOperateID) {
  // Initialize all of your commands and subsystems here
    Wheel.SetDefaultCommand(frc2::RunCommand( //This all is temporary for testing
      [this]{frc::SmartDashboard::PutString("ColorFound", ColorNames[Wheel.FindColor()]);
      if(JoystickDrive.GetRawButtonPressed(2))
      Wheel.CoSensor(true);
      else 
      Wheel.CoSensor(false);}, &Wheel
    ));
  // Configure the button bindings
  ConfigureButtonBindings();
}

void RobotContainer::ConfigureButtonBindings() {
  // Configure your button bindings here
  frc2::JoystickButton(&JoystickOperate, 4).WhenPressed([](){});
}

frc2::Command* RobotContainer::GetAutonomousCommand() {
  // An example command will be run in autonomous
  return &m_autonomousCommand;
}

uint32_t RobotContainer::SpecificColor(){
  auto msg = frc::DriverStation::GetInstance().GetGameSpecificMessage();
  if (msg.length()) for (uint32_t i = 1; i <= 4; ++i) if(msg[0] == ColorNames[i][0]) 
    return i;
  return 0;//0 means no color yet
  //on WPI look for Game Data Details for more iformation about getting color
}

void RobotContainer::CheckScoreColor() {
  uint32_t color = SpecificColor();
  if (color == Color2Score) return;
  Color2Score = color;
  if (color > 2) Color2Find = color - 2;
  else if (color) Color2Find = color + 2;
  else Color2Find = 0;
  frc::SmartDashboard::PutString("Color to score", ColorNames[Color2Score]);
  frc::SmartDashboard::PutString("Color to find", ColorNames[Color2Find]);
}

void RobotContainer::RotateForCount() {
  Wheel.rotate(3.5);
}

bool RobotContainer::RotateForColor() {
  if (Color2Find == 0) return false;
  uint32_t found = Wheel.FindColor();
  if (found == 0) return false;
  Wheel.rotate(remainder(Color2Find - found, 4) / 8);
  return true;
}