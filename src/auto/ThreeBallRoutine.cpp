#include "ThreeBallRoutine.h"

ThreeBallRoutine::ThreeBallRoutine() : COREAuton("Three Ball Routine") {}

void ThreeBallRoutine::AddNodes() {
    launcherOnNode = new Node(5, new LaunchBallsAction(LAUNCHER_ON));
    turretNode = new Node(5, new TurretTrackingAction(TRACKING_ON));
    delayNode1 = new Node(5, new DelayAction());
    conveyorOnNode = new Node(5, new ConveyorAction(CONVEYOR_ON));
    delayNode2 = new Node(2, new DelayAction());
    driveNode = new Node(5, new DriveAction(FORWARD));
    AddFirstNode(launcherOnNode);
    launcherOnNode->AddNext(turretNode);
    turretNode->AddNext(delayNode1);
    delayNode1->AddNext(conveyorOnNode);
    conveyorOnNode->AddNext(delayNode2);
    delayNode2->AddNext(driveNode);
}
