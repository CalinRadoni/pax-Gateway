#include "wifiConfig.h"

WiFiConfig::WiFiConfig(void)
{
    //
}

WiFiConfig::~WiFiConfig()
{
    //
}

void WiFiConfig::Initialize(void)
{
    saveIndex = 0;

    memset(ssid, 0, 32);
    memset(password, 0, 64);
    bssidSet = false;
    memset(bssid, 0, 6);

    useDHCP = true;

    address = (uint32_t)0;
    mask    = (uint32_t)0;
    gateway = (uint32_t)0;
    srvDNS1 = (uint32_t)0;
    srvDNS2 = (uint32_t)0;

    minSearchAuthMode = WiFiAuthMode::WIFI_AUTH_OPEN;

    enableRoaming = true;
    minRSSI = -127;

    apFound = false;
    apRSSI = -127;
}

uint8_t WiFiConfig::msamGet(void)
{
    switch (minSearchAuthMode) {
        case WiFiAuthMode::WIFI_AUTH_OPEN: return 0;
        case WiFiAuthMode::WIFI_AUTH_WPA2_PSK: return 1;
        case WiFiAuthMode::WIFI_AUTH_WPA2_WPA3_PSK: return 2;
        case WiFiAuthMode::WIFI_AUTH_WPA3_PSK: return 3;
    }
    return 0;
}

bool WiFiConfig::msamSet(uint8_t val)
{
    switch (val) {
        case 0: minSearchAuthMode = WiFiAuthMode::WIFI_AUTH_OPEN; break;
        case 1: minSearchAuthMode = WiFiAuthMode::WIFI_AUTH_WPA2_PSK; break;
        case 2: minSearchAuthMode = WiFiAuthMode::WIFI_AUTH_WPA2_WPA3_PSK; break;
        case 3: minSearchAuthMode = WiFiAuthMode::WIFI_AUTH_WPA3_PSK; break;
        default:
            minSearchAuthMode = WiFiAuthMode::WIFI_AUTH_OPEN;
            return false;
    }
    return true;
}

bool WiFiConfig::CheckData(bool strict)
{
    if (enableRoaming) {
        /**
         * BSSID and Channel should NOT be set for BTM and MBO to work !
         */
        // bssid_set = false;
        // memset(bssid, 0, 6);
        // channel = 0;
        // ESP_LOGW(TAG, "BSSID ignored because roaming is set");
        // ESP_LOGW(TAG, "Channel is ignored because roaming is set");
    }

    // SSID's length should be > 0 and <= 32
    // SSID can be 0 if bssid is set
    if (ssid[0] == 0) {
        if (!bssidSet)
            return false;
    }

    // Password's length should be <= 64
    if (minSearchAuthMode != WiFiAuthMode::WIFI_AUTH_OPEN) {
        // ... and at least 8 chars for WPA2, WPA3, ...
        if (strnlen(reinterpret_cast<const char*>(password), 64) < 8)
            return false;
    }

    if (strict) {
        if (useDHCP) {
            if (address != 0) return false;
            if (mask != 0) return false;
            if (gateway != 0) return false;

            if (srvDNS1 != 0) return false;
            if (srvDNS2 != 0) return false;
        }
        else {
            if (address == 0) return false;
            if (mask == 0) return false;
            // if (gateway == 0) return false;

            // if (srvDNS1 == 0) return false;
            // if (srvDNS2 == 0) return false;
        }
    }

    return true;
}
