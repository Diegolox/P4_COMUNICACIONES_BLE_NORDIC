#include <Arduino.h>
#include <BluetoothSerial.h>

BluetoothSerial bluetooth;

void setup() {
    Serial.begin(115200);        // Comunicación USB con el monitor serie.
    bluetooth.begin("ESP32-Chat"); // Nombre visible por Bluetooth.
}

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