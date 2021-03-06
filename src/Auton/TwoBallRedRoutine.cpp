#include "TwoBallRedRoutine.h"

TwoBallRedRoutine::TwoBallRedRoutine() : COREAuton("Two Ball Red Routine") {}

void TwoBallRedRoutine::AddNodes() {
    launcherOnNode = new Node (5, new LauncherAction(LAUNCHER_FORWARD));
    extendNode = new Node(5, new IntakeAction(EXTEND));
    delayNode = new Node(1, new DelayAction());
    intakeOnNode = new Node(5, new IntakeAction(OUTTAKE));
    conveyorOnNode = new Node (5, new ConveyorAction(CONVEYOR_ON));
    driveNode = new Node(10,new DriveAction(BACKWARD, 48));
    delayNode2 = new Node(1, new DelayAction());
    driveNode2 = new Node(10, new DriveAction(FORWARD, 36));
    delayNode3 = new Node(1, new DelayAction());
    launcherPunchNode = new Node (2, new LauncherAction(LAUNCH_EXTEND));
    delayNode4 = new Node(1, new DelayAction());
    launcherPunchNode2 = new Node (2, new LauncherAction(LAUNCH_RETRACT));
    delayNode5 = new Node(3, new DelayAction());
    launcherPunchNode3 = new Node (2, new LauncherAction(LAUNCH_EXTEND));
    LauncherFeedNode = new Node (5, new LauncherAction(LAUNCH_FEED));
    AddFirstNode(launcherOnNode);
    launcherOnNode->AddNext(LauncherFeedNode);
    LauncherFeedNode->AddNext(extendNode);
    extendNode->AddNext(delayNode);
    delayNode->AddNext(intakeOnNode);
    intakeOnNode->AddNext(conveyorOnNode);
    conveyorOnNode->AddNext(driveNode);
    driveNode->AddNext(delayNode2);
    delayNode2->AddNext(driveNode2);
    driveNode2->AddNext(delayNode3);
    delayNode3->AddNext(launcherPunchNode);
    launcherPunchNode->AddNext(delayNode4);
    delayNode4->AddNext(launcherPunchNode2);
    launcherPunchNode2->AddNext(delayNode5);
    delayNode5->AddNext(launcherPunchNode3);
}