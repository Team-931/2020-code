#include "subsystems/drivetrain.h"

using namespace constants::drivetrain;

onewheeldrive::onewheeldrive (unsigned int wheel) : drivetrain (DriveMotor[wheel]), 
turn (TurnMotor[wheel]), Location(WheelPositions[wheel]){
    turn.SetNeutralMode(Brake);//talk to the driver about what they want this to be [coast/brake]
    drivetrain.SetNeutralMode(Brake);
    turn.ConfigSelectedFeedbackSensor(FeedbackDevice::Analog);}

    void drivetrain::Move(
        double rotation,
        double forward,
        double rightward
        ) {fleft.Move (rotation, forward, rightward);
        fright.Move (rotation, forward, rightward);
        bleft.Move (rotation, forward, rightward);
        bright.Move (rotation, forward, rightward);
        }

drivetrain::drivetrain () {}

void drivetrain::Periodic() {}

void onewheeldrive::Move(
    double rotation,
    double forward,
    double rightward
) {} /* {Location.forward*rotation,-Location.rightward*rotation;} */ 
