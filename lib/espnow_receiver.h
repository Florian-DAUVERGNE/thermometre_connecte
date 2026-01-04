#ifndef ESPNOW_RECEIVER_H
#define ESPNOW_RECEIVER_H

#include <WiFi.h>
#include <esp_now.h>

typedef struct message {
    int temperature;
} message;

class EspNowReceiver {
private:
    message data;

    static void onReceive(const esp_now_recv_info_t *info, const uint8_t *incomingData, int len) {
        message received;
        memcpy(&received, incomingData, sizeof(received));
        Serial.print("Température reçue : ");
        Serial.println(received.temperature);

        // Optionnel : afficher MAC de l'émetteur
        char macStr[18];
        snprintf(macStr, sizeof(macStr),
                 "%02X:%02X:%02X:%02X:%02X:%02X",
                 info->src_addr[0], info->src_addr[1], info->src_addr[2],
                 info->src_addr[3], info->src_addr[4], info->src_addr[5]);
        Serial.print("De : "); Serial.println(macStr);
    }

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
