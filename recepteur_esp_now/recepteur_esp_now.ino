#include <WiFi.h>
#include <esp_now.h>

typedef struct message {
  int valeur;
} message;

message data;

void onReceive(const esp_now_recv_info_t *info,
               const uint8_t *incomingData,
               int len) {

  memcpy(&data, incomingData, sizeof(data));

  Serial.print("Valeur reçue : ");
  Serial.println(data.valeur);
}




void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);

  if (esp_now_init() != ESP_OK) {
    Serial.println("Erreur ESP-NOW");
    return;
  }

  esp_now_register_recv_cb(onReceive);
}

void loop() {}
