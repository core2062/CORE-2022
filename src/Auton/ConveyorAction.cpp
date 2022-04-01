#include "ConveyorAction.h"
#include "Robot.h"

ConveyorAction::ConveyorAction(conveyorAction requestedConveyorAction) {
    m_conveyorAction = requestedConveyorAction;
}

void ConveyorAction::ActionInit() {
    m_conveyorForwardSpeed = Robot::GetInstance()->conveyorSubsystem.conveyorForwardSpeed.Get();
    m_conveyorReverseSpeed = Robot::GetInstance()->conveyorSubsystem.conveyorReverseSpeed.Get();
}

CORE::COREAutonAction::actionStatus ConveyorAction::Action() {
    switch(m_conveyorAction) {
        case CONVEYOR_ON:
            Robot::GetInstance()->conveyorSubsystem.setConveyorMotor(m_conveyorForwardSpeed);
            break;
        case CONVEYOR_OFF:
            Robot::GetInstance()->conveyorSubsystem.setConveyorMotor(0);
            break;
    }
    return COREAutonAction::actionStatus::END;
}

void ConveyorAction::ActionEnd() {

}