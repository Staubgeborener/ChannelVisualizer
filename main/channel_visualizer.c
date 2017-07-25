#include "freertos/FreeRTOS.h"
#include "esp_wifi.h"
#include "esp_wifi_types.h"
#include "esp_system.h"
#include "esp_event.h"
#include "esp_event_loop.h"
#include "nvs_flash.h"
#include <stdio.h>
#include <string.h>

#define CHANNEL_SWITCHING true // true, if channel chould be switched
#define SWITCHING_TIME 500 // time (ms) till channel switching

uint8_t channel;
uint32_t all_channels, channel_calculator,
    channel_1 = 0, channel_2 = 0, channel_3 = 0, channel_4 = 0, channel_5 = 0,
    channel_6 = 0, channel_7 = 0, channel_8 = 0, channel_9 = 0, channel_10 = 0,
    channel_11 = 0, channel_12 = 0, channel_13 = 0;
double compare = 1.0;
unsigned long previousMillis;
char buf[256];

esp_err_t event_handler(void* ctx, system_event_t* event);
void wifi_promiscuous(void* buffer, wifi_promiscuous_pkt_type_t type);

void channel_switcher(void* pvParameter)
{
    //Switch threw all channels in a loop
    while (1) {
        unsigned long currentMillis = xTaskGetTickCount() * portTICK_PERIOD_MS;
        if (currentMillis - previousMillis >= SWITCHING_TIME / portTICK_PERIOD_MS) {
            previousMillis = currentMillis;
            channel = (channel % 13) + 1;
            esp_wifi_set_channel(channel, WIFI_SECOND_CHAN_NONE);
        }
    }
}

void app_main()
{
    nvs_flash_init();
    tcpip_adapter_init();
    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_event_loop_init(event_handler, NULL));
    ESP_ERROR_CHECK(esp_wifi_init(&cfg));
    ESP_ERROR_CHECK(esp_wifi_set_country(WIFI_COUNTRY_EU));
    ESP_ERROR_CHECK(esp_wifi_set_storage(WIFI_STORAGE_RAM));
    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_NULL));
    ESP_ERROR_CHECK(esp_wifi_start());
    esp_wifi_set_channel(channel, WIFI_SECOND_CHAN_NONE);

    //create task on second core
    xTaskCreatePinnedToCore(channel_switcher, "channel_switcher", configMINIMAL_STACK_SIZE, NULL, 1, NULL, 1);

    esp_wifi_set_promiscuous(true);
    esp_wifi_set_promiscuous_rx_cb(&wifi_promiscuous);
}

esp_err_t event_handler(void* ctx, system_event_t* event)
{
    return ESP_OK;
}

void wifi_promiscuous(void* buffer, wifi_promiscuous_pkt_type_t type)
{
    //maybe clear your terminal here 
    printf("\n  %c\n", 37);

    //increment the current channel
    if (channel == 1) {
        channel_1++;
    }
    else if (channel == 2) {
        channel_2++;
    }
    else if (channel == 3) {
        channel_3++;
    }
    else if (channel == 4) {
        channel_4++;
    }
    else if (channel == 5) {
        channel_5++;
    }
    else if (channel == 6) {
        channel_6++;
    }
    else if (channel == 7) {
        channel_7++;
    }
    else if (channel == 8) {
        channel_8++;
    }
    else if (channel == 9) {
        channel_9++;
    }
    else if (channel == 10) {
        channel_10++;
    }
    else if (channel == 11) {
        channel_11++;
    }
    else if (channel == 12) {
        channel_12++;
    }
    else if (channel == 13) {
        channel_13++;
    }
    all_channels++;

    //channel_calculator gets value of current channel
    for (int row = 0; row < 20; row++) {
        for (int column = 0; column < 13; column++) {
            if (column == 0) {
                channel_calculator = channel_1;
            }
            else if (column == 1) {
                channel_calculator = channel_2;
            }
            else if (column == 2) {
                channel_calculator = channel_3;
            }
            else if (column == 3) {
                channel_calculator = channel_4;
            }
            else if (column == 4) {
                channel_calculator = channel_5;
            }
            else if (column == 5) {
                channel_calculator = channel_6;
            }
            else if (column == 6) {
                channel_calculator = channel_7;
            }
            else if (column == 7) {
                channel_calculator = channel_8;
            }
            else if (column == 8) {
                channel_calculator = channel_9;
            }
            else if (column == 9) {
                channel_calculator = channel_10;
            }
            else if (column == 10) {
                channel_calculator = channel_11;
            }
            else if (column == 11) {
                channel_calculator = channel_12;
            }
            else if (column == 12) {
                channel_calculator = channel_13;
            }

            //print ordinate
            if (column == 0) {
                if (row != 0) {
                    sprintf(buf, "%.2lf", (double)100 - (100 - compare));
                    char* p = buf;
                    p += 2;
                    printf(" %s ", p);
                }
                else
                    printf("100 ");
            }

            //if relative frequency bigger/equal as ask value (0.95, 0.80, 0.85, ...): print "||"
            if ((double)channel_calculator / all_channels >= compare) {
                printf("||");
            }

            else {
                //... otherwise just dots
                printf("..");
            }

            //we dont want dots after the last column
            if (column != 12) {
                printf("..");
            }

            else {
                //current column is done, so make a paragraph und calculate next value for comparing
                printf("\n");

                if (row != 19) {
                    compare -= 0.05;
                }

                else
                    //finish, so reset compare
                    compare = 1.0;
            }
        }
    }
    //print abscissa
    printf("    1   2   3   4   5   6   7   8   9   10  11  12  13  Channel\n");
}