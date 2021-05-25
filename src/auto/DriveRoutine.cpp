#include "DriveRoutine.h"

DriveRoutine::DriveRoutine() : COREAuton("Drive Routine") {}

void DriveRoutine::AddNodes() {
    driveNode = new Node(5, new DriveAction(FORWARD));
    AddFirstNode(driveNode);
}
