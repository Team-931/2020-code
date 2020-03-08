/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc2/command/SubsystemBase.h>
#include <rev/CANSparkMax.h>
#include "Constants.h"
#include <frc/DoubleSolenoid.h>
#include <CTRE/phoenix.h>

//  

class climber : public frc2::SubsystemBase {
 public:
      //Pull up onto Coat Hanger
  void carry();
      //Raise arm up to Coat Hanger
  void reach();
      //Bring out the arm
  void raise();
      //Lower Arm
  void lower();
      //Stand Still (double check)
  void still();
      // Speed of the Climber Arm Sideways
  void SidewaysSpeed(double Speed);
  climber();
  /**
   * Will be called periodically whenever the CommandScheduler runs.
   */
  void Periodic() override;

 private:

  WPI_TalonSRX ClimbMotor/*, ClimbMover*/;
  //rev::CANSparkMax ClimbMotor;
  //rev::CANEncoder ClimbEncoder {ClimbMotor};
    //Reaches for the bar on the Closet Hanger
  frc::DoubleSolenoid Reach;
  // Components (e.g. motor controllers and sensors) should generally be
  // declared private and exposed only through public methods.
};
