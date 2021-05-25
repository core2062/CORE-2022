#pragma once

#include <frc/DoubleSolenoid.h>
#include <ctre/Phoenix.h>
#include <CORERobotLib.h>
#include "Config.h"

using namespace CORE;

class IntakeSubsystem : public CORESubsystem {
public:
    IntakeSubsystem();
    void robotInit() override;
    void teleopInit() override;
    void teleop() override;
    void SetIntake(double intakeSpeed);
    void ToggleIntake();

    COREConstant<double> intakeSpeed;

private:
    TalonSRX m_intakeMotor;
    frc::DoubleSolenoid m_intakeSolenoid;
    bool m_isIntakeDown;
};