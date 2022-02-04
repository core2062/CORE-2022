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

    void solenoidClimb();
    void talonClimb();

    COREConstant<double> climberSpeed;

private:
    TalonFX m_leftTalon, m_rightTalon;
    DoubleSolenoid m_leftSolenoid, m_rightSolenoid;
};
