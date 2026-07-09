#include "robot_gallato.hpp"

// init sensor + servo
void RA_gallato_setup()
{
    pinMode(PIN_SENSOR_TRIG, OUTPUT);
    pinMode(PIN_SENSOR_ECHO, INPUT);

    servoGallato.attach(PIN_SERVO_GALLATO);
    RA_gallato_apuntar(90); // centro
}

// mueve el servo al angulo indicado
void RA_gallato_apuntar(int _angulo)
{
    _angulo = constrain(_angulo, 0, 180);
    servoGallato.write(_angulo);
    gallato_anguloActual = _angulo;
    delay(150); // tiempo de asentamiento del servo
}

// una lectura de distancia al angulo actual, en cm
long RA_gallato_medirDistancia()
{
    digitalWrite(PIN_SENSOR_TRIG, LOW);
    delayMicroseconds(2);
    digitalWrite(PIN_SENSOR_TRIG, HIGH);
    delayMicroseconds(10);
    digitalWrite(PIN_SENSOR_TRIG, LOW);

    long _duracion = pulseIn(PIN_SENSOR_ECHO, HIGH, 25000UL); // timeout ~4m
    if (_duracion == 0)
        return 400; // sin eco = zona despejada

    return _duracion * 34 / 2000; // us -> cm
}

// barre entre _aIni y _aFin y devuelve el angulo con mas distancia libre
int RA_gallato_mejorDireccion(int _aIni, int _aFin, int _paso)
{
    int _mejorAngulo = 90;
    long _mejorDist = -1;

    for (int _a = _aIni; _a <= _aFin; _a += _paso)
    {
        RA_gallato_apuntar(_a);
        long _d = RA_gallato_medirDistancia();
        if (_d > _mejorDist)
        {
            _mejorDist = _d;
            _mejorAngulo = _a;
        }
    }

    RA_gallato_apuntar(90);
    return _mejorAngulo;
}

// funcion de test del sensor
void RA_gallato_test(int _prueba)
{
    if (_prueba == 0)
    {
        // test - medir distancia al frente
        Serial.print("Gallato Test 0 - Distancia frontal: ");
        Serial.print(RA_gallato_medirDistancia());
        Serial.println(" cm");
        delay(1000);
    }
    else if (_prueba == 1)
    {
        // test - barrido completo
        Serial.println("Gallato Test 1 - Barrido 30-150");
        int _angulo = RA_gallato_mejorDireccion(30, 150, 30);
        Serial.print("Mejor angulo: ");
        Serial.println(_angulo);
    }
}
