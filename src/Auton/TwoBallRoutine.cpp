#include "TwoBallRoutine.h"

TwoBallRoutine::TwoBallRoutine() : COREAuton("Two Ball Routine") {}

void TwoBallRoutine::AddNodes() {
    driveNode1 = new Node(5, new DriveAction(BACKWARD,12));
    launcherNode = new Node(5, new LauncherAction(LAUNCHER_FORWARD));
    punchNode1 = new Node(5, new LauncherAction(LAUNCH));
    delayNode = new Node(2, new DelayAction());
    intakeOutNode = new Node(5, new IntakeAction(EXTEND));
    intakeOnNode = new Node(5, new IntakeAction(INTAKE));
    conveyorNode = new Node(5, new ConveyorAction(CONVEYOR_ON));
    driveNode2 = new Node(5, new DriveAction(BACKWARD,24));
    intakeOffNode = new Node(5, new IntakeAction(STOP));
    intakeInNode = new Node(5, new IntakeAction(RETRACT));
    driveNode3 = new Node(5, new DriveAction(FORWARD,24));
    punchNode2 = new Node(5, new LauncherAction(LAUNCH));
    driveNode4 = new Node(5, new DriveAction(BACKWARD,36));

    AddFirstNode(driveNode1);
    driveNode1->AddNext(launcherNode);
    launcherNode->AddNext(punchNode1);
    punchNode1->AddNext(delayNode);
    delayNode->AddNext(intakeOutNode);
    intakeOutNode->AddNext(intakeOnNode);
    intakeOnNode->AddNext(conveyorNode);
    conveyorNode->AddNext(driveNode2);
    driveNode2->AddNext(intakeOffNode);
    intakeOffNode->AddNext(intakeInNode);
    intakeInNode->AddNext(driveNode3);
    driveNode3->AddNext(punchNode2);
    punchNode2->AddNext(driveNode4);
}