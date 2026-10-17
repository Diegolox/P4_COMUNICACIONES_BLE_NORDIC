#include <BluetoothSerial.h>
#include "hal/bluetooth.h"

static BluetoothSerial bluetooth;

void initBluetooth() {
    bluetooth.begin("ESP32-Chat");
}

// Llamar en cada vuelta del loop().
// Devuelve el mensaje al recibir Enter, o "" si todavía está incompleto.
// Cada llamada lee un char del buffer bluetooth y lo acumula hasta recibir el salto de linea
String leerBluetooth() {
    // Conserva los caracteres recibidos entre llamadas.
    static String buffer = "";

    if (!bluetooth.available()) {
        return ""; // No hay datos nuevos.
    }

    char caracter = bluetooth.read();

    // Acumula el texto hasta recibir un salto de línea (CR o LF).
    if (caracter != '\r' && caracter != '\n') {
        buffer += caracter;
        return "";
    }

    // Devuelve el mensaje y prepara el buffer para el siguiente.
    String mensaje = buffer;
    buffer = "";
    return mensaje;
}

// Envía el mensaje con un salto de línea.
void escribirBluetooth(String mensaje) {
    bluetooth.println(mensaje);
}