/*
 * LED.cpp
 *
 *  Created on: May 1, 2018
 *      Author: daniel
 */

#include "LED.hpp"
#include "configuracion.h"
#include "msp.h"

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

void StartupBlink(){

    const short NUM_BLINKS = 3;

    //Bucle para parpadear LED
    for (int i = 0; i < NUM_BLINKS; i++){
        //P1->OUT ^= l_u8blinker;
        LED_on();
        for (int i = 0; i < 25; i++) { //0.125 s
            _delay_cycles(15000); //15000 ciclos = 5ms @ 3MHz
        }
        LED_off();
        for (int i = 0; i < 25; i++) {
            _delay_cycles(15000); //15000 ciclos = 5ms @ 3MHz
        }
    }

    //P1->OUT &= ~l_u8blinker; //apaga LED
    return;
}
