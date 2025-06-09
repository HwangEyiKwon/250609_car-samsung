#include "partFactory.h"

Engine* PartFactory::createEngine(EngineName engineName) {
    if (engineName == GM)      return new GMEngine();
    if (engineName == TOYOTA)  return new ToyotaEngine();
    if (engineName == WIA)     return new WIAEngine();
    if (engineName == BROKEN)  return new BrokenEngine();
    else                       return nullptr;
}

BrakeSystem* PartFactory::createBrakeSystem(BrakeSystemName brakeSystemName) {
    if (brakeSystemName == MANDO)       return new MandoBrakeSystem();
    if (brakeSystemName == CONTINENTAL) return new ContinentalBrakeSystem();
    if (brakeSystemName == BOSCH_B)     return new BoschBrakeSystem();
    else                                return nullptr;
}

SteeringSystem* PartFactory::createSteeringSystem(SteeringSystemName steeringSystemName) {
    if (steeringSystemName == BOSCH_S) return new BoschSteeringSystem();
    if (steeringSystemName == MOBIS)   return new MobisSteeringSystem();
    else                               return nullptr;
}
