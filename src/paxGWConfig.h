#ifndef paxGWConfig_H
#define paxGWConfig_H

#include "boardConfig.h"

class paxGW_Config : public BoardConfig
{
public:
    paxGW_Config(void);
    virtual ~paxGW_Config();

    virtual void CustomInit(void);
    virtual bool CustomLoad(void);
    virtual bool CustomSave(void);
};

#endif
