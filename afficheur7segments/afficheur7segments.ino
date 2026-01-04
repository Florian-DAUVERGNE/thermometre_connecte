#include "afficheur7segments.h"

#define CLK 9
#define DIO 10

TempDisplay tempDisp(CLK, DIO);

void setup() {
  tempDisp.begin(); // initialisation de l'afficheur
}

void loop() {
  float temp = 25.5;
  tempDisp.showTemperature(temp);
  delay(2000);
}
