#include "ClimberSubsystem.h"

// using namespace CORE;

ClimberSubsystem::ClimberSubsystem() :  m_rightTalon(RIGHT_CLIMBER_PORT),
										m_climberOutSpeed("Climb Out Speed", -0.25),
										m_climberInSpeed("Climb Reverse Speed", 0.1),
										m_climberSoftStop("Climber Soft Stop", 100000),
										m_climberSolinoid(frc::PneumaticsModuleType::REVPH, RIGHT_CLIMBER_LOW_PORT, RIGHT_CLIMBER_HIGH_PORT){
}

void ClimberSubsystem::robotInit(){
	m_climberPin = false;
	driverJoystick->RegisterButton(CORE::COREJoystick::DPAD_N);
	driverJoystick->RegisterButton(CORE::COREJoystick::DPAD_S);
	driverJoystick->RegisterButton(CORE::COREJoystick::Y_BUTTON);

}

void ClimberSubsystem::teleopInit() {
	m_rightTalon.SetNeutralMode(NeutralMode::Brake);
}

void ClimberSubsystem::teleop(){
	if (driverJoystick->GetRisingEdge(CORE::COREJoystick::Y_BUTTON)) { 
		toggleClimberSolenoid(); 
	}
	if (driverJoystick->GetButton(CORE::COREJoystick::DPAD_N) /*&& m_rightTalon.GetSelectedSensorPosition() >= m_climberSoftStop.Get()*/) {
		climberMotor(m_climberOutSpeed.Get());
	} else if(driverJoystick->GetButton(CORE::COREJoystick::DPAD_S) /*&& m_rightTalon.GetSelectedSensorPosition() <= 0*/) {
		climberMotor(m_climberInSpeed.Get());
	} else {
		climberMotor(0);
	}
}

void ClimberSubsystem::climberMotor(double speed) {
	m_rightTalon.Set(ControlMode::PercentOutput, speed);
}

void ClimberSubsystem::toggleClimberSolenoid() {
	if (m_climberPin){
		m_climberSolinoid.Set(DoubleSolenoid::Value::kForward);
	} else {
		m_climberSolinoid.Set(DoubleSolenoid::Value::kReverse);
	}
	m_climberPin = !m_climberPin;
}