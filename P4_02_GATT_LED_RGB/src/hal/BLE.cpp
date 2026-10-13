#include "hal/BLE.h"
#include "network/GATT.h"

static const char* nombreBLE = "Nano-DIEGO";

// UUID con "DIEGO" codificado en ASCII.
static BLEService servicio(
    "44494547-4F00-0000-0000-000000000000"
);


bool initBLE() {
    if (!BLE.begin()) {
        return false;
    }

    BLE.setLocalName(nombreBLE);

    initGATT();

    return BLE.advertise();
}



void updateBLE() {
    BLE.poll(); // Atiende los eventos BLE.
    updateGATT(); // Atiende los eventos de GATT.
}

