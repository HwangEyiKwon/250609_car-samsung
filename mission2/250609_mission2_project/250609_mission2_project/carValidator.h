#pragma once

#include "car.h"
#include <stdio.h>

class CarValidator {
public:
    static bool validate(Car* car);
    static void testProducedCar(Car* car);
};