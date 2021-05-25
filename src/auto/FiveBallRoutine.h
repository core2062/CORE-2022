#pragma once

#include <string>
#include <CORERobotLib.h>
#include "LaunchBallsAction.h"
#include "ConveyorAction.h"
#include "DriveAction.h"
#include "DelayAction.h"
#include "IntakePowerCellsAction.h"
// #include "AutonActionTest.h"

using namespace CORE;
using namespace std;

class FiveBallRoutinePickup: public COREAuton {
public:
    FiveBallRoutinePickup();
    void AddNodes() override;
private:
    Node * delayNode;
    Node * launcherOnNode;
    Node * conveyorOnNode;
    Node * intakeOnNode;
    Node * driveNode1;
    Node * driveNode2;
};
