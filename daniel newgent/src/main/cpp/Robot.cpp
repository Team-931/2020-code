/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include <frc/Joystick.h>
#include <frc/TimedRobot.h>
#include <frc/Timer.h>
#include <frc/drive/DifferentialDrive.h>
#include <frc/livewindow/LiveWindow.h>
#include <CTRE/phoenix.h>
#include <frc/SpeedControllerGroup.h>
#include "rev/ColorSensorV3.h"
#include <frc/smartdashboard/SmartDashboard.h>

class Robot : public frc::TimedRobot {
 public:
  Robot() {
    m_robotDrive.SetExpiration(0.1);
    m_timer.Start();
  }

  void AutonomousInit() override {
    m_timer.Reset();
    m_timer.Start();
  }

  void AutonomousPeriodic() override {
    // Drive for 6 seconds
    if (m_timer.Get() <= 6.0) {
      // Drive forwards half speed
      m_robotDrive.ArcadeDrive(-0.5, 0.0);
      // Turns 2 Seconds / half speed
    } else if(m_timer.Get() <= 8.0) {
      m_robotDrive.ArcadeDrive(0.0, -0.5);
    }
      // Drive forwards half speed 6 Seconds 
    else if(m_timer.Get() <= 14.0) {
      m_robotDrive.ArcadeDrive(-0.5, 0.0);
    }
      // Turn Full Power
    else if(m_timer.Get() <= 18.0) {
      m_robotDrive.ArcadeDrive(0.0, -1.0);
    }

     else {
      // Stop robot
      m_robotDrive.ArcadeDrive(0.0, 0.0);
    }
  }

  void TeleopInit() override {}

  void TeleopPeriodic() override {
    // Drive with arcade style (use right stick)
    if(ControlSwitch == Arcade) m_robotDrive.ArcadeDrive(m_stick.GetY(), m_stick.GetX());
    else m_robotDrive.TankDrive(m_stick.GetY(), m_stick.GetRawAxis(3));
    if(m_stick.GetRawButtonPressed(3))
    if(ControlSwitch == Tank) ControlSwitch = Arcade;
    else ControlSwitch = Tank;
    //Color Sensing
    auto detectedColor = ColorSensor.GetRawColor();
    uint32_t proximity = ColorSensor.GetProximity();
    frc::SmartDashboard::PutNumber("Red", detectedColor.red);
    frc::SmartDashboard::PutNumber("Green", detectedColor.green);
    frc::SmartDashboard::PutNumber("Blue", detectedColor.blue);
    frc::SmartDashboard::PutNumber("Proximity", proximity);
  }

  void TestPeriodic() override {}
                              
 private:
  // Robot drive system
  ::WPI_TalonSRX m_left{3};
  ::WPI_TalonSRX m_right{1};
  ::WPI_TalonSRX m_left2{4};
  ::WPI_TalonSRX m_right2{2};
  frc::SpeedControllerGroup right {m_right, m_right2};
  frc::SpeedControllerGroup left {m_left, m_left2};
  frc::DifferentialDrive m_robotDrive{left, right};
  // Sensors
  rev::ColorSensorV3 ColorSensor {frc::I2C::Port::kOnboard};


  frc::Joystick m_stick{0};
  frc::LiveWindow& m_lw = *frc::LiveWindow::GetInstance();
  frc::Timer m_timer;

  enum{Tank, Arcade} ControlSwitch {Tank};
};

#ifndef RUNNING_FRC_TESTS
int main() { return frc::StartRobot<Robot>(); }
#endif
