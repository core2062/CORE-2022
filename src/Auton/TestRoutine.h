#pragma once

#include <string>
#include <CORERobotLib.h>
// Include Actions being used
#include "LauncherAction.h"

using namespace CORE;
using namespace std;

class TestRoutine: public COREAuton {
public:
    TestRoutine();
    void AddNodes() override;
private:
};