#include "TwoBallWithPickup.h"

TwoBallWithPickup::TwoBallWithPickup() : COREAuton("Two Ball Fire + Pickup Routine") {}

void TwoBallWithPickup::AddNodes() {
    driveNode1 = new Node(5, new DriveAction(BACKWARD));
    driveNode2 = new Node(5, new DriveAction(LEFT_TURN,15)); // TODO: Check which direction it needs to turn; Check turn amount
    driveNode3 = new Node(5, new DriveAction(LEFT_TURN,15)); // TODO: Check which direction it needs to turn; Check turn amount
    driveNode4 = new Node(5, new DriveAction(BACKWARD));
    intakeNode1 = new Node(5, new IntakeAction(INTAKE));
    intakeNode2 = new Node(5, new IntakeAction(STOP));
    delayNode1 = new Node(1, new DelayAction()); // TODO: Figure out length of delay
    delayNode2 = new Node(1, new DelayAction()); // TODO: Figure out length of delay
    delayNode3 = new Node(1, new DelayAction()); // TODO: Figure out length of delay
    delayNode4 = new Node(1, new DelayAction()); // TODO: Figure out length of delay
    conveyorNode1 = new Node(5, new ConveyorAction(CONVEYOR_ON));
    conveyorNode2 = new Node(5, new ConveyorAction(CONVEYOR_OFF));
    launcherNode1 = new Node(5, new LauncherAction(LAUNCHER_FORWARD));
    launcherNode2 = new Node(5, new LauncherAction(LAUNCHER_OFF));
    
    AddFirstNode(driveNode1);
    driveNode1->AddNext(intakeNode1);
    intakeNode1->AddNext(delayNode1);
    delayNode1->AddNext(conveyorNode1);
    conveyorNode1->AddNext(delayNode2);
    delayNode2->AddNext(driveNode2);
    driveNode2->AddNext(launcherNode1);
    launcherNode1->AddNext(delayNode3);
    delayNode3->AddNext(launcherNode2);
    launcherNode1->AddNext(driveNode3);
    driveNode3->AddNext(driveNode4);
    driveNode4->AddNext(delayNode4);
    delayNode4->AddNext(intakeNode2);
    intakeNode2->AddNext(conveyorNode2);
}