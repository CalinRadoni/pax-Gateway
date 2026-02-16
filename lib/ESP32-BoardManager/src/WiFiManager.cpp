#include "WiFiManager.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"
#include "esp_system.h"
#include "esp_wifi.h"
#include "esp_netif.h"
#include "esp_event.h"
#include "esp_log.h"
#include "nvs_flash.h"

#include "lwip/err.h"
#include "lwip/sys.h"
#include "lwip/inet.h"

// #include "dns_server.h"

WiFiManager wifiManager;

/**
 * For documentation see:
 * - {@link https://docs.espressif.com/projects/esp-idf/en/stable/esp32/api-guides/wifi.html Wi-Fi Driver}
 * - {@link https://docs.espressif.com/projects/esp-idf/en/stable/esp32/api-reference/network/esp_wifi.html Wi-Fi}
 * 
 * and the related examples, like:
 * 
 * @link https://github.com/espressif/esp-idf/blob/v5.5.2/examples/wifi/getting_started/station/main/station_example_main.c Wi-Fi Station
 * @link https://github.com/espressif/esp-idf/blob/v5.5.2/examples/wifi/roaming/roaming_app/main/roaming_app_example.c Roaming/Wi-Fi Station
 * @link https://github.com/espressif/esp-idf/blob/v5.5.2/examples/wifi/scan/main/scan.c Wi-Fi Scan
 * 
 * @note
 * There is https://github.com/espressif/esp-idf/tree/v5.5.2/examples/wifi/roaming/roaming_11kvr
 * but somwone have to read and test
 */

#ifdef ADD_DHCPV4_CAPTIVE_PORTAL_OPTION
#pragma warning "Captive Portal DHCPv4 Option is enabled, but this is not a complete implementation of RFC 8908 and 8910!"
#pragma warning "Complete implementation is not feasible because of certificates. See CaptivePortal.md for details."
#endif

static const char *TAG = "WiFiManager";

static StaticEventGroup_t evgStorage;
static EventGroupHandle_t wifiEventGroup;

/**
 * Define two bits to be set when:
 * - we are connected to the AP and an IP is set
 * - we failed to connect after the maximum amount of retries
 */
const EventBits_t WiFiConnectedBit = BIT0;
const EventBits_t WiFiConnFailedBit = BIT1;
const EventBits_t WiFiScanDoneBit = BIT2;

const uint8_t WIFI_MAXIMUM_RETRY = 2;
static int wifiRetryCount = 0;

void WiFiEventHandler(void* arg, esp_event_base_t event_base, int32_t event_id, void* event_data)
{
    if (event_base == WIFI_EVENT ) {
        if (event_id == WIFI_EVENT_STA_START) {
            esp_wifi_connect();
        }
        else if (event_id == WIFI_EVENT_STA_DISCONNECTED) {
            wifi_event_sta_disconnected_t *disconn = (wifi_event_sta_disconnected_t*)event_data;
            if (disconn->reason == WIFI_REASON_ROAMING) {
                ESP_LOGI(TAG, "station disconnected during roaming");
            }
            else {
                if (wifiManager.wmState == WiFiManagerState::Connecting) {
                    ++wifiRetryCount;
                    ESP_LOGI(TAG, "Try %d disconnected with reason %d", wifiRetryCount, disconn->reason);
                    if (wifiRetryCount <= WIFI_MAXIMUM_RETRY) {
                        esp_wifi_connect();
                    }
                    else {
                        xEventGroupSetBits(wifiEventGroup, WiFiConnFailedBit);
                    }
                }
                else {
                    ESP_LOGI(TAG, "Disconnected with reason %d", disconn->reason);
                    wifiManager.wmState = WiFiManagerState::Disconnected;
                }
            }
        }
        else if (event_id == WIFI_EVENT_SCAN_DONE) {
            xEventGroupSetBits(wifiEventGroup, WiFiScanDoneBit);
        }
    }
    else if (event_base == IP_EVENT) {
        if (event_id == IP_EVENT_STA_GOT_IP) {
            ip_event_got_ip_t* event = (ip_event_got_ip_t*) event_data;
            ESP_LOGI(TAG, "got ip:" IPSTR, IP2STR(&event->ip_info.ip));
            wifiRetryCount = 0;
            xEventGroupSetBits(wifiEventGroup, WiFiConnectedBit);
        }
    }
}

WiFiManager::WiFiManager(void)
{
    //
}

WiFiManager::~WiFiManager(void)
{
    //
}

esp_err_t WiFiManager::Initialize(void)
{
    if (wmState != WiFiManagerState::NotInitialized) { return true; }

    wifiEventGroup = xEventGroupCreateStatic(&evgStorage);

    // FIXME: esp_netif_init should be called ONCE but it is also called from NetworkManager::begin and
    // BUG: why ???, from configTime and configTzTime defined in esp32-hal-time.c !
    // BUG: there is no official test and problems may arise if called multiple times !
    esp_err_t err = esp_netif_init();
    if (err != ESP_OK) {
        ESP_LOGE(TAG, "Failed to initialize netif ! Was initialized by other library ?");
        return err;
    }   

    // Create the default event loop
    err = esp_event_loop_create_default();
    if (err != ESP_OK) {
        // ESP_ERR_INVALID_STATE = Default event loop has already been created
        if (err != ESP_ERR_INVALID_STATE) {
            ESP_LOGE(TAG, "Failed to create default event loop!");
            return err;
        }
    }

    // Create the default WiFi station netif if not already exists
    if (defaulStaNetif == nullptr) {
        defaulStaNetif = esp_netif_create_default_wifi_sta();
        if (defaulStaNetif == nullptr) {
            ESP_LOGE(TAG, "Failed to create default WiFi station!");
            return ESP_FAIL;
        }
    }

    // Initialize WiFi
    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    cfg.nvs_enable = 0; // disable keeping the configuration in NVS
    err = esp_wifi_init(&cfg);
    if (err != ESP_OK) {
        ESP_LOGE(TAG, "Failed to initialize WiFi!");
        return err;
    }

    // Register an event handler to the default loop, for all WiFi events
    esp_event_handler_instance_t instance_any_id;
    err = esp_event_handler_instance_register(WIFI_EVENT, ESP_EVENT_ANY_ID, &WiFiEventHandler, NULL, &instance_any_id);
    if (err != ESP_OK) {
        ESP_LOGE(TAG, "Failed to register an event handler for WiFi events!");
        return err;
    }

    // Register an event handler to the default loop, for IP_EVENT::IP_EVENT_STA_GOT_IP event
    esp_event_handler_instance_t instance_got_ip;
    err = esp_event_handler_instance_register(IP_EVENT, IP_EVENT_STA_GOT_IP, &WiFiEventHandler, NULL, &instance_got_ip);
    if (err != ESP_OK) {
        ESP_LOGE(TAG, "Failed to register an event handler for IP events!");
        return err;
    }

    ESP_LOGI(TAG, "WiFiManager initialized");
    wmState = WiFiManagerState::Initialized;
    return ESP_OK;
}

esp_err_t WiFiManager::Scan(void)
{
    if (wmState == WiFiManagerState::NotInitialized) {
        if (Initialize() != ESP_OK) {
            return ESP_FAIL;
        }
    }

    aps.clear();

    esp_wifi_stop();
    wmState = WiFiManagerState::Scanning;

    // (maybe) TODO: Set country with esp_wifi_set_country
    // maybe a flag for a FULL scan (cc = XXX, ...)
    // Warning: in cuntry is changed for scan, maybe it should be changed back
    // https://docs.espressif.com/projects/esp-idf/en/stable/esp32/api-guides/wifi.html#wi-fi-country-code

    wifi_scan_config_t scanConfig = {0};

    scanConfig.ssid = nullptr; // all SSID
    scanConfig.bssid = nullptr; // all BSSID
    scanConfig.channel = 0; // all-channel scan
    scanConfig.show_hidden = true;
    scanConfig.scan_type = WIFI_SCAN_TYPE_ACTIVE;

    esp_err_t err = esp_wifi_set_mode(WIFI_MODE_STA);
    if (err != ESP_OK) {
        ESP_LOGE(TAG, "esp_wifi_set_mode failed: %d", err);
        wmState = WiFiManagerState::Disconnected;
        return err;
    }

    err = esp_wifi_start();
    if (err != ESP_OK) {
        ESP_LOGE(TAG, "esp_wifi_start failed: %d", err);
        wmState = WiFiManagerState::Disconnected;
        return err;
    }

    xEventGroupClearBits(wifiEventGroup, WiFiScanDoneBit);

    err = esp_wifi_scan_start(&scanConfig, false);
    if (err != ESP_OK) {
        ESP_LOGE(TAG, "esp_wifi_scan_start failed: %d", err);
        wmState = WiFiManagerState::Disconnected;
        return err;
    }

    EventBits_t sbits = xEventGroupWaitBits(wifiEventGroup, WiFiScanDoneBit, pdFALSE, pdFALSE, portMAX_DELAY);
    if (sbits & WiFiScanDoneBit) {
        uint16_t apCnt;
        err = esp_wifi_scan_get_ap_num(&apCnt);
        if (err != ESP_OK) {
            ESP_LOGE(TAG, "esp_wifi_scan_get_ap_num failed: %d", err);
        }
        else {
            if (apCnt == 0) {
                ESP_LOGE(TAG, "No AP found!");
            }
            else {
                try {
                    aps.reserve(apCnt);
                }
                catch(...) {
                    ESP_LOGE(TAG, "Failed to reserve memory for %d AP records!", apCnt);
                    // Do NOT fail here ! Memory may be available when push_back is called
                    // (at least) because esp_wifi_scan_get_ap_record frees records one by one
                }

                err = ESP_OK;
                for (uint16_t i = 0; i < apCnt; ++i) {
                    // Do NOT break this loop if err != ESP_OK, try to get all AP records
                    wifi_ap_record_t apr = {0};
                    esp_err_t errs = esp_wifi_scan_get_ap_record(&apr);
                    if (errs != ESP_OK) {
                        err = errs;
                        ESP_LOGE(TAG, "esp_wifi_scan_get_ap_record failed at %d/%d: %d", i, apCnt, errs);
                    }
                    else {
                        try {
                            aps.push_back(apr);
                        }
                        catch(...) {
                            ESP_LOGE(TAG, "Failed to save ap record %d/%d!", i, apCnt);
                            err = ESP_ERR_NO_MEM;
                        }
                    }
                }
            }
        }
    }
    else {
        ESP_LOGE(TAG, "xEventGroupWaitBits unexpected event!");
    }

    // must be called if not all AP records where retrieved
    esp_wifi_clear_ap_list();

    esp_wifi_stop();

    wmState = WiFiManagerState::Disconnected;

    return err;
}

void WiFiManager::DisplayFoundAPs(void)
{
    if (aps.size() == 0) {
        ESP_LOGI(TAG, "No Access Points");
        return;
    }

    for (const wifi_ap_record_t apr : aps) {
        ESP_LOGI(TAG, "SSID: %-32.32s | RSSI:% 3d | Channel: % 2d", 
            (const char *)apr.ssid, 
            apr.rssi,
            apr.primary);
    }
}

void WiFiManager::UpdateWiFiConfigList(void)
{
    if (config == nullptr) return;

    for (unsigned int i = 0; i < config->wifiCnt; ++i) {
        config->wifi[i].apFound = false;
        config->wifi[i].apRSSI = 0;

        auto it = std::find_if(aps.cbegin(), aps.cend(), [&](const auto& apr) {
            if (config->wifi[i].ssid[0] == 0) {
                // empty SSID, check BSSID
                if (!config->wifi[i].bssidSet) {
                    // empty SSID and not BSSID set -> wrong config
                    return false;
                }

                return (memcmp(config->wifi[i].bssid, apr.bssid, 6) == 0);

            }
            return (memcmp(config->wifi[i].ssid, apr.ssid, 32) == 0);
        });

        if (it != aps.cend()) {
            config->wifi[i].apFound = true;
            config->wifi[i].apRSSI = it->rssi;
        }
    }
}

bool WiFiManager::Connect(void)
{
    if (wmState == WiFiManagerState::Connected) {
        return true;
    }

    if (wmState == WiFiManagerState::NotInitialized) {
        if (Initialize() != ESP_OK) {
            return false;
        }
    }

    if (config == nullptr) { return false; }

    if (scanBeforeConnect) {
        if (ESP_OK != Scan()) {
            return false;
        }
        
        if (displayFoundAccessPoints) {
            DisplayFoundAPs();
        }

        UpdateWiFiConfigList();
    }
    else {
        for (unsigned int i = 0; i < config->wifiCnt; ++i) {
            config->wifi[i].apFound = true;
        }
    }

    if (UsableConfigCount() == 0) {
        wmState = WiFiManagerState::Disconnected;
        ESP_LOGW(TAG, "No usable WiFi configuration!");
        return false;
    }

    configIndex = 0;
    wmState = WiFiManagerState::Connecting;
    bool done = false;
    bool nextConfig = false;
    while (!done) {
        if (config->wifi[configIndex].apFound) {
            wifi_config_t wifi_config = {0};

            memcpy(wifi_config.sta.ssid, config->wifi[configIndex].ssid, 32);
            memcpy(wifi_config.sta.password, config->wifi[configIndex].password, 64);

            wifi_config.sta.bssid_set = config->wifi[configIndex].bssidSet;
            if (config->wifi[configIndex].bssidSet) {
                memcpy(wifi_config.sta.bssid, config->wifi[configIndex].bssid, 6);
            }

            wifi_config.sta.scan_method = WIFI_ALL_CHANNEL_SCAN;
            wifi_config.sta.sort_method = WIFI_CONNECT_AP_BY_SIGNAL;

            wifi_config.sta.threshold.rssi = config->wifi[configIndex].minRSSI;

            if (config->wifi[configIndex].enableRoaming) {
                /**
                 * Settings for roaming
                 * Note that:
                 *      minimum RSSI should be set to a value greater then the default -127
                 *      BSSID and Channel should NOT be set for BTM and MBO to work !
                 */
                wifi_config.sta.rm_enabled = 1;     // 802.11k Enable Radio Resource Measurements
                wifi_config.sta.btm_enabled = 1;    // 802.11v BSS Transition Management
                wifi_config.sta.mbo_enabled = 1;    // 802.11 Multi-Band Operation
                wifi_config.sta.ft_enabled = 1;     // 802.11r Enable Fast BSS Transition
            }

            WiFiAuthMode minSearchAuthMode = config->wifi[configIndex].minSearchAuthMode;
            switch (minSearchAuthMode) {
                case WiFiAuthMode::WIFI_AUTH_WPA2_PSK:
                    wifi_config.sta.threshold.authmode = WIFI_AUTH_WPA2_PSK;
                    break;
                case WiFiAuthMode::WIFI_AUTH_WPA2_WPA3_PSK:
                    wifi_config.sta.threshold.authmode = WIFI_AUTH_WPA2_WPA3_PSK;
                    wifi_config.sta.pmf_cfg.capable = true; // ESPIDF: "deprecated", will use PMF if advertised even if false
                    wifi_config.sta.pmf_cfg.required = false;
                    wifi_config.sta.sae_pwe_h2e = WPA3_SAE_PWE_BOTH;
                    break;
                case WiFiAuthMode::WIFI_AUTH_WPA3_PSK:
                    wifi_config.sta.threshold.authmode = WIFI_AUTH_WPA3_PSK;
                    wifi_config.sta.pmf_cfg.capable = true; // ESPIDF: "deprecated", will use PMF if advertised even if false
                    wifi_config.sta.pmf_cfg.required = true;
                    // use WPA3_SAE_PWE_BOTH to also allow older WPA3_SAE_PWE_HUNT_AND_PECK
                    wifi_config.sta.sae_pwe_h2e = WPA3_SAE_PWE_HASH_TO_ELEMENT;
                    break;
                default:
                    wifi_config.sta.threshold.authmode = WIFI_AUTH_OPEN; // default, WIFI_AUTH_OPEN equals 0
                    break;
            }

            esp_err_t err = esp_wifi_set_mode(WIFI_MODE_STA);
            if (err != ESP_OK) {
                ESP_LOGE(TAG, "esp_wifi_set_mode failed: %d", err);
                nextConfig = true;
            }
            else {
                err = esp_wifi_set_config(WIFI_IF_STA, &wifi_config);
                if (err != ESP_OK) {
                    ESP_LOGE(TAG, "esp_wifi_set_config failed: %d", err);
                    nextConfig = true;
                }
                else {        
                    ESP_LOGI(TAG, "Connecting to %.32s", reinterpret_cast<const char*>(config->wifi[configIndex].ssid));
                    wifiRetryCount = 0;
                    xEventGroupClearBits(wifiEventGroup, WiFiConnectedBit | WiFiConnFailedBit);
                    wmState = WiFiManagerState::Connecting;

                    // call esp_wifi_stop before esp_wifi_start, if esp_wifi_start was called !
                    err = esp_wifi_start();
                    if (err != ESP_OK) {
                        ESP_LOGE(TAG, "esp_wifi_start failed: %d", err);
                        nextConfig = true;
                    }
                    else {
                        /** 
                         * Wait until the connection is established (WiFiConnectedBit) or failed (WiFiConnFailedBit).
                         * The bits are set by WiFiEventHandler function.
                         */
                        EventBits_t bits = xEventGroupWaitBits(wifiEventGroup,
                                                WiFiConnectedBit | WiFiConnFailedBit, pdFALSE, pdFALSE, portMAX_DELAY);
                        
                        // Check which event actually happened
                        if (bits & WiFiConnectedBit) {
                            ESP_LOGI(TAG, "connected to %.32s", reinterpret_cast<const char*>(config->wifi[configIndex].ssid));
                            done = true;
                            wmState = WiFiManagerState::Connected;
                        }
                        else {
                            if (bits & WiFiConnFailedBit) {
                                ESP_LOGI(TAG, "Failed to connect to %.32s", reinterpret_cast<const char*>(config->wifi[configIndex].ssid));
                            }
                            else {
                                ESP_LOGE(TAG, "xEventGroupWaitBits unexpected event!");
                            }

                            esp_wifi_stop();
                            nextConfig = true;
                        }
                    }
                }
            }
        }
        else {
            nextConfig = true;
        }

        if (nextConfig) {
            nextConfig = false;

            ++configIndex;
            if (configIndex >= config->wifiCnt) {
                ESP_LOGE(TAG, "WiFi connect failed");
                done = true;
                wmState = WiFiManagerState::Disconnected;
            }
        }
    }

    return WiFiManagerState::Connected == wmState;
}

bool WiFiManager::IsConnected(void)
{
    return wmState == WiFiManagerState::Connected;
}

void WiFiManager::Disconnect(void)
{
    esp_wifi_stop();
}

WiFiManagerState WiFiManager::GetState(void)
{
    return wmState;
}

uint8_t WiFiManager::UsableConfigCount(void)
{
    uint8_t cnt = 0;

    if (config == nullptr) return cnt;

    for (unsigned int i = 0; i < config->wifiCnt; ++i) {
        if (config->wifi[i].apFound)
            ++cnt;
    }
    return cnt;
}

esp_err_t WiFiManager::StartAP(void)
{
    if (wmState == WiFiManagerState::APMode) {
        return ESP_OK;
    }

    if (wmState == WiFiManagerState::NotInitialized) {
        if (Initialize() != ESP_OK) {
            return ESP_FAIL;
        }
    }

    if (config == nullptr) { return ESP_FAIL; }

    esp_wifi_stop();
    wmState = WiFiManagerState::Disconnected;

    // Create the default WiFi AP netif if not already exists
    if (defaultApNetif == nullptr) {
        defaultApNetif = esp_netif_create_default_wifi_ap();
        if (defaultApNetif == nullptr) {
            ESP_LOGE(TAG, "Failed to create default WiFi AP!");
            return ESP_FAIL;
        }
    }
    
    wifi_config_t wifi_config = {0};

    size_t clen = config->deviceName.length();
    if (clen == 0) {
        // HACK Better modify the config->deviceName ?
        // something like config->CreateDefaultDeviceName() ?
        config->deviceName = TAG;
    }

    clen = config->deviceName.length();
    if (clen > 32) { clen = 32; }
    strncpy(reinterpret_cast<char*>(wifi_config.ap.ssid), config->deviceName.c_str(), clen);
    wifi_config.ap.ssid_len = clen;

    clen = config->apPassword.length();
    if (clen > 63) {
        // NOT 64 ! a null char is needed at the end
        clen = 63;
    }
    if (clen > 0) {
        strncpy(reinterpret_cast<char*>(wifi_config.ap.password), config->apPassword.c_str(), clen);
    }
    wifi_config.ap.password[clen] = 0;

    wifi_config.ap.max_connection = 5;

    if (wifi_config.ap.password[0] == 0) {
        wifi_config.ap.authmode = WIFI_AUTH_OPEN;
    }
    else {
        wifi_config.ap.authmode = WIFI_AUTH_WPA2_PSK;
    }

    esp_err_t err = esp_wifi_set_mode(WIFI_MODE_AP);
    if (err != ESP_OK) {
        ESP_LOGE(TAG, "esp_wifi_set_mode failed: %d", err);
        return err;
    }

    err = esp_wifi_set_config(WIFI_IF_AP, &wifi_config);
    if (err != ESP_OK) {
        ESP_LOGE(TAG, "esp_wifi_set_config failed: %d", err);
        return err;
    }

    err = esp_wifi_start();
    if (err != ESP_OK) {
        ESP_LOGE(TAG, "esp_wifi_start failed: %d", err);
        return err;
    }

    ESP_LOGI(TAG, "Access Point started.");

    #ifdef ADD_DHCPV4_CAPTIVE_PORTAL_OPTION
    /**
     * Much more then this is needed to implement the RFC 8908 and 8910 functionality !
     * This is just the IPv4 part of RFC 8910.
     * Complete implementation is not feasible because of certificates.
     * See CaptivePortal.md for details.
     */
    
    err = SetCaptivePortalDHCPv4Option();
    if (err != ESP_OK) {
        ESP_LOGE(TAG, "ConfigureCaptivePortal failed: %d", err);
        // do NOT stop WiFi !
        // do NOT exit
        // AP should work with or without these settings !
    }
    #endif

    wmState = WiFiManagerState::APMode;
    return ESP_OK;
}

#ifdef ADD_DHCPV4_CAPTIVE_PORTAL_OPTION
esp_err_t WiFiManager::SetCaptivePortalDHCPv4Option(void)
{
    if (defaultApNetif == nullptr) {
        ESP_LOGE(TAG, "Default AP netif is not created!");
        return ESP_FAIL;
    }

    esp_netif_ip_info_t ip_info;
    esp_err_t err = esp_netif_get_ip_info(defaultApNetif, &ip_info);
    if (err != ESP_OK) {
        ESP_LOGE(TAG, "esp_netif_get_ip_info failed: %d", err);
        return err;
    }

    // ip max. len is 15 + '0' = 16 + "http://" = 23
    const size_t buflen = 24;
    std::array<char, buflen> buffer;

    strncpy(buffer.data(), "http://", buffer.size());
    size_t offset = strnlen(buffer.data(), buffer.size());
    inet_ntoa_r(ip_info.ip.addr, buffer.data() + offset, buffer.size() - offset);

    err = esp_netif_dhcps_stop(defaultApNetif);
    if (err == ESP_OK || err == ESP_ERR_ESP_NETIF_DHCP_ALREADY_STOPPED) {
        ESP_LOGE(TAG, "esp_netif_dhcps_stop failed: %d", err);
        // do not exit, this error may not be critical, the option may be set in the next call
    }

    // set the Captive-Portal DHCPv4 Option (114) 
    err = esp_netif_dhcps_option(defaultApNetif, ESP_NETIF_OP_SET,
            ESP_NETIF_CAPTIVEPORTAL_URI, buffer.data(), strnlen(buffer.data(), buffer.size()));
    if (err != ESP_OK) {
        ESP_LOGE(TAG, "esp_netif_dhcps_option %d failed: %d", ESP_NETIF_CAPTIVEPORTAL_URI, err);
        // do not exit, try to start the DHCP server back
    }

    err = esp_netif_dhcps_start(defaultApNetif);
    if (err != ESP_OK) {
        ESP_LOGE(TAG, "esp_netif_dhcps_start failed: %d", err);
        return err;
    }

    ESP_LOGI(TAG, "Captive-Portal DHCPv4 Option set to %s",  buffer.data());
    return ESP_OK;
}
#endif

uint32_t WiFiManager::GetStationIP(void)
{
    esp_netif_ip_info_t ipInfo {};
    
    if (wmState != WiFiManagerState::Connected) {
        return 0;
    }

    if (defaulStaNetif == nullptr) {
        ESP_LOGE(TAG, "Default station netif is not created!");
        return 0;
    }

    esp_err_t err = esp_netif_get_ip_info(defaulStaNetif, &ipInfo);
    if (err != ESP_OK) {
        ESP_LOGE(TAG, "esp_netif_get_ip_info failed: %d", err);
        return 0;
    }

    return ipInfo.ip.addr;
}

uint32_t WiFiManager::GetAPIP(void)
{
    esp_netif_ip_info_t ipInfo {};
    
    if (wmState != WiFiManagerState::APMode) {
        return 0;
    }

    if (defaultApNetif == nullptr) {
        ESP_LOGE(TAG, "Default AP netif is not created!");
        return 0;
    }

    esp_err_t err = esp_netif_get_ip_info(defaultApNetif, &ipInfo);
    if (err != ESP_OK) {
        ESP_LOGE(TAG, "esp_netif_get_ip_info failed: %d", err);
        return 0;
    }

    return ipInfo.ip.addr;
}

uint8_t WiFiManager::GetAPClientCount(void)
{
    if (wmState != WiFiManagerState::APMode) {
        return 0;
    }

    wifi_sta_list_t clients;
    if (esp_wifi_ap_get_sta_list(&clients) != ESP_OK) {
        return 0;
    }

    return (uint8_t)clients.num;
}
