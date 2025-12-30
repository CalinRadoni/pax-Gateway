#ifndef webSrv_H
#define webSrv_H

#include <Arduino.h>
#include <FS.h>
#include <SPIFFS.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>

class WebSrv
{
public:
    WebSrv(void);
    virtual ~WebSrv();

    AsyncWebServer web = AsyncWebServer(80);
    AsyncWebSocket ws = AsyncWebSocket("/ws"); // access at ws://[esp ip]/ws
    AsyncEventSource events = AsyncEventSource("/events"); // event source (Server-Sent events)

    void OnEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type, void *arg, uint8_t *data, size_t len);
    void OnNotFound(AsyncWebServerRequest *request);
    void OnRequest(AsyncWebServerRequest *request);
    void OnRequestBody(AsyncWebServerRequest *request, uint8_t *data, size_t len, size_t index, size_t total);
    void OnFileUpload(AsyncWebServerRequest *request, String filename, size_t index, uint8_t *data, size_t len, bool final);

    virtual void ProcessWSData(uint32_t clientID, AwsFrameInfo *info, uint8_t *data, size_t len);

    void Begin(void);
    void End(void);
    void CleanupClients(void);
};

#endif
