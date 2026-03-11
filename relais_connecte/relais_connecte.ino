#include "../lib/espnow_receiver.h"
#include <WiFi.h>

#define RELAIS 6
#define LED 8

#define TEMP_ON  20.5
#define TEMP_OFF 21.5

volatile bool EspNowReceiver::ledFlash = false;
message EspNowReceiver::received;

EspNowReceiver receiver;

bool relaisEtat = true;

void setup() {
  Serial.begin(115200);
  pinMode(LED, OUTPUT);
  pinMode(RELAIS, OUTPUT);
  Serial.print("Démarrage relai");
  
  WiFi.mode(WIFI_STA);   // OBLIGATOIRE
  WiFi.disconnect();

  Serial.print("Adresse MAC (STA) : ");
  Serial.println(WiFi.macAddress());
  receiver.begin();
}
void loop() {
  if (EspNowReceiver::ledFlash) {

    message msg = EspNowReceiver::getReceived();

    Serial.print("Température : ");
    Serial.print(msg.temperature, 2);
    Serial.print(" °C | Humidité : ");
    Serial.print(msg.humidite, 1);
    Serial.println(" %");

    digitalWrite(LED, LOW);
    delay(500);
    digitalWrite(LED, HIGH);
    delay(500);

    EspNowReceiver::ledFlash = false;

    if (!relaisEtat && msg.temperature > TEMP_OFF) {
      relaisEtat = true;
      digitalWrite(RELAIS, LOW);
    } else if (relaisEtat && msg.temperature < TEMP_ON) {
      relaisEtat = false;
      digitalWrite(RELAIS, HIGH);
    }
  }
}
