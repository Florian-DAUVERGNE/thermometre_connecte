#ifndef CAPTEUR_SHT41_H
#define CAPTEUR_SHT41_H

#include <Wire.h>
#include <SensirionI2cSht4x.h>

struct SHT41Data {
    float temperature;
    float humidity;
    float heatIndex;
};

class CapteurSHT41 {
private:
    SensirionI2cSht4x sht4x;
    float temperature;
    float humidity;

public:
    CapteurSHT41() : temperature(0), humidity(0) {}

    void begin() {
        Wire.begin();
        sht4x.begin(Wire, 0x44);
    }

    bool update() {
        uint16_t error;
        error = sht4x.measureHighPrecision(temperature, humidity);
        return error == 0;
    }

    float getTemperature() {
        return temperature;
    }

    float getHumidity() {
        return humidity;
    }

    float getHeatIndex() {
        float T = temperature;
        float RH = humidity;

        return -42.379 +
               2.04901523 * T +
               10.14333127 * RH -
               0.22475541 * T * RH -
               0.00683783 * T * T -
               0.05481717 * RH * RH +
               0.00122874 * T * T * RH +
               0.00085282 * T * RH * RH -
               0.00000199 * T * T * RH * RH;
    }

    SHT41Data lire() {
        SHT41Data data;
        data.temperature = temperature;
        data.humidity = humidity;
        data.heatIndex = getHeatIndex();
        return data;
    }
};

#endif