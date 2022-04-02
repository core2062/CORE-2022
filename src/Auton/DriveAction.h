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
    DriveAction(driveAction requestedDriveAction);
    DriveAction(driveAction requestedDriveAction, double passedDouble);
    void ActionInit() override;
    CORE::COREAutonAction::actionStatus Action() override;
    void ActionEnd() override;
private:
    driveAction m_driveAction;
    double m_encoderStartUpPosition, m_turnAmount, m_navXStartingHeading, m_requestedHeading;
    COREConstant<double> m_distAutonMoveEncoderTicks;
    double m_encoderValue;
    double m_currentHeading,  m_requestedDistance, m_requestedDriveDistance;
};