/*
 * configuracion.h
 *
 *  Created on: Apr 18, 2018
 *      Author: daniel
 *
 */
#ifndef CONFIGURACION_H_
#define CONFIGURACION_H_

#include <msp.h>


//#define LED_5_WATT 1
#define LED_10_WATT 1
//#define LED_15_WATT 1

#define DAY_LUX 500

void ConfigPorts();
void ConfigTimer();
void ConfigADC();
void ConfigSensorLuz();
void StartupBlink();

#endif /* CONFIGURACION_H_ */
