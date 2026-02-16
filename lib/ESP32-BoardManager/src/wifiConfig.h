#ifndef wifiConfig_H
#define wifiConfig_H

#include <cstddef>
#include <cstdint>

/**
 * Note: Modify msamGet and msamGet functions if you change this enum.
 */
enum class WiFiAuthMode {
    WIFI_AUTH_OPEN,
    WIFI_AUTH_WPA2_PSK,
    WIFI_AUTH_WPA2_WPA3_PSK,
    WIFI_AUTH_WPA3_PSK
};

class WiFiConfig
{
public:
    WiFiConfig(void);
    virtual ~WiFiConfig();

    // saveIndex is used for saving each config in its own namespace
    uint8_t saveIndex {0};

    uint8_t ssid[32];
    uint8_t password[64];

    size_t GetSSIDLen(void);
    size_t GetPasswordLen(void);

    bool bssidSet {false};
    uint8_t bssid[6];

    // TODO: MAYBE, implement channel
    // uint8_t channel;

    bool useDHCP {true};
    uint32_t address {0};
    uint32_t mask {0};
    uint32_t gateway {0};
    uint32_t srvDNS1 {0};
    uint32_t srvDNS2 {0};

    // minimum auth mode when searching for AP
    WiFiAuthMode minSearchAuthMode {WiFiAuthMode::WIFI_AUTH_OPEN};
    uint8_t msamGet(void);
    bool msamSet(uint8_t);

    /**
     * Enable Roaming in station mode
     * 
     * For roaming to be efective, minRSSI should be set to a value greater then -127.
     * When roaming the channel should be 0 (no preference) and BSSID should not be set.
     */
    bool enableRoaming {true};
    
    // ESPIDK: RSSI defaults to -127 if set to >= 0
    int8_t minRSSI {-127};

    /**
     * NOT saved, used in scanning, before connection
     */
    bool apFound {false};
    int8_t apRSSI {-127};

    void Initialize(void);

    bool CheckData(bool strict = false);

protected:
    size_t GetByteStringSize(const uint8_t *data, size_t maxLen);

};

#endif
