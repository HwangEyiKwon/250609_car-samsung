#pragma once

#define CLEAR_SCREEN "\033[H\033[2J"

enum QuesionType
{
    First_Q,
    CarType_Q = First_Q,
    Engine_Q,
    BrakeSystem_Q,
    SteeringSystem_Q,
    Run_Test,
};

enum CarType
{
    SEDAN = 1,
    SUV,
    TRUCK
};

enum EngineName
{
    GM = 1,
    TOYOTA,
    WIA,
    BROKEN
};

enum BrakeSystemName
{
    MANDO = 1,
    CONTINENTAL,
    BOSCH_B
};

enum SteeringSystemName
{
    BOSCH_S = 1,
    MOBIS
};

enum ReturnFlag
{
    NORMAL,
    BREAK,
    CONTINUE,
};