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

class TwoBallRedRoutine: public COREAuton {
public:
    TwoBallRedRoutine();
    void AddNodes() override;
private:
    Node * delayNode;
    Node * delayNode2;
    Node * delayNode3;
    Node * delayNode4;
    Node * delayNode5;
    Node * extendNode;
    Node * launcherOnNode;
    Node * conveyorOnNode;
    Node * intakeOnNode;
    Node * driveNode;
    Node * driveNode2;
    Node * launcherPunchNode;
    Node * launcherPunchNode2;
    Node * launcherPunchNode3;
    Node * LauncherFeedNode;
};