---
layout: page
title: "Documentation for pax-Gateway"
description: "pax-Gateway: Documentation about usage, hardware and software"
---

right now this page is for testing the integration with GitHub Pages

## Title 2

### Title 3

#### Title 4

text *text* **text**

* aaa
* bbb
* [pax-devices](https://github.com/CalinRadoni/pax-devices)

```c++
/**
This file is part of pax-devices (https://github.com/CalinRadoni/pax-devices)
*/

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

const char* TAG = "Init";

extern "C" {

    void app_main()
    {
        simpleOTA.CheckApplicationImage();

        esp_err_t err = board.Initialize();
        if (err != ESP_OK) {
            ESP_LOGE(TAG, "Initialization failed !");
            board.DoNothingForever();
        }

        // ... nothing more, just highlighting test

    }
}
```
