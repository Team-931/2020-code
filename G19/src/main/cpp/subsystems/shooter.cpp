/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/shooter.h"

using namespace constants::shooter;

shooter::shooter():shootermotor(motorid, rev::CANSparkMax::MotorType::kBrushless),
hopperbelt(hopperbeltid),
intake(intakeid),
Gate(Gateid),
Angle(AngleForward, AngleBackward)
 {
  // Implementation of subsystem constructor goes here.
}

void shooter::Periodic() {
  // Implementation of subsystem periodic method goes here.
}
