#ifndef boardQueue_H
#define boardQueue_H

#include "freertos/FreeRTOS.h"
#include "freertos/queue.h"

enum class BoardMessageType : uint8_t {
    WiFi_Connected = 0,         ///< WiFi connected to AP
    WiFi_Disconnected = 1,      ///< WiFi disconnected from AP
    WiFi_ScanComplete = 2,      ///< WiFi scan completed
    WiFi_ConnectionFailed = 3,  ///< WiFi connection attempt failed

    WS_TextMessageReceived = 4,     ///< WebSocket message received
    WS_BinaryMessageReceived = 5,   ///< WebSocket binary message received

    // Add more message types as needed, using uint8_t, 255 is the maximum value

    MAX_value = 255                ///< Maximum value for message types (for validation)
};

typedef struct {
    BoardMessageType type;  ///< Message type identifier
    void *data;             ///< Optional pointer to context data (e.g. client context)
} BoardMessage;

class BoardQueue
{
public:
    BoardQueue(void);

    virtual ~BoardQueue();

    static const uint8_t queueLength = 16; ///< Maximum number of messages in the queue

    /**
     * @brief Send a message to the queue
     * 
     * @param msg Pointer to BoardMessage to send
     * @param ticksToWait Maximum time to wait in ticks (portMAX_DELAY for infinite)
     * @return true if message was sent successfully, false otherwise
     */
    bool Send(const BoardMessage *msg, TickType_t ticksToWait = portMAX_DELAY);

    /**
     * @brief Receive a message from the queue
     * 
     * @param msg Pointer to BoardMessage buffer to receive into
     * @param ticksToWait Maximum time to wait in ticks (portMAX_DELAY for infinite)
     * @return true if message was received successfully, false otherwise
     */
    bool Receive(BoardMessage *msg, TickType_t ticksToWait = portMAX_DELAY);

    /**
     * @brief Check if queue is valid
     * 
     * @return true if queue was created successfully, false otherwise
     */
    bool IsValid(void) const;

private:
    QueueHandle_t queueHandle {nullptr};
};

#endif
