#include "LaunchBallsAction.h"
#include "Robot.h"

LaunchBallsAction::LaunchBallsAction(launchBallsAction requestedLaunchBallsAction) {
    m_launchBallsAction = requestedLaunchBallsAction;
}

void LaunchBallsAction::ActionInit() {
}

CORE::COREAutonAction::actionStatus LaunchBallsAction::Action() {
    switch(m_launchBallsAction) {
        case LAUNCHER_ON:
            Robot::GetInstance()->launcherSubsystem.launcherOn(true);
            break;
        case LAUNCHER_OFF:
            Robot::GetInstance()->launcherSubsystem.launcherOn(false);
            break;
    }
    return COREAutonAction::actionStatus::END;
} 

void LaunchBallsAction::ActionEnd() {

}
