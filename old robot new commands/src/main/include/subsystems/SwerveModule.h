
#pragma once

# include <frc2/command/SubsystemBase.h>
# include <frc2/command/PIDSubsystem.h>
# include <ctre/Phoenix.h>
# include <frc/Talon.h>
# include <frc/AnalogInput.h>
# include "Constants.h"
using Constants::DriveSystem::Displacement, Constants::DriveSystem::zero;

class SwerveModule : public frc2::PIDSubsystem {
 public:
  SwerveModule(int ix);

  /**
   * Will be called periodically whenever the CommandScheduler runs.
   */
  //void Periodic() override;

/**
 * Instructs to move as indicated.
 * @param twist is clockwise angular
 * @param center is the point on the frame whose motion is as in SetXY(forward, left)
 */
  void SetXYTwist(double forward, double left, double twist, Displacement center = zero);
  void SetXY(double forward, double left);

  /**
   * If this->speed is greater than maxSpeed
   * @param maxSpeed input/output maximum
   * increase maxSpeed
   */ 
  void CheckMaxSpeed(double & maxSpeed) {
      if (speed > maxSpeed) maxSpeed = speed;
  }

  void ScaleSpeed(double divisor) {
      speed /= divisor;
  }

 protected:
  double GetMeasurement() override;
  void UseOutput(double output, double setpoint) override;
 
 private:
  // Components (e.g. motor controllers and sensors) should generally be
  // declared private and exposed only through public methods.
  /**
   * Motor controllers
  */
  frc::Talon driveCtrl;
  WPI_TalonSRX turnCtrl;
  frc::AnalogInput encoder;
  Displacement displ;
  double speed {0};
};
