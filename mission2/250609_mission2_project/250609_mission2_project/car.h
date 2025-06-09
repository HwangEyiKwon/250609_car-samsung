#pragma once
#include "engine.h"
#include "brakeSystem.h"
#include "steeringSystem.h"

class Car
{
public:
    Car(Engine* engine, BrakeSystem* brakeSystem, SteeringSystem* steeringSystem)
        : myEngine(engine), myBrakeSystem(brakeSystem), mySteeringSystem(steeringSystem) {
    }

protected:
	Engine* myEngine;
	BrakeSystem* myBrakeSystem;
	SteeringSystem* mySteeringSystem;

private:

};

class Sedan : public Car {

};

class SUV : public Car {

};

class Truck : public Car {

};