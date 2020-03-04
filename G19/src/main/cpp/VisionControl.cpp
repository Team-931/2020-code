# include "VisionControl.h"
# include <networktables/NetworkTableInstance.h>

void VisionControl::DriverCam() {
    auto tab = nt::NetworkTableInstance::GetDefault().GetTable("limelight");
    tab->PutNumber("ledMode", 1);
    tab->PutNumber("camMode", 1);
}

void VisionControl::TargetFind() {
    auto tab = nt::NetworkTableInstance::GetDefault().GetTable("limelight");
    tab->PutNumber("ledMode", 0);   
    tab->PutNumber("camMode", 0);
}

VisionControl::Target VisionControl::GetTarget() {
     auto tab = nt::NetworkTableInstance::GetDefault().GetTable("limelight");
    
    return Target{tab->GetNumber("tv",0), tab->GetNumber("tx", 0), tab->GetNumber("ty", 0)};
}