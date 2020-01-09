/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

# pragma once

# include <frc/TimedRobot.h>
# include <frc/SpeedControllerGroup.h>
# include <frc/drive/DifferentialDrive.h>
# include <ctre/Phoenix.h>

# include <frc/Joystick.h>
# include <frc/Encoder.h>

class Robot : public frc::TimedRobot {
  WPI_TalonSRX left1{3}, left2{4},
              right1{1}, right2{2};
  frc::SpeedControllerGroup left{left1, left2}, right{right1, right2};
  //frc::DifferentialDrive drive{left, right};

  frc::Joystick driveStick{0};
  frc::Timer timer;

  frc::Encoder leftEncoder{0, 1, false}, rightEncoder{2, 3, true};

  /**
   * A feedback controller to adjust the SpeedController to yield a target Encoder Rate.
  */
  class DriveWEnc {
    bool active {false};
    frc::SpeedController & ctrlr;
    frc::Encoder & enc;

    double targetRate {0};
  public:
    DriveWEnc(frc::SpeedController & ctl, frc::Encoder & en) :
    ctrlr (ctl), enc (en) {}

    /**
     * Called every cycle to nudge the Encoder's Rate to its target
    */
    void Periodic();

    /**
     * Enables or disables the feedback.
    */
    void SetActive(bool a = true) {
      active = a;
    }

    /**
     * Sets a target Rate for the Encoder.
    */
    void SetRate(double rate){
      targetRate = rate;
    }
  } leftFollow{left, leftEncoder},
    rightFollow{right, rightEncoder};
  /**
   * estimates the angle rotated by comparing the Encoders
   * @return degrees of clockwise rotation
  */
  double AngleEnc() const;
 public:
  void RobotInit() override;

  void RobotPeriodic() override;

  void AutonomousInit() override;
  void AutonomousPeriodic() override;

  void TeleopInit() override;
  void TeleopPeriodic() override;

  void TestInit() override;
  void TestPeriodic() override;
};
