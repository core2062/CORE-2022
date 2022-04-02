#include "ClimberSubsystem.h"

// using namespace CORE;

ClimberSubsystem::ClimberSubsystem() :  m_rightTalon(RIGHT_CLIMBER_PORT),
										m_leftTalon(LEFT_CLIMBER_PORT),
										m_rightSolenoid(frc::PneumaticsModuleType::REVPH, RIGHT_CLIMBER_HIGH_PORT, RIGHT_CLIMBER_LOW_PORT), 
										// m_leftSolenoid(frc::PneumaticsModuleType::REVPH, LEFT_CLIMBER_HIGH_PORT, LEFT_CLIMBER_LOW_PORT),
										climberOutSpeed("Climb Out Speed", 0.25),
										climberInSpeed("Climb Reverse Speed", -0.1) {
}

void ClimberSubsystem::robotInit(){
	driverJoystick->RegisterButton(CORE::COREJoystick::LEFT_BUTTON);
	driverJoystick->RegisterButton(CORE::COREJoystick::LEFT_TRIGGER);
	driverJoystick->RegisterButton(CORE::COREJoystick::Y_BUTTON);

	m_solenoidClimberToggled = false;
}

void ClimberSubsystem::teleopInit() {
	SmartDashboard::PutString("Climber Controls", " Talon Climb Up: Left Trigger,  Talon Climb Down: Left Button, Toggle Solenoids: Y Button");
}

void ClimberSubsystem::teleop(){
	if (driverJoystick->GetButton(CORE::COREJoystick::LEFT_TRIGGER)) {
		talonClimb(climberOutSpeed.Get());
	} else if(driverJoystick->GetButton(CORE::COREJoystick::LEFT_BUTTON)) {
		talonClimb(climberInSpeed.Get());
	} else {
		talonClimb(0);
	}

	if (driverJoystick->GetRisingEdge(CORE::COREJoystick::Y_BUTTON)) {
		solenoidClimb();
	}
}

void ClimberSubsystem::talonClimb(double speed) {
	m_rightTalon.Set(ControlMode::PercentOutput, speed);
	m_leftTalon.Set(ControlMode::PercentOutput, speed);
}

void ClimberSubsystem::solenoidClimb(){
	if (m_solenoidClimberToggled) {
		m_solenoidClimberToggled = true;
		m_rightSolenoid.Set(DoubleSolenoid::Value::kForward);
		// m_leftSolenoid.Set(DoubleSolenoid::Value::kForward);
	} else {
		m_solenoidClimberToggled = false;
		m_rightSolenoid.Set(DoubleSolenoid::Value::kReverse);
		// m_leftSolenoid.Set(DoubleSolenoid::Value::kReverse);
	}
}