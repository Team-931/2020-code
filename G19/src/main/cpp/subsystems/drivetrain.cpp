#include "subsystems/drivetrain.h"
#include <frc/AnalogInput.h>

using namespace constants::drivetrain;

onewheeldrive::onewheeldrive (unsigned int wheel) : drivetrain (DriveMotor[wheel]), 
turn (TurnMotor[wheel]), 
turnmotor (new frc::AnalogInput (Encoder[wheel])) {}


drivetrain::drivetrain () {}

void drivetrain::Periodic() {}

