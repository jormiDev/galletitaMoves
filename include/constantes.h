/*
NOTAS
*/

#ifndef _ROBOT_CONSTANTES_H_
#define _ROBOT_CONSTANTES_H_

/*
pines conectados
*/

// robot_tractora.hpp - Driver de motores L298N
#define     PIN_MOTOR_IN1   4
#define     PIN_MOTOR_IN2   5
#define     PIN_MOTOR_ENA    6       // PWM
#define     PIN_MOTOR_IN3   7
#define     PIN_MOTOR_IN4   8
#define     PIN_MOTOR_ENB    9       // PWM

// robot_gallato.hpp - sensor HC-SR04 + servo SG90
#define     PIN_SENSOR_TRIG     12
#define     PIN_SENSOR_ECHO     13
#define     PIN_SERVO_GALLATO   11      // PWM

// robot_brutus.hpp - modulo bluetooth HC-05/HC-06
#define     PIN_BT_RX           2
#define     PIN_BT_TX           3

/*
main
*/
#define     VERSION             0.02
                                // 0.01 - version inicial

/*
robot_logica.hpp
*/
#define     MAQ_AVANZANDO       0
#define     MAQ_EVALUANDO       1
#define     MAQ_GIRANDO         2
#define     MAQ_RETROCEDIENDO   3

#define     DIST_SEGURIDAD      25      // cm, distancia minima antes de frenar
#define     VELOCIDAD_CRUCERO   180     // 0-255

#endif
