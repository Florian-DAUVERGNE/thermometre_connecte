#include <Arduino.h>
#include "CapteurDHT.h"  // Inclusion de la classe

#define BROCHE_DHT 5
#define TYPE_DHT DHT22

CapteurDHT monDHT(BROCHE_DHT, TYPE_DHT);

void setup() {
  Serial.begin(115200);
  Serial.println("Programme de test du DHT22 en classe (fichier séparé)");
  Serial.println("====================================================");
  Serial.println();
  
  monDHT.begin();
}

void loop() {
  float humidite, temperature, temperatureRessentie;

  if (monDHT.lire(humidite, temperature, temperatureRessentie)) {
    monDHT.afficher(humidite, temperature, temperatureRessentie);
  } else {
    Serial.println("⚠️ Lecture échouée. Vérifiez le branchement du DHT22 !");
    Serial.println("-------------------------------");
  }

  delay(2000); // Respect du temps minimum entre deux lectures
}
