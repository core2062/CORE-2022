#pragma once

#include <CORERobotLib.h>
#include "LauncherSubsystem.h"

using namespace CORE;

enum launcherAction {
    LAUNCHER_FORWARD,
    LAUNCHER_OFF,
    LAUNCH,
    LAUNCH_EXTEND,
    LAUNCH_RETRACT,
    LAUNCH_FEED
};

class LauncherAction : public COREAutonAction {
public:
    LauncherAction(launcherAction requestedLauncherAction);
    void ActionInit() override;
    CORE::COREAutonAction::actionStatus Action() override;
    void ActionEnd() override;
private:
    launcherAction m_launcherAction;
    double m_launcherForward, m_launcherBackward, m_launcherFeed;
};