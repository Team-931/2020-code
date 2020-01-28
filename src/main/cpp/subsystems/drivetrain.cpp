#include "subsystems/drivetrain.h"
#include <frc/AnalogInput.h>

onewheeldrive::onewheeldrive (unsigned int wheel) : drivetrain (0), turn (1), turnmotor (new frc::AnalogInput (0)) {}

drivetrain::drivetrain () {}

void drivetrain::Periodic() {}
