#include <hal/LED.h>
#include <Arduino.h>


void cambiarColorLED(byte color) {
    // LOW enciende; HIGH apaga.
    digitalWrite(LEDR, color == 1 ? LOW : HIGH);
    digitalWrite(LEDG, color == 2 ? LOW : HIGH);
    digitalWrite(LEDB, color == 3 ? LOW : HIGH);
}