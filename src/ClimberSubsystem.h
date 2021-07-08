#pragma once

#include <CORERobotLib.h>
#include <frc/DoubleSolenoid.h>
#include "Config.h"

using namespace CORE;
using namespace frc;

class ClimberSubsystem : public CORESubsystem {
public:
    ClimberSubsystem();
    void robotInit() override;
    void teleopInit() override;
    void teleop() override;

private:
    DoubleSolenoid m_climberOne;
    DoubleSolenoid m_climberTwo;
    bool m_climberExtended = false;
};
