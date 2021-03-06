/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

# include "Robot.h"
# include "Constants.h"

# include <iostream>

# include <frc/smartdashboard/SmartDashboard.h>


void Robot::RobotInit() {
  m_chooser.SetDefaultOption(kAutoNameDefault, kAutoNameDefault);
  m_chooser.AddOption(kAutoNameCustom, kAutoNameCustom);
  frc::SmartDashboard::PutData("Auto Modes", &m_chooser);
}

/**
 * This function is called every robot packet, no matter the mode. Use
 * this for items like diagnostics that you want ran during disabled,
 * autonomous, teleoperated and test.
 *
 * <p> This runs after the mode specific periodic functions, but before
 * LiveWindow and SmartDashboard integrated updating.
 */
//# include <string>

void Robot::RobotPeriodic() {
  auto color = colorEye.GetColor();
  if (std::optional<frc::Color> match; colorEye.GetProximity() >= MinProx &&
    (match = colorMatcher.MatchColor(color)).has_value()) 
      {auto colorM = match.value();
      int matchIx = -1;
      for(unsigned ix = 0; ix < savedColors.size(); ++ix) 
      if (savedColors[ix] == colorM){
          matchIx = ix;
          break;
      }
      frc::SmartDashboard::PutNumber("Match number", matchIx);
      frc::SmartDashboard::PutString("Found match", 
        std::string ("RGB ") + 
        std::to_string (colorM.red) + std::to_string (colorM.green) + std::to_string (colorM.blue));
      }
  else frc::SmartDashboard::PutString("Found match", "None");
  frc::SmartDashboard::PutNumber("Red", color.red);
  frc::SmartDashboard::PutNumber("Green", color.green);
  frc::SmartDashboard::PutNumber("Blue", color.blue);
  int prox = colorEye.GetProximity();
  frc::SmartDashboard::PutNumber("Proximity", prox);
  if(driveStick.GetBumperPressed(frc::XboxController::kLeftHand)) {
    colorMatcher.AddColorMatch(color);
    savedColors.push_back(color);
    savedReds.push_back(color.red);
    savedGreens.push_back(color.green);
    savedBlues.push_back(color.blue);
    frc::SmartDashboard::PutNumberArray("Saved reds", savedReds);
    frc::SmartDashboard::PutNumberArray("Saved greens", savedGreens);
    frc::SmartDashboard::PutNumberArray("Saved blue", savedBlues);
    frc::SmartDashboard::PutNumber("Saved ct", savedColors.size());
  }
/*   if(driveStick.GetRawButton(5)) frc::SmartDashboard::PutBoolean("Save btn", true);
    else frc::SmartDashboard::PutBoolean("Save btn", false);
 */}

/**
 * This autonomous (along with the chooser code above) shows how to select
 * between different autonomous modes using the dashboard. The sendable chooser
 * code works with the Java SmartDashboard. If you prefer the LabVIEW Dashboard,
 * remove all of the chooser code and uncomment the GetString line to get the
 * auto name from the text box below the Gyro.
 *
 * You can add additional auto modes by adding additional comparisons to the
 * if-else structure below with additional strings. If using the SendableChooser
 * make sure to add them to the chooser code above as well.
 */
void Robot::AutonomousInit() {
  m_autoSelected = m_chooser.GetSelected();
  // m_autoSelected = SmartDashboard::GetString("Auto Selector",
  //     kAutoNameDefault);
  std::cout << "Auto selected: " << m_autoSelected << std::endl;

  if (m_autoSelected == kAutoNameCustom) {
    // Custom Auto goes here
  } else {
    // Default Auto goes here
  }
}

void Robot::AutonomousPeriodic() {
  if (m_autoSelected == kAutoNameCustom) {
    // Custom Auto goes here
  } else {
    // Default Auto goes here
    robotDrive.StopMotor();
  }
}

void Robot::TeleopInit() {}

void Robot::TeleopPeriodic() {
  robotDrive.TankDrive(
    driveStick.GetY(frc::XboxController::kLeftHand), 
    driveStick.GetY(frc::XboxController::kRightHand));
}

void Robot::TestPeriodic() {}

#ifndef RUNNING_FRC_TESTS
int main() { return frc::StartRobot<Robot>(); }
#endif
