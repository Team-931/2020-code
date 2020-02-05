#include "subsystems/WOFSpinner.h"

  using namespace constants::WOFSpinner;

extern const frc::Color ColorList[];

WOFSpinner::WOFSpinner():Talon(Spinner){
  for (int i = 0; i < 4; ++i) Matcher.AddColorMatch (ColorList[i]);
  Talon.ConfigSelectedFeedbackSensor(FeedbackDevice::PulseWidthEncodedPosition);
  Talon.ConfigMotionCruiseVelocity(4096);
  Talon.ConfigMotionAcceleration(4096);
  Talon.Config_kP(0, ValueP);}
  
void WOFSpinner::Periodic(){
  }

void WOFSpinner::rotate(double rotations){
  Talon.SetSelectedSensorPosition (0);
  rotations*=WOFDiamater/SpinnerDiameter*WheelRotation;
  Talon.Set (ControlMode::Position, rotations);

}

void WOFSpinner::CoSensor(bool CSensor){
  CSwitch=CSensor;
}

uint32_t WOFSpinner::FindColor() {
if (CSwitch && ColorSensor.GetProximity() >= SensorInRange)
    {/*what is the CSwitch going to read, the button*/
      if(auto match = Matcher.MatchColor(ColorSensor.GetColor()); match.has_value()) 
      for(int i = 0; i < 4; ++i) if (match == ColorList[i]) return i + 1;
    }
return 0;
}  
