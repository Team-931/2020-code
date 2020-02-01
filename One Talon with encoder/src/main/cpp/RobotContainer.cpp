/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "RobotContainer.h"
# include <frc2/command/RunCommand.h>
# include <frc2/command/button/JoystickButton.h>
 ControlMode mode = ControlMode::Position;

constexpr double ticksPerRot = 1024;
/** maps the desired angle to the closest half-rotation, then sets it
 * @param it : Talon to use
 * @param rot : new angle (* ticksPerRot)
 * @param mode : one of ControlMode::Position or ControlMode::MotionMagic
 * @return whether the half-rotation is on the other side
*/
bool SetPos(WPI_TalonSRX &it, double rot) {
  int quot; // will hold 3 bits of rot / (ticksPerRot/2)
  double old = it.GetSelectedSensorPosition();
  rot = remquo(rot, ticksPerRot/2, &quot);
  it.Set(mode, rot);
  return quot & 1;
}

auto constexpr hand = frc::GenericHID::kRightHand;

RobotContainer::RobotContainer() : m_autonomousCommand(&m_subsystem) {
  // Initialize all of your commands and subsystems here
  motor.ConfigSelectedFeedbackSensor(FeedbackDevice::Analog);
  motor.Config_kP(0, .25);
  motor.ConfigMotionAcceleration(512);
  motor.ConfigMotionCruiseVelocity(512);
  m_subsystem.SetDefaultCommand(frc2::RunCommand([this](){
    double x = stick.GetY(hand), y = stick.GetX(hand);
    if(x*x+y*y > .09) SetPos(motor, atan2(x,y));
    }));
  // Configure the button bindings
  ConfigureButtonBindings();
}

void RobotContainer::ConfigureButtonBindings() {
  // Configure your button bindings here
  frc2::JoystickButton  (&stick, 1) . WhenPressed([](){
    if (mode == ControlMode::Position) mode = ControlMode::MotionMagic; 
    else mode = ControlMode::Position;
  });
/*   frc2::JoystickButton (&stick, 2) . WhenPressed([this](){
    motor.GetPIDConfigs();
  });
  frc2::JoystickButton (&stick, 3);
 */
  frc2::JoystickButton (&stick, 5).WhenHeld(frc2::RunCommand([this](){
    motor.Set(ControlMode::PercentOutput, stick.GetX(hand));
  }));
  }

frc2::Command* RobotContainer::GetAutonomousCommand() {
  // An example command will be run in autonomous
  return &m_autonomousCommand;
}
