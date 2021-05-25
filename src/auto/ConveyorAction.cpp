#include "ConveyorAction.h"
#include "Robot.h"

ConveyorAction::ConveyorAction(conveyorAction requestedConveyorAction) {
    m_conveyorAction = requestedConveyorAction;

}

void ConveyorAction::ActionInit() {
    m_lowerConveyorSpeed = Robot::GetInstance()->conveyorSubsystem.lowerConveyorSpeed.Get();
    m_upperConveyorSpeed = Robot::GetInstance()->conveyorSubsystem.upperConveyorSpeed.Get();
}

CORE::COREAutonAction::actionStatus ConveyorAction::Action() {
    switch(m_conveyorAction) {
        case CONVEYOR_ON:
            Robot::GetInstance()->conveyorSubsystem.setLowerMotor(-m_lowerConveyorSpeed);
            Robot::GetInstance()->conveyorSubsystem.setUpperMotor(-m_upperConveyorSpeed);
            break;
        case CONVEYOR_OFF:
            Robot::GetInstance()->conveyorSubsystem.setLowerMotor(0);
            Robot::GetInstance()->conveyorSubsystem.setUpperMotor(0);
            break;
    }
    return COREAutonAction::actionStatus::END;
}

void ConveyorAction::ActionEnd() {

}