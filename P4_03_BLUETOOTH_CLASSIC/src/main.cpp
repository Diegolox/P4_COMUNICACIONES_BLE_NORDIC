#include <Arduino.h>
#include "hal/BLUETOOTH.h

void setup() {
    Serial.begin(115200);
    initBluetooth();
}

void loop() {
    leerBluetooth();
    escribirBluetooth();
}