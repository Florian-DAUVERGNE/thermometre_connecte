#ifndef ESPNOW_EMITTER_H
#define ESPNOW_EMITTER_H

#include <WiFi.h>
#include <esp_now.h>
#include "message.h"

class EspNowEmitter
{
private:
    uint8_t receiverMac[6];
    message data;

    static void onSend(const wifi_tx_info_t *info, esp_now_send_status_t status)
    {
        if (status == ESP_NOW_SEND_SUCCESS)
        {
            Serial.println("Envoyé avec succès !");
        }
        else
        {
            Serial.print("Erreur ESP-NOW : ");
            Serial.println((int)status); // affiche le code numérique
            // Tu peux ajouter un switch pour plus de détails
            switch (status)
            {
            case ESP_NOW_SEND_FAIL:
                Serial.println("ESP_NOW_SEND_FAIL : échec d'envoi !");
                break;
            default:
                Serial.println("Autre erreur inconnue");
                break;
            }
        }
    }

public:
    EspNowEmitter(const uint8_t mac[6])
    {
        memcpy(receiverMac, mac, 6);
    }

    void begin()
    {
        WiFi.mode(WIFI_STA);
        if (esp_now_init() != ESP_OK)
        {
            Serial.println("Erreur ESP-NOW");
            return;
        }

        esp_now_register_send_cb(onSend);

        esp_now_peer_info_t peerInfo = {};
        memcpy(peerInfo.peer_addr, receiverMac, 6);
        peerInfo.channel = 0;
        peerInfo.encrypt = false;

        if (esp_now_add_peer(&peerInfo) != ESP_OK)
        {
            Serial.println("Erreur ajout peer ESP-NOW");
        }
    }

    void sendInt(float val, float humidite)
    {
        data.temperature = val;
        data.humidite = humidite;
        esp_now_send(receiverMac, (uint8_t *)&data, sizeof(data));
    }
};

#endif
