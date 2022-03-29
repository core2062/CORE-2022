#include "OneBallRoutine.h"


OneBallRoutine::OneBallRoutine() : COREAuton("One Ball Routine") {}

void OneBallRoutine::AddNodes() {
    delayNode = new Node(2, new DelayAction());
    delayNode2 = new Node(2, new DelayAction());
    driveNode = new Node(5,new DriveAction(BACKWARD, 15000));
    driveNode2 = new Node(5,new DriveAction(BACKWARD, 60000));
    launcherOnNode = new Node (5, new LauncherAction(LAUNCHER_FORWARD));
    launcherPunchNode = new Node (2, new LauncherAction(LAUNCH));
    AddFirstNode(launcherOnNode);
    // CORELog::LogInfo("delay complete");
    // delayNode->AddNext(driveNode);
    CORELog::LogInfo("Activated Launcher");
    launcherOnNode->AddNext(driveNode);
    CORELog::LogInfo("Drove Backwards"); 
    driveNode->AddNext(delayNode);
    delayNode->AddNext(launcherPunchNode);
    CORELog::LogInfo("Drove Again");
    launcherPunchNode->AddNext(delayNode2);
    delayNode2->AddNext(driveNode2);
}