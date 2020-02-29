/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "RobotContainer.h"
# include <frc2/command/button/JoystickButton.h>
# include <frc/DriverStation.h>
# include <frc/smartdashboard/SmartDashboard.h>
#include <frc2/command/RunCommand.h>

using namespace constants::RobotContainer;
const int BothUp{0};
const int BothDown{1};
const int HDownCUp{2};

RobotContainer::RobotContainer() : m_autonomousCommand(&Drive), JoystickDrive(JoystickDriveID), JoystickOperate(JoystickOperateID) {
  // Initialize all of your commands and subsystems here
    frc::SmartDashboard::SetDefaultNumber("Shooter speed", 3500);// for use on shoot button

    Wheel.SetDefaultCommand(frc2::RunCommand( //This all is temporary for testing
      [this]{frc::SmartDashboard::PutString("ColorFound", ColorNames[Wheel.FindColor()]);
            CheckScoreColor();
/*       if(JoystickDrive.GetRawButtonPressed(2))
      Wheel.CoSensor(true);
      else 
      Wheel.CoSensor(false); */}, &Wheel
    ));
    Gun.SetDefaultCommand(frc2::RunCommand(
      [this] {
        frc::SmartDashboard::PutNumber("ShootRPM", Gun.ReturnRPM());//Look and see if needed for the SmartDashboard
        /* Gun.ShooterRPM(-3500/4*(int)(4*JoystickOperate.GetRawAxis(5))); */
        frc::SmartDashboard::PutNumber("intakeCurrent", Gun.intakecurrent());},
      &Gun
    ));
    Drive.SetDefaultCommand(frc2::RunCommand([this] {
      double NavxYaw = Drive.GetNavX().GetYaw();
      frc::SmartDashboard::PutNumber("Yaw", NavxYaw);
      double ready=-JoystickDrive.GetY(), readx=JoystickDrive.GetX(), readz=JoystickDrive.GetZ();
      double magnitudevector=sqrt(ready*ready+readx*readx);
      ready*=magnitudevector, readx*=magnitudevector, readz*=abs(readz)/constants::drivetrain::WheelRadius;//divid by 16 will change to a name constant
      if(Drive.IsEnabled()) {
        Drive.Move(readx, ready);
        if(int pov = JoystickDrive.GetPOV(); pov >=0) Drive.SetAngleToField(pov);
        
        else if (abs(readz)>constants::drivetrain::Minispeed)
          Drive.SetAngleToField(Drive.GetController().GetSetpoint()+readz*constants::drivetrain::Maxspeed);
        }
      else Drive.Move(readz, ready, readx);
      }, &Drive));
      // Configure the button bindings
  ConfigureButtonBindings();
}

void RobotContainer::ConfigureButtonBindings() {
  // Configure your button bindings here
  frc2::JoystickButton(&JoystickOperate, 5).WhenPressed([this]{
    Hopperclimber(BothUp);});
  frc2::JoystickButton(&JoystickOperate, 6).WhenPressed([this]{//Check to make sure and see if they need both down
    Hopperclimber(HDownCUp);});
  frc2::JoystickButton(&JoystickOperate, 15).WhenPressed([this]{
    Hopperclimber(BothDown);}); //change this button later on
  frc2::JoystickButton(&JoystickDrive, 2).WhenPressed([this]{
    Wheel.CoSensor(true);}).WhenReleased([this]{Wheel.CoSensor(false);});
  frc2::JoystickButton(&JoystickDrive, 4).WhenPressed([this]{
    frc::SmartDashboard::PutString("Rotator", RotateForColor() ? "Working" : "Failed");});
  frc2::JoystickButton(&JoystickDrive, 5).WhenPressed([this]{
    Drive.Enable();});
  frc2::JoystickButton(&JoystickDrive, 6).WhenPressed([this]{
    Drive.Disable();});
  frc2::JoystickButton(&JoystickOperate, 3).WhileHeld([this]{
    double GateOpen = JoystickOperate.GetX();
    if(GateOpen <= -0.1) Gun.OpenGate();
    else Gun.CloseGate();});
//test code
    using constants::Cowl::CountMax, constants::Cowl::CountMin;
  frc2::JoystickButton(&JoystickDrive, 9).WhenReleased(
      [this]{frc::SmartDashboard::PutNumber("Cowl Counter", GunRoof.GetCount());
      int where = (CountMin + CountMax - (CountMax - CountMin) * JoystickDrive.GetY())/2;
      frc::SmartDashboard::PutNumber("Cowl Goal", where);
      GunRoof.LiftCowl(where);}
    );
  frc2::JoystickButton(&JoystickOperate, 11).WhenReleased(
      [this]{frc::SmartDashboard::PutNumber("Cowl Counter", GunRoof.GetCount());
      int what = -10 * JoystickOperate.GetY();
      //frc::SmartDashboard::PutNumber("Cowl Goal", where);
      GunRoof.LiftCowlBy(what);}
    );
  frc2::JoystickButton(&JoystickOperate, 1).WhenPressed([this]{
    double spd = frc::SmartDashboard::GetNumber("Shooter speed", 3500);
    Gun.ShooterRPM(spd);
    });
  frc2::JoystickButton(&JoystickOperate, 4).WhenPressed([this]{
    Gun.StopShooter();});
  frc2::JoystickButton(&JoystickDrive, 8).WhenPressed([this]{
    Drive.GetNavX().ZeroYaw();});
  frc2::JoystickButton(&JoystickOperate, 10).WhileHeld([this]{
    double Transfer = JoystickOperate.GetRawAxis(3);
    if(Transfer <= -0.1) Gun.TransferForwards();
    else if(Transfer >= 0.1) Gun.TransferBackwards();
    else Gun.TransferOff();});
  frc2::JoystickButton(&JoystickOperate, 9).WhileHeld([this]{
double Pickup = JoystickOperate.GetY();
    if(Pickup <= -0.1) Gun.PickUpForwards();
    else if(Pickup >= 0.1) Gun.PickUpBackwards();
    else Gun.PickUpOff();});
}

frc2::Command* RobotContainer::GetAutonomousCommand() {
  // An example command will be run in autonomous
  return &m_autonomousCommand;
}

uint32_t RobotContainer::SpecificColor(){
  auto msg = frc::DriverStation::GetInstance().GetGameSpecificMessage();
  if (msg.length()) for (uint32_t i = 1; i <= 4; ++i) if(msg[0] == ColorNames[i][0]) 
    return i;
  return 0;//0 means no color yet
  //on WPI look for Game Data Details for more iformation about getting color
}

void RobotContainer::CheckScoreColor() {
  uint32_t color = SpecificColor();
  if (color == Color2Score) return;
  Color2Score = color;
  if (color > 2) Color2Find = color - 2;
  else if (color) Color2Find = color + 2;
  else Color2Find = 0;
  frc::SmartDashboard::PutString("Color to score", ColorNames[Color2Score]);
  frc::SmartDashboard::PutString("Color to find", ColorNames[Color2Find]);
}

void RobotContainer::RotateForCount() {
  Wheel.rotate(3.5);
}

bool RobotContainer::RotateForColor() {
  if (Color2Find == 0) return false;
  uint32_t found = Wheel.FindColor();
  if (found == 0) return false;
  Wheel.rotate(remainder(Color2Find - found, 4) / 8);
  return true;
}

void RobotContainer::Hopperclimber(int position){
if (position==0){
  Climb.lower();
  Gun.SolenoidDown();
}
else
if (position==1){
  Climb.raise();
  Gun.SolenoidUp();
}
else 
if (position==2){
  Climb.raise();
  Gun.SolenoidDown();
}

}