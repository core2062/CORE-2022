#include "LauncherSubsystem.h"

using namespace CORE;

LauncherSubsystem::LauncherSubsystem() :m_rightFeed(RIGHT_FEED),
                                        m_leftFeed(LEFT_FEED),
                                        m_rightLauncher(RIGHT_LAUNCHER),
                                        m_leftLauncher(LEFT_LAUNCHER),
                                        forwardSpeed("Launcher Forward Speed", 0.6),
                                        backwardSpeed("Launcher Backward Speed", 0.2)  {
                                        
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

}

void LauncherSubsystem::teleop() {
    if (operatorJoystick->GetButton(CORE::COREJoystick::LEFT_BUTTON)) {
        m_leftFeed.Set(ControlMode::PercentOutput, forwardSpeed.Get());
        m_rightFeed.Set(ControlMode::PercentOutput, -forwardSpeed.Get());
        m_leftLauncher.Set(ControlMode::PercentOutput, forwardSpeed.Get());
        m_rightLauncher.Set(ControlMode::PercentOutput, -forwardSpeed.Get());
    } else if (operatorJoystick->GetButton(CORE::COREJoystick::LEFT_TRIGGER)) {
        m_leftFeed.Set(ControlMode::PercentOutput, backwardSpeed.Get());
        m_rightFeed.Set(ControlMode::PercentOutput, -backwardSpeed.Get());
        m_leftLauncher.Set(ControlMode::PercentOutput, backwardSpeed.Get());
        m_rightLauncher.Set(ControlMode::PercentOutput, -backwardSpeed.Get());
    }
}