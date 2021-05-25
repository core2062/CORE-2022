#include "ThreeBallRoutinePickup.h"

ThreeBallRoutinePickup::ThreeBallRoutinePickup() : COREAuton("Three Ball Routine") {}

void ThreeBallRoutinePickup::AddNodes() {
    delayNode = new Node(5, new DelayAction());
    launcherOnNode = new Node(5, new LaunchBallsAction(LAUNCHER_ON));
    conveyorOnNode = new Node(5, new ConveyorAction(CONVEYOR_ON));
    intakeOnNode = new Node(5, new IntakePowerCellsAction(INTAKE));
    driveNode = new Node(5, new DriveAction(FORWARD)); //replace with pathfinder
    AddFirstNode(delayNode);
    delayNode->AddNext(launcherOnNode);
    launcherOnNode->AddNext(conveyorOnNode);
    conveyorOnNode->AddNext(intakeOnNode);
    intakeOnNode->AddNext(driveNode);
}
