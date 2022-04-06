#include "IntakeAction.h"
#include "Robot.h"

IntakeAction::IntakeAction(intakeAction requestedIntakeAction) {
    m_intakeAction = requestedIntakeAction;
}

void IntakeAction::ActionInit() {
    m_intakeSpeed = Robot::GetInstance()->intakeSubsystem.intakeSpeed.Get();

}

CORE::COREAutonAction::actionStatus IntakeAction::Action() {
    switch(m_intakeAction) {
        case EXTEND:
            Robot::GetInstance()->intakeSubsystem.ExtendIntake(true);
            break;
        case RETRACT:
            Robot::GetInstance()->intakeSubsystem.ExtendIntake(false);
            break;
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

void IntakeAction::ActionEnd() {

}