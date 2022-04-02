#include "LauncherSubsystem.h"

using namespace CORE;

LauncherSubsystem::LauncherSubsystem() :    launcherForwardSpeed("Launcher Forward Speed", 0.7),
                                            launcherLowSpeed("Launcher Low Speed", 0.2),
                                            launcherBackwardSpeed("Launcher Backward Speed", -0.2),
                                            launcherDelayTime("Launcher Delay", 1.25),
                                            m_rightFeed(RIGHT_FEED),
                                            m_leftFeed(LEFT_FEED),
                                            m_rightLauncher(RIGHT_LAUNCHER),
                                            m_leftLauncher(LEFT_LAUNCHER),
                                            m_launcherSolenoid(frc::PneumaticsModuleType::REVPH,LAUNCHER_SOLENOID_IN_PORT,LAUNCHER_SOLENOID_OUT_PORT){
                                        
}

void LauncherSubsystem::robotInit(){
    operatorJoystick->RegisterButton(CORE::COREJoystick::LEFT_TRIGGER);
    operatorJoystick->RegisterButton(CORE::COREJoystick::B_BUTTON);
    operatorJoystick->RegisterButton(CORE::COREJoystick::Y_BUTTON);
    operatorJoystick->RegisterButton(CORE::COREJoystick::LEFT_BUTTON);
    m_leftFeed.Set(ControlMode::PercentOutput, 0);
    m_rightFeed.Set(ControlMode::PercentOutput, 0);
    m_leftLauncher.Set(ControlMode::PercentOutput, 0);
    m_rightLauncher.Set(ControlMode::PercentOutput, 0);
}

void LauncherSubsystem::teleopInit() {
    // SmartDashboard::PutString("Launcher Controls", " Launcher Out: Left Trigger \n Launcher Reverse: Left Button");
    m_launcherSolenoid.Set(DoubleSolenoid::Value::kForward);
    m_leftLauncher.Set(ControlMode::PercentOutput, 0);
    m_rightLauncher.Set(ControlMode::PercentOutput, 0);
}

void LauncherSubsystem::teleop() {
    if (operatorJoystick->GetRisingEdge(CORE::COREJoystick::JoystickButton::LEFT_TRIGGER)){
        toggleLauncher();
    }
    if (operatorJoystick->GetRisingEdge(CORE::COREJoystick::JoystickButton::B_BUTTON)){
        m_launching = true;
        // ExtendLauncher(m_launcherRetracted);
    }
    launchCargo();
}

void LauncherSubsystem::toggleLauncher(){
    if (m_launcherToggled){
        setLauncherSpeed(0);
    } else {
        if (operatorJoystick->GetButton(CORE::COREJoystick::Y_BUTTON)){
            setLauncherSpeed(launcherLowSpeed.Get());
        } else {
            setLauncherSpeed(launcherForwardSpeed.Get());
        }
    }
    m_launcherToggled = !m_launcherToggled;
}


void LauncherSubsystem::setLauncherSpeed(double launcherSpeed) {
        m_rightLauncher.Set(ControlMode::PercentOutput, launcherSpeed);
        m_leftLauncher.Set(ControlMode::PercentOutput, -launcherSpeed);
}

void LauncherSubsystem::setFeedSpeed(double feedSpeed) {
        m_leftFeed.Set(ControlMode::PercentOutput, feedSpeed);
        m_rightFeed.Set(ControlMode::PercentOutput, -feedSpeed);
}

void LauncherSubsystem::extendLauncher(bool launcherRetracted){
    if(launcherRetracted){
        m_launcherSolenoid.Set(DoubleSolenoid::Value::kReverse);
    } else {
        m_launcherSolenoid.Set(DoubleSolenoid::Value::kForward);
    }
    m_launcherRetracted = !m_launcherRetracted;
}

void LauncherSubsystem::launchCargo(){
    if (!m_launcherDelaying && m_launching) {
            setFeedSpeed(launcherLowSpeed.Get());
            StartTimer();
            extendLauncher(true);
            m_launcherDelaying = true;
    } else if (m_launcherDelaying) {
        if (GetTime() >= launcherDelayTime.Get()) {
                setFeedSpeed(0);
                extendLauncher(false);
                m_launcherDelaying = false;
                m_launching = !m_launching;
        }
    }
}

void LauncherSubsystem::StartTimer() {
    m_delayTimer.Reset();
    m_delayTimer.Start();
}

double LauncherSubsystem::GetTime() {
    return m_delayTimer.Get(); 
}