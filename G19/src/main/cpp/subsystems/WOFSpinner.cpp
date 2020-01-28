#include "subsystems/WOFSpinner.h"

  using namespace constants::WOFSpinner;

WOFSpinner::WOFSpinner():Talon(Spinner),Encoder(Encoder1, Encoder2){}
void WOFSpinner::Periodic(){}

