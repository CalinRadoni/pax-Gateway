#include "paxGW.h"
#include "paxGWConfig.h"

paxGW_Board board;
paxGW_Config config;

uint32_t restartRequired = 0;

void printLocalTime()
{
    struct tm timeInfo;
    if (!getLocalTime(&timeInfo)) {
        log_e("Failed to obtain time");
        // restartRequired = 1000;
        return;
    }
    Serial.println(&timeInfo, "%Y.%B.%d %H:%M:%S");
    log_i("%d.%02d.%02d %02d:%02d:%02d",
        1900 + timeInfo.tm_year, 1 + timeInfo.tm_mon, timeInfo.tm_mday,
        timeInfo.tm_hour, timeInfo.tm_min, timeInfo.tm_sec);
}

void setup()
{
    Serial.begin(115200);

    board.Initialize(&config);

    if (config.srvNTP.length() > 0) {
        configTime(config.gmtOffset, config.daylightOffset, config.srvNTP.c_str());
    } else {
        log_e("NTP synchronization is required for Telegram authentication !");
    }
    printLocalTime();

#ifdef SSD1306_DISPLAY
    board.ShowStatus();
#endif

    restartRequired = 0;
}

void loop()
{
    board.CheckConnection(true);
    
    // reset here if requested
    if (restartRequired > 0) {
        board.ResetBoard(restartRequired);
    }

    yield();
}
