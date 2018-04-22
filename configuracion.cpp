#include "configuracion.h"
#include <msp.h>

void ConfigPorts(){
    // LED
    P1->DIR = BIT0;
    P1->OUT = BIT0 & BIT1;

    // Set P4.3 for Analog input, disabling the I/O circuit.
    P4->SEL0 = BIT3;
    P4->SEL1 = BIT3;
    P4->DIR &= ~BIT3;

}

/**
 * Configuración del módulo de timer32
 * XX ms
 */
void ConfigTimer(){
    //TIMER32_1->LOAD = 0x00B71B00; //~0.5s ---> a 48Mhz

    TIMER32_1->LOAD = 0x0000BB80; //~0.5s ---> a 48Mhz
    TIMER32_1->CONTROL = TIMER32_CONTROL_SIZE | TIMER32_CONTROL_PRESCALE_0 | TIMER32_CONTROL_MODE | TIMER32_CONTROL_IE | TIMER32_CONTROL_ENABLE;
    NVIC_SetPriority(T32_INT1_IRQn,1);
    NVIC_EnableIRQ(T32_INT1_IRQn);
    return;
}

/**
 * Configuración del convertidor A/D
 */
void ConfigADC(){
    /**
     * Reloj = Master Clock (3 MHz)
     *
     * Predivisor:
     *      [1] | 4 | [32] | 64
     *
     * Divisor:
     *      1 | 2 | 3 | 4 | [5] | 6 | 7
     *
     * ---> Reloj del ADC = 600 kHz
     *
     * Pulse Sample Mode: Se inicia una conversión al recibir un
     * pulso (posedge) en el sample-and-hold source.
     *
     * Sample and Hold source = ADC14SC
     *
     * SAMPCON define el periodo de muestreo, a partir del reloj del ADC
     * el número de ciclos se define en los registros de control
     * ADC14SHT1x y ADC14SHT0x
     *
     * Cantidad de ciclos para muestreo:
     *      4 | 8 | 16 | 32 | [64] | 96 | 128 | 192
     *
     * ---> Periodo de muestreo = 0.107 ms (9.375 kHz)
     * ---> Tiempo total de conversión =
     *
     *
     */
    ADC14->CTL0 = ADC14_CTL0_PDIV__1 | ADC14_CTL0_SHS_0 | ADC14_CTL0_DIV__5 |
                  ADC14_CTL0_SSEL__MCLK | ADC14_CTL0_SHT0__64 | ADC14_CTL0_ON
                  | ADC14_CTL0_SHP;

    /**
     * Tension de referencia VRSel =
     * INput CHannel =
     */
    ADC14->MCTL[0] = ADC14_MCTLN_INCH_10 | ADC14_MCTLN_VRSEL_0;

    ADC14->CTL0 = ADC14->CTL0 | ADC14_CTL0_ENC; // Habilitar conversion

    ADC14->IER0 = ADC14_IER0_IE0; // Habilitar interrupciones de MEM0

    NVIC_SetPriority(ADC14_IRQn,1);
    NVIC_EnableIRQ(ADC14_IRQn);
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

