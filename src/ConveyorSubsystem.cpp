#include "ConveyorSubsystem.h"

// using namespace CORE;

ConveyorSubsystem::ConveyorSubsystem() : conveyorForwardSpeed("Conveyor Forward Speed", -0.7),
                                         conveyorReverseSpeed("Conveyor Reverse Speed", 0.7),
                                         m_conveyorMotor(CONVEYOR_PORT) {
}

void ConveyorSubsystem::robotInit(){
    operatorJoystick->RegisterButton(CORE::COREJoystick::JoystickButton::RIGHT_TRIGGER);
    operatorJoystick->RegisterButton(CORE::COREJoystick::JoystickButton::RIGHT_BUTTON);
}

void ConveyorSubsystem::teleopInit() {
	SmartDashboard::PutString("Conveyor Controls", " In: Right Trigger \n Out: Right Button");
}

void ConveyorSubsystem::teleop(){
    if(operatorJoystick->GetButton(CORE::COREJoystick::JoystickButton::RIGHT_TRIGGER)) {
        setConveyorMotor(conveyorForwardSpeed.Get());
    } else if(operatorJoystick->GetButton(CORE::COREJoystick::JoystickButton::RIGHT_BUTTON)) {
        setConveyorMotor(conveyorReverseSpeed.Get());
    } else {
        setConveyorMotor(0);
    }
}

void ConveyorSubsystem::setConveyorMotor(double speed) {
    m_conveyorMotor.Set(ControlMode::PercentOutput, speed);
}
