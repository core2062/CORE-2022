#pragma once

#include <CORERobotLib.h>
#include "Config.h"

using namespace CORE;

class ClimberSubsystem : public CORESubsystem {
public:
    ClimberSubsystem();
    void robotInit() override;
    void teleopInit() override;
    void teleop() override;
};
