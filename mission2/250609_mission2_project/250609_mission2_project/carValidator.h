#include "car.h"
#include <stdio.h>

class CarValidator {
public:
    static bool validate(Car* car) {
        Engine* engine = car->getEngine();
        BrakeSystem* brakeSystem = car->getBrakeSystem();
        SteeringSystem* steeringSystem = car->getSteeringSystem();

        if (car->getCarType() == SEDAN && brakeSystem->getBrakeSystemName() == CONTINENTAL)                     return false;
        if (car->getCarType() == SUV && engine->getEngineName() == TOYOTA)                                      return false;
        if (car->getCarType() == TRUCK && engine->getEngineName() == WIA)                                       return false;
        if (car->getCarType() == TRUCK && brakeSystem->getBrakeSystemName() == MANDO)                           return false;
        if (brakeSystem->getBrakeSystemName() == BOSCH_B && steeringSystem->getSteeringSystemName() != BOSCH_S) return false;
        
        return true;
    }

    static void testProducedCar(Car* car) {
        Engine* engine = car->getEngine();
        BrakeSystem* brakeSystem = car->getBrakeSystem();
        SteeringSystem* steeringSystem = car->getSteeringSystem();

        if (car->getCarType() == SEDAN && brakeSystem->getBrakeSystemName() == CONTINENTAL)
        {
            printf("자동차 부품 조합 테스트 결과 : FAIL\n");
            printf("Sedan에는 Continental제동장치 사용 불가\n");
            return;
        }
        if (car->getCarType() == SUV && engine->getEngineName() == TOYOTA)
        {
            printf("자동차 부품 조합 테스트 결과 : FAIL\n");
            printf("SUV에는 TOYOTA엔진 사용 불가\n");
            return;
        }
        if (car->getCarType() == TRUCK && engine->getEngineName() == WIA)
        {
            printf("자동차 부품 조합 테스트 결과 : FAIL\n");
            printf("Truck에는 WIA엔진 사용 불가\n");
            return;
        }
        if (car->getCarType() == TRUCK && brakeSystem->getBrakeSystemName() == MANDO)
        {
            printf("자동차 부품 조합 테스트 결과 : FAIL\n");
            printf("Truck에는 Mando제동장치 사용 불가\n");
            return;
        }
        if (brakeSystem->getBrakeSystemName() == BOSCH_B && steeringSystem->getSteeringSystemName() != BOSCH_S)
        {
            printf("자동차 부품 조합 테스트 결과 : FAIL\n");
            printf("Bosch제동장치에는 Bosch 조향장치 이외 사용 불가\n");
            return;
        }

        printf("자동차 부품 조합 테스트 결과 : PASS\n");
    }
};