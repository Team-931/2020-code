/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc2/command/PIDSubsystem.h>
#include <CTRE/phoenix.h>
#include "Constants.h"
#include <AHRS.h>

class onewheeldrive {
    WPI_TalonSRX drivetrain; 
    WPI_TalonSRX turn;
    const Coordinate Location;
    double speed;

public:
    onewheeldrive (unsigned int wheel);
      // + is forward, - is reversed
    double Move(      //Returns the absolute value of the speed
      double rotation,
      double forward,
      double rightward
    );
    void dividspeed(double divider){
      speed/=divider;
    }
    void setspd(){
      drivetrain.Set(speed);
    }
};

class drivetrain : public frc2::PIDSubsystem {
    onewheeldrive fleft {0};
    onewheeldrive fright {1};
    onewheeldrive bleft {2};
    onewheeldrive bright {3};    
    

    public:
  drivetrain();
  // Clockwise is Positive, Counter-Clockwise is Negative // does not take field orientation
  void Move(
    double rotation,
    double forward,
    double rightward);
      //  Rotation will be controlled in a seperate way //This does take field orientation
  void Move(
    double rightward,
    double forward);
      // Takes the field, then navigates based on it
  void SetAngleToField(
    double rotation);
  /**
   * Will be called periodically whenever the CommandScheduler runs.
   */
  //void Periodic() override;
  AHRS & GetNavX() {return navx;}

 private:

    AHRS navx {::SPI::kMXP};//reports in degrees, clockwise
    // saved motion components
    double xaxis=0;
    double yaxis=0;
    // for feed-forward rotation
    double futureSetpoint;

  // Components (e.g. motor controllers and sensors) should generally be
  // declared private and exposed only through public methods.
  protected:
  double GetMeasurement() override;
  void UseOutput(double output, double setpoint) override;
 };
