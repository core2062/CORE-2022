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

class ThreeBallRoutine : public COREAuton {
    public:
    ThreeBallRoutine();
    void AddNodes() override;
    private:
    Node * driveNode1;      // Drive Backwards
    Node * intakeNode1;     // Intakes in
    Node * delayNode1;      // Delay before turning on Robot to reach ball
    Node * conveyorNode1;   // Conveyor on to make space for second ball
    Node * delayNode2;      // Delay to intake ball
    Node * driveNode2;      // Turning robot to aim
    Node * launcherPunchInNode1; 
    Node * launcherNode1;   // Turning on launcher
    Node * delayNode3;      // Delay to launch all balls
    Node * launcherPunchOutNode1; 
    Node * launcherNode2;   // Turns launcher off
    Node * launcherPunchInNode2; 
    Node * launcherNode3;   // Turns launcher on 
    Node * delayNode4;
    Node * launcherPunchOutNode2;
    Node * launcherNode4;
    Node * driveNode3;      // Turns robot to aim to next ball
    Node * driveNode4;      // Drives to next ball
    Node * driveNode5;      // Turns robot to aim
    Node * launcherPunchInNode3; 
    Node * launcherNode5;
    Node * delayNode5;      // Delay to launch all balls
    Node * launcherPunchOutNode3; 
    Node * launcherNode6;
    Node * intakeNode2;     // Turns intake off
    Node * conveyorNode2;   // Turns conveyor off
    Node * extendNode;      // Extend the Intake
};