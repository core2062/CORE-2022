#include "OneBallRoutine.h"


OneBallRoutine::OneBallRoutine() : COREAuton("One Ball Routine") {}

void OneBallRoutine::AddNodes() {
    delayNode = new Node(5, new DelayAction());
    driveNode = new Node(5,new DriveAction(BACKWARD, 75000));
    launcherOnNode = new Node (5, new LauncherAction(LAUNCHER_FORWARD));
    launcherPunchNode = new Node (5, new LauncherAction(LAUNCH));
    AddFirstNode(launcherOnNode);
    // CORELog::LogInfo("delay complete");
    // delayNode->AddNext(driveNode);
    CORELog::LogInfo("Activated Launcher");
    launcherOnNode->AddNext(driveNode);
    CORELog::LogInfo("Drove Backwards");
    driveNode->AddNext(launcherPunchNode);
    launcherPunchNode->AddNext(delayNode);
    CORELog::LogInfo("Drove Again");
}