#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define CLEAR_SCREEN "\033[H\033[2J"

enum QuestionType
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

enum Engine
{
    GM = 1,
    TOYOTA,
    WIA,
    BROKEN
};

enum BrakeSystem
{
    MANDO = 1,
    CONTINENTAL,
    BOSCH_B
};

enum SteeringSystem
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

int inputDataStack[10];

// delay function
void delayMilliSecond(int milliSecond);

// execution function
void executeActionByStep(int& step, int answer);
void selectCarType(CarType carType);
void selectEngine(Engine engine);
void selectBrakeSystem(BrakeSystem brakeSystem);
void selectSteeringSystem(SteeringSystem steeringSystem);
void runProducedCar();
void testProducedCar();

// input function
ReturnFlag getAndCheckInputData(char  inputBuf[100], int& answer, int& step);
bool checkReturnMenuInput(int answer, int& step);
bool checkInvalidInput(char* checkNumber, int step, int answer);
bool checkExitInput(char inputBuf[100]);
void getInputData(char inputBuf[100]);

// print question function
void printQuestionByStep(int step);
void printRunTestQuestion();
void printSteeringSystemQuestion();
void printBrakeSystemQuestion();
void printEngineQuestion();
void printCarTypeQuestion();

void delayMilliSecond(int milliSecond)
{
    volatile int delaySum = 0;

    const int NANO_SECOND_LOOP = 1000;
    const int MICRO_SECOND_LOOP = 1000;

    for (int nanoSecondLoopIdx = 0; nanoSecondLoopIdx < NANO_SECOND_LOOP; nanoSecondLoopIdx++)
    {
        for (int microSecondLoopIdx = 0; microSecondLoopIdx < MICRO_SECOND_LOOP; microSecondLoopIdx++)
        {
            for (int milliSecondLoopIdx = 0; milliSecondLoopIdx < milliSecond; milliSecondLoopIdx++)
            {
                delaySum++;
            }
        }
    }
}

int main()
{
    char inputBuf[100];
    int step = First_Q;

    while (1)
    {
        // step 1. print question
        printQuestionByStep(step);

        // step 2. get and check input data
        int answer;
        ReturnFlag retFlag = getAndCheckInputData(inputBuf, answer, step);
        if (retFlag == BREAK) break;
        if (retFlag == CONTINUE) continue;

        // step 3. execute action
        executeActionByStep(step, answer);
    }
}

void printQuestionByStep(int step)
{
    switch (step)
    {
    case CarType_Q:
        printCarTypeQuestion();
        break;
    case Engine_Q:
        printEngineQuestion();
        break;
    case BrakeSystem_Q:
        printBrakeSystemQuestion();
        break;
    case SteeringSystem_Q:
        printSteeringSystemQuestion();
        break;
    case Run_Test:
        printRunTestQuestion();
        break;
    default:
        break;
    }
}

ReturnFlag getAndCheckInputData(char  inputBuf[100], int& answer, int& step)
{
    getInputData(inputBuf);

    char* checkNumber; // 숫자로 된 대답인지 확인하기 위한 변수
    answer = strtol(inputBuf, &checkNumber, 10); // 문자열을 10진수로 변환

    // exit 입력되었는지 확인
    if (true == checkExitInput(inputBuf)) return BREAK;
    // invalid input이 입력되었는지 확인
    if (true == checkInvalidInput(checkNumber, step, answer)) return CONTINUE;
    // return menu input이 입력되었는지 확인
    if (true == checkReturnMenuInput(answer, step)) return CONTINUE;

    return NORMAL;
}

void executeActionByStep(int& step, int answer)
{
    if (step == CarType_Q)
    {
        selectCarType(static_cast<CarType>(answer));
        delayMilliSecond(800);
        step = Engine_Q;
    }
    else if (step == Engine_Q)
    {
        selectEngine(static_cast<Engine>(answer));
        delayMilliSecond(800);
        step = BrakeSystem_Q;
    }
    else if (step == BrakeSystem_Q)
    {
        selectBrakeSystem(static_cast<BrakeSystem>(answer));
        delayMilliSecond(800);
        step = SteeringSystem_Q;
    }
    else if (step == SteeringSystem_Q)
    {
        selectSteeringSystem(static_cast<SteeringSystem>(answer));
        delayMilliSecond(800);
        step = Run_Test;
    }
    else if (step == Run_Test && answer == 1)
    {
        runProducedCar();
        delayMilliSecond(2000);
    }
    else if (step == Run_Test && answer == 2)
    {
        printf("Test...\n");
        delayMilliSecond(1500);
        testProducedCar();
        delayMilliSecond(2000);
    }
}

bool checkReturnMenuInput(int answer, int& step)
{
    // 처음으로 돌아가기
    if (answer == 0 && step == Run_Test)
    {
        step = CarType_Q;
        return true;
    }

    // 이전으로 돌아가기
    if (answer == 0 && step >= 1)
    {
        step -= 1;
        return true;
    }

    return false;
}

bool checkInvalidInput(char* checkNumber, int step, int answer)
{
    if (*checkNumber != '\0')
    {
        printf("ERROR :: 숫자만 입력 가능\n");
        delayMilliSecond(800);
        return true;
    }

    if (step == CarType_Q && !(answer >= 1 && answer <= 3))
    {
        printf("ERROR :: 차량 타입은 1 ~ 3 범위만 선택 가능\n");
        delayMilliSecond(800);
        return true;
    }

    if (step == Engine_Q && !(answer >= 0 && answer <= 4))
    {
        printf("ERROR :: 엔진은 1 ~ 4 범위만 선택 가능\n");
        delayMilliSecond(800);
        return true;
    }

    if (step == BrakeSystem_Q && !(answer >= 0 && answer <= 3))
    {
        printf("ERROR :: 제동장치는 1 ~ 3 범위만 선택 가능\n");
        delayMilliSecond(800);
        return true;
    }

    if (step == SteeringSystem_Q && !(answer >= 0 && answer <= 2))
    {
        printf("ERROR :: 조향장치는 1 ~ 2 범위만 선택 가능\n");
        delayMilliSecond(800);
        return true;
    }

    if (step == Run_Test && !(answer >= 0 && answer <= 2))
    {
        printf("ERROR :: Run 또는 Test 중 하나를 선택 필요\n");
        delayMilliSecond(800);
        return true;
    }

    return false;
}

bool checkExitInput(char inputBuf[100])
{
    if (strcmp(inputBuf, "exit") == 0)
    {
        printf("바이바이\n");
        return true;
    }

    return false;
}

void getInputData(char buf[100])
{
    printf("INPUT > ");
    fgets(buf, sizeof(buf), stdin);

    // 엔터 개행문자 제거
    char* context = nullptr;
    strtok_s(buf, "\r", &context);
    strtok_s(buf, "\n", &context);
}

void printRunTestQuestion()
{
    printf(CLEAR_SCREEN);
    printf("멋진 차량이 완성되었습니다.\n");
    printf("어떤 동작을 할까요?\n");
    printf("0. 처음 화면으로 돌아가기\n");
    printf("1. RUN\n");
    printf("2. Test\n");
    printf("===============================\n");
}

void printSteeringSystemQuestion()
{
    printf(CLEAR_SCREEN);
    printf("어떤 조향장치를 선택할까요?\n");
    printf("0. 뒤로가기\n");
    printf("1. BOSCH\n");
    printf("2. MOBIS\n");
    printf("===============================\n");
}

void printBrakeSystemQuestion()
{
    printf(CLEAR_SCREEN);
    printf("어떤 제동장치를 선택할까요?\n");
    printf("0. 뒤로가기\n");
    printf("1. MANDO\n");
    printf("2. CONTINENTAL\n");
    printf("3. BOSCH\n");
    printf("===============================\n");
}

void printEngineQuestion()
{
    printf(CLEAR_SCREEN);
    printf("어떤 엔진을 탑재할까요?\n");
    printf("0. 뒤로가기\n");
    printf("1. GM\n");
    printf("2. TOYOTA\n");
    printf("3. WIA\n");
    printf("4. 고장난 엔진\n");
    printf("===============================\n");
}

void printCarTypeQuestion()
{
    printf(CLEAR_SCREEN);

    printf("        ______________\n");
    printf("       /|            | \n");
    printf("  ____/_|_____________|____\n");
    printf(" |                      O  |\n");
    printf(" '-(@)----------------(@)--'\n");
    printf("===============================\n");
    printf("어떤 차량 타입을 선택할까요?\n");
    printf("1. Sedan\n");
    printf("2. SUV\n");
    printf("3. Truck\n");
    printf("===============================\n");
}

void selectCarType(CarType carType)
{
    inputDataStack[CarType_Q] = carType;
    if (carType == CarType::SEDAN)
        printf("차량 타입으로 Sedan을 선택하셨습니다.\n");
    else if (carType == CarType::SUV)
        printf("차량 타입으로 SUV을 선택하셨습니다.\n");
    else if (carType == CarType::TRUCK)
        printf("차량 타입으로 Truck을 선택하셨습니다.\n");
}

void selectEngine(Engine engine)
{
    inputDataStack[Engine_Q] = engine;
    if (engine == Engine::GM)
        printf("GM 엔진을 선택하셨습니다.\n");
    else if (engine == Engine::TOYOTA)
        printf("TOYOTA 엔진을 선택하셨습니다.\n");
    else if (engine == Engine::WIA)
        printf("WIA 엔진을 선택하셨습니다.\n");
}

void selectBrakeSystem(BrakeSystem brakeSystem)
{
    inputDataStack[BrakeSystem_Q] = brakeSystem;
    if (brakeSystem == BrakeSystem::MANDO)
        printf("MANDO 제동장치를 선택하셨습니다.\n");
    else if (brakeSystem == BrakeSystem::CONTINENTAL)
        printf("CONTINENTAL 제동장치를 선택하셨습니다.\n");
    else if (brakeSystem == BrakeSystem::BOSCH_B)
        printf("BOSCH 제동장치를 선택하셨습니다.\n");
}

void selectSteeringSystem(SteeringSystem steeringSystem)
{
    inputDataStack[SteeringSystem_Q] = steeringSystem;
    if (steeringSystem == SteeringSystem::BOSCH_S)
        printf("BOSCH 조향장치를 선택하셨습니다.\n");
    else if (steeringSystem == SteeringSystem::MOBIS)
        printf("MOBIS 조향장치를 선택하셨습니다.\n");
}

int isValidAssemblyCheck()
{
    if (inputDataStack[CarType_Q] == SEDAN && inputDataStack[BrakeSystem_Q] == CONTINENTAL)       return false;
    if (inputDataStack[CarType_Q] == SUV && inputDataStack[Engine_Q] == TOYOTA)                   return false;
    if (inputDataStack[CarType_Q] == TRUCK && inputDataStack[Engine_Q] == WIA)                    return false;
    if (inputDataStack[CarType_Q] == TRUCK && inputDataStack[BrakeSystem_Q] == MANDO)             return false;
    if (inputDataStack[BrakeSystem_Q] == BOSCH_B && inputDataStack[SteeringSystem_Q] != BOSCH_S)  return false;

    return true;
}

void runProducedCar()
{
    if (isValidAssemblyCheck() == false)
    {
        printf("자동차가 동작되지 않습니다\n");
        return;
    }

    if (inputDataStack[Engine_Q] == BROKEN)
    {
        printf("엔진이 고장나있습니다.\n");
        printf("자동차가 움직이지 않습니다.\n");
        return;
    }

    if (inputDataStack[CarType_Q] == SEDAN)                 printf("Car Type : Sedan\n");
    else if (inputDataStack[CarType_Q] == SUV)              printf("Car Type : SUV\n");
    else if (inputDataStack[CarType_Q] == TRUCK)            printf("Car Type : Truck\n");
    
    if (inputDataStack[Engine_Q] == GM)                     printf("Engine : GM\n");
    else if (inputDataStack[Engine_Q] == TOYOTA)            printf("Engine : TOYOTA\n");
    else if (inputDataStack[Engine_Q] == WIA)               printf("Engine : WIA\n");
    
    if (inputDataStack[BrakeSystem_Q] == MANDO)             printf("Brake System : Mando");
    else if (inputDataStack[BrakeSystem_Q] == CONTINENTAL)  printf("Brake System : Continental\n");
    else if (inputDataStack[BrakeSystem_Q] == BOSCH_B)      printf("Brake System : Bosch\n");
    
    if (inputDataStack[SteeringSystem_Q] == BOSCH_S)        printf("SteeringSystem : Bosch\n");
    else if (inputDataStack[SteeringSystem_Q] == MOBIS)     printf("SteeringSystem : Mobis\n");

    printf("자동차가 동작됩니다.\n");
}

void testProducedCar()
{
    if (inputDataStack[CarType_Q] == SEDAN && inputDataStack[BrakeSystem_Q] == CONTINENTAL)
    {
        printf("자동차 부품 조합 테스트 결과 : FAIL\n");
        printf("Sedan에는 Continental제동장치 사용 불가\n");
        return;
    }
    if (inputDataStack[CarType_Q] == SUV && inputDataStack[Engine_Q] == TOYOTA)
    {
        printf("자동차 부품 조합 테스트 결과 : FAIL\n");
        printf("SUV에는 TOYOTA엔진 사용 불가\n");
        return;
    }
    if (inputDataStack[CarType_Q] == TRUCK && inputDataStack[Engine_Q] == WIA)
    {
        printf("자동차 부품 조합 테스트 결과 : FAIL\n");
        printf("Truck에는 WIA엔진 사용 불가\n");
        return;
    }
    if (inputDataStack[CarType_Q] == TRUCK && inputDataStack[BrakeSystem_Q] == MANDO)
    {
        printf("자동차 부품 조합 테스트 결과 : FAIL\n");
        printf("Truck에는 Mando제동장치 사용 불가\n");
        return;
    }
    if (inputDataStack[BrakeSystem_Q] == BOSCH_B && inputDataStack[SteeringSystem_Q] != BOSCH_S)
    {
        printf("자동차 부품 조합 테스트 결과 : FAIL\n");
        printf("Bosch제동장치에는 Bosch 조향장치 이외 사용 불가\n");
        return;
    }

    printf("자동차 부품 조합 테스트 결과 : PASS\n");
}
