#pragma once

#include <CORERobotLib.h>
#include "LauncherSubsystem.h"

using namespace CORE;

enum launchBallsAction {
    LAUNCHER_ON,
    LAUNCHER_OFF
};

class LaunchBallsAction : public COREAutonAction {
public:
    LaunchBallsAction(launchBallsAction requestedLaunchBallsAction);
    void ActionInit() override;
    CORE::COREAutonAction::actionStatus Action() override;
    void ActionEnd() override;
private:
    launchBallsAction m_launchBallsAction;
};