#pragma once

#include "carAssemblyTypes.h"

class SteeringSystem
{
public:
	virtual SteeringSystemName getSteeringSystemName() = 0;
protected:

private:

};

class BoschSteeringSystem : public SteeringSystem
{
public:
	SteeringSystemName getSteeringSystemName()
	{
		return SteeringSystemName::BOSCH_S;
	}
};

class MobisSteeringSystem : public SteeringSystem
{
public:
	SteeringSystemName getSteeringSystemName()
	{
		return SteeringSystemName::MOBIS;
	}
};
