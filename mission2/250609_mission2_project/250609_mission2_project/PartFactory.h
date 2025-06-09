#pragma once

#include "engine.h"
#include "brakeSystem.h"
#include "steeringSystem.h"
#include <string>

using namespace std;

class PartFactory {
public:
    static Engine* createEngine(EngineName engineName);
    static BrakeSystem* createBrakeSystem(BrakeSystemName brakeSystemName);
    static SteeringSystem* createSteeringSystem(SteeringSystemName steeringSystemName);
};