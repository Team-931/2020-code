/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once


namespace constants {
    namespace Cowl {
    constexpr int LiftID=2;
    constexpr int CounterID=3;
    //Place Holders for the CounterID
    constexpr int CountMin=0;
    constexpr int CountMax=1000;
    }
    namespace RobotContainer {
        constexpr int JoystickDriveID=0, JoystickOperateID=1;
        constexpr const char * ColorNames[] = {"None yet", "Red", "Green", "Blue", "Yellow"};
    }
    namespace climber {constexpr int motorid=1;}
    namespace drivetrain {
        constexpr int TurnMotor[]={1,3,5,7},
        DriveMotor[]={2,4,6,8};
    }
    namespace shooter {constexpr int motorid=0;
    constexpr int intakeid=4;
    constexpr int hopperbeltid=5; }
    namespace WOFSpinner {
        constexpr int Spinner{31};
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
