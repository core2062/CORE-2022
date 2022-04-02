#include "LauncherAction.h"
#include "Robot.h"

LauncherAction::LauncherAction(launcherAction requestedLauncherAction) {
    m_launcherAction = requestedLauncherAction;
}

void LauncherAction::ActionInit() {
    m_launcherForward = Robot::GetInstance()->launcherSubsystem.launcherForwardSpeed.Get();
    m_launcherBackward = Robot::GetInstance()->launcherSubsystem.launcherBackwardSpeed.Get();
    Robot::GetInstance()->launcherSubsystem.m_launching = true;
}

CORE::COREAutonAction::actionStatus LauncherAction::Action() {
    switch(m_launcherAction) {
        case LAUNCHER_FORWARD:
            Robot::GetInstance()->launcherSubsystem.setLauncherSpeed(m_launcherForward);
            break;
        case LAUNCHER_OFF:
            Robot::GetInstance()->launcherSubsystem.setLauncherSpeed(0);
            break;
        case LAUNCH:
            Robot::GetInstance()->launcherSubsystem.launchCargo();

    }
    return COREAutonAction::actionStatus::END;
} 

void LauncherAction::ActionEnd() {
    Robot::GetInstance()->launcherSubsystem.m_launching = false;
}