#pragma once

#include <CORERobotLib.h>
#include "DriveSubsystem.h"

using namespace CORE;

enum driveAction {
    FORWARD,
    BACKWARD,
    RIGHT_TURN,
    LEFT_TURN
};

class DriveAction : public COREAutonAction {
public:
    DriveAction(driveAction requestedDriveAction); // Use for FORWARD and BACKWARD actions
    DriveAction(driveAction requestedDriveAction, double turnAmount); // Use for TURN_RIGHT and TURN_LEFT actions
    void ActionInit() override;
    CORE::COREAutonAction::actionStatus Action() override;
    void ActionEnd() override;
private:
    driveAction m_driveAction;
    double m_encoderStartUpPosition, m_turnAmount, m_navXStartingHeading, m_requestedHeading;
    COREConstant<double> m_distAutonMoveEncoderTicks;
    double m_encoderValue;
    double m_currentHeading, m_requestedDriveDistance;
};