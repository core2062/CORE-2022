#include "IntakePowerCellsAction.h"
#include "Robot.h"

IntakePowerCellsAction::IntakePowerCellsAction(intakePowerCellsAction requestedIntakePowerCellAction) {
    m_intakePowerCellsAction = requestedIntakePowerCellAction;

}

void IntakePowerCellsAction::ActionInit() {
    m_intakeSpeed = Robot::GetInstance()->intakeSubsystem.intakeSpeed.Get();

}

CORE::COREAutonAction::actionStatus IntakePowerCellsAction::Action() {
    switch(m_intakePowerCellsAction) {
        case INTAKE:
            Robot::GetInstance()->intakeSubsystem.SetIntake(m_intakeSpeed);
            break;
        case OUTTAKE:
            Robot::GetInstance()->intakeSubsystem.SetIntake(-m_intakeSpeed);
            break;
        case STOP:
            Robot::GetInstance()->intakeSubsystem.SetIntake(0);
            break;
    }
    return COREAutonAction::actionStatus::END;
}

void IntakePowerCellsAction::ActionEnd() {

}