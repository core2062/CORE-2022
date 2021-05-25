#pragma once

#include <string>
#include <CORERobotLib.h>
#include "DriveAction.h"
// #include "AutonActionTest.h"

using namespace CORE;
using namespace std;

class DriveRoutine: public COREAuton {
public:
    DriveRoutine();
    void AddNodes() override;
private:
    Node * driveNode;
};
