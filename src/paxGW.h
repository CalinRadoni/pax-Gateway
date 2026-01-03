#ifndef paxGW_H
#define paxGW_H

#include <Arduino.h>
#include <SPI.h>

#include "board.h"
#include "paxGWConfig.h"

#ifdef Radio_RFM69
#include <RHReliableDatagram.h>
#include <RH_RF69.h>
#endif

#ifdef SSD1306_DISPLAY
#include "Display_SSD1306.h"
#endif

/*
pax-GW (esp32-rfm-gateway)

ESP-WROOM-32xxx-16 connections
SDA = IO21 (pin 33) with 2k2 pull-up
SCL = IO22 (pin 36) with 2k2 pull-up
SDA and SCL goes to:
- J4, J5, J8
- HDC1080DMB, if installed, address 0x80/0x81
- CryptoAuth chip, if installed
    - ATSHA204A, address 0xC8/0xC9
    - ATECC508A, address 0xC0/0xC1
    - ATECC608A, address 0xC4/0xC5 (probably))

U0RXD and U0TXD = pins 34 and 35 = J3
U0RXD and U0TXD = pins 27 and 28 = J6

LED0 = IO19 (pin 31) with 100 ohms to 3V3
LED1 = IO18 (pin 30) with 100 ohms to 3V3
LED2 = IO5  (pin 29) with 100 ohms to 3V3
LED3 = IO4  (pin 26) with 100 ohms to 3V3

On board LED on IO2 with 330 ohms to ground

HSPICS0 = IO15 (pin 23) = radio -SS
HSPID   = IO13 (pin 16) = radio MOSI
HSPIQ   = IO12 (pin 14) = radio MISO
HSPICLK = IO14 (pin 13) = radio SCK

DIO0 = IO25 (pin 10) = radio DIO0
DIO1 = IO26 (pin 11) = radio DIO1
DIO2 = IO27 (pin 12) = radio DIO2

ChargeStat = IO33 (pin 9) = STAT pin of the MCP73832T-2ACI
ADC_Batt = Sensor_VP (pin 4) = half the battery voltage
ADC_Vin = Sensor_VN (pin 5 ESP-WROOM-32) = half the voltage of the 5V power source

IO34 (pin 6) with 100nF to ground goes to J7
IO35 (pin 7) with 100nF to ground goes to J7
*/

class paxGW_Board : public Board
{
public:
    paxGW_Board(void);
    virtual ~paxGW_Board();

    virtual bool Init_level0(void);
    virtual bool Init_level1(void);
    virtual bool Init_level2(void);
    virtual bool Init_level3(void);

    virtual void CustomReset(void);

    uint16_t GetVIn(void);
    uint16_t GetVBatt(void);
    bool IsCharging(void);

    /**
     * 0 - 3 for LED0 - LED3
     * any other value controls the onboard LED
     */
    void SetLED(uint8_t, bool);

#ifdef SSD1306_DISPLAY
    Display_SSD1306 display;
#endif

    void ShowStatus(void);

#ifdef Radio_RFM69
    RHReliableDatagram *radioManager;
#endif

protected:
    void InitGPIO(void);

    bool InitADC(void);

    SPIClass *hspi;
    bool InitHSPI(void);
    void CleanupHSPI(void);

#ifdef Radio_RFM69
    unsigned char radio_server_address;
    bool CreateRadio(void);
    bool InitializeRadio(void);
    void CleanupRadio(void);
#endif
};

#endif
