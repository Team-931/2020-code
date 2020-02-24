/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

struct Coordinate {double rightward; double forward;};//measure these in inches.
namespace constants {
    namespace Cowl {
    constexpr int LiftID=11;
    constexpr int CounterID=0;
    //Place Holders for the CounterID
    constexpr int CountMin=0;
    constexpr int CountMax=100;
    }
    namespace RobotContainer {
        constexpr int JoystickDriveID=0, JoystickOperateID=1;
        constexpr const char * ColorNames[] = {"None yet", "Red", "Green", "Blue", "Yellow"};
    }
    namespace climber {constexpr int motorid=21;
    constexpr int climbmoverid=31;
    constexpr int ReachUp=7;
    constexpr int ReachDown =0;
    }
    namespace drivetrain {
        // front left, front right, back left, back right 
        constexpr int TurnMotor[]={6,5,7,8},
        DriveMotor[]={9,2,4,1};
        constexpr Coordinate WheelPositions[]={
            {-11.5, 11.875},
            {11.5, 11.875},
            {-11.5, -11.875},
            {11.5, -11.875},
        };
    }
    namespace shooter {constexpr int motorid=20;
    constexpr int intakeid=10;
    constexpr int hopperbeltid=3;
    constexpr int Gateid=12;
    constexpr int AngleForward=5;
    constexpr int AngleBackward=2;
    constexpr int SolenoidForward=6;
    constexpr int SolenoidBackward=1;
            // These are for the PID Control of the shooter motor speed
    constexpr double kP=0.0006, kI=.0000001, kD=0, kIz=0,
     kFF=0.000015, kMaxOutput=1, kMinOutput=-1;}
    namespace WOFSpinner {
        constexpr int Spinner{10};
        constexpr int WheelRotation{40960};
            // Reports WheelOfFortune at 40960 ticks/rotation
        constexpr int WOFDiamater{2*12+8};
            // Wheel Of Fortune Diameter is 2' 8"
        constexpr int SpinnerDiameter{4};
            // Wheel Spinner is 4"
        constexpr double ValueP{.25};
            // Fine tune later
        constexpr unsigned SensorInRange = 512;
            // Maximum ColorSensor Range
    }
}
/**
 * The Constants header provides a convenient place for teams to hold robot-wide
 * numerical or boolean constants.  This should not be used for any other
 * purpose.
 *
 * It is generally a good idea to place constants into subsystem- or
 * command-specific namespaces within this header, which can then be used where
 * they are needed.
 */
