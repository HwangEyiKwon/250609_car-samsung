#include "carRunner.h"

void CarRunner::runProducedCar(Car* car)
{
    Engine* engine = car->getEngine();
    BrakeSystem* brakeSystem = car->getBrakeSystem();
    SteeringSystem* steeringSystem = car->getSteeringSystem();

    if (CarValidator::validate(car) == false)
    {
        printf("자동차가 동작되지 않습니다\n");
        return;
    }

    if (engine->getEngineName() == BROKEN)
    {
        printf("엔진이 고장나있습니다.\n");
        printf("자동차가 움직이지 않습니다.\n");
        return;
    }

    if (car->getCarType() == SEDAN)                             printf("Car Type : Sedan\n");
    else if (car->getCarType() == SUV)                          printf("Car Type : SUV\n");
    else if (car->getCarType() == TRUCK)                        printf("Car Type : Truck\n");

    if (engine->getEngineName() == GM)                          printf("Engine : GM\n");
    else if (engine->getEngineName() == TOYOTA)                 printf("Engine : TOYOTA\n");
    else if (engine->getEngineName() == WIA)                    printf("Engine : WIA\n");

    if (brakeSystem->getBrakeSystemName() == MANDO)             printf("Brake System : Mando");
    else if (brakeSystem->getBrakeSystemName() == CONTINENTAL)  printf("Brake System : Continental\n");
    else if (brakeSystem->getBrakeSystemName() == BOSCH_B)      printf("Brake System : Bosch\n");

    if (steeringSystem->getSteeringSystemName() == BOSCH_S)     printf("SteeringSystem : Bosch\n");
    else if (steeringSystem->getSteeringSystemName() == MOBIS)  printf("SteeringSystem : Mobis\n");

    printf("자동차가 동작됩니다.\n");
}