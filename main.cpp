#include "msp.h"


/**
 * main.c
 */

uint16_t ADC14Result = 0U;
int main(void)
{
    //uint32_t csregister = 0x0;

    WDTCTL = WDTPW | WDTHOLD;                    /* Stop watchdog timer */

    P1->DIR = BIT0;
    P1->OUT = BIT0;
    // Set P4.3 for Analog input, disabling the I/O circuit.
    P4->SEL0 = BIT3;
    P4->SEL1 = BIT3;
    P4->DIR &= ~BIT3;

    //TIMER32_1->LOAD = 0x00B71B00; //~0.5s ---> a 48Mhz
    TIMER32_1->LOAD = 0x0000BB80; //~0.5s ---> a 48Mhz
    TIMER32_1->CONTROL = TIMER32_CONTROL_SIZE | TIMER32_CONTROL_PRESCALE_0 | TIMER32_CONTROL_MODE | TIMER32_CONTROL_IE | TIMER32_CONTROL_ENABLE;
    NVIC_SetPriority(T32_INT1_IRQn,1);
    NVIC_EnableIRQ(T32_INT1_IRQn);

    ADC14->CTL0 = ADC14_CTL0_PDIV_0 | ADC14_CTL0_SHS_0 | ADC14_CTL0_DIV_7 |
                  ADC14_CTL0_SSEL__MCLK | ADC14_CTL0_SHT0_1 | ADC14_CTL0_ON
                  | ADC14_CTL0_SHP;
    ADC14->MCTL[0] = ADC14_MCTLN_INCH_10 | ADC14_MCTLN_VRSEL_0;
    ADC14->CTL0 = ADC14->CTL0 | ADC14_CTL0_ENC;
    ADC14->IER0 = ADC14_IER0_IE0;
    NVIC_SetPriority(ADC14_IRQn,1);
    NVIC_EnableIRQ(ADC14_IRQn);
    while (1)
    {

    }

    return 0;
}

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
