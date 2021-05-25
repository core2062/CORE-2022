#pragma once

#include <frc/smartdashboard/SmartDashboard.h>
#include <ctre/Phoenix.h>
#include <CORERobotLib.h>
#include <networktables/NetworkTableInstance.h>
#include <COREControl/COREPID.h>
#include "Config.h"
#include <math.h>

using namespace CORE;
using namespace frc;

class TurretSubsystem : public CORESubsystem {
private:
    TalonSRX m_turret;
    double m_startupTurretPosition, m_motorPercent;
    nt::NetworkTableInstance ntinst;
    //Distance Coefficent A,B,C,D
    COREConstant<double> m_KP, m_KI, m_KD, m_KF, m_turretSpeed, m_DistCoefA, m_DistCoefB /*, m_DistCoefC, m_DistCoefD, m_DistCoffee*/;
    COREPID corePID;

public:
    TurretSubsystem();
    void robotInit() override;
    void teleopInit() override;
    void teleop() override;

    double turretPosition();
    double VisionMove(bool atLeftStop, bool atRightStop);
    double CalculateMotorFromVision(bool atLeftStop, bool atRightStop);
    double GetDistance();
    void InitTalons();
    void SetTurret(double turretPercent);
    double centerError;
    bool hasCenterX;
};
