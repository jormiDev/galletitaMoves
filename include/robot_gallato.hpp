#ifndef _ROBOT_GALLATO_
#define _ROBOT_GALLATO_

#include "Arduino.h"
#include "constantes.h"
#include "Servo.h"

/*
objetos y variables
*/
extern Servo servoGallato;
extern int gallato_anguloActual;

/*
funciones
*/

// init sensor + servo
void RA_gallato_setup();

// mueve el servo al angulo indicado (0-180)
void RA_gallato_apuntar(int _angulo);

// una lectura de distancia al angulo actual, en cm
long RA_gallato_medirDistancia();

// barre entre _aIni y _aFin y devuelve el angulo con mas distancia libre
// al terminar deja el servo centrado en 90
int RA_gallato_mejorDireccion(int _aIni, int _aFin, int _paso);

// funcion de test del sensor
void RA_gallato_test(int _prueba);

#endif
