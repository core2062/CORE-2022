#include "FiveBallRoutine.h"

FiveBallRoutinePickup::FiveBallRoutinePickup() : COREAuton("Three Ball Routine") {}

void FiveBallRoutinePickup::AddNodes() {
    delayNode = new Node(5, new DelayAction());
    launcherOnNode = new Node(5, new LaunchBallsAction(LAUNCHER_ON));
    intakeOnNode = new Node(5, new IntakePowerCellsAction(INTAKE));
    driveNode1 = new Node(5, new DriveAction(BACKWARD)); //replace with pathfinder
    driveNode2 = new Node(5, new DriveAction(FORWARD)); //replace with pathfinder
    conveyorOnNode = new Node(5, new ConveyorAction(CONVEYOR_ON));
    AddFirstNode(delayNode);
    delayNode->AddNext(launcherOnNode);
    launcherOnNode->AddNext(intakeOnNode);
    intakeOnNode->AddNext(driveNode1);
    driveNode1->AddNext(driveNode2);
    driveNode2->AddNext(conveyorOnNode);
    conveyorOnNode->AddNext(intakeOnNode);
    intakeOnNode->AddNext(driveNode1);
}
