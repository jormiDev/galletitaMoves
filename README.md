# Robot Autonomo — Arduino + PlatformIO

Estructura y convenciones adaptadas al estilo del proyecto `despertadorSolar`:
modulos en C (sin clases), prefijo `RA_` en las funciones, objetos globales
`extern` en cada `.hpp` y definidos en `main.cpp`, y `constantes.h` centralizando
todos los `#define`.

## Estructura del proyecto

```
robot-autonomo/
├── platformio.ini
├── include/
│   ├── constantes.h         # pines y constantes, por modulo
│   ├── robot_tractora.hpp    # motores
│   ├── robot_gallato.hpp      # sensor de distancia + servo
│   ├── robot_brutus.hpp        # bluetooth / app movil
│   └── robot_logica.hpp         # maquina de estados
└── src/
    ├── main.cpp
    ├── robot_tractora.cpp
    ├── robot_gallato.cpp
    ├── robot_brutus.cpp
    └── robot_logica.cpp
```

## Antes de subir el codigo

Revisa en `include/constantes.h`:

- Pines de motores, sensor, servo y modulo bluetooth segun tu cableado real.
- `DIST_SEGURIDAD` y `VELOCIDAD_CRUCERO` segun el tamaño/peso del robot.
- El tiempo de giro en `robot_logica.cpp` (`MAQ_GIRANDO`, 400 ms de partida).

## Protocolo Bluetooth (app MIT App Inventor)

| Caracter | Accion                          |
|----------|-----------------------------------|
| `A`      | Modo autonomo                       |
| `M`      | Modo manual                          |
| `F`      | Adelante (solo en manual)             |
| `B`      | Atras (solo en manual)                 |
| `L`      | Pivotar izquierda (solo en manual)      |
| `R`      | Pivotar derecha (solo en manual)         |
| `S`      | Detener (solo en manual)                  |

El Arduino tambien envia estados por bluetooth (`RA_brutus_enviarEstado(...)`),
utiles para un `Label` en la app.

## Funciones de test

Cada modulo trae su propia `RA_xxx_test(int _prueba)`, igual que en
`dSolar_boton_test` / `dSolar_buzzer_test`. Estan comentadas al final de
`loop()` en `main.cpp`; descomenta la que quieras probar de forma aislada.
