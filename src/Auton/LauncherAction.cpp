#include "LauncherAction.h"
#include "Robot.h"

LauncherAction::LauncherAction(launcherAction requestedLauncherAction) {
    m_launcherAction = requestedLauncherAction;
}

void LauncherAction::ActionInit() {
    m_launcherForward = Robot::GetInstance()->launcherSubsystem.launcherForwardSpeed.Get();
    m_launcherBackward = Robot::GetInstance()->launcherSubsystem.launcherBackwardSpeed.Get();
    m_launcherFeed = Robot::GetInstance()->launcherSubsystem.launcherLowSpeed.Get();
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
            break;
        case LAUNCH_EXTEND:
            std::cout << "Extending Launcher" << endl;
            Robot::GetInstance()->launcherSubsystem.extendLauncher(true);
            break;
        case LAUNCH_RETRACT:
            std::cout << "Retracting Launcher" << endl;
            Robot::GetInstance()->launcherSubsystem.extendLauncher(false);
            break;
        case LAUNCH_FEED:
            Robot::GetInstance()->launcherSubsystem.setFeedSpeed(m_launcherFeed);
            break;
    }
    return COREAutonAction::actionStatus::END;
} 

void LauncherAction::ActionEnd() {
    Robot::GetInstance()->launcherSubsystem.m_launching = false;
}