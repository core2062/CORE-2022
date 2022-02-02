#pragma once

#include <ctre/Phoenix.h>
#include <CORERobotLib.h>
#include "Config.h"

using namespace CORE;
using namespace frc;


class LauncherSubsystem : public CORESubsystem {
    public:
	    LauncherSubsystem();
        void robotInit() override;
        void teleopInit() override;
        void teleop() override;

        COREConstant<double> forwardSpeed, backwardSpeed;

    private:
        TalonSRX m_rightFeed, m_leftFeed;
        TalonFX m_rightLauncher, m_leftLauncher;

};
