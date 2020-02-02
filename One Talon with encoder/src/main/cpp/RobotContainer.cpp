/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "RobotContainer.h"
# include <frc2/command/RunCommand.h>
# include <frc2/command/button/JoystickButton.h>
# include <wpi/math>
using wpi::math::pi;

 ControlMode mode = ControlMode::Position;

constexpr double ticksPerHalfRot = 1024/2;
/** maps the desired angle to the closest half-rotation, then sets it
 * @param it : Talon to use
 * @param rot : new angle (* ticksPerRot)
 * @param mode : one of ControlMode::Position or ControlMode::MotionMagic
 * @return whether the half-rotation is on the other side
*/
bool SetPos(WPI_TalonSRX &it, double rot) {
  int quot; // will hold 3 bits of rot / (ticksPerHalfRot)
  double old = it.GetSelectedSensorPosition();
  rot = old + remquo(rot - old, ticksPerHalfRot, &quot);
  it.Set(mode, rot);
  return quot & 1;
}

auto constexpr spinSide = frc::GenericHID::kRightHand;
auto constexpr wheelSide = frc::GenericHID::kLeftHand;

RobotContainer::RobotContainer() : m_autonomousCommand(&wheel) {
  // Initialize all of your commands and subsystems here
  wheel.SetDefaultCommand(frc2::RunCommand([this](){
    double x = stick.GetY(spinSide), y = stick.GetX(spinSide);
    if(x*x+y*y > .09) wheel.RotateTo( atan2(x,y)/pi, mode);
  },&wheel));
  spinner.SetDefaultCommand(frc2::RunCommand([this](){
    double x = stick.GetX(wheelSide);
    if(abs(x > .125)) spinner.RotateBy(x, mode);
  }, &spinner));
  // Configure the button bindings
  ConfigureButtonBindings();
}

void RobotContainer::ConfigureButtonBindings() {
  // Configure your button bindings here
  frc2::JoystickButton  (&stick, 1) . WhenPressed([](){
    if (mode == ControlMode::Position) mode = ControlMode::MotionMagic; 
    else mode = ControlMode::Position;
  });
  frc2::JoystickButton (&stick, 2) . WhenPressed([this](){
    spinner.RotateTo(0, mode);
  });
  frc2::JoystickButton (&stick, 3) . WhenPressed([this](){
    spinner.RotateBy(.125, mode);
  });

  frc2::JoystickButton (&stick, 5).WhenHeld(frc2::RunCommand([this](){
    //motor.Set(ControlMode::PercentOutput, stick.GetX(spinSide));
  },&wheel));
  }

frc2::Command* RobotContainer::GetAutonomousCommand() {
  // An example command will be run in autonomous
  return &m_autonomousCommand;
}
