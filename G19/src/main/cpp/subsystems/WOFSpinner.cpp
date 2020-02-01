#include "subsystems/WOFSpinner.h"

  using namespace constants::WOFSpinner;

WOFSpinner::WOFSpinner():Talon(Spinner){
  Talon.ConfigSelectedFeedbackSensor(FeedbackDevice::PulseWidthEncodedPosition);
  Talon.Config_kP(ValueP);}
  
void WOFSpinner::Periodic(){}

void WOFSpinner::rotate(double rotations){
  Talon.SetSelectedSensorPosition (0);
  rotations*=WOFDiamater/SpinnerDiameter*WheelRotation;
  Talon.Set (ControlMode::Position, rotations);

}
