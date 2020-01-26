# include "subsystems/shooter.h"

constexpr auto Brake = rev::CANSparkMax::IdleMode::kBrake;
Shooter::Shooter() {
    left.SetInverted(true);
    left.SetIdleMode(Brake);
    right.SetInverted(false);
    // Alternatively: 
    //right.Follow(left, true);
    right.SetIdleMode(Brake);
}

void Shooter::Periodic() {

}