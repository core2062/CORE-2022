#include "ClimberSubsystem.h"
ClimberSubsystem :: ClimberSubsystem() : m_climberOne(CLIMBER_PCM, frc::PneumaticsModuleType::CTREPCM, CLIMBER_RIGHT_UP_PORT, CLIMBER_RIGHT_DOWN_PORT),
                                         m_climberTwo(CLIMBER_PCM, frc::PneumaticsModuleType::CTREPCM, CLIMBER_LEFT_UP_PORT, CLIMBER_LEFT_DOWN_PORT){

}
void ClimberSubsystem::robotInit() {

}

void ClimberSubsystem::teleopInit() {
    driverJoystick->RegisterButton(CORE::COREJoystick::Y_BUTTON);
}

void ClimberSubsystem::teleop() {
    if (!m_climberExtended && driverJoystick->GetRisingEdge(CORE::COREJoystick::Y_BUTTON)) {
        m_climberOne.Set(DoubleSolenoid::kForward);
        m_climberTwo.Set(DoubleSolenoid::kForward);
        m_climberExtended = true;
    } else if (m_climberExtended && driverJoystick->GetRisingEdge(CORE::COREJoystick::Y_BUTTON)) {
        m_climberOne.Set(DoubleSolenoid::kReverse);
        m_climberTwo.Set(DoubleSolenoid::kReverse);
        m_climberExtended = false;
    }
}
