/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc2/command/SubsystemBase.h>
#include <rev/CANSparkMax.h>
#include <CTRE/phoenix.h>
#include "Constants.h"
//#include <frc/Encoder.h>

 

class shooter : public frc2::SubsystemBase {
  rev::CANSparkMax shootermotor;
  rev::CANEncoder shooterencoder{shootermotor};
  WPI_TalonSRX hopperbelt;
  WPI_TalonSRX intake;
  //frc::Encoder shooterencoder;


 public:
  shooter();

  /**
   * Will be called periodically whenever the CommandScheduler runs.
   */
  void Periodic() override;

 private:
  // Components (e.g. motor controllers and sensors) should generally be
  // declared private and exposed only through public methods.
};
