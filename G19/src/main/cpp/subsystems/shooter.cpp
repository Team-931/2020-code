/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/shooter.h"

using namespace constants::shooter;

shooter::shooter():shootermotor(motorid, rev::CANSparkMax::MotorType::kBrushless), 
m2(mid2, rev::CANSparkMax::MotorType::kBrushless),
hopperbelt(hopperbeltid),
intake(intakeid),
Gate(Gateid),
RightSolenoid(AngleForward, AngleBackward),
LeftSolenoid(SolenoidForward, SolenoidBackward)
 {
  // Implementation of subsystem constructor goes here.
  shootermotor.RestoreFactoryDefaults(); m2.RestoreFactoryDefaults();
  m2.Follow(shootermotor, true);
  rev::CANPIDController UniqueName = shootermotor.GetPIDController();
      UniqueName.SetP(kP);
      UniqueName.SetI(kI);
      UniqueName.SetD(kD);
      UniqueName.SetIZone(kIz);
      UniqueName.SetFF(kFF);
      UniqueName.SetOutputRange(kMinOutput, kMaxOutput);
      //SolenoidUp();
}

void shooter::Periodic() {
  // Implementation of subsystem periodic method goes here.
  if(double rpm = shooterencoder.GetVelocity(); GateOpen && rpm >= minRPM &&  rpm <= maxRPM) {
    Gate.Set(1);
    TransferSpeed = 1;
  }
  else Gate.Set(0);// changed from -1

  if(safeToUseIntake) intake.Set(PickupSpeed);
  // Causes stuttering to keep balls from treadmilling.
  static short irregularity = 0;
  constexpr short irr_period = 20;
  if(irregularity >= irr_period * 3/4) hopperbelt.StopMotor();
  else hopperbelt.Set(TransferSpeed);
  if(++irregularity == irr_period) irregularity = 0;
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
