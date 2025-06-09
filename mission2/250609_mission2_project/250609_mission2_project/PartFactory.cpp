#include "PartFactory.h"

Engine* PartFactory::createEngine(string brand) {
    if (brand == "GM")      return new GMEngine();
    if (brand == "Toyota")  return new ToyotaEngine();
    if (brand == "WIA")     return new WIAEngine();
}

BrakeSystem* PartFactory::createBrakeSystem(string brand) {
    if (brand == "Mando")       return new MandoBrakeSystem();
    if (brand == "Continental") return new ContinentalBrakeSystem();
    if (brand == "Bosch")       return new BoschBrakeSystem();
}

SteeringSystem* PartFactory::createSteeringSystem(string brand) {
    if (brand == "Bosch") return new BoschSteeringSystem();
    if (brand == "Mobis") return new MobisSteeringSystem();
}
