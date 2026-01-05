#ifndef TEMP_DISPLAY_H
#define TEMP_DISPLAY_H

#include <Arduino.h>
#include <TM1637Display.h>

class TempDisplay {
  private:
    TM1637Display display;

  public:
    // Constructeur : on passe les broches CLK et DIO
    TempDisplay(uint8_t clk, uint8_t dio) : display(clk, dio) {}

    // Initialisation de l'afficheur
    void begin(uint8_t brightness = 0x0f) {
      display.setBrightness(brightness);
    }

    // Affiche une température float sur 4 digits (23.5 -> 23.5°C)
  void showTemperature(float temp)
  {

      int tempInt = int(temp * 10); // 23.5 -> 235

      int digit1 = tempInt / 100;
      int digit2 = (tempInt / 10) % 10;
      int digit3 = tempInt % 10;

      uint8_t data[4];

        data[0] = display.encodeDigit(digit1);
      data[1] = display.encodeDigit(digit2) | 0b10000000; // point décimal
      data[2] = display.encodeDigit(digit3);
      data[3] = 0b01100011; // approximation °C

      display.setSegments(data);
    }
};

#endif
