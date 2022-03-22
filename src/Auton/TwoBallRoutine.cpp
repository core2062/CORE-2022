// #include "TwoBallRoutine.h"

// TwoBallRoutine::TwoBallRoutine() : COREAuton("Two Ball Routine") {}

// void TwoBallRoutine::AddNodes() {
//     delayNode = new Node(5, new DelayAction());
//     extendNode = new Node(5, new IntakeAction(EXTEND));
//     driveNode = new Node(5,new DriveAction(BACKWARD));
//     intakeOnNode = new Node(5, new IntakeAction(INTAKE));
//     conveyorOnNode = new Node (5, new ConveyorAction(CONVEYOR_ON));
//     launcherOnNode = new Node (5, new LauncherAction(LAUNCHER_FORWARD));
//     driveNode2 = new Node(5, new DriveAction(LEFT_TURN, 15));
//     AddFirstNode(delayNode);
//     delayNode->AddNext(extendNode);
//     extendNode->AddNext(driveNode);
//     driveNode->AddNext(intakeOnNode);
//     intakeOnNode->AddNext(delayNode);
//     delayNode->AddNext(driveNode2);
//     driveNode2->AddNext(launcherOnNode);
//     launcherOnNode->AddNext(delayNode);
//     delayNode->AddNext(conveyorOnNode);

// }