#include "CameraSubsystem.h"
 
using namespace CORE;

CameraSubsystem::CameraSubsystem(){


}

void CameraSubsystem::robotInit(){
    operatorJoystick->RegisterButton(CORE::COREJoystick::JoystickButton::X_BUTTON);
  cameraSelection = nt::NetworkTableInstance::GetDefault().GetTable("")->GetEntry("CameraServer");
    cameraSelection.SetString("rPi Camera 0");
}


void CameraSubsystem::teleopInit() {
        std::cout << cameraSelection.GetString("NULL") << endl;
}

void CameraSubsystem::teleop(){
    bool xButtonPressed = operatorJoystick->GetRisingEdge(CORE::COREJoystick::JoystickButton::X_BUTTON);
    // std::cout << m_cameraId << endl;
    // std::cout << cameraSelection.GetString("nonefound") << endl;
    if(m_cameraId == 1 && xButtonPressed){
        cameraSelection.SetString("rPi Camera 0");
        m_cameraId = 2;
    }else if(m_cameraId == 2 && xButtonPressed){
        cameraSelection.SetString("rPi Camera 1");
        m_cameraId = 1;
    }

}