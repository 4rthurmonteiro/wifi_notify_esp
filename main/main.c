
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "sdkconfig.h"
#include "connect.h"
#include "esp_log.h"
#include "esp_wifi.h"

#define TAG "WIFI"

TaskHandle_t taskHandle;

const uint32_t WIFI_ON = BIT1;
const uint32_t WIFI_OFF = BIT2;

// void on(void *params)
// {

//     uint32_t command = 0;

//     while (true)
//     {
//     vTaskDelay(5000 / portTICK_PERIOD_MS);
//     }
// }

void off(void *params)
{
    uint32_t command = 0;

    while (true)
    {
        xTaskNotifyWait(0, 0, &command, portMAX_DELAY);
        
        switch (command)
        {
            case WIFI_ON:
                ESP_LOGI(TAG, "WIFI TA ON!\n");
                 vTaskDelay(3000 / portTICK_PERIOD_MS);

            break;
            case WIFI_OFF:
                ESP_LOGI(TAG, "WIFI TA OFF!\n");
                vTaskDelay(4000 / portTICK_PERIOD_MS);

            break;
            default:
            break;
        }
    }
}

void app_main(void)
{
  wifiInit();
  ESP_ERROR_CHECK(esp_wifi_start());

  xTaskCreate(off, "off", 1024 * 5, NULL, 5, &taskHandle);

}
