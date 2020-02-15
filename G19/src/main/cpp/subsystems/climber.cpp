#include "Subsystems/climber.h"


using namespace constants::climber;

                                        // Changed Motor type from Brushless to Brushed
climber::climber():ClimbMotor(motorid, rev::CANSparkMax::MotorType::kBrushed),
Reach(ReachUp, ReachDown), ClimbMover(climbmoverid){
    ClimbMotor.SetIdleMode(rev::CANSparkMax::IdleMode::kBrake);}

void climber::Periodic(){}

void climber::reach(){
    ClimbMotor.Set(1);}

void climber::carry(){
    ClimbMotor.Set(-1);}

void climber::raise(){
    Reach.Set(frc::DoubleSolenoid::kForward);}

void climber::lower(){
    Reach.Set(frc::DoubleSolenoid::kReverse);}

void climber::SidewaysSpeed(double Speed){
    ClimbMover.Set(Speed);}