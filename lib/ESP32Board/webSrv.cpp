#include "webSrv.h"

WebSrv::WebSrv(void)
{
    //
}

WebSrv::~WebSrv()
{
    //
}

void WebSrv::OnRequest(AsyncWebServerRequest *request)
{
    //
}

void WebSrv::OnRequestBody(AsyncWebServerRequest *request, uint8_t *data, size_t len, size_t index, size_t total)
{
    // https://github.com/me-no-dev/ESPAsyncWebServer/blob/master/examples/ESP_AsyncFSBrowser/ESP_AsyncFSBrowser.ino
}

void WebSrv::OnFileUpload(AsyncWebServerRequest *request, String filename, size_t index, uint8_t *data, size_t len, bool final)
{
    // https://github.com/me-no-dev/ESPAsyncWebServer/blob/master/examples/ESP_AsyncFSBrowser/ESP_AsyncFSBrowser.ino
}

void WebSrv::OnEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type, void *arg, uint8_t *data, size_t len)
{
    switch(type) {
    case WS_EVT_CONNECT:
        log_i("ws %s %u connect", server->url(), client->id());
        break;
    case WS_EVT_DISCONNECT:
        log_i("ws %s %u disconnect", server->url(), client->id());
        break;
    case WS_EVT_ERROR:
        log_e("ws %s %u error %u: %s", server->url(), client->id(), *((uint16_t*)arg), (char*)data);
        break;
    case WS_EVT_PONG:
        log_i("ws %s %u pong[%u]: %s", server->url(), client->id(), len, (len > 0) ? (char*)data : "");
        break;
    case WS_EVT_DATA:
        ProcessWSData(client->id(), (AwsFrameInfo*)arg, data, len);
        break;
    default:
        break;
    }
}

void WebSrv::ProcessWSData(uint32_t clientID, AwsFrameInfo *info, uint8_t *data, size_t len)
{
    if (info == nullptr) return;
    if (data == nullptr) return;
    if (len == 0) return;

    // A long message was received in multiple packets (fragmented frame, not multiple frames):
    // - info->index, info->len and len wer OK
    // - not OK: num is not increased and may be !=0
    // - not OK: final was always set
    // I have only seen long messages with a single, fragmented, frame and not with multiple frames

    // TODO: This is a test implementation, msg should be external and client dependent !!!

    if (info->index == 0) {
        // beginning of data
        // the client dependent buffer should be cleared
    }

    String msg = "";
    if (info->opcode == WS_TEXT) {
        for(size_t i = 0; i < len; ++i) {
            msg += (char)data[i];
        }
    } else {
        char buff[4];
        for (size_t i = 0; i < len; ++i) {
            sprintf(buff, "%02x ", (uint8_t)data[i]);
            msg += buff;
        }
    }

    if ((info->index + len) == info->len) {
        // all data was received
        if (info->final) {
            // the message can be processed
        }
    }
}

void WebSrv::OnNotFound(AsyncWebServerRequest *request)
{
    if (request != nullptr)
        request->send(404, "text/plain", "Not found");
}

void WebSrv::Begin(void)
{
    ws.onEvent(std::bind(&WebSrv::OnEvent, this,
        std::placeholders::_1, std::placeholders::_2, std::placeholders::_3,
        std::placeholders::_4, std::placeholders::_5, std::placeholders::_6));
    web.addHandler(&ws);

    web.addHandler(&events);

    // web.on("/", HTTP_ANY, std::bind(&WebSrv::OnRequest, this, std::placeholders::_1));
    web.serveStatic("/", SPIFFS, "/").setDefaultFile("index.html");

    web.onNotFound(std::bind(&WebSrv::OnNotFound, this, std::placeholders::_1));
    web.onFileUpload(std::bind(&WebSrv::OnFileUpload, this,
        std::placeholders::_1, std::placeholders::_2, std::placeholders::_3,
        std::placeholders::_4, std::placeholders::_5, std::placeholders::_6));
    web.onRequestBody(std::bind(&WebSrv::OnRequestBody, this,
        std::placeholders::_1, std::placeholders::_2, std::placeholders::_3,
        std::placeholders::_4, std::placeholders::_5));

    web.begin();
}

void WebSrv::End(void)
{
    // remove all rewrites, handlers and onNotFound/onFileUpload/onRequestBody callbacks
    web.reset();

    web.end();
}

void WebSrv::CleanupClients(void)
{
    ws.cleanupClients();
}
