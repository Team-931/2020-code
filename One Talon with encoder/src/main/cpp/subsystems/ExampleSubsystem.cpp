/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/ExampleSubsystem.h"

ExampleSubsystem::ExampleSubsystem(SysType t): motor((t == Wheel)? 12: 31),
          TicksPerRot((t == Wheel)? 1024 : 40960)
 {
  // Implementation of subsystem constructor goes here.
  motor.ConfigSelectedFeedbackSensor((t == Wheel)? FeedbackDevice::Analog : FeedbackDevice::PulseWidthEncodedPosition);
  motor.Config_kP(0, (t == Wheel)? .25 : .25);
  motor.ConfigMotionAcceleration((t == Wheel)? 512 : 4096);
  motor.ConfigMotionCruiseVelocity((t == Wheel)? 512 : 4096);
  }

void ExampleSubsystem::Periodic() {
  // Implementation of subsystem periodic method goes here.
}

void ExampleSubsystem::RotateTo(double amt,ControlMode mode) {
  motor.Set(mode, amt*TicksPerRot);
}

void ExampleSubsystem::RotateBy(double amt,ControlMode mode) {
  motor.Set(mode, amt*TicksPerRot + motor.GetClosedLoopTarget());
}