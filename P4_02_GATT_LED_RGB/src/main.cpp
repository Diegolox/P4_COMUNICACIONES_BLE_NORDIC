#include <Arduino.h>
#include "hal/BLE.h"

void setup() {
    Serial.begin(115200);

    if (!initBLEAdvertising()) {
        Serial.println("Error al iniciar advertising BLE");

        while (true) {
            delay(1000);
        }
    }

    Serial.println("Advertising iniciado");
}

void loop() {
    updateBLE();
}