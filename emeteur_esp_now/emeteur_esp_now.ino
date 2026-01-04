#include "../lib/espnow_emitter.h"

// Adresse MAC du récepteur
uint8_t receiverMac[] = {0x1C, 0xDB, 0xD4, 0x3A, 0xD8, 0xC4};
EspNowEmitter emitter(receiverMac);

void setup() {
    Serial.begin(115200);
    emitter.begin();
}

void loop() {
    int temp = 23; // Exemple : récupère ta valeur réelle ici
    emitter.sendInt(temp);
    delay(1000);
}
