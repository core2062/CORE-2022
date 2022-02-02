#include "IntakeSubsystem.h"

using namespace CORE;

IntakeSubsystem::IntakeSubsystem() :
    m_intakeMotor(INTAKE_PORT),
    intakeSpeed("Intake Speed", 0.20) {

}

void IntakeSubsystem::robotInit(){
    m_intakeMotor.Set(ControlMode::PercentOutput, 0);
    operatorJoystick->RegisterButton(CORE::COREJoystick::JoystickButton::RIGHT_TRIGGER);
    operatorJoystick->RegisterButton(CORE::COREJoystick::JoystickButton::RIGHT_BUTTON);
    m_intakeMotor.SetInverted(true);
}


void IntakeSubsystem::teleopInit() {}

void IntakeSubsystem::teleop(){
    if(operatorJoystick->GetButton(CORE::COREJoystick::JoystickButton::RIGHT_TRIGGER)) {
        SetIntake(-intakeSpeed.Get());
    } else if (operatorJoystick->GetButton(CORE::COREJoystick::JoystickButton::RIGHT_BUTTON)) {
        SetIntake(intakeSpeed.Get());
    } else{
        SetIntake(0.0);
    }
    
}

void IntakeSubsystem::SetIntake(double intakeSpeed) {
    m_intakeMotor.Set(ControlMode::PercentOutput, intakeSpeed);
}
