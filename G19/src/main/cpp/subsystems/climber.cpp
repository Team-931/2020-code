#include "Subsystems/climber.h"

using namespace constants::climber;


climber::climber():ClimbMotor(motorid, rev::CANSparkMax::MotorType::kBrushless),
Reach(ReachUp, ReachDown)
{}
void climber::Periodic(){}
