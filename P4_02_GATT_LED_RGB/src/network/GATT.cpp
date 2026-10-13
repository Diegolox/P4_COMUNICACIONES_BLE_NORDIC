#include <Arduino.h>
#include <ArduinoBLE.h>
#include "network/GATT.h"
#include "hal/LED.h"
#include "hal/IMU.h"

bool acelerometroActivo = true;

// GATT organiza los servicios y el acceso a sus características.
// Un servicio agrupa características relacionadas.
// Una característica contiene un valor y define sus operaciones.
// Un descriptor añade información sobre una característica.


//------------------//
// SERVICIO LED     //
//------------------//

static BLEService servicioLED(
    "44494547-4F00-0000-0000-000000000000" // Primeros bytes: "DIEGO" en ASCII.
);

// Color: 0 apagado, 1 rojo, 2 verde, 3 azul.
static BLEByteCharacteristic colorLED(
    "44494547-4F00-0000-0000-000000000001",
    BLERead | BLEWrite // Permite leer y escribir desde el cliente.
);

// Descriptor 2901: descripción textual del valor.
static BLEDescriptor descripcionLED(
    "2901",
    "Color LED: 0 apagado, 1 rojo, 2 verde, 3 azul"
);


//-----------------------//
// SERVICIO ACELEROMETRO //
//-----------------------//

static BLEService servicioIMU(
    "44494547-4F00-0000-0000-000000000010"
);

// Medidas en texto: x;y;z.
static BLEStringCharacteristic car_leerAcelerometro(
    "44494547-4F00-0000-0000-000000000011",
    BLERead | BLENotify, // Permite leer y suscribirse a actualizaciones.
    20 // Máximo 20 bytes de texto.
);

// Descriptor: explica el orden de los ejes y su unidad.
static BLEDescriptor descripcionAcelerometro(
    "2901",
    "Aceleracion X;Y;Z en g"
);

// Control: 0 detiene las lecturas, 1 las reanuda.
static BLEBoolCharacteristic car_activarAcelerometro(
    "44494547-4F00-0000-0000-000000000100",
    BLEWrite // Permite enviar la orden desde el cliente.
);

// Descriptor: explica los valores de la orden.
static BLEDescriptor descripcionActivacion(
    "2901",
    "Acelerometro: 0 desactiva, 1 activa"
);


void activarAcelerometro(bool valor) {
    acelerometroActivo = valor;
}

void actualizarAcelerometroGATT(const Vector3D &aceleracion) {
    char datos[21]; // Texto y terminador '\0'.

    // Formatea los tres ejes con tres decimales.
    snprintf(
        datos,
        sizeof(datos),
        "%.3f;%.3f;%.3f",
        aceleracion.x,
        aceleracion.y,
        aceleracion.z
    );

    // Guarda la medida y notifica al cliente suscrito.
    car_leerAcelerometro.writeValue(datos);
}


//------------------//
//       GATT       //
//------------------//

void initGATT() {
    // Asocia las descripciones a sus características.
    colorLED.addDescriptor(descripcionLED);
    car_leerAcelerometro.addDescriptor(descripcionAcelerometro);
    car_activarAcelerometro.addDescriptor(descripcionActivacion);

    // Añade la característica al servicio LED y registra el servicio.
    servicioLED.addCharacteristic(colorLED);
    BLE.addService(servicioLED);

    // Añade las características al servicio IMU y registra el servicio.
    servicioIMU.addCharacteristic(car_leerAcelerometro);
    servicioIMU.addCharacteristic(car_activarAcelerometro);
    BLE.addService(servicioIMU);

    // Inicializa los valores almacenados en las características.
    colorLED.writeValue(0);
    car_leerAcelerometro.writeValue("0.000;0.000;0.000");
    car_activarAcelerometro.writeValue(acelerometroActivo);
}

void updateGATT() {
    // Aplica el color escrito por el cliente.
    if (colorLED.written()) {
        cambiarColorLED(colorLED.value());
    }

    // Aplica la orden antes de comprobar el sensor.
    if (car_activarAcelerometro.written()) {
        activarAcelerometro(car_activarAcelerometro.value());
    }

    // Publica solo medidas nuevas mientras la lectura esté activa.
    if (acelerometroActivo) {
        Vector3D aceleracion;

        if (leerAcelerometro(aceleracion)) {
            actualizarAcelerometroGATT(aceleracion);
        }
    }
}