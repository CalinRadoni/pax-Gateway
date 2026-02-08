#ifndef boardConfig_H
#define boardConfig_H

#include <Arduino.h>
#include <ArduinoJson.h>

#include <array>
#include <string>

#include "nvs_flash.h"
#include "nvs.h"

#include "wifiConfig.h"

class BoardConfig
{
public:
    BoardConfig(void);
    virtual ~BoardConfig();

    std::string deviceName;
    std::string mDNSname;

    std::string timeZone;
    std::string srvNTP;

    std::string apPassword; // max.63 chars will be used

    static const uint8_t wifiCnt = 3;
    WiFiConfig wifi[wifiCnt];

    bool Initialize(void);
    bool Load(void);
    bool Save(void);

    bool EraseNamespaces(void);
    bool EraseDefaultNVS(void);

    // jdoc as a public member eases usage and reusage, requires less memory, ...
    // serialize with serializeJson(jdoc, put_a_string_here)
    // documentation for jdoc: https://arduinojson.org/v7/
    JsonDocument jdoc;
    bool BuildJsonDocument(void);

protected:
    bool InitializeNVS(void);
    bool InitializeNamespace(void);

    virtual bool CustomInit(void);
    virtual bool CustomLoad(void);
    virtual bool CustomSave(void);
    virtual bool CustomEraseNamespace(void);
    virtual bool CustomBuildJsonDocument(void);

    /**
     * To reduce heap fragmentation, this variable is used as temporary buffer
     * by the GetBlob, SetBlob and SetString functions.
     */
    std::array<uint8_t, 128> buffer = {0};

    bool GetBool(nvs_handle_t nvsh, const char *key, bool *out);
    bool GetU8(nvs_handle_t nvsh, const char *key, uint8_t *out);
    bool GetI8(nvs_handle_t nvsh, const char *key, int8_t *out);
    bool GetU32(nvs_handle_t nvsh, const char *key, uint32_t *out);
    bool GetBlob(nvs_handle_t nvsh, const char *key, void *data, size_t length);
    bool GetString(nvs_handle_t nvsh, const char *key, std::string& str);
    
    bool SetBool(nvs_handle_t nvsh, const char *key, bool value);
    bool SetU8(nvs_handle_t nvsh, const char *key, uint8_t value);
    bool SetI8(nvs_handle_t nvsh, const char *key, int8_t value);
    bool SetU32(nvs_handle_t nvsh, const char *key, uint32_t value);
    bool SetBlob(nvs_handle_t nvsh, const char *key, void *data, size_t length);
    bool SetString(nvs_handle_t nvsh, const char *key, std::string& str);

    bool LoadWiFiConfig(WiFiConfig *cfg, uint8_t *failed);
    bool SaveWiFiConfig(WiFiConfig *cfg, uint8_t *failed, bool skipCommit = true);
};

#endif
