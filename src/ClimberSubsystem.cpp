#include "ClimberSubsystem.h"

// using namespace CORE;

ClimberSubsystem::ClimberSubsystem() :  m_rightTalon(RIGHT_CLIMBER_PORT),
										m_climberOutSpeed("Climb Out Speed", 0.25),
										m_climberInSpeed("Climb Reverse Speed", -0.1),
										m_climberSoftStop("Climber Soft Stop", 100000),
										m_climberSolinoid(CLIMBER_PCM, frc::PneumaticsModuleType::REVPH, IN_CLIMBER_PIN_PORT, OUT_CLIMBER_PIN_PORT),
										m_climberCompressor(CLIMBER_PCM,frc::PneumaticsModuleType::REVPH) {
}

void ClimberSubsystem::robotInit(){
	driverJoystick->RegisterButton(CORE::COREJoystick::DPAD_N);
	driverJoystick->RegisterButton(CORE::COREJoystick::DPAD_S);
	driverJoystick->RegisterButton(CORE::COREJoystick::Y_BUTTON);

}

void ClimberSubsystem::teleopInit() {
	m_rightTalon.SetNeutralMode(NeutralMode::Brake);
}

void ClimberSubsystem::teleop(){
	if (driverJoystick->GetButton(CORE::COREJoystick::Y_BUTTON)) { 
		climberSolenoid(m_climberPin); 
	}
	if (driverJoystick->GetButton(CORE::COREJoystick::DPAD_N) && m_rightTalon.GetSelectedSensorPosition() <= m_climberSoftStop.Get()) {
		climberMotor(m_climberOutSpeed.Get());
	} else if(driverJoystick->GetButton(CORE::COREJoystick::DPAD_S) && m_rightTalon.GetSelectedSensorPosition() >= 0 ) {
		climberMotor(m_climberInSpeed.Get());
	} else {
		climberMotor(0);
	}
}

void ClimberSubsystem::climberMotor(double speed) {
	m_rightTalon.Set(ControlMode::PercentOutput, speed);
}

void ClimberSubsystem::climberSolenoid(bool climberPin) {
	if (m_climberPin == 0){
		m_climberSolinoid.Set(DoubleSolenoid::Value::kForward);
	} else if(m_climberPin == 1) {
		m_climberSolinoid.Set(DoubleSolenoid::Value::kReverse);
	}
}