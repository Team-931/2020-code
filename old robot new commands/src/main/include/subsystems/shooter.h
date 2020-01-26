/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc2/command/SubsystemBase.h>

# include <rev/CanSparkmax.h>

class Shooter : public frc2::SubsystemBase {
 public:
  Shooter();

 // void SetXYTwist(double forward, double left, double twist, bool squareInputs = true, Displacement center = zero);

  /**
   * Will be called periodically whenever the CommandScheduler runs.
   */
  void Periodic() override;

 private:
  //void AdjustSpeeds();
  // Components (e.g. motor controllers and sensors) should generally be
  // declared private and exposed only through public methods.
  typedef rev::CANSparkMax::MotorType MType;

  rev::CANSparkMax left{0, MType::kBrushless}, right{1,MType::kBrushless};
};
