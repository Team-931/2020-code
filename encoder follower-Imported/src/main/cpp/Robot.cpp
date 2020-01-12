/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

# include "Robot.h"

//# include <iostream>
# include <frc/smartdashboard/SmartDashboard.h>

constexpr double pi = 3.141592;

void Robot::RobotInit() {
    left1.SetInverted(false);
    left2.SetInverted(false);
    right1.SetInverted(true);
    right2.SetInverted(true);
    leftEncoder.SetDistancePerPulse(pi *.5/*feet*//2048/*ticks*/);
    rightEncoder.SetDistancePerPulse(pi *.5/*feet*//2048/*ticks*/);
}

void Robot::RobotPeriodic() {
    frc::SmartDashboard::PutNumber ("Left rate: " , leftEncoder.GetRate() );
    frc::SmartDashboard::PutNumber ("Right rate: ", rightEncoder.GetRate() );
}

unsigned stage;
constexpr double wheelbase = 21.5/12 /*feet */;
inline double Robot::AngleEnc() const {
    return (leftEncoder.GetDistance() - rightEncoder.GetDistance()) / wheelbase / pi * 180/*degrees*/;
}

void Robot::AutonomousInit() {
    leftEncoder.Reset(); rightEncoder.Reset();
    leftFollow.SetRate(0); leftFollow.SetActive();
    rightFollow.SetRate(0); rightFollow.SetActive();
    timer.Reset(); timer.Start();
    stage = 0;
}

void Robot::AutonomousPeriodic() {
    leftFollow.Periodic(); rightFollow.Periodic();

    frc::SmartDashboard::PutNumber("stage", stage);
    switch (stage)
    {
    case 0:
        if(timer.Get() >= 1) {
            ++stage;
            leftFollow.SetRate(1); rightFollow.SetRate(1);
        }
        break;
    case 1:
        if(leftEncoder.GetDistance() >= 10) {
            ++stage;
            leftFollow.SetRate(0);
        }
        break;
    case 2:
        if(AngleEnc() < -90) {
            ++stage;
            rightFollow.SetRate(0);
        }
        break;
    default:
        /*to do: safety code*/
        break;
    }
}

void Robot::TeleopInit() {
    leftFollow.SetActive(false); rightFollow.SetActive(false);
}

void Robot::TeleopPeriodic() {
    left.Set(driveStick.GetY());
    right.Set(driveStick.GetRawAxis(3));
}

void Robot::TestInit() {}
void Robot::TestPeriodic() {}

#ifndef RUNNING_FRC_TESTS
int main() { return frc::StartRobot<Robot>(); }
#endif
