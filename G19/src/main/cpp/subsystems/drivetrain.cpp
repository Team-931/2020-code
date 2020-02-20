#include "subsystems/drivetrain.h"

# include <wpi/math>
using wpi::math::pi;

using namespace constants::drivetrain;

onewheeldrive::onewheeldrive (unsigned int wheel) : drivetrain (DriveMotor[wheel]), 
turn (TurnMotor[wheel]), Location(WheelPositions[wheel]){
    turn.ConfigFactoryDefault();
    turn.SetNeutralMode(Brake);//talk to the driver about what they want this to be [coast/brake]
    drivetrain.SetNeutralMode(Brake);
    turn.ConfigSelectedFeedbackSensor(FeedbackDevice::Analog);
    turn.SetSensorPhase(true);
    turn.Config_kP(0,8);
    turn.ConfigFeedbackNotContinuous(false);
    }

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
) {
    rightward += Location.forward*rotation, forward += -Location.rightward*rotation;
    int n;//for quotient bits
    double angle = atan2(forward, rightward), halfangle = remquo(angle, pi, &n),
           spd = sqrt(rightward * rightward + forward * forward);
    if (n & 1)
        spd = -spd;
    drivetrain. Set (spd);
    turn.Set(ControlMode::MotionMagic, halfangle);
} 
