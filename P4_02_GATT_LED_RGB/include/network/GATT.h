#pragma once
#include "hal/IMU.h"
#include "hal/LED.h"

void initGATT();
void updateGATT();
void actualizarAcelerometroGATT(const Vector3D &aceleracion);