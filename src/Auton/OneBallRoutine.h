#pragma once

#include <string>
#include <CORERobotLib.h>
#include "DriveAction.h"
#include "ConveyorAction.h"
#include "LauncherAction.h"
#include "DelayAction.h"

using namespace CORE;
using namespace std;

class OneBallRoutine: public COREAuton {
public:
    OneBallRoutine();
    void AddNodes() override;
private:
    Node * delayNode;
    Node * launcherOnNode;
    Node * conveyorOnNode;
    Node * driveNode;
    Node * driveNode2;
};