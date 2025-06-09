#pragma once

#include "carAssemblyTypes.h"

class BrakeSystem
{
public:
	virtual BrakeSystemName getBrakeSystemName() = 0;
protected:

private:

};

class MandoBrakeSystem : public BrakeSystem
{
public:
	BrakeSystemName getBrakeSystemName()
	{
		return BrakeSystemName::MANDO;
	}
};

class ContinentalBrakeSystem : public BrakeSystem
{
public:
	BrakeSystemName getBrakeSystemName()
	{
		return BrakeSystemName::CONTINENTAL;
	}
};

class BoschBrakeSystem : public BrakeSystem
{
public:
	BrakeSystemName getBrakeSystemName()
	{
		return BrakeSystemName::BOSCH_B;
	}
};