#include "LauncherSubsystem.h"

using namespace CORE;

LauncherSubsystem::LauncherSubsystem() :m_rightFeed(RIGHT_FEED),
                                        m_leftFeed(LEFT_FEED),
                                        m_rightLauncher(RIGHT_LAUNCHER),
                                        m_leftLauncher(LEFT_LAUNCHER),
                                        forwardSpeed("Launcher Forward Speed", 0.6),
                                        backwardSpeed("Launcher Backward Speed", -0.2)  {
                                        
}

void LauncherSubsystem::robotInit(){
    operatorJoystick->RegisterButton(CORE::COREJoystick::LEFT_BUTTON);
    operatorJoystick->RegisterButton(CORE::COREJoystick::LEFT_TRIGGER);
    m_leftFeed.Set(ControlMode::PercentOutput, 0);
    m_rightFeed.Set(ControlMode::PercentOutput, 0);
    m_leftLauncher.Set(ControlMode::PercentOutput, 0);
    m_rightLauncher.Set(ControlMode::PercentOutput, 0);
}

void LauncherSubsystem::teleopInit() {
    SmartDashboard::PutString("Launcher Controls", " Launcher Out: Left Trigger \n Launcher Reverse: Left Button");
}

void LauncherSubsystem::teleop() {
    if (operatorJoystick->GetButton(CORE::COREJoystick::LEFT_TRIGGER)) {
        setLauncherSpeed(forwardSpeed.Get());
    } else if (operatorJoystick->GetButton(CORE::COREJoystick::LEFT_BUTTON)) {
        setLauncherSpeed(backwardSpeed.Get());
    } else {
        setLauncherSpeed(0);
    }
}

void LauncherSubsystem::setLauncherSpeed(double launcherSpeed) {
        m_leftFeed.Set(ControlMode::PercentOutput, launcherSpeed);
        m_rightFeed.Set(ControlMode::PercentOutput, -launcherSpeed);
        m_leftLauncher.Set(ControlMode::PercentOutput, launcherSpeed);
        m_rightLauncher.Set(ControlMode::PercentOutput, -launcherSpeed);
}