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
#include <frc/DoubleSolenoid.h>

class shooter : public frc2::SubsystemBase {
    //  Fires the Power Cells out of shooter to goal 
  rev::CANSparkMax shootermotor, m2;
    //  Lets us know the speed the motors are going to firing the Power Cells at the goal
  rev::CANEncoder shooterencoder{shootermotor};
    //  Passes the Power Cells from Intake to the Shooter to fire
  WPI_TalonSRX hopperbelt;
    //  Picks the Power Cells up off of the ground
  WPI_TalonSRX intake;
    // Lets the power cells move into the shooter or keeps them out of the shooter
  WPI_TalonSRX Gate;
    //  The Input to change angle of the shooter
  frc::DoubleSolenoid RightSolenoid;
    //  The Input to change angle of the shooter
  frc::DoubleSolenoid LeftSolenoid;
    //  Checks if the Gate is opened or closed
  bool GateOpen {false};
    //  Sets starting speed of Intake
    //  Can be changed later in the game
  double PickupSpeed=0;
    //  Sets starting speed of Hopperbelt
    //  Can be changed later in the game
  double TransferSpeed=0;
  
  double minRPM, maxRPM;
 public:
  shooter();
  /**
   * Will be called periodically whenever the CommandScheduler runs.
   */
  void Periodic() override;
    /* Asks if gate is open or closed */
  bool GateStatus() {return GateOpen;}
      // Spins the Gate toward the Shooter, moving the Power Cells into the Shooter.
  void OpenGate() {GateOpen = true;}
      // Spins the Gate reverse to keep the Power Cells out of the Shooter
  void CloseGate() {GateOpen = false;}
      /*  Tells how fast the Shooter should spin
          How fast it rotates will give the Power Cell its Distance and Spin for better aim */
  void ShooterRPM(double RPM);
      //  Stop the Shooter Motor
  void StopShooter() {shootermotor.StopMotor();};
      //  Returns RPM(Rotations Per Minute)
  double ReturnRPM() {return shooterencoder.GetVelocity();}
      //  Hopperbelt; being able to transfer the Power Cells from Intake to Shooter.
  void TransferForwards();
      //  Turns off Hopperbelt
  void TransferOff();
      //  Hopperbelt; Gives the Power Cells back to the Intake
  void TransferBackwards();
      //  Intake; Forwards; picks up the Power Cells
  void PickUpForwards();
      //  Intake; Backwards; picks up the Power Cells
  void PickUpBackwards();
      //  Turns off Intake
  void PickUpOff();
      /* Picks up the Intake until next usage */
  void SolenoidUp();
      /* Puts down the Intake to pick up Power Cells */
  void SolenoidDown();
      //expand later
  double intakecurrent(){return intake.GetStatorCurrent();}
  
 private:
  // Components (e.g. motor controllers and sensors) should generally be
  // declared private and exposed only through public methods.
};
