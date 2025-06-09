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

	virtual CarType getCarType() = 0;

	Engine* getEngine() { return myEngine; };
	BrakeSystem* getBrakeSystem() { return myBrakeSystem; };
	SteeringSystem* getSteeringSystem() { return mySteeringSystem; };

protected:
	Engine* myEngine;
	BrakeSystem* myBrakeSystem;
	SteeringSystem* mySteeringSystem;

private:

};

class Sedan : public Car {
public:
	Sedan(Engine* engine, BrakeSystem* brakeSystem, SteeringSystem* steeringSystem)
		: Car(engine, brakeSystem, steeringSystem)
	{
	};

	CarType getCarType()
	{
		return CarType::SEDAN;
	}
};

class Suv : public Car {
public:
	Suv(Engine* engine, BrakeSystem* brakeSystem, SteeringSystem* steeringSystem)
		: Car(engine, brakeSystem, steeringSystem)
	{
	};

	CarType getCarType()
	{
		return CarType::SUV;
	}
};

class Truck : public Car {
public:
	Truck(Engine* engine, BrakeSystem* brakeSystem, SteeringSystem* steeringSystem)
		: Car(engine, brakeSystem, steeringSystem)
	{
	};

	CarType getCarType()
	{
		return CarType::TRUCK;
	}
};