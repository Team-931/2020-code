# include "Robot.h"

inline double limit (double in, double max) {
    if(std::abs (in) < max) return in;
    return std::copysign(max, in);
}

constexpr double maxRateChg = .25 * 32 /*ft/sec^2 : gravity*/ * .02 /*sec/cycle*/;
constexpr double rateConversion = -.1 / 14 /*ft/sec : max rate*/;

void Robot::DriveWEnc::Periodic() {
    if(!active) return;
    double currentRate = enc.GetRate();
    double currentPower = ctrlr.Get();
    ctrlr.Set (currentPower + limit((targetRate-currentRate) * rateConversion , maxRateChg));
}