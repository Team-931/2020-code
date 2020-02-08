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


class shooter : public frc2::SubsystemBase {
    //  Fires the Power Cells out of shooter to goal 
  rev::CANSparkMax shootermotor;
    //  Lets us know the speed the motors are going to firing the Power Cells at the goal
  rev::CANEncoder shooterencoder{shootermotor};
    //  Passes the Power Cells from Intake to the Shooter to fire
  WPI_TalonSRX hopperbelt;
    //  Picks the Power Cells up off of the ground
  WPI_TalonSRX intake;

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
