#pragma once

#include <Arduino.h>
#include <ArduinoBLE.h>

// Devuelve true si inicia el advertising.
bool initBLE();

// Llamar desde loop().
void updateBLE();