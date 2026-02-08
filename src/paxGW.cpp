#include "paxGW.h"

#include "credentials.h"

// On-board LED pin number
const uint8_t PIN_LED_BUILTIN = 2; // on = HIGH

// On-board user button
const uint8_t PIN_USER_BTN = 0;

// charge status (open-drain output from charger IC)
const uint8_t PIN_CHARGE_STAT = 33;
// V_Batt is half of the battery voltage
const uint8_t PIN_VBATT = 36; // ADC1_0
// V_in is half of the input voltage
const uint8_t PIN_VIN = 39; // ADC1_3

// Board LEDs, on = LOW
const uint8_t PIN_LED0 = 19;
const uint8_t PIN_LED1 = 18;
const uint8_t PIN_LED2 = 5;
const uint8_t PIN_LED3 = 4;

// IRQ from RFM module
const uint8_t PIN_Radio_DIO0 = 25;
const uint8_t PIN_Radio_DIO1 = 26;
const uint8_t PIN_Radio_DIO2 = 27;

// SPI definitions
const uint8_t PIN_SPI_SS_Radio = 15; // HSPI_SS
const uint8_t PIN_SPI_SCK = 14;      // HSPI_SCLK
const uint8_t PIN_SPI_Q = 12;        // HSPI_MISO
const uint8_t PIN_SPI_D = 13;        // HSPI_MOSI

// I2C
const uint8_t PIN_SDA = 21;
const uint8_t PIN_SCL = 22;

#ifdef Radio_RFM69
    // Singleton instance of the radio driver
    RH_RF69 radioDriver(PIN_SPI_SS_Radio, PIN_Radio_DIO0);
#endif

paxGW_Board::paxGW_Board(void)
{
    hspi = nullptr;

#ifdef Radio_RFM69
    radioManager = nullptr;
    radio_server_address = 1;
#endif
}

paxGW_Board::~paxGW_Board(void)
{
#ifdef Radio_RFM69
    CleanupRadio();
#endif

    CleanupHSPI();
}

bool paxGW_Board::Init_level0(void)
{
    bool res = true;

    InitGPIO();
    res = res & InitADC();

    // HSPI will be initialized by the RadioHead library
    // res = res & InitHSPI();

    SDA_pin = PIN_SDA;
    SCL_pin = PIN_SCL;

    return res;
}

bool paxGW_Board::Init_level1(void)
{
    return true;
}

bool paxGW_Board::Init_level2(void)
{
    bool res = true;

    // initialize board chips here

#ifdef SSD1306_DISPLAY
    display.Initialize("pax-GW", 10, 20);
#endif

#ifdef Radio_RFM69
    res &= CreateRadio();
    res &= InitializeRadio();
#endif

    return res;
}

bool paxGW_Board::Init_level3(void)
{
    // initialization after WiFi is connected or timeout
    return true;
}

void paxGW_Board::CustomReset(void)
{
#ifdef CAMERA_PRESENT
    espCam.Deinit();
#endif
}

void paxGW_Board::InitGPIO(void)
{
    pinMode(PIN_USER_BTN, INPUT_PULLUP);
    pinMode(PIN_CHARGE_STAT, INPUT_PULLUP);

    pinMode(PIN_Radio_DIO0, INPUT);
    pinMode(PIN_Radio_DIO1, INPUT);
    pinMode(PIN_Radio_DIO2, INPUT);

    pinMode(PIN_LED_BUILTIN, OUTPUT);
    digitalWrite(PIN_LED_BUILTIN, LOW);

    pinMode(PIN_LED0, OUTPUT); digitalWrite(PIN_LED0, HIGH);
    pinMode(PIN_LED1, OUTPUT); digitalWrite(PIN_LED1, HIGH);
    pinMode(PIN_LED2, OUTPUT); digitalWrite(PIN_LED2, HIGH);
    pinMode(PIN_LED3, OUTPUT); digitalWrite(PIN_LED3, HIGH);
}

bool paxGW_Board::InitHSPI(void)
{
    if (hspi != nullptr) return true;

    try {
        hspi = new SPIClass(HSPI);
    }
    catch(...) {
        hspi = nullptr;
    }
    if (hspi == nullptr) return false;

    //initialize hspi with default pins: SCLK = 14, MISO = 12, MOSI = 13, SS = 15
    hspi->begin();

    // https://github.com/espressif/arduino-esp32/tree/master/libraries/SPI
    // for SPI 2.x use:
    // pinMode(hspi->pinSS(), OUTPUT);
    // digitalWrite(hspi->pinSS(), HIGH);
    // for SPI 1.x use:
    pinMode(PIN_SPI_SS_Radio, OUTPUT);
    digitalWrite(PIN_SPI_SS_Radio, HIGH);

    return true;
}

void paxGW_Board::CleanupHSPI(void)
{
    if (hspi == nullptr) return;

    hspi->end();
    delete hspi;
    hspi = nullptr;
}

bool paxGW_Board::InitADC(void)
{
    analogSetAttenuation(ADC_11db);
    analogSetWidth(12);

    uint16_t val = analogRead(PIN_VBATT);
    val += analogRead(PIN_VIN);
    return (val > 0);
}

uint16_t paxGW_Board::GetVIn(void)
{
    uint16_t val = analogReadMilliVolts(PIN_VIN);
    return val << 1;
}

uint16_t paxGW_Board::GetVBatt(void)
{
    uint16_t val = analogReadMilliVolts(PIN_VBATT);
    return val << 1;
}

bool paxGW_Board::IsCharging(void)
{
    return digitalRead(PIN_CHARGE_STAT) == LOW;
}

void paxGW_Board::SetLED(uint8_t idx, bool on)
{
    switch (idx) {
        case 0: digitalWrite(PIN_LED0, on ? LOW : HIGH); break;
        case 1: digitalWrite(PIN_LED1, on ? LOW : HIGH); break;
        case 2: digitalWrite(PIN_LED2, on ? LOW : HIGH); break;
        case 3: digitalWrite(PIN_LED3, on ? LOW : HIGH); break;
        default: digitalWrite(PIN_LED_BUILTIN, on ? HIGH : LOW); break;
    }
}

void paxGW_Board::ShowStatus(void)
{
#ifdef SSD1306_DISPLAY
    display.Clear();
    display.SetCursor(0, 0);
    
    display.SetTextSize(1);

    const uint8_t buflen = 128;
    char buf[buflen] {};
    uint8_t len = 0;

    WiFiManagerState wmState = wifiManager.GetState();

    if (WiFiManagerState::Connected == wmState) {
        wifi_ap_record_t apInfo;
        if (esp_wifi_sta_get_ap_info(&apInfo) == ESP_OK) {
            snprintf(buf, buflen, "%d dBm ", apInfo.rssi);

            len = strnlen(buf, buflen);
            if (strnlen((const char *)apInfo.ssid, 32) > 0) {
                snprintf(buf + len, buflen - len, "%s", (const char *)apInfo.ssid);
            }
            else {
                snprintf(buf + len, buflen - len, "%02X:%02X:%02X:%02X:%02X:%02X",
                    apInfo.bssid[0], apInfo.bssid[1], apInfo.bssid[2],
                    apInfo.bssid[3], apInfo.bssid[4], apInfo.bssid[5]);
            }
        }
        else {
            snprintf(buf, buflen, "WiFi connected");
        }

        len = strnlen(buf, buflen);
        esp_ip4_addr_t ip = wifiManager.GetStationIP();
        if (ip.addr != 0) {
            snprintf(buf + len, buflen - len, "\n%d.%d.%d.%d",
                ip.addr & 0xFF,
                (ip.addr >> 8) & 0xFF,
                (ip.addr >> 16) & 0xFF,
                (ip.addr >> 24) & 0xFF);
        }

        display.Println(buf);
    }
    else if (WiFiManagerState::APMode == wmState) {
        esp_ip4_addr_t ip = wifiManager.GetAPIP();
        if (ip.addr != 0) {
            snprintf(buf, buflen, "AP: %d.%d.%d.%d",
                ip.addr & 0xFF,
                (ip.addr >> 8) & 0xFF,
                (ip.addr >> 16) & 0xFF,
                (ip.addr >> 24) & 0xFF);
        }
        else {
            snprintf(buf, buflen, "AP mode");
        }

        len = strnlen(buf, buflen);
        uint8_t clientCount = wifiManager.GetAPClientCount();
        snprintf(buf + len, buflen - len, "\n%d client%s",
            clientCount,
            clientCount != 1 ? "s" : "");

        display.Println(buf);
    }
    else {
        display.Println("WiFi not\nconnected");
    }
    
    snprintf(buf, 128, "%.2f %c %.2f",
        GetVIn()/1000.0,
        IsCharging() ? (char)0x1E : (char)0x1F,
        GetVBatt()/1000.0);
    display.Println(buf);

    display.Show();
#endif
}

#ifdef Radio_RFM69
// https://www.airspayce.com/mikem/arduino/RadioHead/

bool paxGW_Board::CreateRadio(void) {
    if (radioManager != nullptr) {
        CleanupRadio();
    }

    try {
        radioManager = new RHReliableDatagram(radioDriver, radio_server_address);
    }
    catch(...){
        log_e("Failed to create the radio manager !");
        CleanupRadio();
        return false;
    }

    log_n("Created the radio manager");

    return true;
}

bool paxGW_Board::InitializeRadio(void)
{
    bool res = true;

    if (radioManager == nullptr) {
        if (!CreateRadio()) {
            return false;
        }
    }

    if (radioManager->init()) {
        // For RF69HW valid values are from -2 to +20.
        // Caution: at +20dBm, duty cycle is limited to 1% and a maximum VSWR of 3:1 at the antenna port.
        radioDriver.setTxPower(14, true);
        log_n("Radio initialized");
    }
    else {
        log_e("Radio initialization failed !");
        res = false;
    }

    return res;
}

void paxGW_Board::CleanupRadio(void)
{
    if (radioManager != nullptr) {
        delete radioManager;
        radioManager = nullptr;
    }
}
#endif
