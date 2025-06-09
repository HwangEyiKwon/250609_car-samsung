#pragma once

#include "carAssemblyTypes.h"

class Engine
{
public:
	virtual EngineName getEngineName() = 0;
protected:

private:

};

class GMEngine : public Engine
{
public:
	EngineName getEngineName()
	{
		return EngineName::GM;
	}
};

class ToyotaEngine : public Engine
{
public:
	EngineName getEngineName()
	{
		return EngineName::TOYOTA;
	}
};

class WIAEngine : public Engine
{
public:
	EngineName getEngineName()
	{
		return EngineName::WIA;
	}
};

class BrokenEngine : public Engine
{
public:
	EngineName getEngineName()
	{
		return EngineName::BROKEN;
	}
};