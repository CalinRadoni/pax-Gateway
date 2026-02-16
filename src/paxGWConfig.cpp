#include "paxGWConfig.h"

paxGW_Config::paxGW_Config(void)
{
    //
}

paxGW_Config::~paxGW_Config()
{
    //
}

bool paxGW_Config::CustomInit(void)
{
    return true;
}

bool paxGW_Config::CustomLoad(void)
{
    return true;
}

bool paxGW_Config::CustomSave(void)
{
    return true;
}

bool paxGW_Config::CustomBuildJsonDocument(void)
{
    // example code
    JsonObject jse = jdoc["settings"].as<JsonObject>();
    if (jse.isNull())
        return false;

    return true;
}
