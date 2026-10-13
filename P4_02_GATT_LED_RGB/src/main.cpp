#include <Arduino.h>
#include "hal/BLE.h"
#include "hal/LED.h"
#include "network/GATT.h"


void setup() {
    initLED();

    Serial.begin(115200);

    initGATT();

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