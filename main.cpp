#include "msp.h"
#include "configuracion.h"
#include "Button.hpp"



/**
 * main.c
 */

uint16_t ADC14Result = 0U;
int main(void)
{
    //uint32_t csregister = 0x0;

    WDTCTL = WDTPW | WDTHOLD;                    /* Stop watchdog timer */

    ConfigPorts();


    Button l_pButton(BUTTONS1);

    while (1)
    {
        if (l_pButton.Pressed()) {
            P1->OUT |= BIT0;
        } else {
            P1->OUT &= ~BIT0;
        }


    }
    return 0;
}
