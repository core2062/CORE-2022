#pragma once

#include <ctre/Phoenix.h>
#include <CORERobotLib.h>
#include "Config.h"

#include <frc/DoubleSolenoid.h>

using namespace CORE;
using namespace frc;


class LauncherSubsystem : public CORESubsystem {
    public:
	    LauncherSubsystem();
        void robotInit() override;
        void teleopInit() override;
        void teleop() override;
        void setLauncherSpeed(double launcherSpeed);
        void ExtendLauncher(bool launcherRetracted);
        COREConstant<double> forwardSpeed, backwardSpeed;

    private:
        TalonSRX m_rightFeed, m_leftFeed;
        TalonFX m_rightLauncher, m_leftLauncher;
        DoubleSolenoid m_launcherSolenoid;
        bool m_launcherRetracted;
};
