#include "lib/afficheur7segments.h"
#include "lib/CapteurDHT.h"
#include "lib/espnow_emitter.h"

#define CLK 0
#define DIO 1
#define BROCHE_DHT 10
#define TYPE_DHT DHT22
#define BUTTON_PIN 3

uint8_t receiverMac[] = { 0x1C, 0xDB, 0xD4, 0x3C, 0x75, 0xC8 };

CapteurDHT monDHT(BROCHE_DHT, TYPE_DHT);
TempDisplay tempDisp(CLK, DIO);
EspNowEmitter emitter(receiverMac);

struct Mesures {
  float humidite;
  float temperature;
  float ressenti;
};

unsigned long lastUpdate = 0;
const unsigned long UPDATE_INTERVAL = 500;

bool lireCapteur(Mesures &m) {
  return monDHT.lire(m.humidite, m.temperature, m.ressenti);
}

void envoyerDonnees(const Mesures &m) {
  emitter.sendInt(m.ressenti, m.humidite);
}

void afficherMesures(const Mesures &m, bool boutonAppuye) {
  if (boutonAppuye) {
    tempDisp.showHumidity(m.humidite);
  } else {
    tempDisp.showTemperature(m.ressenti);
  }
}

void setup() {
  Serial.begin(115200);
  pinMode(BUTTON_PIN, INPUT_PULLUP);

  emitter.begin();
  monDHT.begin();
  tempDisp.begin();
}

void loop() {
  if (millis() - lastUpdate < UPDATE_INTERVAL) return;
  lastUpdate = millis();

  Mesures mesures;

  if (!lireCapteur(mesures)) {
    tempDisp.showError();
    return;
  }

  bool boutonAppuye = digitalRead(BUTTON_PIN) == LOW;

  afficherMesures(mesures, boutonAppuye);
  envoyerDonnees(mesures);
}
