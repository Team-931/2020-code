#include "subsystems/WOFSpinner.h"

  using namespace constants::WOFSpinner;

WOFSpinner::WOFSpinner():Talon(Spinner){
  Talon.ConfigSelectedFeedbackSensor(FeedbackDevice::PulseWidthEncodedPosition);}
  
void WOFSpinner::Periodic(){}

