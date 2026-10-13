#include <Arduino.h>
#include <ArduinoBLE.h>
#include "network/GATT.h"
#include "hal/LED.h"

// Servicio de control del LED RGB.
static BLEService servicioLED(
    "44494547-4F00-0000-0000-000000000000"
);

// 0 apagado, 1 rojo, 2 verde, 3 azul.
static BLEByteCharacteristic colorLED(
    "44494547-4F00-0000-0000-000000000001",
    BLERead | BLEWrite
);

void initGATT() {
    // Añade la característica y registra el servicio.
    servicioLED.addCharacteristic(colorLED);
    BLE.addService(servicioLED);

    colorLED.writeValue(0);
    BLE.setAdvertisedService(servicioLED);
}

void updateGATT() {
    if (colorLED.written()) {
        cambiarColorLED(colorLED.value());
    }
}