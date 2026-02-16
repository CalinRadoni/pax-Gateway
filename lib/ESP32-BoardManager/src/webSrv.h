#ifndef webSrv_H
#define webSrv_H

#include <Arduino.h>
#include <FS.h>
#include <LittleFS.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>

#include "boardQueue.h"

/**
 * @brief Buffer size for per-client message buffer
 */
constexpr size_t WS_CTX_BUFF_SIZE = 3072;

/**
 * @brief Maximum number of concurrent WebSocket clients
 */
constexpr size_t WS_MAX_CLIENTS = 3;

/**
 * @brief Client context structure for managing per-client data with fixed buffers
 */
typedef struct {
    uint32_t clientID;              ///< Client ID from AsyncWebSocketClient
    char buffData[WS_CTX_BUFF_SIZE]; ///< Fixed buffer for fragmented message data
    size_t buffDataLen;             ///< Current length of data in buffer
    bool isActive;              ///< Flag indicating if context is in use
} ClientContext;

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

    bool SendWSMessage(ClientContext*, const char *message);
    bool BroadcastWSMessage(const char *message);

    void Begin(BoardQueue*);
    void End(void);
    void CleanupClients(void);

protected:
    BoardQueue *messageQueue {nullptr}; ///< Pointer to the shared message queue
    BoardMessage msg;

    ClientContext contextPool[WS_MAX_CLIENTS];             ///< Pre-allocated context pool for 4 clients

    /**
     * @brief Get or create a client context
     * 
     * @param clientID ID of the client
     * @return Pointer to ClientContext, nullptr if failed
     */
    ClientContext* GetClientContext(uint32_t clientID);

    /**
     * @brief Remove a client context
     * 
     * @param clientID ID of the client
     */
    void RemoveClientContext(uint32_t clientID);
};

#endif
