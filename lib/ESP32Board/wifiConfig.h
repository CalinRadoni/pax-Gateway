#ifndef wifiConfig_H
#define wifiConfig_H

#include <Arduino.h>

class WiFiConfig
{
public:
    WiFiConfig(void);
    virtual ~WiFiConfig();

    String SSID;
    String Pass;

    bool useStaticIP;
    uint32_t address;
    uint32_t mask;
    uint32_t gateway;
    uint32_t srvDNS1;
    uint32_t srvDNS2;

    void Initialize(void);
};

#endif
