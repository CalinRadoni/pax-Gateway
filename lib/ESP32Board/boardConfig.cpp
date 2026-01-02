#include "boardConfig.h"

#include "nvs_flash.h"
#include "nvs.h"

const unsigned int BoardConfig::wifiCnt;

const char* nvsNamespace = "ESP32Board";
const char* nvsNsStatus = "nsStatus";

BoardConfig::BoardConfig(void)
{
    nsStatus = 0;
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
            log_e("Failed to erase the default NVS partition [%d : %s]",
                err,
                esp_err_to_name(err));
            return false;
        }
        log_i("NVS erased");
        
        err = nvs_flash_init();
    }
    if (err != ESP_OK) {
        log_e("Failed to initialize the default NVS partition [%d : %s]",
            err,
            esp_err_to_name(err));
        return false;
    }

    log_i("NVS initialized");
    return true;
}

bool BoardConfig::EmptyNamespace(void)
{
    if (!prefs.begin(nvsNamespace, false)) {
        log_e("Failed to open namespace [%s]", nvsNamespace);
        return false;
    }

    bool res = prefs.clear();
    if (!res) {
        log_e("Failed to empty %s namespace", nvsNamespace);
    }
    else {
        log_i("Namespace %s empty", nvsNamespace);
    }
    prefs.end();

    return res;
}

bool BoardConfig::EraseDefaultNVS(void)
{
    esp_err_t err = nvs_flash_erase();
    if (err != ESP_OK) {
        log_e("Failed to erase the default NVS partition [%d : %s]",
            err,
            esp_err_to_name(err));
        return false;
    }
    log_i("NVS erased");

    err = nvs_flash_init();
    if (err != ESP_OK) {
        log_e("Failed to initialize the default NVS partition [%d : %s]",
            err,
            esp_err_to_name(err));
        return false;
    }
    log_i("NVS initialized");

    return true;
}

bool BoardConfig::cPutInt(const char *key, int32_t val)
{
    int32_t actualVal = prefs.getInt(key);
    if (actualVal == val) { return true; }

    size_t cnt = prefs.putInt(key, val);

    return (cnt == 0) ? false : true;
}

bool BoardConfig::cPutUInt(const char *key, uint32_t val)
{
    uint32_t actualVal = prefs.getUInt(key);
    if (actualVal == val) { return true; }

    size_t cnt = prefs.putUInt(key, val);

    return (cnt == 0) ? false : true;
}

bool BoardConfig::cPutString(const char *key, String val)
{
    String actualVal = prefs.getString(key);
    if (actualVal.equals(val)) { return true; }

    size_t cnt = prefs.putString(key, val);
    if (cnt == 0) {
        if(val.length() != 0) {
            return false;
        }
    }

    return true;
}

bool BoardConfig::Initialize(void)
{
    bool res = InitializeNVS();

    res &= InitializeNamespace();

    for (unsigned int i = 0; i < wifiCnt; ++i) {
        wifi[i].Initialize();
    }

    mDNSname.clear();

    gmtOffset = 0;
    daylightOffset = 0;
    srvNTP.clear();

    res &= CustomInit();

    return res;
}

bool BoardConfig::InitializeNamespace(void)
{
    // Open (or create and then open if it does not yet exist) the namespace in RW mode
    // Ignore the function return value, false may be because of an error on just because
    // the namespace does not yet exists.
    prefs.begin(nvsNamespace, false);
    if (!prefs.isKey(nvsNsStatus)) {
        prefs.putUChar(nvsNsStatus, (uint8_t)1);
        prefs.end();
    }

    if (!prefs.begin(nvsNamespace, true)) {
        log_e("Failed to open namespace [%s]", nvsNamespace);
        return false;
    }
    nsStatus = prefs.getUChar(nvsNsStatus, 0);
    prefs.end();

    if (nsStatus == 0) {
        log_e("Namespace status is 0, is namespace initialized ?");
        return false;
    }

    return true;
}

bool BoardConfig::Load(void)
{
    if (!prefs.begin(nvsNamespace, true)) {
        log_e("Failed to open namespace [%s]", nvsNamespace);
        return false;
    }

    // TODO nsStatus enum
    nsStatus = prefs.getUChar(nvsNsStatus, 0);
    switch (nsStatus) {
        case 0:
            log_e("Namespace status is 0, is namespace initialized ?");
            break;
        case 1:
            // TODO: should set default values and set nsStatus to 2
            break;
        default: break;
    }

    for (unsigned int i = 0; i < wifiCnt; ++i) {
        String base = "w";
        base += i;
        String str;

        str = base + "SSID"; wifi[i].SSID = prefs.getString(str.c_str());
        str = base + "Pass"; wifi[i].Pass = prefs.getString(str.c_str());

        uint32_t flags;
        str = base + "Flags"; flags = prefs.getUInt(str.c_str());
        wifi[i].useStaticIP = (flags & 0x01);

        str = base + "addr";    wifi[i].address = prefs.getUInt(str.c_str());
        str = base + "mask";    wifi[i].mask    = prefs.getUInt(str.c_str());
        str = base + "gateway"; wifi[i].gateway = prefs.getUInt(str.c_str());
        str = base + "srvDNS1"; wifi[i].srvDNS1 = prefs.getUInt(str.c_str());
        str = base + "srvDNS2"; wifi[i].srvDNS2 = prefs.getUInt(str.c_str());
    }

    mDNSname = prefs.getString("mDNSname");

    gmtOffset = prefs.getLong("gmtOffset");
    daylightOffset = prefs.getInt("daylightOffset");
    srvNTP = prefs.getString("srvNTP");

    bool res = CustomLoad();

    prefs.end();
    return res;
}

bool BoardConfig::Save(void)
{
    if (!prefs.begin(nvsNamespace, false)) {
        log_e("Failed to open namespace [%s]", nvsNamespace);
        return false;
    }

    bool res = true;
    size_t cnt;

    for (unsigned int i = 0; i < wifiCnt; ++i) {
        String base = "w";
        base += i;
        String str;

        str = base + "SSID"; if (!cPutString(str.c_str(), wifi[i].SSID)) res = false;
        str = base + "Pass"; if (!cPutString(str.c_str(), wifi[i].Pass)) res = false;

        uint32_t flags = 0;
        if (wifi[i].useStaticIP) { flags |= 0x01; }

        str = base + "Flags";   if (!cPutUInt(str.c_str(), flags)) res = false;
        str = base + "addr";    if (!cPutUInt(str.c_str(), wifi[i].address)) res = false;
        str = base + "mask";    if (!cPutUInt(str.c_str(), wifi[i].mask))    res = false;
        str = base + "gateway"; if (!cPutUInt(str.c_str(), wifi[i].gateway)) res = false;
        str = base + "srvDNS1"; if (!cPutUInt(str.c_str(), wifi[i].srvDNS1)) res = false;
        str = base + "srvDNS2"; if (!cPutUInt(str.c_str(), wifi[i].srvDNS2)) res = false;
    }

    if (!cPutString("mDNSname", mDNSname)) res = false;

    if (!cPutInt("gmtOffset", gmtOffset)) res = false;
    if (!cPutInt("daylightOffset", daylightOffset)) res = false;
    if (!cPutString("srvNTP", srvNTP)) res = false;

    if (!CustomSave()) res = false;

    prefs.end();
    return res;
    return false;
}

bool BoardConfig::CustomInit(void) { return true; }
bool BoardConfig::CustomLoad(void) { return true; }
bool BoardConfig::CustomSave(void) { return true; }
