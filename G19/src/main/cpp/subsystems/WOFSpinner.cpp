#include "subsystems/WOFSpinner.h"

  using namespace constants::WOFSpinner;

WOFSpinner::WOFSpinner():Talon(Spinner){
  Talon.ConfigSelectedFeedbackSensor(FeedbackDevice::PulseWidthEncodedPosition);
  Talon.Config_kP(0, ValueP);}
  
void WOFSpinner::Periodic(){
  if (CSwitch)
    {/*what is the CSwitch going to read, the button*/}
}

void WOFSpinner::rotate(double rotations){
  Talon.SetSelectedSensorPosition (0);
  rotations*=WOFDiamater/SpinnerDiameter*WheelRotation;
  Talon.Set (ControlMode::Position, rotations);

}

void WOFSpinner::ColorSensor(bool CSensor){
  CSwitch=CSensor;
}

  
