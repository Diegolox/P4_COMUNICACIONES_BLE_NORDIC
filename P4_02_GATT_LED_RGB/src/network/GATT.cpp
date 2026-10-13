#include <Arduino.h>
#include <ArduinoBLE.h>
#include "network/GATT.h"
#include "hal/LED.h"

// EL GATT ES EL CONJUNTO DE SERVICIOS DE LA APLICACIÓN
//LOS SERVICIOS SON MEROS CONJUNTOS DE CARACTERÍSTICAS. LAS CARACTERÍSITCAS SOLO PUEDEN PERTENECER A UN SERVICIO
// Servicio de control del LED RGB.
static BLEService servicioLED(
    "44494547-4F00-0000-0000-000000000000" // UUID del servicio, codificado en ASCII como "DIEGO"
);

// CARACTERÍSTICA ES UN DATO QUE PUEDO LEER O ESCRIBIR
// 0 apagado, 1 rojo, 2 verde, 3 azul.
static BLEByteCharacteristic colorLED(
    "44494547-4F00-0000-0000-000000000001", // UUID de la característica.
    BLERead | BLEWrite // Configura la característica para ser de lectura y escritura.
);

void initGATT() {
    // Añade la característica y registra el servicio.
    servicioLED.addCharacteristic(colorLED);
    BLE.addService(servicioLED); // añade el servicio al GATT para que el cliente lo vea una vez conectado.

    colorLED.writeValue(0); // PONE A CERO EL LED AL INICIO ESCRIBIENDO EN LA CARACTERÍSTICA.
    BLE.setAdvertisedService(servicioLED); // añade el servicio al advertising para que el cliente lo vea.
}

void updateGATT() {
    if (colorLED.written()) { // Si el cliente ha escrito en la característica.
        cambiarColorLED(colorLED.value()); // cambia el color del led
    }
}