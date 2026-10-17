#include <Arduino.h>
#include <BluetoothSerial.h>
#include "hal/BLUETOOTH.h"

// Solo se utilizan dentro de este archivo.
static BluetoothSerial bluetooth;
static String mensaje = "";
static bool mensajeCompleto = false;

void initBluetooth() {
    bluetooth.begin("ESP32-Chat");
}

// Recibe texto y detecta el final del mensaje.
void leerBluetooth() {
    if (bluetooth.available()) {
        char caracter = bluetooth.read();
        Serial.write(caracter);

        if (caracter == '\r' || caracter == '\n') {
            if (mensaje.length() > 0) {
                mensajeCompleto = true;
            }
        } else {
            mensaje += caracter;
        }
    }
}

// Envía el texto del USB y el eco del mensaje recibido.
void escribirBluetooth() {
    if (Serial.available()) {
        bluetooth.write(Serial.read());
    }

    if (mensajeCompleto) {
        bluetooth.print("eco-");
        bluetooth.println(mensaje);

        mensaje = "";
        mensajeCompleto = false;
    }
}