
#include "subsystems/SwerveModule.h"
using namespace Constants::DriveSystem;

SwerveModule::SwerveModule(int ix) : frc2::PIDSubsystem(frc2::PIDController(PID[ix].D, PID[ix].I, PID[ix].D)),
                    driveCtrl(driveChannel[ix]),
                    turnCtrl (turnChannel[ix]),
                    encoder  (encChannel[ix]),
                    displ (displacement[ix]) {
  // Implementation of subsystem constructor goes here.
  turnCtrl.SetNeutralMode(Coast);
  GetController().EnableContinuousInput(-pi, pi);
  Enable();
}
/* 
void SwerveModule::Periodic() {
  // Implementation of subsystem periodic method goes here.
}
 */
void SwerveModule::SetXYTwist(double x, double y , double twist, Displacement center) {
  SetXY(x + twist * (displ.Left - center.Left), y - twist * (displ.Forward - center.Forward));
}

void SwerveModule::SetXY(double x, double y) {
  double angle = atan2(y, x), halfangle = remainder(angle, pi),
  spd = sqrt (x*x + y*y);
  if (angle != halfangle) spd = -spd;
  speed = spd;
  SetSetpoint (halfangle); 
}

double SwerveModule::GetMeasurement() {
    return remainder(2*encoder.GetVoltage()/encMax, 1) * pi;
}

void SwerveModule::UseOutput(double output, double setpoint) {
    driveCtrl.Set(speed * cos(encoder.GetVoltage() / encMax * pi - setpoint));
    if (speed < speedMin) turnCtrl.StopMotor();
    else turnCtrl.Set(output);
}