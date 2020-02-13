#pragma once

#include <frc2/command/SubsystemBase.h>
#include <CTRE/phoenix.h>
#include "Constants.h"
#include <frc/Counter.h>

class Cowl : public frc2::SubsystemBase {
      // Components (e.g. motor controllers and sensors) should generally be
  // declared private and exposed only through public methods.

    //  Allows the Cowl to move up and down for aiming
  WPI_TalonSRX CowlLift;
    //  Counts the ticks while moving the Cowl
  frc::Counter CowlCounter;
    int CurrentPosition, MotorVelocity, DesiredTicks;
 public:
  Cowl();
  //  Can we have set positions with Cowl?
  /**  @param DesiredLocation is the rotation for the Cowl
   * if it can, go to the desired level
   * it it can't, close to the desired level
  */
  void LiftCowl(int DesiredLocation);
  /**
   * Will be called periodically whenever the CommandScheduler runs.
   */
  void Periodic() override;

  int GetCount() {return CowlCounter.Get();}

};
