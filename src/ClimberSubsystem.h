#pragma once

#include <ctre/Phoenix.h>
#include <frc/DoubleSolenoid.h>
#include <CORERobotLib.h>
#include "Config.h"

using namespace CORE;
using namespace frc;


class ClimberSubsystem : public CORESubsystem {
public:
	ClimberSubsystem();
    void robotInit() override;
    void teleopInit() override;
    void teleop() override;

    void talonClimb(double);
    void solenoidClimb();

    COREConstant<double> climberOutSpeed,climberInSpeed;

private:
    TalonFX m_rightTalon, m_leftTalon;
    DoubleSolenoid m_rightSolenoid, m_leftSolenoid;
    bool m_solenoidClimberToggled;
};
