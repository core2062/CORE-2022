#include "ClimberSubsystem.h"

// using namespace CORE;

ClimberSubsystem::ClimberSubsystem() :  m_rightTalon(RIGHT_CLIMBER_PORT),
										m_leftTalon(LEFT_CLIMBER_PORT),
										m_rightSolenoid(CLIMBER_PCM, frc::PneumaticsModuleType::CTREPCM, RIGHT_CLIMBER_HIGH_PORT, RIGHT_CLIMBER_LOW_PORT), 
										m_leftSolenoid(CLIMBER_PCM, frc::PneumaticsModuleType::CTREPCM, LEFT_CLIMBER_HIGH_PORT, LEFT_CLIMBER_LOW_PORT),
										climberSpeed("Climb Speed", 0.25) {
}

void ClimberSubsystem::robotInit(){
	driverJoystick->RegisterButton(CORE::COREJoystick::LEFT_BUTTON);
	driverJoystick->RegisterButton(CORE::COREJoystick::LEFT_TRIGGER);
	driverJoystick->RegisterButton(CORE::COREJoystick::RIGHT_BUTTON);
	driverJoystick->RegisterButton(CORE::COREJoystick::RIGHT_TRIGGER);
}

void ClimberSubsystem::teleopInit() {
	SmartDashboard::PutString("Climber Controls", " Toggle: ");
}

void ClimberSubsystem::teleop(){
}

void ClimberSubsystem::talonClimb() {

}

void ClimberSubsystem::solenoidClimb(){

}