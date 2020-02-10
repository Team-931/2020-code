#include "Subsystems/climber.h"


using namespace constants::climber;


climber::climber():ClimbMotor(motorid, rev::CANSparkMax::MotorType::kBrushless),
Reach(ReachUp, ReachDown)
{
    ClimbMotor.SetIdleMode(rev::CANSparkMax::IdleMode::kBrake);
}
void climber::Periodic(){}
void climber::reach(){
    ClimbMotor.Set(1);
}
void climber::carry(){
    ClimbMotor.Set(-1);
}
void climber::raise(){
    Reach.Set(frc::DoubleSolenoid::kForward);
}
void climber::lower(){
    Reach.Set(frc::DoubleSolenoid::kReverse);
}