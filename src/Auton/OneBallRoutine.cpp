#include "OneBallRoutine.h"


OneBallRoutine::OneBallRoutine() : COREAuton("One Ball Routine") {}

void OneBallRoutine::AddNodes() {
    delayNode = new Node(5, new DelayAction());
    driveNode = new Node(5,new DriveAction(BACKWARD));
    launcherOnNode = new Node (5, new LauncherAction(LAUNCHER_FORWARD));
    launcherPunchNode = new Node (5, new LauncherAction(LAUNCH));
    AddFirstNode(driveNode);
    // CORELog::LogInfo("delay complete");
    // delayNode->AddNext(driveNode);
    CORELog::LogInfo("drove Backward");
    driveNode->AddNext(launcherOnNode);
    CORELog::LogInfo("PUNCH TRIGGERED");
    launcherOnNode->AddNext(launcherPunchNode);
    CORELog::LogInfo("Launched");
    launcherPunchNode->AddNext(delayNode);
    CORELog::LogInfo("Delayed Again");
}