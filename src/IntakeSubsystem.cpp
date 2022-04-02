#include "IntakeSubsystem.h"

using namespace CORE;

IntakeSubsystem::IntakeSubsystem() :
                                    m_intakeMotor(INTAKE_PORT),
                                    m_intakeSolenoid(frc::PneumaticsModuleType::REVPH,INTAKE_SOLENOID_IN_PORT,INTAKE_SOLENOID_OUT_PORT),
                                    intakeSpeed("Intake Speed", 0.80) {

}

void IntakeSubsystem::robotInit(){
    m_intakeMotor.Set(ControlMode::PercentOutput, 0);
    operatorJoystick->RegisterButton(CORE::COREJoystick::JoystickButton::RIGHT_TRIGGER);
    operatorJoystick->RegisterButton(CORE::COREJoystick::JoystickButton::RIGHT_BUTTON);
    operatorJoystick->RegisterButton(CORE::COREJoystick::JoystickButton::A_BUTTON);
    m_intakeMotor.SetInverted(true);
}


void IntakeSubsystem::teleopInit() {
	SmartDashboard::PutString("Intake Controls", " In: Right Trigger \n Out: Right Button");
}

void IntakeSubsystem::teleop(){
    if(operatorJoystick->GetRisingEdge(CORE::COREJoystick::JoystickButton::A_BUTTON)){
        ExtendIntake(m_intakeRetracted);
        m_intakeRetracted = !m_intakeRetracted;
    }
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
void IntakeSubsystem::ExtendIntake(bool intakeRetracted){
    if(intakeRetracted == 1){
        m_intakeSolenoid.Set(DoubleSolenoid::Value::kForward);
    } else if(intakeRetracted == 0){
        m_intakeSolenoid.Set(DoubleSolenoid::Value::kReverse);
    }
}