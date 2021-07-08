#pragma once

#include <CORERobotLib.h>
#include <ctre/Phoenix.h>
#include <frc/smartdashboard/SmartDashboard.h>
#include <networktables/NetworkTableInstance.h>
#include "Config.h"

class CameraSubsystem : public CORESubsystem {
public:
    CameraSubsystem();
    void robotInit() override;
    void teleopInit() override;
    void teleop() override;
private: 
    int m_cameraId = 1;
    nt::NetworkTableEntry cameraSelection;
};

