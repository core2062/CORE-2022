#pragma once

#include <string>
#include <CORERobotLib.h>
#include "DriveAction.h"
#include "IntakeAction.h"
#include "ConveyorAction.h"
#include "LauncherAction.h"
#include "DelayAction.h"

using namespace CORE;
using namespace std;

class TwoBallRoutine: public COREAuton {
public:
    TwoBallRoutine();
    void AddNodes() override;
private:
    Node * delayNode;
    Node * launcherOnNode;
    Node * conveyorOnNode;
    Node * intakeOnNode;
    Node * driveNode;
    Node * driveNode2;
};