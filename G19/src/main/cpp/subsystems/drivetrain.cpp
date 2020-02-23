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
    turn.ConfigMotionAcceleration(512);
    turn.ConfigMotionCruiseVelocity(512);
    turn.ConfigFeedbackNotContinuous(false);
    }
    double bigger(double x,double y){
        if(x>y)
            return x;
            return y;}
    void drivetrain::Move(
        double rotation,
        double forward,
        double rightward
        ) {double divisor=1;
        divisor=bigger (fleft.Move (rotation, forward, rightward), divisor);
        divisor=bigger(fright.Move (rotation, forward, rightward), divisor);
        divisor=bigger (bleft.Move (rotation, forward, rightward), divisor);
        divisor=bigger(bright.Move (rotation, forward, rightward), divisor);
        if (divisor>1){
            fleft.dividspeed(divisor);
            fright.dividspeed(divisor);
            bleft.dividspeed(divisor);
            bright.dividspeed(divisor);
        }
        fleft.setspd();
        fright.setspd();
        bleft.setspd();
        bright.setspd();
        }

drivetrain::drivetrain () :frc2::PIDSubsystem(frc2::PIDController(1,0,0))/*these are for PID*/{ 
    GetController().EnableContinuousInput(-pi,pi);
    Enable();
    }

//void drivetrain::Periodic() {}
double drivetrain::GetMeasurement() {
    return navx.GetYaw()*pi/180;
}


void drivetrain::UseOutput(double output, double setpoint) {
    double rangle=GetMeasurement();
    double sangle=sin(rangle);
    double cangle=cos(rangle);
    Move(output, sangle*xaxis+cangle*yaxis, cangle*yaxis-sangle*xaxis);
}

void drivetrain::Move(double rightward, double forward) {
    xaxis=rightward;
    yaxis=forward;
}

void drivetrain::SetAngleToField(double rotation) {
    SetSetpoint (rotation);
}

double onewheeldrive::Move(
    double rotation,
    double forward,
    double rightward
) {
    rightward += Location.forward*rotation, forward += -Location.rightward*rotation;
    int n;//for quotient bits
    double current = turn.GetSelectedSensorPosition(), //our wheel alignment in units of 1024/rotation
           angle = 512 * atan2(rightward, forward) / pi - current, //change in alignment
           halfangle = remquo(angle, 512, &n) + current, // new alignment is changed be as close as poss. to old
           spd = sqrt(rightward * rightward + forward * forward); // magnitude of drive
    if (n & 1)
        speed=-spd; // backwards if wheel is reversed
    else
        speed=spd;
    //drivetrain. Set (spd);
    turn.Set(ControlMode::MotionMagic, halfangle);
    return spd;
} 
