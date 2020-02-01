#include "subsystems/drivetrain.h"

using namespace constants::drivetrain;

onewheeldrive::onewheeldrive (unsigned int wheel) : drivetrain (DriveMotor[wheel]), 
turn (TurnMotor[wheel]){
    turn.ConfigSelectedFeedbackSensor(FeedbackDevice::Analog);}


drivetrain::drivetrain () {}

void drivetrain::Periodic() {}

