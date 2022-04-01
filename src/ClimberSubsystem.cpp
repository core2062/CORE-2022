#include "ClimberSubsystem.h"

// using namespace CORE;

ClimberSubsystem::ClimberSubsystem() :  m_rightTalon(RIGHT_CLIMBER_PORT),
										m_leftTalon(LEFT_CLIMBER_PORT),
										m_climberOutSpeed("Climb Out Speed", 0.25),
										m_climberInSpeed("Climb Reverse Speed", -0.1),
										m_climberSoftStop("Climber Soft Stop", 100000) {
}

void ClimberSubsystem::robotInit(){
	driverJoystick->RegisterButton(CORE::COREJoystick::DPAD_N);
	driverJoystick->RegisterButton(CORE::COREJoystick::DPAD_S);
	m_rightTalon.ConfigSelectedFeedbackSensor(ctre::phoenix::motorcontrol::FeedbackDevice::IntegratedSensor, 0, 0);

}

void ClimberSubsystem::teleopInit() {
	m_rightTalon.SetNeutralMode(NeutralMode::Brake);
	m_leftTalon.SetNeutralMode(NeutralMode::Brake);
}

void ClimberSubsystem::teleop(){
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
	m_leftTalon.Set(ControlMode::PercentOutput, speed);
}
