#include "OneBallRoutine.h"

OneBallRoutine::OneBallRoutine() : COREAuton("One BAll Routine") {}

void OneBallRoutine::AddNodes() {
    delayNode = new Node(5, new DelayAction());
    driveNode = new Node(5,new DriveAction(BACKWARD));
    conveyorOnNode = new Node (5, new ConveyorAction(CONVEYOR_ON));
    launcherOnNode = new Node (5, new LauncherAction(LAUNCHER_FORWARD));
    driveNode2 = new Node(5, new DriveAction(LEFT_TURN, 15));
    AddFirstNode(delayNode);
    delayNode->AddNext(driveNode);
    driveNode->AddNext(driveNode2);
    driveNode2->AddNext(launcherOnNode);
    launcherOnNode->AddNext(delayNode);
    delayNode->AddNext(conveyorOnNode);
    conveyorOnNode->AddNext(delayNode);
}