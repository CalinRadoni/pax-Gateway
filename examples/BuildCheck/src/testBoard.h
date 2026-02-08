#ifndef testBoard_H
#define testBoard_H

#include <Arduino.h>

#include "board.h"
#include "boardConfig.h"

class TestBoard : public Board
{
public:
    TestBoard(void);
    virtual ~TestBoard();

    virtual bool Init_level0(void);
    virtual bool Init_level1(void);
    virtual bool Init_level2(void);
    virtual bool Init_level3(void);

    virtual void CustomReset(void);

protected:
    void InitGPIO(void);

    bool InitADC(void);
};

#endif
