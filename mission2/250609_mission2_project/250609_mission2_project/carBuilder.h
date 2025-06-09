#pragma once

#include "carAssemblyTypes.h"
#include "car.h"
#include "partFactory.h"
#include "carValidator.h"

class CarBuilder {
public:
    virtual CarBuilder& setEngine(EngineName engineName) = 0;
    virtual CarBuilder& setBrakeSystem(BrakeSystemName brakeSystemName) = 0;
    virtual CarBuilder& setSteeringSystem(SteeringSystemName steeringSystemName) = 0;
    virtual CarBuilder& setCarType(CarType carType) = 0;

    virtual Car* build() = 0;
};

class ConcreteCarBuilder : public CarBuilder {
private:
    EngineName engineName;
    BrakeSystemName brakeSystemName;
    SteeringSystemName steeringSystemName;
    CarType carType;

public:
    CarBuilder& setEngine(EngineName engineName) {
        this->engineName = engineName;
        return *this;
    }

    CarBuilder& setBrakeSystem(BrakeSystemName brakeSystemName) {
        this->brakeSystemName = brakeSystemName;
        return *this;
    }

    CarBuilder& setSteeringSystem(SteeringSystemName steeringSystemName) {
        this->steeringSystemName = steeringSystemName;
        return *this;
    }

    CarBuilder& setCarType(CarType carType) {
        this->carType = carType;
        return *this;
    }

    Car* build() override {
        Engine* engine = PartFactory::createEngine(engineName);
        BrakeSystem* brakeSystem = PartFactory::createBrakeSystem(brakeSystemName);
        SteeringSystem* steeringSystem = PartFactory::createSteeringSystem(steeringSystemName);

        if (carType == SEDAN) return new Sedan(engine, brakeSystem, steeringSystem);
        if (carType == SUV) return new Suv(engine, brakeSystem, steeringSystem);
        if (carType == TRUCK) return new Truck(engine, brakeSystem, steeringSystem);
    }
};