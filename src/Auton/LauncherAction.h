#pragma once

#include <CORERobotLib.h>
#include "LauncherSubsystem.h"

using namespace CORE;

enum launcherAction {
    LAUNCHER_FORWARD,
    LAUNCHER_REVERSE,
    LAUNCHER_OFF,
    LAUNCHER_PUNCH_OUT,
    LAUNCHER_PUNCH_IN
};

class LauncherAction : public COREAutonAction {
public:
    LauncherAction(launcherAction requestedLauncherAction);
    void ActionInit() override;
    CORE::COREAutonAction::actionStatus Action() override;
    void ActionEnd() override;
private:
    launcherAction m_launcherAction;
    double m_launcherForward, m_launcherBackward;
};