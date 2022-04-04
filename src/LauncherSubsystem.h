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
        void toggleLauncher();
        void setLauncherSpeed(double launcherSpeed);
        void setFeedSpeed(double feedSpeed);
        void extendLauncher(bool launcherRetracted);
        void launchCargo();
        COREConstant<double> launcherForwardSpeed, launcherLowSpeed, launcherBackwardSpeed, launcherFeedDelayTime, launcherPunchDelayTime;
        bool m_launching;

    private:
        TalonSRX m_rightFeed, m_leftFeed;
        TalonFX m_rightLauncher, m_leftLauncher;
        DoubleSolenoid m_launcherSolenoid;
        CORETimer m_punchDelayTimer, m_feedDelayTimer;
        double m_launcherSpeed;
        bool m_launcherRetracted,m_launcherToggled,m_launcherDelaying;
	
        void StartPunchTimer();
        void ResetPunchTimer();
	    double GetPunchTime();
	
        void StartFeedTimer();
        void ResetFeedTimer();
	    double GetFeedTime();
};