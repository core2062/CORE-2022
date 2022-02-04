#pragma once

#include <CORERobotLib.h>
#include "IntakeSubsystem.h"

using namespace CORE;

enum intakeAction{
    INTAKE,
    OUTTAKE,
    STOP
};

class IntakeAction : public COREAutonAction {
public:
    IntakeAction(intakeAction requestedIntakeAction);
    void ActionInit() override;
    CORE::COREAutonAction::actionStatus Action() override;
    void ActionEnd() override;
private:
    intakeAction m_intakeAction;
    double m_intakeSpeed;
};