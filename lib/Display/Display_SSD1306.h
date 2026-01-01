#ifndef Display_SSD1306_H
#define Display_SSD1306_H

#ifdef SSD1306_DISPLAY

#include <Arduino.h>

class Display_SSD1306
{
public:
    Display_SSD1306(void);
    virtual ~Display_SSD1306();

    bool Initialize(void);

    void Clear(void);
    void TestDraw(void);
};

#endif

#endif
