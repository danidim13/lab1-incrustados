#include <HAL_I2C.hpp>
#include <HAL_OPT.hpp>
#include "configuracion.h"
#include "audio.h"
#include <msp.h>

// BIT1=Boton P1.1, BIT4=Boton P1.4
//u16int_t g_u16SelectedButton = BIT4;
uint16_t g_u16SelectedButton = BIT1;



void ConfigPorts(){


    // LED como salida
    P1->DIR |= BIT0;
    P1->OUT |= BIT0;

#ifdef LED_15_WATT
    P2->DIR |= BIT6 | BIT4;
    P5->DIR |= BIT6;
#elif LED_10_WATT
    P2->DIR |= BIT6 | BIT4;
#elif LED_5_WATT
    P2->DIR |= BIT6;
#endif


    
    // Configurar resistencia pulldown y puerto como entrada (boton)
    P1->DIR &= ~g_u16SelectedButton;
    P1->REN |= g_u16SelectedButton;
    P1->OUT |= ~g_u16SelectedButton;

    // Interrupts habilitados, limpia interrupt flag,
    // interrupt edge select en flanco de bajada
    P1->IE |= g_u16SelectedButton;
    P1->IFG |= ~g_u16SelectedButton;
    P1->IES |= ~g_u16SelectedButton;

    // Set P4.3 for Analog input, disabling the I/O circuit.
    // P4.3 (micrófono) Como entrada.
    P4->SEL0 = BIT3;
    P4->SEL1 = BIT3;
    P4->DIR &= ~BIT3;
}

/**
 * Configuración del botón
 */
void ConfigButton(){
    NVIC_SetPriority(PORT1_IRQn,1);
    NVIC_EnableIRQ(PORT1_IRQn);
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
 * Configuracion de sensor de luz
 */
void ConfigSensorLuz(){
    /* Inicializa comunicacion I2C */
    Init_I2C_GPIO();
    I2C_init();

    /* Inicializar sensor de luz */
    OPT_init();
    __delay_cycles(1000);
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
     *      [1] | 4 | 32 | 64
     *
     * Divisor:
     *      1 | 2 | 3 | [4] | 5 | 6 | 7
     *
     * ---> Reloj del ADC = 750 kHz
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
     * ---> Periodo de muestreo = 85 us (11.718 kHz)
     * ---> Tiempo total de conversión = 116 us exactos (87 ciclos, 8.620 kHz)
     *
     *
     */
    ADC14->CTL0 = ADC14_CTL0_PDIV__1 | ADC14_CTL0_DIV__4 | ADC14_CTL0_SHT0__64
                | ADC14_CTL0_SSEL__MCLK | ADC14_CTL0_SHS_0 | ADC14_CTL0_SHP
                //| ADC14_CTL0_CONSEQ_2 | ADC14_CTL0_MSC
                | ADC14_CTL0_ON ;

    /**
     * Tension de referencia VRSel:
     *      V+ = AVCC (3.3 V) y V- = AVSS (0 V)
     * INput CHannel = A10 (P4.3)
     */
    ADC14->MCTL[0] = ADC14_MCTLN_INCH_10 | ADC14_MCTLN_VRSEL_0;

    // Habilitar conversion
    ADC14->CTL0 = ADC14->CTL0 | ADC14_CTL0_ENC;

    // Habilitar interrupciones de MEM0
    ADC14->IER0 = ADC14_IER0_IE0;

    NVIC_SetPriority(ADC14_IRQn,1);
    NVIC_EnableIRQ(ADC14_IRQn);
}

/**
 * Función para parpadear LEDs al inicio del ciclo de operación
 */
void StartupBlink(){

    uint8_t l_u8blinker = BIT0;
    const short NUM_LOOPS = 3;

    //Bucle para parpadear LED
    for (int i = 0; i>NUM_LOOPS; i++){
        P1->OUT ^= l_u8blinker;
        _delay_cycles(1500); //1500 ciclos = 0.5s @ 3kHz
    }

    P1->OUT &= ~l_u8blinker; //apaga LED
    return;
}

extern "C"
{
    
/*
* Atencion de interrupcion puerto 1
*/
void PORT1_IRQHandler(void)
    {
    __disable_irq();
    //Comprueba fuente de interrupcion P1.BITx
    if (P1->IFG and g_u16SelectedButton){
        //if Boton pulsado, IES por flanco de bajada
        // else, IES flanco de subida
        if (P1->IN and g_u16SelectedButton){
            P1->IES |= g_u16SelectedButton;
        } else {
            P1->IES |= ~g_u16SelectedButton;
        }
        //limpia flag de interrupcion
        P1->IFG |= ~g_u16SelectedButton;
    }
    __enable_irq();
    return;
    }
    
    /*
    void T32_INT1_IRQHandler(void)
    {
        __disable_irq();
        TIMER32_1->INTCLR = 0U;


        __enable_irq();
        return;
    }*/

    /**
     * Atencion de interrupcion ADC
     *
     */

}


