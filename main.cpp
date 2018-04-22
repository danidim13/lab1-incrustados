#include "msp.h"
#include "configuracion.h"
#include "Button.hpp"



/**
 * main.c
 */


int main(void)
{
    //uint32_t csregister = 0x0;

    WDTCTL = WDTPW | WDTHOLD;                    /* Stop watchdog timer */

    ConfigPorts();

    ConfigADC();

    // Empezar conversión
    ADC14->CTL0 = ADC14->CTL0 | ADC14_CTL0_SC;


    //Button l_pButton(BUTTONS1);

    while (1)
    {
        /*
        if (l_pButton.Pressed()) {
            P1->OUT |= BIT0;
        } else {
            P1->OUT &= ~BIT0;
        }
        */


    }
    return 0;
}
