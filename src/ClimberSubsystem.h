#pragma once

#include <ctre/Phoenix.h>
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

private:
};
