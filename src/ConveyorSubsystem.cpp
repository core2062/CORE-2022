#include "ConveyorSubsystem.h"

using namespace CORE;

ConveyorSubsystem::ConveyorSubsystem() : m_lowerConveyorMotor(CONVEYOR_1_PORT),
                                         m_frontConveyorMotor(CONVEYOR_2_PORT),
                                         m_backConveyorMotor(CONVEYOR_3_PORT),
                                         lowerConveyorSpeed("Lower Conveyor Speed", 0.75),
                                         upperConveyorSpeed("Upper Conveyor Speed", 0.75) {
}

void ConveyorSubsystem::robotInit(){
    /* Inits Talons */
    m_lowerConveyorMotor.Set(ControlMode::PercentOutput, 0);
    m_frontConveyorMotor.Set(ControlMode::PercentOutput, 0);
    m_backConveyorMotor.Set(ControlMode::PercentOutput, 0);
    m_lowerConveyorMotor.SetInverted(true);
    m_frontConveyorMotor.SetInverted(false);

    /* Registers Controls */
    operatorJoystick->RegisterButton(CORE::COREJoystick::JoystickButton::RIGHT_TRIGGER);
    operatorJoystick->RegisterButton(CORE::COREJoystick::JoystickButton::RIGHT_BUTTON);
    operatorJoystick->RegisterButton(CORE::COREJoystick::JoystickButton::LEFT_TRIGGER);
    operatorJoystick->RegisterButton(CORE::COREJoystick::JoystickButton::LEFT_BUTTON);
}

void ConveyorSubsystem::teleopInit() {}

void ConveyorSubsystem::teleop(){
    
    if(operatorJoystick->GetButton(CORE::COREJoystick::JoystickButton::RIGHT_TRIGGER)) {
        setLowerMotor(lowerConveyorSpeed.Get());
    } else if(operatorJoystick->GetButton(CORE::COREJoystick::JoystickButton::RIGHT_BUTTON)) {
        setLowerMotor(-lowerConveyorSpeed.Get());
    } else {
        setLowerMotor(0.0);
    }
    
    if(operatorJoystick->GetButton(CORE::COREJoystick::JoystickButton::LEFT_TRIGGER)) {
        setUpperMotor(upperConveyorSpeed.Get());
    } else if(operatorJoystick->GetButton(CORE::COREJoystick::JoystickButton::LEFT_BUTTON)) {
        setUpperMotor(-upperConveyorSpeed.Get());
    } else {
        setUpperMotor(0.0);
    }
}

void ConveyorSubsystem::setLowerMotor(double lowerConveyorSpeed){
    m_lowerConveyorMotor.Set(ControlMode::PercentOutput, lowerConveyorSpeed); 
}

void ConveyorSubsystem::setUpperMotor(double upperConveyorSpeed) {
    m_frontConveyorMotor.Set(ControlMode::PercentOutput, upperConveyorSpeed);
    m_backConveyorMotor.Set(ControlMode::PercentOutput, upperConveyorSpeed);
}