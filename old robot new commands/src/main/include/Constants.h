/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

# pragma once
# include <wpi/math>

using wpi::math::pi;
/**
 * The Constants header provides a convenient place for teams to hold robot-wide
 * numerical or boolean constants.  This should not be used for any other
 * purpose.
 *
 * It is generally a good idea to place constants into subsystem- or
 * command-specific namespaces within this header, which can then be used where
 * they are needed.
 */

namespace Constants {
    namespace RobotContainer {
        constexpr int driveStickChannel = 0;
    }
    namespace DriveSystem {
        constexpr double encMax = 5;
        constexpr double speedMin = .001;
        constexpr struct {double P; double I; double D;} PID[] = {{1,0,0}, {1,0,0}, {1,0,0}, {1,0,0}};
        constexpr int driveChannel[] = {2,3,0,1};
        constexpr int turnChannel[] = {12,40,31,41};
        constexpr int encChannel[] = {0,1,2,3};
        constexpr struct Displacement {double Forward; double Left;} displacement[] = 
            {{.35, .31}, {.35, -.31}, {-.35, -.31}, {-.35, .31}}, zero = {};
    }
}