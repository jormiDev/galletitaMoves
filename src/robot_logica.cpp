#include "robot_logica.hpp"
#include "robot_tractora.hpp"
#include "robot_gallato.hpp"
#include "robot_brutus.hpp"

// llamada en cada loop - gestiona comandos de brutus y la maquina de estados
void RA_logica_loop()
{
    // 1) comandos entrantes desde el movil (app MIT App Inventor)
    if (RA_brutus_hayComando())
    {
        char _cmd = RA_brutus_leerComando();

        if (_cmd == 'A')
            RA_brutus_modo(true);
        else if (_cmd == 'M')
        {
            RA_brutus_modo(false);
            RA_tractora_detener();
        }
        else if (RA_brutus_modo() == false)
        {
            // conduccion manual directa
            if (_cmd == 'F')
                RA_tractora_adelante(VELOCIDAD_CRUCERO);
            else if (_cmd == 'B')
                RA_tractora_atras(VELOCIDAD_CRUCERO);
            else if (_cmd == 'L')
                RA_tractora_pivotarIzquierda(VELOCIDAD_CRUCERO);
            else if (_cmd == 'R')
                RA_tractora_pivotarDerecha(VELOCIDAD_CRUCERO);
            else if (_cmd == 'S')
                RA_tractora_detener();
            return; // en modo manual no se ejecuta la maquina de estados
        }
    }

    if (RA_brutus_modo() == false)
        return;

    // 2) maquina de estados - modo autonomo (evitar paredes)
    switch (maqEstado)
    {
    case MAQ_AVANZANDO:
        RA_gallato_apuntar(90);
        if (RA_gallato_medirDistancia() < DIST_SEGURIDAD)
        {
            RA_tractora_detener();
            RA_brutus_enviarEstado("Obstaculo detectado");
            maqEstadoPrevio = maqEstado;
            maqEstado = MAQ_EVALUANDO;
        }
        else
        {
            RA_tractora_adelante(VELOCIDAD_CRUCERO);
        }
        break;

    case MAQ_EVALUANDO:
    {
       
    long _distMejor = 0;
    int _mejorAngulo = RA_gallato_mejorDireccion(30, 150, 30, &_distMejor);

    if (_distMejor < DIST_SEGURIDAD)
    {
        RA_brutus_enviarEstado("Bloqueado, retrocediendo");
        maqEstadoPrevio = maqEstado;
        maqEstado = MAQ_RETROCEDIENDO;
    }
    else if (_mejorAngulo < 90)
    {
        RA_tractora_pivotarIzquierda(VELOCIDAD_CRUCERO);
        maqEstadoPrevio = maqEstado;
        maqEstado = MAQ_GIRANDO;
    }
    else if (_mejorAngulo > 90)
    {
        RA_tractora_pivotarDerecha(VELOCIDAD_CRUCERO);
        maqEstadoPrevio = maqEstado;
        maqEstado = MAQ_GIRANDO;
    }
    else
    {
        maqEstado = MAQ_AVANZANDO;
    }
    break;
    }

    case MAQ_GIRANDO:
    {
        static unsigned long _inicioGiro = 0;
        if (_inicioGiro == 0)
            _inicioGiro = millis();

        if (millis() - _inicioGiro > 400) // ajustar segun peso del robot
        {
            RA_tractora_detener();
            _inicioGiro = 0;
            maqEstadoPrevio = maqEstado;
            maqEstado = MAQ_AVANZANDO;
        }
        break;
    }

    case MAQ_RETROCEDIENDO:
    {
        static unsigned long _inicioRet = 0;
        static bool _girando180 = false;

        if (_inicioRet == 0 && !_girando180)
        {
            RA_tractora_atras(VELOCIDAD_CRUCERO);
            _inicioRet = millis();
        }

        if (!_girando180 && millis() - _inicioRet > 500)
        {
            RA_tractora_pivotarDerecha(VELOCIDAD_CRUCERO);
            _inicioRet = millis();
            _girando180 = true;
        }
        else if (_girando180 && millis() - _inicioRet > 700)
        {
            RA_tractora_detener();
            _inicioRet = 0;
            _girando180 = false;
            maqEstadoPrevio = maqEstado;
            maqEstado = MAQ_AVANZANDO;
        }
        break;
    }
    } // fin switch
}
