#pragma once

#include <CORERobotLib.h>
#include "IntakeSubsystem.h"


using namespace CORE;

enum intakePowerCellsAction{
    INTAKE,
    OUTTAKE,
    STOP
};

class IntakePowerCellsAction : public COREAutonAction {
public:
    IntakePowerCellsAction(intakePowerCellsAction requestedIntakePowerCellAction);
    void ActionInit() override;
    CORE::COREAutonAction::actionStatus Action() override;
    void ActionEnd() override;
private:
    intakePowerCellsAction m_intakePowerCellsAction;
    double m_intakeSpeed;
};
