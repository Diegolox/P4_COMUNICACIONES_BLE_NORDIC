#include "hal/BLE.h"

static const char* nombreBLE = "Nano-DIEGO";

// UUID con "DIEGO" codificado en ASCII.
static BLEService servicio(
    "44494547-4F00-0000-0000-000000000000"
);

// Inicialización común a los modos BLE.
static bool initBLE(const char* nombre) {
    if (!BLE.begin()) {
        return false;
    }

    BLE.setLocalName(nombre);
    return true;
}

bool initBLEAdvertising() {
    if (!initBLE(nombreBLE)) {
        return false;
    }

    BLE.setAdvertisedService(servicio); // Anuncia el UUID.
    BLE.addService(servicio);           // Registra el servicio en GATT.

    return BLE.advertise();
}

void updateBLE() {
    BLE.poll(); // Atiende los eventos BLE.
}

