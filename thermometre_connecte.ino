#include "lib/afficheur7segments.h"
#include "lib/CapteurDHT.h"
#include "lib/espnow_emitter.h"

#define CLK 0
#define DIO 1

#define BROCHE_DHT 10
#define TYPE_DHT DHT22

#define BUTTON_PIN 3

CapteurDHT monDHT(BROCHE_DHT, TYPE_DHT);

TempDisplay tempDisp(CLK, DIO);

// Adresse MAC du récepteur
uint8_t receiverMac[] = { 0x1C, 0xDB, 0xD4, 0x3C, 0x75, 0xC8 };
EspNowEmitter emitter(receiverMac);

void setup() {
  Serial.begin(115200);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  emitter.begin();
  monDHT.begin();
  tempDisp.begin();  // initialisation de l'afficheur
}

void loop() {
  float humidite, temperature, temperatureRessentie;
  int etat = digitalRead(BUTTON_PIN);


  if (!monDHT.lire(humidite, temperature, temperatureRessentie)) {
    tempDisp.showError();
    delay(1000);
    return;
  }

  if (etat == LOW) {
    tempDisp.showHumidity(humidite);
    emitter.sendInt(temperatureRessentie,humidite);
    delay(500);
    return;
  }

  tempDisp.showTemperature(temperatureRessentie);
  emitter.sendInt(temperatureRessentie,humidite);
  delay(500);
}
