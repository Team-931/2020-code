/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <rev/ColorSensorV3.h>
#include <frc2/command/SubsystemBase.h>
#include <CTRE/phoenix.h>
#include "Constants.h"



class WOFSpinner : public frc2::SubsystemBase {
 public:
 void rotate (double rotations);//this is for the parameter for the WOF color wheel
  WOFSpinner();

  /**
   * Will be called periodically whenever the CommandScheduler runs.
   */
  void Periodic() override;

  void CoSensor(bool CSensor);//This is so you can turn on and off the colorsensor so you are not using it all match

 private:
  WPI_TalonSRX Talon;

  bool CSwitch=false;

  rev::ColorSensorV3 ColorSensor{frc::I2C::Port::kOnboard};
  // Components (e.g. motor controllers and sensors) should generally be
  // declared private and exposed only through public methods.
};
