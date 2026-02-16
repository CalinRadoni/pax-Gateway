#include "boardConfig.h"

#include "nvs_flash.h"
#include "nvs.h"
#include "esp_netif.h"

const char* defaultDeviceName = "ESP32Board";
const char* defaultTimeZone = "UTC";
const char* defaultTimeServer = "pool.ntp.org";

const char *NK_BoardNamespace = "ESP32Board";
const char *NK_deviceName = "deviceName";
const char *NK_mDNSname = "mDNSName";
const char *NK_timeZone = "timeZone";
const char *NK_srvNTP = "srvNTP";
const char *NK_apPassword = "apPassword";

const char *NK_WiFiNamespace = "WiFiCfg";
const char *NK_ssid = "SSID";
const char *NK_bssidSet = "BSSIDset";
const char *NK_bssid = "BSSID";
const char *NK_password = "Pass";
const char *NK_useDHCP = "UseDHCP";
const char *NK_address = "IPv4";
const char *NK_mask = "Mask";
const char *NK_gateway = "Gateway";
const char *NK_srvDNS1 = "srvDNS1";
const char *NK_srvDNS2 = "srvDNS2";
const char *NK_minSearchAM = "minSearchAM";
const char *NK_enRoaming = "enRoaming";
const char *NK_minRSSI = "minRSSI";

BoardConfig::BoardConfig(void)
{
    //
}

BoardConfig::~BoardConfig()
{
    //
}

bool BoardConfig::InitializeNVS(void)
{
    esp_err_t err = nvs_flash_init();
    if (err == ESP_ERR_NVS_NO_FREE_PAGES || err == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        err = nvs_flash_erase();
        if (err != ESP_OK) {
            log_e("Failed to erase the default NVS partition, %d: %s", err, esp_err_to_name(err));
            return false;
        }
        log_i("NVS erased");
        
        err = nvs_flash_init();
    }
    if (err != ESP_OK) {
        log_e("Failed to initialize the default NVS partition, %d: %s", err, esp_err_to_name(err));
        return false;
    }

    log_d("NVS initialized");
    return true;
}

bool BoardConfig::EraseNamespaces(void)
{
    nvs_handle_t nvh;
    uint8_t cnt = 0;

    if (ESP_OK == nvs_open(NK_BoardNamespace, NVS_READWRITE, &nvh)) {
        if (ESP_OK == nvs_erase_all(nvh)) {
            if (ESP_OK == nvs_commit(nvh)) {
                log_i("%s erased", NK_BoardNamespace);
                ++cnt;
            }
            else { log_e("Error: erase %s failed!", NK_BoardNamespace); }
        }
        nvs_close(nvh);
    }

    for (uint8_t i = 0; i < wifiCnt; ++i) {
        snprintf(reinterpret_cast<char*>(buffer.data()), buffer.size(), "%s%d", NK_WiFiNamespace, wifi[i].saveIndex);
        if (ESP_OK == nvs_open(reinterpret_cast<const char*>(buffer.data()), NVS_READWRITE, &nvh)) {
            if (ESP_OK == nvs_erase_all(nvh)) {
                if (ESP_OK == nvs_commit(nvh)) {
                    log_i("%s erased", reinterpret_cast<const char*>(buffer.data()));
                    ++cnt;
                }
                else { log_e("Error: erase %s failed!", reinterpret_cast<const char*>(buffer.data())); }
            }
            nvs_close(nvh);
        }
    }

    if (CustomEraseNamespace()) { ++cnt; }

    return cnt == (1 + wifiCnt + 1);
}

bool BoardConfig::EraseDefaultNVS(void)
{
    esp_err_t err = nvs_flash_erase();
    if (err != ESP_OK) {
        log_e("Failed to erase the default NVS partition, %d: %s", err, esp_err_to_name(err));
        return false;
    }
    log_i("NVS erased");

    err = nvs_flash_init();
    if (err != ESP_OK) {
        log_e("Failed to initialize the default NVS partition, %d: %s", err, esp_err_to_name(err));
        return false;
    }
    log_i("NVS initialized");

    return true;
}

bool BoardConfig::InitDataToDefaults(void)
{
    deviceName = defaultDeviceName;
    mDNSname.clear();

    timeZone = defaultTimeZone;
    srvNTP = defaultTimeServer;

    apPassword.clear();

    for (unsigned int i = 0; i < wifiCnt; ++i) {
        wifi[i].Initialize();
        wifi[i].saveIndex = i;
    }

    return CustomInitDataToDefaults();
}

bool BoardConfig::CustomInitDataToDefaults(void)
{
    return true;
}

bool BoardConfig::Initialize(void)
{
    bool res = InitializeNVS();

    res &= InitDataToDefaults();

    res &= CustomInit();

    return res;
}

bool BoardConfig::Load(void)
{
    nvs_handle_t nvh;
    esp_err_t err = nvs_open(NK_BoardNamespace, NVS_READONLY, &nvh);
    if (err != ESP_OK) {
        log_e("Error opening NVS namespace %s, %d: %s", NK_BoardNamespace, err, esp_err_to_name(err));
        return false;
    }

    uint8_t cnt = 0;
    bool res = true;

    if (!GetString(nvh, NK_deviceName, deviceName)) { ++cnt; }
    if (!GetString(nvh, NK_mDNSname, mDNSname)) { ++cnt; }
    if (!GetString(nvh, NK_timeZone, timeZone)) { ++cnt; }
    if (!GetString(nvh, NK_srvNTP, srvNTP)) { ++cnt; }
    if (!GetString(nvh, NK_apPassword, apPassword)) { ++cnt; }

    if (cnt > 0) {
        log_d("%d errors when loading board configuration!", cnt);
        res= false;
    }

    for (uint8_t i = 0; i < wifiCnt; ++i) {
        if (!LoadWiFiConfig(&wifi[i], &cnt)) { res = false; }
        if (cnt > 0) {
            log_d("%d errors when loading WiFiConfig %d", cnt, i);
        }
    }

    if (!CustomLoad()) { res = false; }

    nvs_close(nvh);

    return res;
}

bool BoardConfig::Save(void)
{
    nvs_handle_t nvh;
    esp_err_t err = nvs_open(NK_BoardNamespace, NVS_READWRITE, &nvh);
    if (err != ESP_OK) {
        log_e("Error opening NVS namespace %s, %d: %s", NK_BoardNamespace, err, esp_err_to_name(err));
        return false;
    }

    uint8_t cnt = 0;
    bool res = true;

    if (!SetString(nvh, NK_deviceName, deviceName)) { ++cnt; }
    if (!SetString(nvh, NK_mDNSname, mDNSname)) { ++cnt; }
    if (!SetString(nvh, NK_timeZone, timeZone)) { ++cnt; }
    if (!SetString(nvh, NK_srvNTP, srvNTP)) { ++cnt; }
    if (!SetString(nvh, NK_apPassword, apPassword)) { ++cnt; }

    if (cnt > 0) {
        log_d("%d errors when saving board configuration!", cnt);
        res= false;
    }

    for (uint8_t i = 0; i < wifiCnt; ++i) {
        if (!SaveWiFiConfig(&wifi[i], &cnt, true)) { res = false; }
        if (cnt > 0) {
            log_d("%d errors when saving WiFiConfig %d", cnt, i);
        }
    }

    if (!CustomSave()) { res = false; }

    err = nvs_commit(nvh);
    if (err != ESP_OK) {
        log_e("Failed to commit NVS changes, %d: %s", err, esp_err_to_name(err));
        res = false;
    }

    nvs_close(nvh);

    return res;
}

bool BoardConfig::CustomInit(void) { return true; }
bool BoardConfig::CustomLoad(void) { return true; }
bool BoardConfig::CustomSave(void) { return true; }
bool BoardConfig::CustomEraseNamespace(void) { return true; }

void BoardConfig::BSSIDToStr(uint8_t *bssid)
{
    if (bssid == nullptr) {
        buffer[0] = 0;
        return;
    }
    snprintf(reinterpret_cast<char*>(buffer.data()), buffer.size(),
            "%02X:%02X:%02X:%02X:%02X:%02X",
            bssid[0], bssid[1], bssid[2], bssid[3], bssid[4], bssid[5]);
}

void BoardConfig::IPv4ToStr(uint32_t ip)
{
    if (ip == 0) {
        buffer[0] = 0;
        return;
    }

    esp_ip4_addr_t ip4 {};
    ip4.addr = ip;
    esp_ip4addr_ntoa(&ip4, reinterpret_cast<char*>(buffer.data()), buffer.size());
}

bool BoardConfig::BuildJsonDocument(void)
{
    jdoc.clear();

    // https://arduinojson.org/v7/

    /**
     * Attention !
     *    .to<JsonArray>()
     *    .add<JsonObject>()
     * and many other return references.
     * Quote from official docs: "Don’t pass that by reference or pointer because it would be a reference
     * to a reference, which is very confusing and can lead to dangling references if is reassigned!"
     */

    JsonObject jse = jdoc["settings"].to<JsonObject>();
    jse[NK_deviceName] = deviceName;
    jse[NK_mDNSname] = mDNSname;
    jse[NK_timeZone] = timeZone;
    jse[NK_srvNTP] = srvNTP;
    jse[NK_apPassword] = apPassword;

    for (unsigned int i = 0; i < wifiCnt; ++i) {
        JsonObject jsw = jse[NK_WiFiNamespace + std::to_string(i)].to<JsonObject>();

        std::string_view cSSID(reinterpret_cast<char*>(wifi[i].ssid), wifi[i].GetSSIDLen());
        jsw[NK_ssid] = cSSID;

        std::string_view cPass(reinterpret_cast<char*>(wifi[i].password), wifi[i].GetPasswordLen());
        jsw[NK_password] = cPass;

        if (wifi[i].bssidSet) {
            BSSIDToStr(wifi[i].bssid);
            jsw[NK_bssid] = reinterpret_cast<char*>(buffer.data());
        }
        else {
            jsw[NK_bssid] = "";
        }

        jsw[NK_useDHCP] = wifi[i].useDHCP ? "true" : "false";
        IPv4ToStr(wifi[i].address); jsw[NK_address] = reinterpret_cast<char*>(buffer.data());
        IPv4ToStr(wifi[i].mask);    jsw[NK_mask] = reinterpret_cast<char*>(buffer.data());
        IPv4ToStr(wifi[i].gateway); jsw[NK_gateway] = reinterpret_cast<char*>(buffer.data());
        IPv4ToStr(wifi[i].srvDNS1); jsw[NK_srvDNS1] = reinterpret_cast<char*>(buffer.data());
        IPv4ToStr(wifi[i].srvDNS2); jsw[NK_srvDNS2] = reinterpret_cast<char*>(buffer.data());
    }

    bool res = CustomBuildJsonDocument();

    if (res) {
        res = !jdoc.overflowed();
    }

    jdoc.shrinkToFit();

    return res;
}

bool BoardConfig::CustomBuildJsonDocument(void)
{
    // example code
    JsonObject jse = jdoc["settings"].as<JsonObject>();
    if (jse.isNull())
        return false;

    return true;
}

bool BoardConfig::SetFromJsonObject(const JsonObject& jse)
{
    if (jse.isNull())
        return false;

    InitDataToDefaults();

    const char *cstr;
    
    cstr = jse[NK_deviceName].as<const char*>();
    if (cstr != nullptr) {
        deviceName = cstr;
    }
    cstr = jse[NK_mDNSname].as<const char*>();
    if (cstr != nullptr) {
        mDNSname = cstr;
    }
    cstr = jse[NK_timeZone].as<const char*>();
    if (cstr != nullptr) {
        timeZone = cstr;
    }
    cstr = jse[NK_srvNTP].as<const char*>();
    if (cstr != nullptr) {
        srvNTP = cstr;
    }
    cstr = jse[NK_apPassword].as<const char*>();
    if (cstr != nullptr) {
        apPassword = cstr;
    }

    for (unsigned int i = 0; i < wifiCnt; ++i) {
        JsonObject jsw = jse[NK_WiFiNamespace + std::to_string(i)].as<JsonObject>();
        if (!jsw.isNull()) {
            esp_ip4_addr_t ipa {};

            cstr = jsw[NK_ssid].as<const char*>();
            if (cstr != nullptr) {
                strncpy(reinterpret_cast<char*>(wifi[i].ssid), cstr, sizeof(wifi[i].ssid));
            }
            cstr = jsw[NK_password].as<const char*>();
            if (cstr != nullptr) {
                strncpy(reinterpret_cast<char*>(wifi[i].password), cstr, sizeof(wifi[i].password));
            }

            cstr = jsw[NK_bssid].as<const char*>();
            if (cstr != nullptr) {
                if (*cstr != '\0') {
                    sscanf(cstr, "%hhx:%hhx:%hhx:%hhx:%hhx:%hhx",
                        &wifi[i].bssid[0], &wifi[i].bssid[1], &wifi[i].bssid[2],
                        &wifi[i].bssid[3], &wifi[i].bssid[4], &wifi[i].bssid[5]);
                    wifi[i].bssidSet = true;
                }
            }

            cstr = jsw[NK_useDHCP].as<const char*>();
            if (cstr != nullptr) {
                wifi[i].useDHCP = (strcmp(cstr, "true") == 0);
            }

            cstr = jsw[NK_address].as<const char*>();
            if (cstr != nullptr) {
                if (*cstr != '\0') {
                    wifi[i].address = esp_ip4addr_aton(cstr);
                }
            }
            cstr = jsw[NK_mask].as<const char*>();
            if (cstr != nullptr) {
                if (*cstr != '\0') { 
                    wifi[i].mask = esp_ip4addr_aton(cstr);
                }
            }
            cstr = jsw[NK_gateway].as<const char*>();
            if (cstr != nullptr) {
                if (*cstr != '\0') {
                    wifi[i].gateway = esp_ip4addr_aton(cstr);
                }
            }
            cstr = jsw[NK_srvDNS1].as<const char*>();
            if (cstr != nullptr) {
                if (*cstr != '\0') {
                    wifi[i].srvDNS1 = esp_ip4addr_aton(cstr);
                }
            }
            cstr = jsw[NK_srvDNS2].as<const char*>();
            if (cstr != nullptr) {
                if (*cstr != '\0') {
                    wifi[i].srvDNS2 = esp_ip4addr_aton(cstr);
                }
            }
        }
    }

    return CustomSetFromJsonObject(jse);
}

bool BoardConfig::CustomSetFromJsonObject(const JsonObject& jse) {
    return !jse.isNull();
}

bool BoardConfig::GetBool(nvs_handle_t nvsh, const char *key, bool *out)
{
    uint8_t val = 0;
    bool res = GetU8(nvsh, key, &val);
    if (res)
        if (out != nullptr)
            *out = val;
    return res;
}

bool BoardConfig::GetU8(nvs_handle_t nvsh, const char *key, uint8_t *out)
{
    if (key == nullptr) return false;

    nvs_type_t dataType;
    esp_err_t err = nvs_find_key(nvsh, key, &dataType);
    if (err == ESP_ERR_NVS_NOT_FOUND) {
        log_d("Error: the key %s doesn't exist!", key);
        return false;
    }
    if (err != ESP_OK) {
        log_d("Error: nvs_find_key %s, %d: %s", key, err, esp_err_to_name(err));
        return false;
    }
    if (dataType != NVS_TYPE_U8) {
        log_d("Error: wrong data type for %s", key);
        return false;
    }

    if (out == nullptr) return true;

    err = nvs_get_u8(nvsh, key, out);
    if (err != ESP_OK) {
        log_d("Error: nvs_get_u8 %s, %d: %s", key, err, esp_err_to_name(err));
        return false;
    }
    return true;
}

bool BoardConfig::GetI8(nvs_handle_t nvsh, const char *key, int8_t *out)
{
    if (key == nullptr) return false;

    nvs_type_t dataType;
    esp_err_t err = nvs_find_key(nvsh, key, &dataType);
    if (err == ESP_ERR_NVS_NOT_FOUND) {
        log_d("Error: the key %s doesn't exist!", key);
        return false;
    }
    if (err != ESP_OK) {
        log_d("Error: nvs_find_key %s, %d: %s", key, err, esp_err_to_name(err));
        return false;
    }
    if (dataType != NVS_TYPE_I8) {
        log_d("Error: wrong data type for %s", key);
        return false;
    }

    if (out == nullptr) return true;

    err = nvs_get_i8(nvsh, key, out);
    if (err != ESP_OK) {
        log_d("Error: nvs_get_i8 %s, %d: %s", key, err, esp_err_to_name(err));
        return false;
    }
    return true;
}

bool BoardConfig::GetU32(nvs_handle_t nvsh, const char *key, uint32_t *out)
{
    if (key == nullptr) return false;

    nvs_type_t dataType;
    esp_err_t err = nvs_find_key(nvsh, key, &dataType);
    if (err == ESP_ERR_NVS_NOT_FOUND) {
        log_d("Error: the key %s doesn't exist!", key);
        return false;
    }
    if (err != ESP_OK) {
        log_d("Error: nvs_find_key %s, %d: %s", key, err, esp_err_to_name(err));
        return false;
    }
    if (dataType != NVS_TYPE_U32) {
        log_d("Error: wrong data type for %s", key);
        return false;
    }

    if (out == nullptr) return true;

    err = nvs_get_u32(nvsh, key, out);
    if (err != ESP_OK) {
        log_d("Error: nvs_get_u32 %s, %d: %s", key, err, esp_err_to_name(err));
        return false;
    }
    return true;
}

bool BoardConfig::GetBlob(nvs_handle_t nvsh, const char *key, void *data, size_t length)
{
    if (key == nullptr) return false;
    if (length > buffer.size()) {
        log_d("Error: Max allowed length is %d bytes!", buffer.size());
        return false;
    }

    nvs_type_t dataType;
    esp_err_t err = nvs_find_key(nvsh, key, &dataType);
    if (err == ESP_ERR_NVS_NOT_FOUND) {
        log_d("Error: the key %s doesn't exist!", key);
        return false;
    }
    if (err != ESP_OK) {
        log_d("Error: nvs_find_key %s, %d: %s", key, err, esp_err_to_name(err));
        return false;
    }
    if (dataType != NVS_TYPE_BLOB) {
        log_d("Error: wrong data type for %s", key);
        return false;
    }

    size_t mlen = length;
    err = nvs_get_blob(nvsh, key, buffer.data(), &mlen);
    if (err != ESP_OK) {
        log_d("Error: nvs_get_blob %s, %d: %s", key, err, esp_err_to_name(err));
        return false;
    }
    if (mlen != length) {
        log_d("Error: wrong length for %s %d/%d", key, mlen, length);
        return false;
    }
    if (data != nullptr) {
        memcpy(data, buffer.data(), length);
    }
    return true;
}

bool BoardConfig::GetString(nvs_handle_t nvsh, const char *key, std::string& str)
{
    if (key == nullptr) return false;

    nvs_type_t dataType;
    esp_err_t err = nvs_find_key(nvsh, key, &dataType);
    if (err == ESP_ERR_NVS_NOT_FOUND) {
        log_d("Error: the key %s doesn't exist!", key);
        return false;
    }
    if (err != ESP_OK) {
        log_d("Error: nvs_find_key %s, %d: %s", key, err, esp_err_to_name(err));
        return false;
    }
    if (dataType != NVS_TYPE_STR) {
        log_d("Error: wrong data type for %s", key);
        return false;
    }

    size_t mlen = 0;
    err = nvs_get_str(nvsh, key, nullptr, &mlen);
    if (err != ESP_OK && err != ESP_ERR_NVS_INVALID_LENGTH) {
        log_d("Error: nvs_get_str len %s, %d: %s", key, err, esp_err_to_name(err));
        return false;
    }

    str.reserve(mlen);
    mlen = str.capacity();
    err = nvs_get_str(nvsh, key, &str[0], &mlen);
    if (err != ESP_OK) {
        log_d("Error: nvs_get_str %s, %d: %s", key, err, esp_err_to_name(err));
        return false;
    }

    return true;
}

bool BoardConfig::SetBool(nvs_handle_t nvsh, const char *key, bool value)
{
    if (key == nullptr) return false;

    nvs_type_t dataType;
    uint8_t data;
    esp_err_t err = nvs_find_key(nvsh, key, &dataType);
    if (err == ESP_OK && dataType == NVS_TYPE_U8) {
        err = nvs_get_u8(nvsh, key, &data);
        if (err == ESP_OK) {
            if ((data > 0) == value) {
                return true;
            }
        }
    }

    err = nvs_set_u8(nvsh, key, value ? 1 : 0);
    if (err != ESP_OK) {
        log_d("Failed to set %s, %d: %s", key, err, esp_err_to_name(err));
        return false;
    }
    return true;
}

bool BoardConfig::SetU8(nvs_handle_t nvsh, const char *key, uint8_t value)
{
    if (key == nullptr) return false;

    nvs_type_t dataType;
    uint8_t data;
    esp_err_t err = nvs_find_key(nvsh, key, &dataType);
    if (err == ESP_OK && dataType == NVS_TYPE_U8) {
        err = nvs_get_u8(nvsh, key, &data);
        if (err == ESP_OK) {
            if (data == value) {
                return true;
            }
        }
    }

    err = nvs_set_u8(nvsh, key, value);
    if (err != ESP_OK) {
        log_d("Failed to set %s, %d: %s", key, err, esp_err_to_name(err));
        return false;
    }
    return true;
}

bool BoardConfig::SetI8(nvs_handle_t nvsh, const char *key, int8_t value)
{
    if (key == nullptr) return false;

    nvs_type_t dataType;
    int8_t data;
    esp_err_t err = nvs_find_key(nvsh, key, &dataType);
    if (err == ESP_OK && dataType == NVS_TYPE_I8) {
        err = nvs_get_i8(nvsh, key, &data);
        if (err == ESP_OK) {
            if (data == value) {
                return true;
            }
        }
    }

    err = nvs_set_i8(nvsh, key, value);
    if (err != ESP_OK) {
        log_d("Failed to set %s, %d: %s", key, err, esp_err_to_name(err));
        return false;
    }
    return true;
}

bool BoardConfig::SetU32(nvs_handle_t nvsh, const char *key, uint32_t value)
{
    if (key == nullptr) return false;

    nvs_type_t dataType;
    uint32_t data;
    esp_err_t err = nvs_find_key(nvsh, key, &dataType);
    if (err == ESP_OK && dataType == NVS_TYPE_U32) {
        err = nvs_get_u32(nvsh, key, &data);
        if (err == ESP_OK) {
            if (data == value) {
                return true;
            }
        }
    }

    err = nvs_set_u32(nvsh, key, value);
    if (err != ESP_OK) {
        log_d("Failed to set %s, %d: %s", key, err, esp_err_to_name(err));
        return false;
    }
    return true;
}

bool BoardConfig::SetBlob(nvs_handle_t nvsh, const char *key, void *data, size_t length)
{
    if (key == nullptr) return false;
    if (length > buffer.size()) {
        log_d("Error: Max allowed length is %d bytes!", buffer.size());
        return false;
    }

    nvs_type_t dataType;
    size_t mlen = length;
    esp_err_t err = nvs_find_key(nvsh, key, &dataType);
    if (err == ESP_OK && dataType == NVS_TYPE_BLOB) {
        err = nvs_get_blob(nvsh, key, buffer.data(), &mlen);
        if (err == ESP_OK && mlen == length) {
            if (memcmp(buffer.data(), data, length) == 0) {
                return true;
            }
        }
    }

    err = nvs_set_blob(nvsh, key, data, length);
    if (err != ESP_OK) {
        log_d("Failed to set %s, %d: %s", key, err, esp_err_to_name(err));
        return false;
    }
    return true;
}

bool BoardConfig::SetString(nvs_handle_t nvsh, const char *key, std::string& str)
{
    if (key == nullptr) return false;
    if (str.length() >= buffer.size()) {
        log_d("Error: Max allowed length is %d chars!", buffer.size() - 1);
        return false;
    }

    /**
     * @note: to reduce heap fragmentation, this function uses the `buffer` variable as temporary storage.
     * A temporary std::string, char* or the like will increase heap usage and fragmentation.
     * A std::string as class member will just increase "static" memory usage, instead, a bigger `buffer`
     * is what I decided to use, also shared with GetBlob and SetBlob functions.
     */

    nvs_type_t dataType;
    esp_err_t err = nvs_find_key(nvsh, key, &dataType);
    if (err == ESP_OK && dataType == NVS_TYPE_STR) {
        size_t mlen = 0;
        err = nvs_get_str(nvsh, key, nullptr, &mlen);
        // mlen should be the required length, including the zero terminator
        if ((err == ESP_OK || err == ESP_ERR_NVS_INVALID_LENGTH) && ((mlen - 1) == str.length())) {
            err = nvs_get_str(nvsh, key, reinterpret_cast<char*>(buffer.data()), &mlen);
            if (err == ESP_OK && ((mlen - 1) == str.length())) {
                if (memcmp(buffer.data(), &str[0], str.length()) == 0) {
                    return true;
                }
            }
        }
    }

    err = nvs_set_str(nvsh, key, str.c_str());
    if (err != ESP_OK) {
        log_d("Failed to set %s, %d: %s", key, err, esp_err_to_name(err));
        return false;
    }
    return true;
}

bool BoardConfig::LoadWiFiConfig(WiFiConfig *cfg, uint8_t *failed)
{    
    if (cfg == nullptr) {
        if (failed != nullptr) *failed = 0;
        return false;
    }

    nvs_handle_t nwh;

    snprintf(reinterpret_cast<char*>(buffer.data()), buffer.size(), "%s%d", NK_WiFiNamespace, cfg->saveIndex);

    esp_err_t err = nvs_open(reinterpret_cast<const char*>(buffer.data()), NVS_READONLY, &nwh);
    if (err != ESP_OK) {
        log_e("Error opening NVS handle, %d: %s", err, esp_err_to_name(err));
        if (failed != nullptr) *failed = 0;
        return false;
    }

    uint8_t u8 = cfg->saveIndex;
    cfg->Initialize();
    cfg->saveIndex = u8;

    uint8_t cnt = 0;

    if (!GetBlob(nwh, NK_ssid, &(cfg->ssid), 32)) { ++cnt; }
    if (!GetBlob(nwh, NK_password, &(cfg->password), 64)) { ++cnt; }
    if (!GetBool(nwh, NK_bssidSet, &(cfg->bssidSet))) { ++cnt; }
    if (!GetBlob(nwh, NK_bssid, &(cfg->bssid), 6)) { ++cnt; }
    if (!GetBool(nwh, NK_useDHCP, &(cfg->useDHCP))) { ++cnt; }
    if (!GetU32(nwh, NK_address, &(cfg->address))) { ++cnt; }
    if (!GetU32(nwh, NK_mask, &(cfg->mask))) { ++cnt; }
    if (!GetU32(nwh, NK_gateway, &(cfg->gateway))) { ++cnt; }
    if (!GetU32(nwh, NK_srvDNS1, &(cfg->srvDNS1))) { ++cnt; }
    if (!GetU32(nwh, NK_srvDNS2, &(cfg->srvDNS2))) { ++cnt; }

    if (!GetU8(nwh, NK_minSearchAM, &u8)) { ++cnt; }
    else { cfg->msamSet(u8); }

    if (!GetBool(nwh, NK_enRoaming, &(cfg->enableRoaming))) { ++cnt; }
    if (!GetI8(nwh, NK_minRSSI, &(cfg->minRSSI))) { ++cnt; }

    if (failed != nullptr) *failed = cnt;

    nvs_close(nwh);

    return (cnt == 0);
}

bool BoardConfig::SaveWiFiConfig(WiFiConfig *cfg, uint8_t *failed, bool skipCommit)
{
    if (cfg == nullptr) {
        if (failed != nullptr) *failed = 0;
        return false;
    }

    nvs_handle_t nwh;

    snprintf(reinterpret_cast<char*>(buffer.data()), buffer.size(), "%s%d", NK_WiFiNamespace, cfg->saveIndex);

    esp_err_t err = nvs_open(reinterpret_cast<const char*>(buffer.data()), NVS_READWRITE, &nwh);
    if (err != ESP_OK) {
        log_e("Error opening NVS handle, %d: %s", err, esp_err_to_name(err));
        if (failed != nullptr) *failed = 0;
        return false;
    }

    uint8_t cnt = 0;

    if (!SetBlob(nwh, NK_ssid, cfg->ssid, 32)) { ++cnt; }
    if (!SetBlob(nwh, NK_password, cfg->password, 64)) { ++cnt; }
    if (!SetBool(nwh, NK_bssidSet, cfg->bssidSet)) { ++cnt; }
    if (!SetBlob(nwh, NK_bssid, cfg->bssid, 6)) { ++cnt; }
    if (!SetBool(nwh, NK_useDHCP, cfg->useDHCP)) { ++cnt; }
    if (!SetU32(nwh, NK_address, cfg->address)) { ++cnt; }
    if (!SetU32(nwh, NK_mask, cfg->mask)) { ++cnt; }
    if (!SetU32(nwh, NK_gateway, cfg->gateway)) { ++cnt; }
    if (!SetU32(nwh, NK_srvDNS1, cfg->srvDNS1)) { ++cnt; }
    if (!SetU32(nwh, NK_srvDNS2, cfg->srvDNS2)) { ++cnt; }
    if (!SetU8(nwh, NK_minSearchAM, cfg->msamGet())) { ++cnt; }
    if (!SetBool(nwh, NK_enRoaming, cfg->enableRoaming)) { ++cnt; }
    if (!SetI8(nwh, NK_minRSSI, cfg->minRSSI)) { ++cnt; }

    if (failed != nullptr) *failed = cnt;

    if (!skipCommit) {
        err = nvs_commit(nwh);
        if (err != ESP_OK) {
            log_e("Failed to commit WiFi NVS changes, %d: %s", err, esp_err_to_name(err));
            ++cnt;
        }
    }

    nvs_close(nwh);

    return (cnt == 0);
}
