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
//#define LED_10_WATT 1
#define LED_15_WATT 1

void ConfigPorts();
void ConfigButton();
void ConfigTimer();
void ConfigADC();
void ConfigSensorLuz();

#endif /* CONFIGURACION_H_ */
