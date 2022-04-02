// #include "ThreeBallRoutine.h"

// ThreeBallRoutine::ThreeBallRoutine() : COREAuton("Three Ball Fire Routine") {}

// void ThreeBallRoutine::AddNodes() {
//     driveNode1 = new Node(5, new DriveAction(BACKWARD));
//     extendNode = new Node(5, new IntakeAction(EXTEND));
//     driveNode2 = new Node(5, new DriveAction(LEFT_TURN,15)); // TODO: Check which direction it needs to turn; Check turn amount
//     driveNode3 = new Node(5, new DriveAction(LEFT_TURN,15)); // TODO: Check which direction it needs to turn; Check turn amount
//     driveNode4 = new Node(5, new DriveAction(BACKWARD));
//     driveNode5 = new Node(5, new DriveAction(RIGHT_TURN,15)); // TODO: Check which direction it needs to turn; Check turn amount
//     intakeNode1 = new Node(5, new IntakeAction(INTAKE));
//     intakeNode2 = new Node(5, new IntakeAction(STOP));
//     delayNode1 = new Node(1, new DelayAction()); // TODO: Figure out length of delay
//     delayNode2 = new Node(1, new DelayAction()); // TODO: Figure out length of delay
//     delayNode3 = new Node(1, new DelayAction()); // TODO: Figure out length of delay
//     delayNode4 = new Node(1, new DelayAction()); // TODO: Figure out length of delay
//     delayNode5 = new Node(1, new DelayAction()); // TODO: Figure out length of delay
//     conveyorNode1 = new Node(5, new ConveyorAction(CONVEYOR_ON));
//     conveyorNode2 = new Node(5, new ConveyorAction(CONVEYOR_OFF));
//     launcherNode1 = new Node(5, new LauncherAction(LAUNCHER_FORWARD));
//     launcherNode2 = new Node(5, new LauncherAction(LAUNCHER_OFF));
//     launcherNode3 = new Node(5, new LauncherAction(LAUNCHER_FORWARD));
//     launcherNode4 = new Node(5, new LauncherAction(LAUNCHER_OFF));
//     launcherNode5 = new Node(5, new LauncherAction(LAUNCHER_FORWARD));
//     launcherNode6 = new Node(5, new LauncherAction(LAUNCHER_OFF));
//     launcherPunchInNode1 = new Node(5, new LauncherAction(LAUNCHER_PUNCH_IN));
//     launcherPunchInNode2 = new Node(5, new LauncherAction(LAUNCHER_PUNCH_IN));
//     launcherPunchInNode3 = new Node(5, new LauncherAction(LAUNCHER_PUNCH_IN));
//     launcherPunchOutNode1 = new Node(5, new LauncherAction(LAUNCHER_PUNCH_OUT));
//     launcherPunchOutNode2 = new Node(5, new LauncherAction(LAUNCHER_PUNCH_OUT));
//     launcherPunchOutNode3 = new Node(5, new LauncherAction(LAUNCHER_PUNCH_OUT));

//     AddFirstNode(driveNode1);
//     driveNode1->AddNext(extendNode);
//     extendNode->AddNext(intakeNode1);
//     intakeNode1->AddNext(delayNode1);
//     delayNode1->AddNext(conveyorNode1);
//     conveyorNode1->AddNext(delayNode2);
//     delayNode2->AddNext(driveNode2);
//     driveNode2->AddNext(launcherPunchInNode1);
//     launcherPunchInNode1->AddNext(launcherNode1);
//     launcherNode1->AddNext(delayNode3);
//     delayNode3->AddNext(launcherPunchOutNode1);
//     launcherPunchOutNode1->AddNext(launcherNode2);
//     launcherNode2->AddNext(launcherPunchInNode2);
//     launcherPunchInNode2->AddNext(launcherNode3);
//     launcherNode3->AddNext(delayNode4);
//     delayNode4->AddNext(launcherPunchOutNode2);
//     launcherPunchOutNode2->AddNext(launcherNode4);
//     launcherNode4->AddNext(driveNode3);
//     driveNode3->AddNext(driveNode4);
//     driveNode4->AddNext(driveNode5);
//     driveNode5->AddNext(launcherPunchInNode3);
//     launcherPunchInNode3->AddNext(launcherNode5);
//     launcherNode5->AddNext(delayNode4);
//     delayNode5->AddNext(launcherPunchOutNode3);
//     launcherPunchOutNode3->AddNext(launcherNode6);
//     launcherNode6->AddNext(intakeNode2);
//     intakeNode2->AddNext(conveyorNode2);
// }