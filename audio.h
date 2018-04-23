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

#define RAW_BUFF_S 512;
#define MIC_ZERO 8192;
extern CircularBuffer<int16_t> *g_16ipRawData;




#endif /* AUDIO_H_ */
