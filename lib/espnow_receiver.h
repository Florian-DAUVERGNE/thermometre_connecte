#ifndef ESPNOW_RECEIVER_H
#define ESPNOW_RECEIVER_H

#include <WiFi.h>
#include <esp_now.h>
#include "message.h"

class EspNowReceiver {
public:
    static volatile bool ledFlash;
    static message received;

static void onReceive(const esp_now_recv_info_t *info,
                      const uint8_t *incomingData,
                      int len)
{
    if (len < sizeof(message)) return;

    memcpy(&received, incomingData, sizeof(message));

    Serial.print("Température : ");
    Serial.print(received.temperature, 2);
    Serial.print(" °C | Humidité : ");
    Serial.print(received.humidite, 1);
    Serial.println(" %");

    char macStr[18];
    snprintf(macStr, sizeof(macStr),
             "%02X:%02X:%02X:%02X:%02X:%02X",
             info->src_addr[0], info->src_addr[1], info->src_addr[2],
             info->src_addr[3], info->src_addr[4], info->src_addr[5]);

    Serial.print("De : ");
    Serial.println(macStr);
    ledFlash = true;
}


    void begin() {
        WiFi.mode(WIFI_STA);
        if (esp_now_init() != ESP_OK) {
            Serial.println("Erreur ESP-NOW");
            return;
        }
        esp_now_register_recv_cb(onReceive);
    }
};

#endif
