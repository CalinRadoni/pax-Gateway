#ifndef WiFiManager_H
#define WiFiManager_H

#include "esp_wifi.h"

#include "boardConfig.h"

enum class WiFiManagerState {
    NotInitialized,
    Initialized,
    Scanning,
    Connecting,
    Connected,
    DisconnectedNoAP,
    Disconnected,
    APMode
};

class WiFiManager
{
    friend void WiFiEventHandler(void* arg, esp_event_base_t event_base, int32_t event_id, void* event_data);

public:
    WiFiManager(void);
    virtual ~WiFiManager();

    BoardConfig *config;

    bool displayFoundAccessPoints {true};
    bool scanBeforeConnect {true};

    esp_err_t Initialize(void);

    bool Connect(void);
    bool IsConnected(void);
    void Disconnect(void);

    /**
     * Scanning stops the WiFi system. `Connect()` again.
     */
    esp_err_t Scan(void);

    esp_err_t StartAP(void);

    WiFiManagerState GetState(void);
    uint8_t UsableConfigCount(void);

    // TODO: return uint32_t
    esp_ip4_addr_t GetStationIP(void);
    esp_ip4_addr_t GetAPIP(void);
    uint8_t GetAPClientCount(void);

private:
    WiFiManagerState wmState {WiFiManagerState::NotInitialized};

    uint8_t configIndex {0};

    std::vector<wifi_ap_record_t> aps;
    void DisplayFoundAPs(void);
    void UpdateWiFiConfigList(void);

    esp_err_t SetCaptivePortalDHCPv4Option(void);
};

extern WiFiManager wifiManager;

#endif
