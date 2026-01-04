#ifndef CAPTEUR_DHT_H
#define CAPTEUR_DHT_H

#include <DHT.h>

class CapteurDHT {
  private:
    uint8_t pin;       // Pin de connexion
    uint8_t type;      // Type du DHT (DHT22, DHT11, etc.)
    DHT dht;           // Objet DHT

  public:
    // Constructeur
    CapteurDHT(uint8_t broche, uint8_t typeDHT) 
      : pin(broche), type(typeDHT), dht(broche, typeDHT) {}

    // Initialisation
    void begin() {
      dht.begin();
      Serial.println("Capteur DHT initialisé");
      Serial.println("=====================");
    }

    // Lecture des valeurs
    bool lire(float &humidite, float &temperature, float &temperatureRessentie) {
      humidite = dht.readHumidity();
      temperature = dht.readTemperature();
      if (isnan(humidite) || isnan(temperature)) {
        return false; // Lecture échouée
      }
      temperatureRessentie = dht.computeHeatIndex(temperature, humidite, false);
      return true;
    }

    // Affichage des valeurs sur le moniteur série
    void afficher(float humidite, float temperature, float temperatureRessentie) {
      Serial.print("Humidité         : "); Serial.print(humidite); Serial.println(" %");
      Serial.print("Température      : "); Serial.print(temperature); Serial.println(" °C");
      Serial.print("Température ressentie : "); Serial.print(temperatureRessentie); Serial.println(" °C");
      Serial.println("-------------------------------");
    }
};

#endif
