/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/ExampleSubsystem.h"

DriveSystem::DriveSystem() {
  // Implementation of subsystem constructor goes here.
}

void DriveSystem::SetXYTwist(double forward, double left, double twist, bool squareInputs, Displacement center) {
  if (squareInputs) {
    double norm = sqrt (forward*forward + left*left);
    forward *= norm;
    left *= norm;
  }
  fl.SetXYTwist(forward, left, twist, center); fr.SetXYTwist(forward, left, twist, center);
  bl.SetXYTwist(forward, left, twist, center); br.SetXYTwist(forward, left, twist, center);
  AdjustSpeeds();
}

void DriveSystem::Periodic() {
  // Implementation of subsystem periodic method goes here.
}

void DriveSystem::AdjustSpeeds() {
  double max = 1;
  fl.CheckMaxSpeed(max); fr.CheckMaxSpeed(max);
  bl.CheckMaxSpeed(max); br.CheckMaxSpeed(max);
  if (max > 1) {
    fl.ScaleSpeed(max); fr.ScaleSpeed(max);
    bl.ScaleSpeed(max); bl.ScaleSpeed(max);
  }
}