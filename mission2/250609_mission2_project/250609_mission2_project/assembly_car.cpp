#include "gmock/gmock.h"
#include "car.h"
#include "carValidator.h"
#include "carBuilder.h"
#include "carRunner.h"

using namespace testing;

class MockEngine : public Engine {
public:
    MOCK_METHOD(EngineName, getEngineName, (), (override));
};

class MockBrakeSystem : public BrakeSystem {
public:
    MOCK_METHOD(BrakeSystemName, getBrakeSystemName, (), (override));
};

class MockSteeringSystem : public SteeringSystem {
public:
    MOCK_METHOD(SteeringSystemName, getSteeringSystemName, (), (override));
};

TEST(CarPartValidatorTest, TC1_SEDAN_CONTINENTAL) {
    CarType carType = SEDAN;
    EngineName engineName = GM;
    BrakeSystemName brakeSystemName = CONTINENTAL;
    SteeringSystemName steeringSystemName = MOBIS;

    ConcreteCarBuilder* builder = new ConcreteCarBuilder();
    Car* car = builder->setCarType(carType)
        .setEngine(engineName)
        .setBrakeSystem(brakeSystemName)
        .setSteeringSystem(steeringSystemName)
        .build();

    bool result = CarValidator::validate(car);
    CarValidator::testProducedCar(car);
    CarRunner::runProducedCar(car);

    EXPECT_FALSE(result);
}

TEST(CarPartValidatorTest, TC2_SUV_TOYOTA) {
    CarType carType = SUV;
    EngineName engineName = TOYOTA;
    BrakeSystemName brakeSystemName = CONTINENTAL;
    SteeringSystemName steeringSystemName = MOBIS;

    ConcreteCarBuilder* builder = new ConcreteCarBuilder();
    Car* car = builder->setCarType(carType)
        .setEngine(engineName)
        .setBrakeSystem(brakeSystemName)
        .setSteeringSystem(steeringSystemName)
        .build();

    bool result = CarValidator::validate(car);
    CarValidator::testProducedCar(car);
    CarRunner::runProducedCar(car);

    EXPECT_FALSE(result);
}

TEST(CarPartValidatorTest, TC3_TRUCK_WIA) {
    CarType carType = TRUCK;
    EngineName engineName = WIA;
    BrakeSystemName brakeSystemName = CONTINENTAL;
    SteeringSystemName steeringSystemName = MOBIS;

    ConcreteCarBuilder* builder = new ConcreteCarBuilder();
    Car* car = builder->setCarType(carType)
        .setEngine(engineName)
        .setBrakeSystem(brakeSystemName)
        .setSteeringSystem(steeringSystemName)
        .build();

    bool result = CarValidator::validate(car);
    CarValidator::testProducedCar(car);
    CarRunner::runProducedCar(car);

    EXPECT_FALSE(result);
}

TEST(CarPartValidatorTest, TC4_TRUCK_MANDO) {
    CarType carType = TRUCK;
    EngineName engineName = GM;
    BrakeSystemName brakeSystemName = MANDO;
    SteeringSystemName steeringSystemName = MOBIS;

    ConcreteCarBuilder* builder = new ConcreteCarBuilder();
    Car* car = builder->setCarType(carType)
        .setEngine(engineName)
        .setBrakeSystem(brakeSystemName)
        .setSteeringSystem(steeringSystemName)
        .build();

    bool result = CarValidator::validate(car);
    CarValidator::testProducedCar(car);
    CarRunner::runProducedCar(car);

    EXPECT_FALSE(result);
}

TEST(CarPartValidatorTest, TC5_BOSCH_DUO) {
    CarType carType = SEDAN;
    EngineName engineName = GM;
    BrakeSystemName brakeSystemName = BOSCH_B;
    SteeringSystemName steeringSystemName = MOBIS;

    ConcreteCarBuilder* builder = new ConcreteCarBuilder();
    Car* car = builder->setCarType(carType)
        .setEngine(engineName)
        .setBrakeSystem(brakeSystemName)
        .setSteeringSystem(steeringSystemName)
        .build();

    bool result = CarValidator::validate(car);
    CarValidator::testProducedCar(car);
    CarRunner::runProducedCar(car);

    EXPECT_FALSE(result);
}

TEST(CarPartValidatorTest, TC6_BROKEN_ENGINE) {
    CarType carType = SUV;
    EngineName engineName = BROKEN;
    BrakeSystemName brakeSystemName = CONTINENTAL;
    SteeringSystemName steeringSystemName = MOBIS;

    ConcreteCarBuilder* builder = new ConcreteCarBuilder();
    Car* car = builder->setCarType(carType)
        .setEngine(engineName)
        .setBrakeSystem(brakeSystemName)
        .setSteeringSystem(steeringSystemName)
        .build();

    bool result = CarValidator::validate(car);
    CarValidator::testProducedCar(car);
    CarRunner::runProducedCar(car);

    EXPECT_TRUE(result);
}

TEST(CarPartValidatorTestUsingMock, TC1_SEDAN_CONTINENTAL) {
    MockEngine engine;
    MockBrakeSystem brakeSystem;
    MockSteeringSystem steeringSystem;

    CarType carType = SEDAN;
    EXPECT_CALL(engine, getEngineName()).WillRepeatedly(Return(TOYOTA));
    EXPECT_CALL(brakeSystem, getBrakeSystemName()).WillRepeatedly(Return(CONTINENTAL));
    EXPECT_CALL(steeringSystem, getSteeringSystemName()).WillRepeatedly(Return(BOSCH_S));

    ConcreteCarBuilder* builder = new ConcreteCarBuilder();
    Car* car = builder->setCarType(carType)
        .setEngine(engine.getEngineName())
        .setBrakeSystem(brakeSystem.getBrakeSystemName())
        .setSteeringSystem(steeringSystem.getSteeringSystemName())
        .build();

    bool result = CarValidator::validate(car);
    CarValidator::testProducedCar(car);

    EXPECT_FALSE(result);
}

TEST(CarPartValidatorTestUsingMock, TC2_SUV_TOYOTA) {
    MockEngine engine;
    MockBrakeSystem brakeSystem;
    MockSteeringSystem steeringSystem;

    CarType carType = SUV;
    EXPECT_CALL(engine, getEngineName()).WillRepeatedly(Return(TOYOTA));
    EXPECT_CALL(brakeSystem, getBrakeSystemName()).WillRepeatedly(Return(CONTINENTAL));
    EXPECT_CALL(steeringSystem, getSteeringSystemName()).WillRepeatedly(Return(BOSCH_S));

    ConcreteCarBuilder* builder = new ConcreteCarBuilder();
    Car* car = builder->setCarType(carType)
        .setEngine(engine.getEngineName())
        .setBrakeSystem(brakeSystem.getBrakeSystemName())
        .setSteeringSystem(steeringSystem.getSteeringSystemName())
        .build();

    bool result = CarValidator::validate(car);
    CarValidator::testProducedCar(car);

    EXPECT_FALSE(result);
}

TEST(CarPartValidatorTestUsingMock, TC3_TRUCK_WIA) {
    MockEngine engine;
    MockBrakeSystem brakeSystem;
    MockSteeringSystem steeringSystem;

    CarType carType = TRUCK;
    EXPECT_CALL(engine, getEngineName()).WillRepeatedly(Return(WIA));
    EXPECT_CALL(brakeSystem, getBrakeSystemName()).WillRepeatedly(Return(CONTINENTAL));
    EXPECT_CALL(steeringSystem, getSteeringSystemName()).WillRepeatedly(Return(BOSCH_S));

    ConcreteCarBuilder* builder = new ConcreteCarBuilder();
    Car* car = builder->setCarType(carType)
        .setEngine(engine.getEngineName())
        .setBrakeSystem(brakeSystem.getBrakeSystemName())
        .setSteeringSystem(steeringSystem.getSteeringSystemName())
        .build();

    bool result = CarValidator::validate(car);
    CarValidator::testProducedCar(car);

    EXPECT_FALSE(result);
}

TEST(CarPartValidatorTestUsingMock, TC4_TRUCK_MANDO) {
    MockEngine engine;
    MockBrakeSystem brakeSystem;
    MockSteeringSystem steeringSystem;

    CarType carType = TRUCK;
    EXPECT_CALL(engine, getEngineName()).WillRepeatedly(Return(TOYOTA));
    EXPECT_CALL(brakeSystem, getBrakeSystemName()).WillRepeatedly(Return(MANDO));
    EXPECT_CALL(steeringSystem, getSteeringSystemName()).WillRepeatedly(Return(BOSCH_S));

    ConcreteCarBuilder* builder = new ConcreteCarBuilder();
    Car* car = builder->setCarType(carType)
        .setEngine(engine.getEngineName())
        .setBrakeSystem(brakeSystem.getBrakeSystemName())
        .setSteeringSystem(steeringSystem.getSteeringSystemName())
        .build();

    bool result = CarValidator::validate(car);
    CarValidator::testProducedCar(car);

    EXPECT_FALSE(result);
}

TEST(CarPartValidatorTestUsingMock, TC5_BOSCH_DUO) {
    MockEngine engine;
    MockBrakeSystem brakeSystem;
    MockSteeringSystem steeringSystem;

    CarType carType = TRUCK;
    EXPECT_CALL(engine, getEngineName()).WillRepeatedly(Return(TOYOTA));
    EXPECT_CALL(brakeSystem, getBrakeSystemName()).WillRepeatedly(Return(BOSCH_B));
    EXPECT_CALL(steeringSystem, getSteeringSystemName()).WillRepeatedly(Return(MOBIS));

    ConcreteCarBuilder* builder = new ConcreteCarBuilder();
    Car* car = builder->setCarType(carType)
        .setEngine(engine.getEngineName())
        .setBrakeSystem(brakeSystem.getBrakeSystemName())
        .setSteeringSystem(steeringSystem.getSteeringSystemName())
        .build();

    bool result = CarValidator::validate(car);
    CarValidator::testProducedCar(car);

    EXPECT_FALSE(result);
}

TEST(CarPartValidatorTestUsingMock, TC6_BROKEN_ENGINE) {
    MockEngine engine;
    MockBrakeSystem brakeSystem;
    MockSteeringSystem steeringSystem;

    CarType carType = SEDAN;
    EXPECT_CALL(engine, getEngineName()).WillRepeatedly(Return(BROKEN));
    EXPECT_CALL(brakeSystem, getBrakeSystemName()).WillRepeatedly(Return(BOSCH_B));
    EXPECT_CALL(steeringSystem, getSteeringSystemName()).WillRepeatedly(Return(BOSCH_S));

    ConcreteCarBuilder* builder = new ConcreteCarBuilder();
    Car* car = builder->setCarType(carType)
        .setEngine(engine.getEngineName())
        .setBrakeSystem(brakeSystem.getBrakeSystemName())
        .setSteeringSystem(steeringSystem.getSteeringSystemName())
        .build();

    bool result = CarValidator::validate(car);
    CarValidator::testProducedCar(car);

    EXPECT_TRUE(result);
}