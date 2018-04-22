/*
 * configuracion.h
 *
 *  Created on: Apr 18, 2018
 *      Author: daniel
 *
 */

#include <msp.h>

extern uint16_t ADC14Result;

#ifndef CONFIGURACION_H_
#define CONFIGURACION_H_

extern uint16_t ADC14Result;
void ConfigPorts();
void ConfigTimer();
void ConfigADC();
void ConfigSensorLuz();

#endif /* CONFIGURACION_H_ */
