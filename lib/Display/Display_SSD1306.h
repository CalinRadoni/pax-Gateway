#ifndef Display_SSD1306_H
#define Display_SSD1306_H

#ifdef SSD1306_DISPLAY

#include <Arduino.h>

class Display_SSD1306
{
public:
    Display_SSD1306(void);
    virtual ~Display_SSD1306();

    bool Initialize(const char* splash_text, uint8_t x = 0, uint8_t y = 0);

    void Clear(void);
    void Show(void);
    void SetCursor(uint8_t x, uint8_t y);
    void SetTextSize(uint8_t size);
    void Print(const char* str);
    void Println(const char* str);

    void TestDraw(void);
};

#endif

#endif
