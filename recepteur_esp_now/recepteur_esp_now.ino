#include "../lib/espnow_receiver.h"

EspNowReceiver receiver;

void setup() {
    Serial.begin(115200);
    receiver.begin();
}

void loop() {
    // Rien à faire ici, tout est géré par le callback ESP-NOW
}
