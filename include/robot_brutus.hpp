#ifndef _ROBOT_BRUTUS_
#define _ROBOT_BRUTUS_

#include "Arduino.h"
#include "constantes.h"
#include "SoftwareSerial.h"

/*
objetos y variables
*/
extern SoftwareSerial btBrutus;
extern bool modoAutonomo;

/*
funciones
*/

// init comunicacion bluetooth
void RA_brutus_setup();

// hay algun byte pendiente de leer
bool RA_brutus_hayComando();

// lee un caracter enviado desde la app
char RA_brutus_leerComando();

// envia una linea de texto a la app (estado, telemetria...)
void RA_brutus_enviarEstado(String _txt);

// cambia el modo: true(autonomo) / false(manual)
void RA_brutus_modo(bool _modo);

// devuelve el modo actual
bool RA_brutus_modo();

// funcion de test de bluetooth
void RA_brutus_test(int _prueba);

#endif
