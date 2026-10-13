#include <Arduino.h>
#include "hal/BLE.h"
#include "hal/LED.h"
#include "hal/IMU.h"

void setup() {
    Serial.begin(115200);

    // Espera al monitor serie un máximo de 3 segundos.
    unsigned long inicio = millis();
    while (!Serial && millis() - inicio < 3000) {}

    initLED();

    Serial.println("Iniciando IMU...");
    if (!initIMU()) {
        Serial.println("Error al iniciar IMU");
        while (true) {
            delay(1000);
        }
    }

    Serial.println("Iniciando BLE...");
    if (!initBLE()) {
        Serial.println("Error al iniciar BLE");
        while (true) {
            delay(1000);
        }
    }

    Serial.println("Advertising iniciado");
}

void loop() {
    updateBLE();
}