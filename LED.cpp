/*
 * LED.cpp
 *
 *  Created on: May 1, 2018
 *      Author: daniel
 */

#include "LED.hpp"
#include "configuracion.h"

void LED_on()
{
#ifdef LED_15_WATT
    P2->OUT |= BIT6 | BIT4;
    P5->OUT |= BIT6;
#elif LED_10_WATT
    P2->OUT |= BIT6 | BIT4;
#elif LED_5_WATT
    P2->OUT |= BIT6 | BIT4;

#endif
    return;
}

void LED_off()
{
#ifdef LED_15_WATT
    P2->OUT &= ~(BIT6 | BIT4);
    P5->OUT &= ~BIT6;
#elif LED_10_WATT
    P2->OUT &= ~(BIT6 | BIT4);
#elif LED_5_WATT
    P2->OUT &= ~(BIT6 | BIT4);

#endif
    return;
}

