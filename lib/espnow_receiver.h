#ifndef ESPNOW_RECEIVER_H
#define ESPNOW_RECEIVER_H

#include <WiFi.h>
#include <esp_now.h>
#include "message.h"  // ← ajoute ça en haut

class EspNowReceiver {
private:
    message data;

    ledFlash = true;

public:
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
