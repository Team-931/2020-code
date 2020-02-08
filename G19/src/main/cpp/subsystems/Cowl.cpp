
#include "subsystems/Cowl.h"

using namespace constants::Cowl;

Cowl::Cowl():CowlLift(LiftID), 
CowlCounter(CounterID)
{

}

    //NOTE: Find out the ticks for the Cowl from Minimum to Maximum

void Cowl::LiftCowl(int DesiredLocation) {
    CurrentPosition+=CowlCounter.Get()*MotorVelocity;
    CowlCounter.Reset();
    if(DesiredLocation > CountMax) DesiredLocation = CountMax;
    if(DesiredLocation < CountMin) DesiredLocation = CountMin;
    DesiredTicks=DesiredLocation-CurrentPosition;
    if(DesiredTicks > 0){MotorVelocity = 1;}
    else if(DesiredTicks == 0){MotorVelocity = 0;}
    else{MotorVelocity = -1; DesiredTicks = -DesiredTicks;}
}

void Cowl::Periodic() {}
