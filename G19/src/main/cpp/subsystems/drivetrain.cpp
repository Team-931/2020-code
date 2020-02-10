#include "subsystems/drivetrain.h"

using namespace constants::drivetrain;

onewheeldrive::onewheeldrive (unsigned int wheel) : drivetrain (DriveMotor[wheel]), 
turn (TurnMotor[wheel]), Location(WheelPositions[wheel]){
    turn.SetNeutralMode(Brake);//talk to the driver about what they want this to be [coast/brake]
    drivetrain.SetNeutralMode(Brake);
    turn.ConfigSelectedFeedbackSensor(FeedbackDevice::Analog);}

drivetrain::drivetrain () {}

void drivetrain::Periodic() {}

