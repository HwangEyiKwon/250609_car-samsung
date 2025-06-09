#ifdef _DEBUG

#include "gmock/gmock.h"

int main() {
    testing::InitGoogleMock();
    return RUN_ALL_TESTS();
}
#else

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "carAssemblyTypes.h"
#include "car.h"
#include "carValidator.h"
#include "carRunner.h"
#include "carBuilder.h"

// delay function
void delayMilliSecond(int milliSecond);

// execution function
void executeActionByStep(int& step, int answer);
void selectCarType(CarType carType);
void selectEngine(EngineName engineName);
void selectBrakeSystem(BrakeSystemName brakeSystem);
void selectSteeringSystem(SteeringSystemName steeringSystem);

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

int inputDataStack[10];

int main() {
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

    char* checkNumber; // ���ڷ� �� ������� Ȯ���ϱ� ���� ����
    answer = strtol(inputBuf, &checkNumber, 10); // ���ڿ��� 10������ ��ȯ

    // exit �ԷµǾ����� Ȯ��
    if (true == checkExitInput(inputBuf)) return BREAK;
    // invalid input�� �ԷµǾ����� Ȯ��
    if (true == checkInvalidInput(checkNumber, step, answer)) return CONTINUE;
    // return menu input�� �ԷµǾ����� Ȯ��
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
        selectEngine(static_cast<EngineName>(answer));
        delayMilliSecond(800);
        step = BrakeSystem_Q;
    }
    else if (step == BrakeSystem_Q)
    {
        selectBrakeSystem(static_cast<BrakeSystemName>(answer));
        delayMilliSecond(800);
        step = SteeringSystem_Q;
    }
    else if (step == SteeringSystem_Q)
    {
        selectSteeringSystem(static_cast<SteeringSystemName>(answer));
        delayMilliSecond(800);
        step = Run_Test;
    }
    else if (step == Run_Test)
    {
        ConcreteCarBuilder* builder = new ConcreteCarBuilder();
        Car* car = builder->setCarType(static_cast<CarType>(inputDataStack[CarType_Q]))
                            .setEngine(static_cast<EngineName>(inputDataStack[Engine_Q]))
                            .setBrakeSystem(static_cast<BrakeSystemName>(inputDataStack[BrakeSystem_Q]))
                            .setSteeringSystem(static_cast<SteeringSystemName>(inputDataStack[SteeringSystem_Q]))
                            .build();
        if (answer == 1)
        {
            CarRunner::runProducedCar(car);
            delayMilliSecond(2000);
        }
        else if (answer == 2)
        {
            printf("Test...\n");
            delayMilliSecond(1500);
            CarValidator::testProducedCar(car);
            delayMilliSecond(2000);
        }
    }
}

bool checkReturnMenuInput(int answer, int& step)
{
    // ó������ ���ư���
    if (answer == 0 && step == Run_Test)
    {
        step = CarType_Q;
        return true;
    }

    // �������� ���ư���
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
        printf("ERROR :: ���ڸ� �Է� ����\n");
        delayMilliSecond(800);
        return true;
    }

    if (step == CarType_Q && !(answer >= 1 && answer <= 3))
    {
        printf("ERROR :: ���� Ÿ���� 1 ~ 3 ������ ���� ����\n");
        delayMilliSecond(800);
        return true;
    }

    if (step == Engine_Q && !(answer >= 0 && answer <= 4))
    {
        printf("ERROR :: ������ 1 ~ 4 ������ ���� ����\n");
        delayMilliSecond(800);
        return true;
    }

    if (step == BrakeSystem_Q && !(answer >= 0 && answer <= 3))
    {
        printf("ERROR :: ������ġ�� 1 ~ 3 ������ ���� ����\n");
        delayMilliSecond(800);
        return true;
    }

    if (step == SteeringSystem_Q && !(answer >= 0 && answer <= 2))
    {
        printf("ERROR :: ������ġ�� 1 ~ 2 ������ ���� ����\n");
        delayMilliSecond(800);
        return true;
    }

    if (step == Run_Test && !(answer >= 0 && answer <= 2))
    {
        printf("ERROR :: Run �Ǵ� Test �� �ϳ��� ���� �ʿ�\n");
        delayMilliSecond(800);
        return true;
    }

    return false;
}

bool checkExitInput(char inputBuf[100])
{
    if (strcmp(inputBuf, "exit") == 0)
    {
        printf("���̹���\n");
        return true;
    }

    return false;
}

void getInputData(char buf[100])
{
    printf("INPUT > ");
    fgets(buf, sizeof(buf), stdin);

    // ���� ���๮�� ����
    char* context = nullptr;
    strtok_s(buf, "\r", &context);
    strtok_s(buf, "\n", &context);
}

void printRunTestQuestion()
{
    printf(CLEAR_SCREEN);
    printf("���� ������ �ϼ��Ǿ����ϴ�.\n");
    printf("� ������ �ұ��?\n");
    printf("0. ó�� ȭ������ ���ư���\n");
    printf("1. RUN\n");
    printf("2. Test\n");
    printf("===============================\n");
}

void printSteeringSystemQuestion()
{
    printf(CLEAR_SCREEN);
    printf("� ������ġ�� �����ұ��?\n");
    printf("0. �ڷΰ���\n");
    printf("1. BOSCH\n");
    printf("2. MOBIS\n");
    printf("===============================\n");
}

void printBrakeSystemQuestion()
{
    printf(CLEAR_SCREEN);
    printf("� ������ġ�� �����ұ��?\n");
    printf("0. �ڷΰ���\n");
    printf("1. MANDO\n");
    printf("2. CONTINENTAL\n");
    printf("3. BOSCH\n");
    printf("===============================\n");
}

void printEngineQuestion()
{
    printf(CLEAR_SCREEN);
    printf("� ������ ž���ұ��?\n");
    printf("0. �ڷΰ���\n");
    printf("1. GM\n");
    printf("2. TOYOTA\n");
    printf("3. WIA\n");
    printf("4. ���峭 ����\n");
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
    printf("� ���� Ÿ���� �����ұ��?\n");
    printf("1. Sedan\n");
    printf("2. SUV\n");
    printf("3. Truck\n");
    printf("===============================\n");
}

void selectCarType(CarType carType)
{
    inputDataStack[CarType_Q] = carType;
    if (carType == CarType::SEDAN)
        printf("���� Ÿ������ Sedan�� �����ϼ̽��ϴ�.\n");
    else if (carType == CarType::SUV)
        printf("���� Ÿ������ SUV�� �����ϼ̽��ϴ�.\n");
    else if (carType == CarType::TRUCK)
        printf("���� Ÿ������ Truck�� �����ϼ̽��ϴ�.\n");
}

void selectEngine(EngineName engineName)
{
    inputDataStack[Engine_Q] = engineName;
    if (engineName == EngineName::GM)
        printf("GM ������ �����ϼ̽��ϴ�.\n");
    else if (engineName == EngineName::TOYOTA)
        printf("TOYOTA ������ �����ϼ̽��ϴ�.\n");
    else if (engineName == EngineName::WIA)
        printf("WIA ������ �����ϼ̽��ϴ�.\n");
}

void selectBrakeSystem(BrakeSystemName brakeSystemName)
{
    inputDataStack[BrakeSystem_Q] = brakeSystemName;
    if (brakeSystemName == BrakeSystemName::MANDO)
        printf("MANDO ������ġ�� �����ϼ̽��ϴ�.\n");
    else if (brakeSystemName == BrakeSystemName::CONTINENTAL)
        printf("CONTINENTAL ������ġ�� �����ϼ̽��ϴ�.\n");
    else if (brakeSystemName == BrakeSystemName::BOSCH_B)
        printf("BOSCH ������ġ�� �����ϼ̽��ϴ�.\n");
}

void selectSteeringSystem(SteeringSystemName steeringSystemName)
{
    inputDataStack[SteeringSystem_Q] = steeringSystemName;
    if (steeringSystemName == SteeringSystemName::BOSCH_S)
        printf("BOSCH ������ġ�� �����ϼ̽��ϴ�.\n");
    else if (steeringSystemName == SteeringSystemName::MOBIS)
        printf("MOBIS ������ġ�� �����ϼ̽��ϴ�.\n");
}
#endif