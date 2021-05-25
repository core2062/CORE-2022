#pragma once

#include <CORERobotLib.h>
#include "DriveSubsystem.h"

using namespace CORE;

enum driveAction {
    FORWARD,
    BACKWARD
};

class DriveAction : public COREAutonAction {
public:
    DriveAction(driveAction requestedDriveAction);
    void ActionInit() override;
    CORE::COREAutonAction::actionStatus Action() override;
    void ActionEnd() override;
private:
    driveAction m_driveAction;
    double m_encoderStartUpPosition;
    COREConstant<double> m_distAutonMoveEncoderTicks;
};
