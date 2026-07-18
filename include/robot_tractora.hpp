#ifndef _ROBOT_TRACTORA_
#define _ROBOT_TRACTORA_

#include "Arduino.h"
#include "constantes.h"

/*
funciones
*/

// init pines de los motores
void RA_tractora_setup();

// velocidades independientes por rueda: -255..255
// permite avanzar recto, curvas suaves o pivotar sobre el eje
void RA_tractora_girar(int _velIzq, int _velDer);

void RA_tractora_adelante(int _velocidad);
void RA_tractora_atras(int _velocidad);
void RA_tractora_pivotarIzquierda(int _velocidad);
void RA_tractora_pivotarDerecha(int _velocidad);
void RA_tractora_detener();

// funcion de test de motores
void RA_tractora_test(int _prueba);

#endif
