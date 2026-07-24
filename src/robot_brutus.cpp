#include "robot_brutus.hpp"

// init comunicacion bluetooth
void RA_brutus_setup()
{
    btBrutus.begin(9600);
    modoAutonomo = true; // arranca en modo autonomo
}

// hay algun byte pendiente de leer
bool RA_brutus_hayComando()
{
    return btBrutus.available() > 0;
}

// lee un caracter enviado desde la app
char RA_brutus_leerComando()
{
    return (char)btBrutus.read();
}

// envia una linea de texto a la app
void RA_brutus_enviarEstado(const char* _txt)
{
    btBrutus.println(_txt);
}

// cambia el modo: true(autonomo) / false(manual)
void RA_brutus_modo(bool _modo)
{
    modoAutonomo = _modo;

    if (_modo == true)
        Serial.println("Modo autonomo activado");
    else
        Serial.println("Modo manual activado");
}

// devuelve el modo actual
bool RA_brutus_modo()
{
    return modoAutonomo;
}

// funcion de test de bluetooth
void RA_brutus_test(int _prueba)
{
    if (_prueba == 0)
    {
        // test - eco de comandos recibidos
        if (RA_brutus_hayComando())
        {
            char _c = RA_brutus_leerComando();
            Serial.print("Brutus Test 0 - Comando recibido: ");
            Serial.println(_c);
        }
    }
    else if (_prueba == 1)
    {
        // test - enviar estado de prueba
        Serial.println("Brutus Test 1 - Enviando estado de prueba");
        RA_brutus_enviarEstado("Test desde Arduino");
        delay(1000);
    }
}
