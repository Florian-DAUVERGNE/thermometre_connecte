#include <WiFi.h>
#include <esp_now.h>

// Adresse MAC du récepteur
uint8_t receiverMac[] = { 0x1C, 0xDB, 0xD4, 0x3A, 0xD8, 0xC4 };

typedef struct message {
  int valeur;
} message;

message data;

void onSend(const wifi_tx_info_t *info, esp_now_send_status_t status) {
  Serial.print("Statut envoi : ");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Succès" : "Échec");
}


void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);

  if (esp_now_init() != ESP_OK) {
    Serial.println("Erreur ESP-NOW");
    return;
  }

  esp_now_peer_info_t peerInfo = {};
  memcpy(peerInfo.peer_addr, receiverMac, 6);
  peerInfo.channel = 0;  // canal Wi-Fi
  peerInfo.encrypt = false;

  esp_err_t addStatus = esp_now_add_peer(&peerInfo);
  if (addStatus != ESP_OK) {
    Serial.println("Erreur ajout peer ESP-NOW");
  }
}

void loop() {
  data.valeur = random(0, 100);
  esp_now_send(receiverMac, (uint8_t *)&data, sizeof(data));
  delay(1000);
}
