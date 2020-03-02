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
RightSolenoid(AngleForward, AngleBackward),
LeftSolenoid(SolenoidForward, SolenoidBackward)
 {
  // Implementation of subsystem constructor goes here.
  shootermotor.RestoreFactoryDefaults();
  rev::CANPIDController UniqueName = shootermotor.GetPIDController();
      UniqueName.SetP(kP);
      UniqueName.SetI(kI);
      UniqueName.SetD(kD);
      UniqueName.SetIZone(kIz);
      UniqueName.SetFF(kFF);
      UniqueName.SetOutputRange(kMinOutput, kMaxOutput);
      SolenoidUp();
}

void shooter::Periodic() {
  // Implementation of subsystem periodic method goes here.
  if(double rpm = shooterencoder.GetVelocity(); GateOpen && rpm >= minRPM &&  rpm <= maxRPM) Gate.Set(1);
  else Gate.Set(-1);

  intake.Set(PickupSpeed);
  hopperbelt.Set(TransferSpeed);
}
// Implements
  void shooter::ShooterRPM(double RPM) {
    minRPM = .98 * RPM;
    maxRPM = 1.02 * RPM;
    shootermotor.GetPIDController ().SetReference(RPM, rev::kVelocity);
    }

  void shooter::TransferForwards() {TransferSpeed = 1;}
  void shooter::TransferOff() {TransferSpeed = 0;}
  void shooter::TransferBackwards() {TransferSpeed = -1;}
  void shooter::PickUpForwards() {PickupSpeed = 1;}
  void shooter::PickUpBackwards() {PickupSpeed = -1;}
  void shooter::PickUpOff() {PickupSpeed = 0;}
  void shooter::SolenoidUp() {LeftSolenoid.Set(frc::DoubleSolenoid::kForward); RightSolenoid.Set(frc::DoubleSolenoid::kForward);}
  void shooter::SolenoidDown() {LeftSolenoid.Set(frc::DoubleSolenoid::kReverse); RightSolenoid.Set(frc::DoubleSolenoid::kReverse);}
