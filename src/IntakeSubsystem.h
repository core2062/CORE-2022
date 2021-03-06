#pragma once

#include <ctre/Phoenix.h>
#include <frc/DoubleSolenoid.h>
#include <CORERobotLib.h>
#include "Config.h"


using namespace CORE;
using namespace frc;


class IntakeSubsystem : public CORESubsystem {
public:
	IntakeSubsystem();
    void robotInit() override;
    void teleopInit() override;
    void teleop() override;
    void SetIntake(double intakeSpeed);
    void ToggleIntake();
    void ExtendIntake(bool intakeRetracted);

    COREConstant<double> intakeSpeed;
private:
    TalonSRX m_intakeMotor;
    DoubleSolenoid m_intakeSolenoid;
    bool m_intakeRetracted;
};
