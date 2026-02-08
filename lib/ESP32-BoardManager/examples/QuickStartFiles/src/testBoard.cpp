#include "testBoard.h"

const uint8_t PIN_SDA = 21;
const uint8_t PIN_SCL = 22;

// RGB LED Data = 2
// RGB LED Power = 4 (active low)

TestBoard::TestBoard(void)
{
}

TestBoard::~TestBoard(void)
{
}

bool TestBoard::Init_level0(void)
{
    bool res = true;

    InitGPIO();
    res = res & InitADC();

    SDA_pin = PIN_SDA;
    SCL_pin = PIN_SCL;

    return res;
}

bool TestBoard::Init_level1(void)
{
    return true;
}

bool TestBoard::Init_level2(void)
{
    return true;
}

bool TestBoard::Init_level3(void)
{
    return true;
}

void TestBoard::CustomReset(void)
{
}

void TestBoard::InitGPIO(void)
{
}

bool TestBoard::InitADC(void)
{
    return true;
}
