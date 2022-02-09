#include <Arduino.h>

#include "SimpleWiFi.h"
#include "credentials.h"

SimpleWiFi simpleWiFi;

const long gmtOffset = 7200;        // seconds
const int daylightOffset = 3600;    // seconds

void printLocalTime()
{
    struct tm timeInfo;
    if (!getLocalTime(&timeInfo)) {
        Serial.println(F("Failed to obtain time"));
        delay(1000);
        ESP.restart();
        return;
    }
    Serial.println(&timeInfo, "%Y.%B.%d %H:%M:%S");
}

void CheckTimes(void)
{
    struct tm timeInfo;
    time_t now;
    time(&now);
    localtime_r(&now, &timeInfo);
}

void setup()
{
    Serial.begin(115200);

    unsigned short cnt = credCnt;
    for (unsigned short i = 0; i < cnt && i < CredentialCount; ++i) {
        strncpy(simpleWiFi.credentials[i].SSID, SSID[i], 32); simpleWiFi.credentials[i].SSID[32] = 0;
        strncpy(simpleWiFi.credentials[i].PASS, PASS[i], 64); simpleWiFi.credentials[i].PASS[64] = 0;
    }

    simpleWiFi.Reconnect(true);

    while (!simpleWiFi.IsConnected()) { delay(10); }

    configTime(gmtOffset, daylightOffset, "pool.ntp.org");
    printLocalTime();
}

void loop()
{
    simpleWiFi.CheckConnection(true);
}
