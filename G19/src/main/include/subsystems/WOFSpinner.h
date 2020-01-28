/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/encoder.h>
#include <rev/ColorSensorV3.h>
#include <frc2/command/SubsystemBase.h>
#include <frc/Controller/PIDController.h>
#include <CTRE/phoenix.h>
#include "Constants.h"

  using namespace constants::WOFSpinner;

class WOFSpinner : public frc2::SubsystemBase {
 public:
  WOFSpinner();

  /**
   * Will be called periodically whenever the CommandScheduler runs.
   */
  void Periodic() override;

 private:
  WPI_TalonSRX Talon{Spinner};

  frc::Encoder Encoder{Encoder1, Encoder2};
  rev::ColorSensorV3 ColorSensor{frc::I2C::Port::kOnboard};
  frc2::PIDController pid{1,0,0};
  units::radians theta;
  // Components (e.g. motor controllers and sensors) should generally be
  // declared private and exposed only through public methods.
};
