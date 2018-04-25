/*
 * audio.h
 *
 *  Created on: Apr 22, 2018
 *      Author: daniel
 */

#ifndef AUDIO_H_
#define AUDIO_H_


#include "msp.h"
#include "CircularBuffer.hpp"

/**
 * Variable global que indica si el nivel del
 * último segundo estuvo por encima del promedio
 * de los últimos 5 segundos.
 */
//extern bool g_bHighAudio;
bool HighAudioLevel();

#endif /* AUDIO_H_ */
