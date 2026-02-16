#ifndef board_H
#define board_H

#include "boardConfig.h"
#include "WiFiManager.h"
#ifdef USE_UpdateFromWeb
    #include "UpdateFromWeb.h"
#endif
#include "webSrv.h"
#include "boardQueue.h"

class Board
{
public:
    Board(void);
    virtual ~Board();

    int SDA_pin {-1};
    int SCL_pin {-1};

    virtual bool Init_level0(void) = 0;
    virtual bool Init_level1(void) = 0;
    virtual bool Init_level2(void) = 0;
    virtual bool Init_level3(void) = 0;

    /**
     * @brief Initialize the board
     *
     * Workflow:
     *   calls Init_level0
     *   Load configuration from NVS
     *   calls Init_level1
     *   Initialize the Wire object, make sure SDA_pin and SCL_pin are set !
     *   Initialize WiFi connection
     *   Print application description
     *   calls Init_level2
     *   Try to connect to a WiFi Access Point
     *   call Init_level3
     *
     * @return 0 if Init_level0 returns false
     * @return 1 if Init_level1 returns false
     * @return 2 if Init_level2 returns false
     * @return 3 if Init_level3 returns false
     * @return 0xFF on success
     * 
     * @note Use GetWiFiState to find the state of WiFi
     */
    unsigned int Initialize(BoardConfig*);

    WiFiManagerState GetWiFiState(void);

    virtual void CustomReset(void) = 0;

    /**
     * @brief Reset the board
     *
     * Workflow:
     *    call CustomReset
     *    wait delayMS
     *    reset the board
     */
    void ResetBoard(uint32_t delayMS);

    bool CheckConnection(bool restartOnFail);

    bool UpdateFromLink(String);

    void PrintApplicationDescription(void);

    void ScanI2CBus(void);

    void CheckQueue(void);

    virtual void CustomProcessBoardMessage(ClientContext *ctx, const JsonDocument& jdoc);

protected:
    BoardConfig *boardConfig {nullptr};
    #ifdef USE_UpdateFromWeb
        UpdateFromWeb webUpdater;
    #endif
    WebSrv webSrv;

    BoardQueue boardMessageQueue;  ///< Queue for board messages
    void ProcessBoardMessage(const BoardMessage *msg);

    bool mDNS_started {false};
    esp_err_t Start_mDNS(void);
    esp_err_t Stop_mDNS(void);
};

#endif
