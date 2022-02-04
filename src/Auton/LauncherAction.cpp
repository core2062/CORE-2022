#include "LauncherAction.h"
#include "Robot.h"

LauncherAction::LauncherAction(launcherAction requestedLauncherAction) {
    m_launcherAction = requestedLauncherAction;
}

void LauncherAction::ActionInit() {
    m_launcherForward = Robot::GetInstance()->launcherSubsystem.forwardSpeed.Get();
    m_launcherBackward = Robot::GetInstance()->launcherSubsystem.backwardSpeed.Get();
}

CORE::COREAutonAction::actionStatus LauncherAction::Action() {
    switch(m_launcherAction) {
        case LAUNCHER_FORWARD:
            Robot::GetInstance()->launcherSubsystem.setLauncherSpeed(m_launcherForward);
            break;
        case LAUNCHER_REVERSE:
            Robot::GetInstance()->launcherSubsystem.setLauncherSpeed(m_launcherBackward);
            break;
        case LAUNCHER_OFF:
            Robot::GetInstance()->launcherSubsystem.setLauncherSpeed(0);
            break;
    }
    return COREAutonAction::actionStatus::END;
} 

void LauncherAction::ActionEnd() {

}