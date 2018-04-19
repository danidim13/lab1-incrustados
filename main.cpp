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


    Button *l_pButton = new Button(BUTTONS1);

    while (1)
    {
        if (l_pButton->Pressed()) {
            P1->OUT |= BIT0;
        } else {
            P1->OUT &= ~BIT0;
        }

    }

    delete l_pButton;
    return 0;
}
/*
extern "C"
{
    void T32_INT1_IRQHandler(void)
    {
        __disable_irq();
        TIMER32_1->INTCLR = 0U;
        P1->OUT ^= BIT0;
        ADC14->CTL0 = ADC14->CTL0 | ADC14_CTL0_SC; // Start
        __enable_irq();
        return;
    }

    void ADC14_IRQHandler(void)
    {
        __disable_irq();
        ADC14Result = ADC14->MEM[0];
        ADC14->CLRIFGR0 = ADC14_CLRIFGR0_CLRIFG0;
        __enable_irq();
        return;
    }
}
*/
