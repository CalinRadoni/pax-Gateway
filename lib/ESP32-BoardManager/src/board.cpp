#include "board.h"

#include <Wire.h>
#include <Update.h>
#include <esp_ota_ops.h>
#include <mdns.h>

Board::Board(void)
{
    // BoardQueue constructor creates the message queue automatically
}

Board::~Board()
{
    //
}

#ifdef ShowDirectoryListing
void listDir(fs::FS &fs, const char *dirname, uint8_t levels) {
  Serial.printf("Listing directory: %s\r\n", dirname);

  File root = fs.open(dirname);
  if (!root) {
    Serial.println("- failed to open directory");
    return;
  }
  if (!root.isDirectory()) {
    Serial.println(" - not a directory");
    return;
  }

  File file = root.openNextFile();
  while (file) {
    if (file.isDirectory()) {
      Serial.print("  DIR : ");
      Serial.println(file.name());
      if (levels) {
        listDir(fs, file.path(), levels - 1);
      }
    } else {
      Serial.print("  FILE: ");
      Serial.print(file.name());
      Serial.print("\tSIZE: ");
      Serial.println(file.size());
    }
    file = root.openNextFile();
  }
}
#endif

unsigned int Board::Initialize(BoardConfig *cfgIn)
{
    boardConfig = cfgIn;

    if (!Init_level0()) { return 0; }

    if (boardConfig == nullptr) { return 0; }

    boardConfig->Initialize();
    if (!boardConfig->Load()) {
        log_w("Failed to load configuration");
    }

    if (!Init_level1()) { return 1; }

    Wire.setPins(SDA_pin, SCL_pin); // call Wire.begin() after this call or call it like Wire.begin(pinSDA, pinSCL)
    Wire.begin();
      
    wifiManager.config = boardConfig;
    wifiManager.Initialize();

    PrintApplicationDescription();

    if(!Init_level2()) { return 2; }

    /**
     * LittleFS.begin default arguments are:
     *   bool formatOnFail = false
     *   const char *basePath = "/littlefs"
     *   (deprecated, not used) uint8_t maxOpenFiles = 10
     *   const char *partitionLabel = "spiffs"
     * Initialize LittleFS, format if begin failed.
     * If 'partitionLabel' != null it will use the partition with that label
     * If 'partitionLabel' == null it will use the first partition with type data and subtype littlefs
     */
    if (!LittleFS.begin(true, "/files", 0, "fs")) {
        log_e("Failed to initialize LittleFS");
    }
    else {
        log_n("LittleFS initialized, %d free from %d", LittleFS.usedBytes(), LittleFS.totalBytes());
        #ifdef ShowDirectoryListing
        listDir(LittleFS, "/", 99);
        #endif
    }

    wifiManager.Connect();

    WiFiManagerState wmState = wifiManager.GetState();

    if (WiFiManagerState::Connected != wmState) {
        log_n("Starting AP ...");
        wifiManager.StartAP();
        
        wmState = wifiManager.GetState();
    }

    if (WiFiManagerState::Connected == wmState || WiFiManagerState::APMode == wmState) {
        log_n("Starting the web server");
        // "begin" the server only if connected or AP mode
        webSrv.Begin(&boardMessageQueue);
    }

    if (!Init_level3()) { return 3; }

    return 0xFF;
}

WiFiManagerState Board::GetWiFiState(void)
{
    return wifiManager.GetState();
}

void Board::ResetBoard(uint32_t delayMS)
{
    log_i("Resetting the board");

    CustomReset();

    if (delayMS > 0) {
        delay(delayMS);
    }
    ESP.restart();
}

bool Board::CheckConnection(bool restartOnFail)
{
    #pragma warning CheckConnection must be rebuilt

    return true;
}

bool Board::UpdateFromLink(String link)
{
#ifdef USE_UpdateFromWeb
    return webUpdater.UpdateFromLink(link);
#else
    return false;
#endif
}

void Board::PrintApplicationDescription(void)
{
    // const esp_app_desc_t *appDesc = esp_ota_get_app_description();
    const esp_app_desc_t *appDesc = esp_app_get_description();
    if (appDesc == nullptr) {
        log_e("Failed to get application description");
        return;
    }

    log_i("%s %s", appDesc->project_name, appDesc->version);
    log_i("Compiled with ESP-IDF %s on %s %s",
        appDesc->idf_ver,
        appDesc->date,
        appDesc->time);
}

void Board::ScanI2CBus(void)
{
    log_i("Scanning for I2C devices ...");
    for (byte address = 0x01; address < 0x7f; ++address) {
        Wire.beginTransmission(address);
        byte error = Wire.endTransmission();
        if (error == 0) {
            log_i("I2C device found at address 0x%02X", address);
        } else if (error != 2) {
            log_i("Error %d at address 0x%02X", error, address);
        }
    }
    log_i("Done scanning for I2C devices.");
}

esp_err_t Board::Start_mDNS(void)
{
    if (mDNS_started) { return ESP_OK; }

    if (boardConfig == nullptr) { return ESP_FAIL; }

    esp_err_t err = mdns_init();
    if (err != ESP_OK) {
        log_e("mdns_init failed: %d", err);
        return err;
    }

    err = mdns_hostname_set(boardConfig->mDNSname.c_str());
    if (err != ESP_OK) {
        log_e("mdns_hostname_set failed: %d", err);
        mdns_free();
        return err;
    }

    err = mdns_instance_name_set(boardConfig->mDNSname.c_str());
    if (err != ESP_OK) {
        log_e("mdns_instance_name_set failed: %d", err);
        mdns_free();
        return err;
    }

    err = mdns_service_add(NULL, "_http", "_tcp", 80, NULL, 0);
    if (err != ESP_OK) {
        log_e("mdns_service_add failed: %d", err);
        mdns_free();
        return err;
    }

    mDNS_started = true;
    return err;
}

esp_err_t Board::Stop_mDNS(void)
{
    if (!mDNS_started) { return ESP_OK; }

    esp_err_t err = mdns_service_remove_all();
    if (err != ESP_OK) {
        log_e("mdns_service_remove_all failed: %d", err);
    }

    mdns_free();
    mDNS_started = false;

    return err;
}

void Board::CheckQueue(void)
{
    if (!boardMessageQueue.IsValid()) {
        log_e("Board message queue is not valid!");
        return;
    }

    BoardMessage msg;
    while (boardMessageQueue.Receive(&msg, 0)) {
        switch (msg.type) {
            case BoardMessageType::WiFi_Connected:
                break;
            case BoardMessageType::WiFi_Disconnected:
                break;
            case BoardMessageType::WiFi_ScanComplete:
                break;
            case BoardMessageType::WiFi_ConnectionFailed:
                break;

            case BoardMessageType::WS_TextMessageReceived:
                ProcessBoardMessage(&msg);
                break;

            case BoardMessageType::WS_BinaryMessageReceived:
                break;

            default:
                log_w("Unknown message type received: %d", static_cast<uint8_t>(msg.type));
                break;
        }
    }
}

void Board::ProcessBoardMessage(const BoardMessage *msg)
{
    if (msg == nullptr) { return; }
    if (msg->data == nullptr) { return; }

    ClientContext *ctx = reinterpret_cast<ClientContext*>(msg->data);
    if(ctx->buffDataLen == 0) { return; }

    JsonDocument jdoc;
    DeserializationError err = deserializeJson(jdoc, ctx->buffData, ctx->buffDataLen);
    if (err) {
        log_e("Failed to parse JSON message: %s", err.c_str());
        return;
    }

    const char *cmd = jdoc["cmd"];
    if (cmd == nullptr) {
        log_e("JSON message does not contain 'cmd' field");
        return;
    }

    if (strcmp(cmd, "getSettings") == 0) {
        if (boardConfig->BuildJsonDocument()) {
            std::string str;
            serializeJson(boardConfig->jdoc, str);
            webSrv.SendWSMessage(ctx, str.c_str());
        }
        return;
    }

    if (strcmp(cmd, "setSettings") == 0) {
        JsonObject jse = jdoc["data"];
        if (jse.isNull()) {
            log_e("JSON message does not contain the 'data' object");
            return;
        }

        if (!boardConfig->SetFromJsonObject(jse)) {
            log_e("Failed to update settings from JSON object");
            return;
        }

        if (!boardConfig->Save()) {
            log_e("Failed to save updated settings");
            return;
        }
        
        webSrv.SendWSMessage(ctx, "{\"status\":\"Settings saved\"}");
        return;
    }

    CustomProcessBoardMessage(ctx, jdoc);
}

void Board::CustomProcessBoardMessage(ClientContext *ctx, const JsonDocument& jdoc)
{
    if (ctx == nullptr) { return; }

    /**
     * Prior to calling this function, the jdoc is already parsed and the "cmd" field is available.
     * You can process your custom commands here.
     * Example code follows.
     */
    const char *cmd = jdoc["cmd"];
    if (strcmp(cmd, "customCommand") == 0) {
        // process custom command

        // (optional) send response
        webSrv.SendWSMessage(ctx, "{\"status\":\"success\"}");
    }
}
