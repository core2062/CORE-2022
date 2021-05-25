#pragma once

#include <CORERobotLib.h>
#include "TurretSubsystem.h"

using namespace CORE;

enum turretTrackingAction {
    TRACKING_ON,
    TRACKING_OFF
};

class TurretTrackingAction : public COREAutonAction {
public:
    TurretTrackingAction(turretTrackingAction requestedTurretTrackingAction);
    void ActionInit() override;
    CORE::COREAutonAction::actionStatus Action() override;
    void ActionEnd() override;
private:
    turretTrackingAction m_turretTrackingAction;
    double m_turretStartupPosition, m_turretPosition;

};