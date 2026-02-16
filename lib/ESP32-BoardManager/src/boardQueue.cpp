#include "boardQueue.h"

#include "esp_log.h"

BoardQueue::BoardQueue(void)
{
    queueHandle = xQueueCreate(queueLength, sizeof(BoardMessage));
    if (queueHandle == NULL) {
        ESP_LOGE("BoardQueue", "Failed to create queue!");
    }
}

BoardQueue::~BoardQueue()
{
    if (queueHandle != NULL) {
        vQueueDelete(queueHandle);
        queueHandle = NULL;
    }
}

bool BoardQueue::Send(const BoardMessage *msg, TickType_t ticksToWait)
{
    if (queueHandle == NULL || msg == NULL) {
        return false;
    }
    
    BaseType_t result = xQueueSend(queueHandle, (void *)msg, ticksToWait);
    return (result == pdPASS);
}

bool BoardQueue::Receive(BoardMessage *msg, TickType_t ticksToWait)
{
    if (queueHandle == NULL || msg == NULL) {
        return false;
    }
    
    BaseType_t result = xQueueReceive(queueHandle, (void *)msg, ticksToWait);
    return (result == pdPASS);
}

bool BoardQueue::IsValid(void) const
{
    return (queueHandle != NULL);
}
