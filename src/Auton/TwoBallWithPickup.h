#pragma once

#include <string>
#include <CORERobotLib.h>
// Include Actions being used
#include "DelayAction.h"
#include "DriveAction.h"
#include "IntakeAction.h"
#include "ConveyorAction.h"
#include "LauncherAction.h"

using namespace CORE;
using namespace std;

class TwoBallWithPickup : public COREAuton {
    public:
    TwoBallWithPickup();
    void AddNodes() override;
    private:
    Node * driveNode1;      // Drive Backwards
    Node * extendNode;
    Node * intakeNode1;     // Intakes in
    Node * delayNode1;      // Delay before turning on Robot to reach ball
    Node * conveyorNode1;   // Conveyor on to make space for second ball
    Node * delayNode2;      // Delay to intake ball
    Node * driveNode2;      // Turning robot to aim
    Node * launcherNode1;   // Turning on launcher
    Node * delayNode3;      // Delay to launch all balls
    Node * launcherNode2;   // Turns launcher off
    Node * driveNode3;      // Turns robot to aim to next ball
    Node * driveNode4;      // Drives to next ball
    Node * delayNode4;      // Delay to launch all balls
    Node * intakeNode2;     // Turns intake off
    Node * conveyorNode2;   // Turns conveyor off
};