#include "TestRoutine.h"

TestRoutine::TestRoutine() : COREAuton("Test Routine") {}

void TestRoutine::AddNodes() {
    testNode = new Node(5, new TurretTrackingAction(TRACKING_ON));
    delayNode = new Node(3, new DelayAction());
    testNode2 = new Node(5, new TurretTrackingAction(TRACKING_OFF));
    AddFirstNode(testNode);
    testNode->AddNext(testNode2);
    //delayNode->AddNext(testNode2);
}