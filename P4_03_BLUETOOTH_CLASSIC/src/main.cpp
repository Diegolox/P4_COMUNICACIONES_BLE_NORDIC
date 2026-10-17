#include <Arduino.h>
#include "protocol/chat_bluetooth.h"
#include "hal/bluetooth.h"

void setup() {
    Serial.begin(115200);
    initBluetooth();
}

void loop() {
    eco_mensaje();
}