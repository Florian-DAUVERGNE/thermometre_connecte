#include "../lib/espnow_receiver.h"


volatile bool EspNowReceiver::ledFlash = false;
message EspNowReceiver::received;

EspNowReceiver receiver;


void setup() {
    Serial.begin(115200);
    pinMode(8, OUTPUT);
    receiver.begin();
}

void loop() {
  if (EspNowReceiver::ledFlash) {
    digitalWrite(8, LOW);   // ON
    delay(500);
    digitalWrite(8, HIGH);  // OFF
    delay(500);
    EspNowReceiver::ledFlash = false;
  }
}
