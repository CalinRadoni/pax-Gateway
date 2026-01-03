#include "Display_SSD1306.h"

#ifdef SSD1306_DISPLAY

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

const uint8_t screen_width = 128;
const uint8_t screen_height = 64;
const uint8_t screen_address = 0x3C;
const int8_t screen_reset_pin = -1;

// Singleton instance of the display
Adafruit_SSD1306 display(screen_width, screen_height, &Wire, screen_reset_pin);

Display_SSD1306::Display_SSD1306(void)
{
    //
}

Display_SSD1306::~Display_SSD1306(void)
{
    //
}

bool Display_SSD1306::Initialize(const char* splash_text, uint8_t x, uint8_t y)
{
    // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
    // reset = false
    // periphBegin = false because Wire should have been initialized already
    if(!display.begin(SSD1306_SWITCHCAPVCC, screen_address, false, false))
        return false;

    display.clearDisplay();

    display.cp437(true);
    display.setTextColor(SSD1306_WHITE);

    if (splash_text != nullptr) {
        display.setTextSize(3);
        display.setCursor(x, y);
        display.println(splash_text);
    }

    display.display();

    return true;
}

void Display_SSD1306::Clear(void)
{
    display.clearDisplay();
}
void Display_SSD1306::Show(void)
{
    display.display();
}
void Display_SSD1306::SetCursor(uint8_t x, uint8_t y)
{
    display.setCursor(x, y);
}
void Display_SSD1306::SetTextSize(uint8_t size)
{
    display.setTextSize(size);
}
void Display_SSD1306::Print(const char* str)
{
    display.print(str);
}
void Display_SSD1306::Println(const char* str)
{
    display.println(str);
}

void Display_SSD1306::TestDraw(void)
{
    display.clearDisplay();

    unsigned int i, step;

    display.drawRect(0, 0, display.width() - 1, display.height() - 1, SSD1306_WHITE);
    display.display();
    delay(200);
    
    step = 7;
    for (i = step; i < display.height(); i += step) {
        display.drawLine(display.width() - 3 - i, i, display.width() - 3, i, SSD1306_WHITE);
        display.display();
        delay(200);
    }

    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0, 0);
    display.cp437(true);

    for (i = 1; i < 5; ++i) {
        display.setTextSize(i);
        display.println("ABC12");
        display.display();
        delay(200);
    }

    display.drawCircle(display.width()/2, display.height()/2, 33, SSD1306_WHITE);
    display.display();
}

#endif
