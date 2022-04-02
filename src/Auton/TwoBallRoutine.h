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
    Node * driveNode1;
    Node * launcherNode;
    Node * punchNode1;
    Node * delayNode;
    Node * intakeOutNode;
    Node * intakeOnNode;
    Node * conveyorNode;
    Node * driveNode2;
    Node * intakeOffNode;
    Node * intakeInNode;
    Node * driveNode3;
    Node * punchNode2;
    Node * driveNode4;
};