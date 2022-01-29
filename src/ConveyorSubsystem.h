#pragma once

#include <ctre/Phoenix.h>
#include <CORERobotLib.h>
#include "Config.h"

using namespace CORE;
using namespace frc;


class ConveyorSubsystem : public CORESubsystem {
public:
	ConveyorSubsystem();
    void robotInit() override;
    void teleopInit() override;
    void teleop() override;

private:
};
