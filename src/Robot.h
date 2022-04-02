#pragma once

#include <string>
#include <iostream>
#include <frc/TimedRobot.h>
#include <CORERobotLib.h>
#include <COREFramework/COREScheduler.h>

#include "DriveSubsystem.h"
#include "IntakeSubsystem.h"
#include "ConveyorSubsystem.h"
#include "LauncherSubsystem.h"
#include "ClimberSubsystem.h"
#include "OneBallRoutine.h"
#include "TwoBallRoutine.h"
#include "TwoBallWithPickup.h"
#include "ThreeBallRoutine.h"
#include "DriveRoutine.h"
#include "Config.h"

// #include "Auton/TestRoutine.h"
// #include "Auton/DriveRoutine.h"

using namespace CORE;
using namespace std;

class Robot : public CORERobot {
    public:
        Robot();
        void robotInit() override;
        void teleopInit() override;
        void teleop() override;
        void test() override;
        void testInit() override;
        static Robot * GetInstance();
        DriveSubsystem driveSubsystem;
        IntakeSubsystem intakeSubsystem;
        ConveyorSubsystem conveyorSubsystem;
        LauncherSubsystem launcherSubsystem;
        // ClimberSubsystem climberSubsystem;
        DriveRoutine driveRoutine;
        OneBallRoutine oneBallRoutine;
        // TwoBallRoutine twoBallRoutine;
        // TwoBallWithPickup twoBallWithPickup;
        // ThreeBallRoutine threeBallRoutine;
    private:
        static Robot * m_instance;
};
