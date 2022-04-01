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
    Node * extendNode;      // Extend the intake
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
    Node * launcherPunchNode1; // Pushes piston out
    Node * launcherPunchNode2; // Pulls piston in
    Node * delayNode5; 
    Node * conveyorNode3;
    Node * conveyorNode4;
    Node * launcherPunchNode3; // Pushes piston out
    Node * launcherPunchNode4; // Pulls piston in
    Node * launcherNode3;   // Turning on launcher
    Node * launcherNode4;   // Turns launcher off
    Node * delayNode6;
};