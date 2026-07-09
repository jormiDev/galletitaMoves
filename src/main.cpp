/*
Robot Autonomo - notas de cableado

Driver de motores L298N (modulo "tractora")
    IN1/IN2/ENA -> motor izquierdo
    IN3/IN4/ENB -> motor derecho
    ENA/ENB deben ir a pines PWM

Sensor de distancia HC-SR04 sobre servo SG90 (modulo "gallato")
    TRIG, ECHO -> HC-SR04
    servo en PIN_SERVO_GALLATO (pin PWM)

Modulo Bluetooth HC-05/HC-06 (modulo "brutus")
    RX/TX por SoftwareSerial, PIN_BT_RX / PIN_BT_TX
    App companion hecha en MIT App Inventor

Protocolo de comandos (un caracter) enviados desde la app:
    A -> modo autonomo
    M -> modo manual
    F / B / L / R / S -> adelante / atras / izquierda / derecha / stop (solo en manual)
*/

#include <Arduino.h>

#include <Servo.h>
#include <SoftwareSerial.h>

#include "constantes.h"

#include "robot_tractora.hpp"
#include "robot_gallato.hpp"
#include "robot_brutus.hpp"
#include "robot_logica.hpp"

// robot_gallato
Servo servoGallato;
int gallato_anguloActual;

// robot_brutus
SoftwareSerial btBrutus(PIN_BT_RX, PIN_BT_TX);
bool modoAutonomo;

// robot_logica
int maqEstado;
int maqEstadoPrevio;

/*
********   S E T U P   ***************
*/

void setup()
{
    // Serial init
    Serial.begin(9600);
    while (!Serial)
        ;

    Serial.println("setup   INIT");

    // init tractora
    RA_tractora_setup();
    Serial.println("setup   -  Tractora");

    // init gallato
    RA_gallato_setup();
    Serial.println("setup   -  Gallato");

    // init brutus
    RA_brutus_setup();
    Serial.println("setup   -  Brutus");

    // init logica
    maqEstado = MAQ_AVANZANDO;
    maqEstadoPrevio = MAQ_AVANZANDO;
    Serial.println("setup   -  Logica");

    // fin setup
    Serial.println("setup   FIN");
    Serial.println("");

    Serial.println("loop    INIT");
}

/*
********   L O O P   ***************
*/

void loop()
{

    // llamada en cada loop
    RA_logica_loop();

    /*
    zona de test
    */
    // RA_tractora_test(0);  ok
    // RA_tractora_test(1);  ok
    // RA_gallato_test(0);   ok
    // RA_gallato_test(1);   ok
    // RA_brutus_test(0);    ok
    // RA_brutus_test(1);    ok

} // fin loop
