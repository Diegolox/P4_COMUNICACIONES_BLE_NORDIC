#include <Arduino.h>
#include <ArduinoBLE.h>
#include "network/GATT.h"

//------------------//
// SERVICIO LED     //
//------------------//

// EL GATT ES EL CONJUNTO DE SERVICIOS DE LA APLICACIÓN
// LOS SERVICIOS SON MEROS CONJUNTOS DE CARACTERÍSTICAS. LAS CARACTERÍSITCAS SOLO PUEDEN PERTENECER A UN SERVICIO
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



//-------------------------------//
// SERVICIO LECTURA ACELEROMETRO //
//-------------------------------//

static BLEService servicioIMU( // CREACION DEL SERVICIO PARA LA IMU
    "44494547-4F00-0000-0000-000000000010"
);

// Texto x;y;z, con lectura y notificaciones.
static BLEStringCharacteristic caracteristicaAcelerometro( // CARACTERISTICA IMU
    "44494547-4F00-0000-0000-000000000011",
    BLERead | BLENotify,
    20
);

void actualizarAcelerometroGATT(const Vector3D &aceleracion) {
    char datos[21];

    snprintf( // convierte lectura del acelerómetro a 0.000;0.000;0.000 y lo guarda en datos
        datos,
        sizeof(datos),
        "%.3f;%.3f;%.3f",
        aceleracion.x,
        aceleracion.y,
        aceleracion.z
    );

    // Actualiza el valor y notifica al móvil si está suscrito.
    caracteristicaAcelerometro.writeValue(datos); // guarda datos en la característica
}




//------------------//
//       GATT       //
//------------------//

void initGATT() {
    //---LED RGB
    // Añade la característica y registra el servicio.
    servicioLED.addCharacteristic(colorLED);
    // añade el servicio al GATT para que el cliente lo vea una vez conectado.
    BLE.addService(servicioLED);

    // PONE A CERO EL LED AL INICIO ESCRIBIENDO EN LA CARACTERÍSTICA.
    colorLED.writeValue(0);
    // Añade el servicio al advertising para que el cliente lo vea.
    BLE.setAdvertisedService(servicioLED); 

    //---IMU
    // CREA LA CARACTERISTICA DEL IMU
    servicioIMU.addCharacteristic(caracteristicaAcelerometro);
    // AÑADE EL SERVICIO DEL IMU AL GATT
    BLE.addService(servicioIMU);
    // PONE A CERO EL VALOR DE LA CARACTERISTICA DEL IMU
    caracteristicaAcelerometro.writeValue("0.000;0.000;0.000");
    // AÑADE EL SERVICIO DEL IMU AL ADVERTISING PARA QUE EL CLIENTE LO VEA ANTES DE CONECTARSE.
    BLE.setAdvertisedService(servicioIMU);
}


void updateGATT() {
    // Aplica el color recibido del cliente.
    if (colorLED.written()) {
        cambiarColorLED(colorLED.value());
    }

    // Publica la aceleración cuando hay una medida nueva.
    Vector3D aceleracion;

    if (leerAcelerometro(aceleracion)) {
        actualizarAcelerometroGATT(aceleracion);
    }
}
