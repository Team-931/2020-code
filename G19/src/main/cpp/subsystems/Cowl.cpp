
#include "subsystems/Cowl.h"

using namespace constants::Cowl;

Cowl::Cowl():CowlLift(LiftID), 
CowlCounter(CounterID), SlowCowl(SlowCowlID, SlRange, SlOffset)
{
    CurrentPosition = CountMin;
    MotorVelocity = 0;
    DesiredTicks = 0;
}

    //NOTE: Find out the ticks for the Cowl from Minimum to Maximum

void Cowl::LiftCowl(double DesiredLocation) {
    Target = DesiredLocation;
/*     CurrentPosition+=CowlCounter.Get()*MotorVelocity;
    CowlCounter.Reset();
    if(DesiredLocation > CountMax) DesiredLocation = CountMax;
    if(DesiredLocation < CountMin) DesiredLocation = CountMin;
    DesiredTicks=DesiredLocation-CurrentPosition;
    if(DesiredTicks > 0){MotorVelocity = 1;}
    else if(DesiredTicks == 0){MotorVelocity = 0;}
    else{MotorVelocity = -1; DesiredTicks = -DesiredTicks;}
 */}

void Cowl::LiftCowlBy(double Change) {
    Target += Change;
/*     CurrentPosition+=CowlCounter.Get()*MotorVelocity;
    CowlCounter.Reset();
    DesiredTicks=Change;
    if(DesiredTicks > 0){MotorVelocity = 1;}
    else if(DesiredTicks == 0){MotorVelocity = 0;}
    else{MotorVelocity = -1; DesiredTicks = -DesiredTicks;}
 */}

void Cowl::Periodic() {
    CowlLift.Set(.5*(Target - Potentiometer()));
/*     if(DesiredTicks > CowlCounter.Get()) CowlLift.Set(MotorVelocity*.5);
    else CowlLift.StopMotor();
 */}
