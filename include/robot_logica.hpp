#ifndef _ROBOT_LOGICA_
#define _ROBOT_LOGICA_

#include "Arduino.h"
#include "constantes.h"

/*
objetos y variables
*/
extern int maqEstado;
extern int maqEstadoPrevio;

/*
funciones
*/

// llamada en cada loop - gestiona comandos de brutus y la maquina de estados
void RA_logica_loop();

#endif
