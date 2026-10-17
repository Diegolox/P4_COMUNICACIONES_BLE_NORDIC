#include <Arduino.h>
#include "hal/bluetooth.h"
#include "protocol/chat_bluetooth.h"

void eco_mensaje() {
    String mensaje = leerBluetooth();
    if (mensaje != "") {
        escribirBluetooth("ECO-" + mensaje);
    }
}