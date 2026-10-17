#include <Arduino.h>
#include <BluetoothSerial.h>

BluetoothSerial bluetooth;
String mensaje = "";

void setup() {
    Serial.begin(115200);        // Comunicación USB con el monitor serie.
    bluetooth.begin("ESP32-Chat"); // Nombre visible por Bluetooth.
}


void loop() {
    // USB → Bluetooth.
    if (Serial.available()) {
        bluetooth.write(Serial.read());
    }

    // Recibir texto por Bluetooth.
    if (bluetooth.available()) {
        char caracter = bluetooth.read();
        Serial.write(caracter);

        // Enter marca el final del mensaje: CR o LF.
        if (caracter == '\r' || caracter == '\n') {
            if (mensaje.length() > 0) {
                bluetooth.print("eco-");
                bluetooth.println(mensaje);
                mensaje = "";
            }
        } else {
            mensaje += caracter;
        }
    }
}



/*
void loop() {
    // USB → Bluetooth.
    if (Serial.available()) {
        bluetooth.write(Serial.read());
    }

    // Bluetooth → USB.
    if (bluetooth.available()) {
        Serial.write(bluetooth.read());
    }
}
*/