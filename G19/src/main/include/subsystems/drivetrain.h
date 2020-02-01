/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc2/command/SubsystemBase.h>
#include <CTRE/phoenix.h>
#include "Constants.h"
#include <AHRS.h>

class onewheeldrive {
    WPI_TalonSRX drivetrain; 
    WPI_TalonSRX turn;

public:
    onewheeldrive (unsigned int wheel);
};

class drivetrain : public frc2::SubsystemBase {
    onewheeldrive fleft {0};
    onewheeldrive fright {1};
    onewheeldrive bleft {2};
    onewheeldrive bright {3};    
    
 public:
  drivetrain();
  
  /**
   * Will be called periodically whenever the CommandScheduler runs.
   */
  void Periodic() override;

 private:

    AHRS navx {::SPI::kMXP};

  // Components (e.g. motor controllers and sensors) should generally be
  // declared private and exposed only through public methods.
};
