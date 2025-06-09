#pragma once

#include "engine.h"
#include "brakeSystem.h"
#include "steeringSystem.h"
#include <string>

using namespace std;

class PartFactory {
public:
    static Engine* createEngine(string brand);
    static BrakeSystem* createBrakeSystem(string brand);
    static SteeringSystem* createSteeringSystem(string brand);
};