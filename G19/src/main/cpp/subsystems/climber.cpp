#include "Subsystems/climber.h"


using namespace constants::climber;

                                        // Changed Motor type from Brushless to Brushed
climber::climber():/* ClimbMover(climbmoverid), */ ClimbMotor(motorid/* , rev::CANSparkMax::MotorType::kBrushed */),
Reach(ReachUp, ReachDown){
    ClimbMotor.SetNeutralMode(Brake) /* SetIdleMode(rev::CANSparkMax::IdleMode::kBrake) */;}

void climber::Periodic(){}

void climber::reach(){
    ClimbMotor.Set(1);}

void climber::carry(){
    ClimbMotor.Set(-1);}

void climber::still() {
    ClimbMotor.Set(0);
}

void climber::raise(){
    Reach.Set(frc::DoubleSolenoid::kForward);}

void climber::lower(){
    Reach.Set(frc::DoubleSolenoid::kReverse);}

void climber::SidewaysSpeed(double Speed){
    /* ClimbMover.Set(Speed); */}