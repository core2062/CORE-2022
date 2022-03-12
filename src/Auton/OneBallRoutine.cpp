#include "OneBallRoutine.h"


OneBallRoutine::OneBallRoutine() : COREAuton("One Ball Routine") {}

void OneBallRoutine::AddNodes() {
    delayNode = new Node(5, new DelayAction());
    driveNode = new Node(5,new DriveAction(BACKWARD));
    launcherOnNode = new Node (5, new LauncherAction(LAUNCHER_FORWARD));
    launcherPunchNode = new Node (5, new LauncherAction(LAUNCHER_PUNCH_IN));
    AddFirstNode(driveNode);
    // CORELog::LogInfo("delay complete");
    // delayNode->AddNext(driveNode);
    CORELog::LogInfo("drove Backward");
    driveNode->AddNext(launcherPunchNode);
    CORELog::LogInfo("PUNCH TRIGGERED");
    launcherPunchNode->AddNext(launcherOnNode);
    CORELog::LogInfo("Launched");
    launcherOnNode->AddNext(delayNode);
    CORELog::LogInfo("Delayed Again");
}