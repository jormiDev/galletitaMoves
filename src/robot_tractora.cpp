#include "robot_tractora.hpp"

// init pines de los motores
void RA_tractora_setup()
{
    pinMode(PIN_MOTOR_IZQ_IN1, OUTPUT);
    pinMode(PIN_MOTOR_IZQ_IN2, OUTPUT);
    pinMode(PIN_MOTOR_IZQ_EN, OUTPUT);
    pinMode(PIN_MOTOR_DER_IN1, OUTPUT);
    pinMode(PIN_MOTOR_DER_IN2, OUTPUT);
    pinMode(PIN_MOTOR_DER_EN, OUTPUT);

    RA_tractora_detener();
}

// velocidades independientes por rueda: -255..255
void RA_tractora_girar(int _velIzq, int _velDer)
{
    digitalWrite(PIN_MOTOR_IZQ_IN1, _velIzq >= 0 ? HIGH : LOW);
    digitalWrite(PIN_MOTOR_IZQ_IN2, _velIzq >= 0 ? LOW : HIGH);
    analogWrite(PIN_MOTOR_IZQ_EN, constrain(abs(_velIzq), 0, 255));

    digitalWrite(PIN_MOTOR_DER_IN1, _velDer >= 0 ? HIGH : LOW);
    digitalWrite(PIN_MOTOR_DER_IN2, _velDer >= 0 ? LOW : HIGH);
    analogWrite(PIN_MOTOR_DER_EN, constrain(abs(_velDer), 0, 255));
}

void RA_tractora_adelante(int _velocidad)
{
    RA_tractora_girar(_velocidad, _velocidad);
}

void RA_tractora_atras(int _velocidad)
{
    RA_tractora_girar(-_velocidad, -_velocidad);
}

void RA_tractora_pivotarIzquierda(int _velocidad)
{
    RA_tractora_girar(-_velocidad, _velocidad);
}

void RA_tractora_pivotarDerecha(int _velocidad)
{
    RA_tractora_girar(_velocidad, -_velocidad);
}

void RA_tractora_detener()
{
    RA_tractora_girar(0, 0);
}

// funcion de test de motores
void RA_tractora_test(int _prueba)
{
    if (_prueba == 0)
    {
        // test - adelante / atras
        Serial.println("Tractora Test 0 - Adelante 2s");
        RA_tractora_adelante(VELOCIDAD_CRUCERO);
        delay(2000);
        RA_tractora_detener();
        delay(500);
        Serial.println("Tractora Test 0 - Atras 2s");
        RA_tractora_atras(VELOCIDAD_CRUCERO);
        delay(2000);
        RA_tractora_detener();
    }
    else if (_prueba == 1)
    {
        // test - pivotar izquierda / derecha
        Serial.println("Tractora Test 1 - Pivotar izquierda 1s");
        RA_tractora_pivotarIzquierda(VELOCIDAD_CRUCERO);
        delay(1000);
        RA_tractora_detener();
        delay(500);
        Serial.println("Tractora Test 1 - Pivotar derecha 1s");
        RA_tractora_pivotarDerecha(VELOCIDAD_CRUCERO);
        delay(1000);
        RA_tractora_detener();
    }
}
