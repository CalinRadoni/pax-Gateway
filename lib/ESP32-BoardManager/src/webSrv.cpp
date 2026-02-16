#include "webSrv.h"

WebSrv::WebSrv(void)
{
    // Initialize context pool
    for (size_t i = 0; i < WS_MAX_CLIENTS; i++) {
        contextPool[i].clientID = 0;
        contextPool[i].buffDataLen = 0;
        contextPool[i].isActive = false;
    }
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
        GetClientContext(client->id());  // Create context for new client
        log_d("ws %s %u connect", server->url(), client->id());
        break;
    case WS_EVT_DISCONNECT:
        RemoveClientContext(client->id());  // Clean up client context
        log_d("ws %s %u disconnect", server->url(), client->id());
        break;
    case WS_EVT_ERROR:
        log_e("ws %s %u error %u: %s", server->url(), client->id(), *((uint16_t*)arg), (char*)data);
        break;
    case WS_EVT_PONG:
        log_d("ws %s %u pong[%u]: %s", server->url(), client->id(), len, (len > 0) ? (char*)data : "");
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

    ClientContext *ctx = GetClientContext(clientID);
    if (ctx == nullptr) {
        log_e("Failed to get context for WS client");
        return;
    }

    // A long message was received in multiple packets (fragmented frame, not multiple frames):
    // - info->index, info->len and len were OK
    // - not OK: num is not increased and may be !=0
    // - not OK: final was always set
    // I have only seen long messages with a single, fragmented, frame and not with multiple frames
    // TODO: test again with long messages !

    if (info->index == 0) {
        // beginning of data
        ctx->buffDataLen = 0;
    }

    // Append data to context buffer
    size_t spaceLeft = WS_CTX_BUFF_SIZE - ctx->buffDataLen;
    if (len > spaceLeft) {
        log_w("Buffer overflow prevented for client %u: needed %u, have %u", clientID, len, spaceLeft);
        len = spaceLeft;  // Truncate to fit
    }
    if (len > 0) {
        memcpy(&ctx->buffData[ctx->buffDataLen], data, len);
        ctx->buffDataLen += len;
    }

    if ((info->index + len) == info->len) {
        // all data was received
        if (info->final) {
            if (messageQueue != nullptr) {
                msg.type = info->opcode == WS_TEXT ?
                    BoardMessageType::WS_TextMessageReceived : BoardMessageType::WS_BinaryMessageReceived;
                msg.data = ctx;
                if (!messageQueue->Send(&msg)) {
                    log_e("Failed to send WS_*MessageReceived message to queue");
                }
            }
        }
    }
}

void WebSrv::OnNotFound(AsyncWebServerRequest *request)
{
    if (request != nullptr)
        request->send(404, "text/plain", "Not found");
}

void WebSrv::Begin(BoardQueue *queue)
{
    messageQueue = queue;

    ws.onEvent(std::bind(&WebSrv::OnEvent, this,
        std::placeholders::_1, std::placeholders::_2, std::placeholders::_3,
        std::placeholders::_4, std::placeholders::_5, std::placeholders::_6));
    web.addHandler(&ws);

    web.addHandler(&events);

    // web.on("/", HTTP_ANY, std::bind(&WebSrv::OnRequest, this, std::placeholders::_1));
    web.serveStatic("/", LittleFS, "/").setDefaultFile("index.html");

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

ClientContext* WebSrv::GetClientContext(uint32_t clientID)
{
    // Search for existing context in pool
    for (size_t i = 0; i < WS_MAX_CLIENTS; i++) {
        if (contextPool[i].isActive && contextPool[i].clientID == clientID) {
            return &contextPool[i];
        }
    }

    // Find an available slot in the pool
    for (size_t i = 0; i < WS_MAX_CLIENTS; i++) {
        if (!contextPool[i].isActive) {
            // Found available slot - initialize it
            contextPool[i].clientID = clientID;
            contextPool[i].buffDataLen = 0;
            contextPool[i].isActive = true;
            
            log_d("Created context for client %u at pool index %u", clientID, i);
            return &contextPool[i];
        }
    }

    log_e("Max clients (%u) reached, cannot add client %u", WS_MAX_CLIENTS, clientID);
    return nullptr;
}

void WebSrv::RemoveClientContext(uint32_t clientID)
{
    for (size_t i = 0; i < WS_MAX_CLIENTS; i++) {
        if (contextPool[i].isActive && contextPool[i].clientID == clientID) {
            // Mark pool entry as inactive
            contextPool[i].isActive = false;
            contextPool[i].buffDataLen = 0;
            log_d("Removed context for client %u (pool index %u)", clientID, i);
            return;
        }
    }
}

bool WebSrv::SendWSMessage(ClientContext* ctx, const char *message)
{
    if (ctx == nullptr) {
        log_e("Cannot send message: client context is null");
        return false;
    }
    if (!ctx->isActive) {
        log_w("Cannot send message: client %u is not active", ctx->clientID);
        return false;
    }
    AsyncWebSocketClient *client = ws.client(ctx->clientID);
    if (client == nullptr) {
        log_e("Cannot send message: client %u not found in WebSocket server", ctx->clientID);
        return false;
    }
    return client->text(message);
}

bool WebSrv::BroadcastWSMessage(const char *message)
{
    return ws.textAll(message);
}
