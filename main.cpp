#include "msp.h"
#include "configuracion.h"
#include "Button.hpp"
#include "audio.h"
#include "HAL_OPT.hpp"



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



/**
 * main.c
 */


int main(void)
{
    //uint32_t csregister = 0x0;

    WDTCTL = WDTPW | WDTHOLD;                    /* Stop watchdog timer */

    ConfigPorts();

    ConfigADC();

    ConfigSensorLuz();

    // Empezar conversión
    ADC14->CTL0 = ADC14->CTL0 | ADC14_CTL0_SC;


    //Button l_pButton(BUTTONS1);

    //uint16_t size = 512;
    //uint16_t datos[512];

    //g_u16pRawData = datos;
    //g_u16RawDataSize = size;



    int lux = 0;
    while (1)
    {

        if (HighAudioLevel()) {
            P1->OUT |= BIT0;

        } else {
            P1->OUT &= ~BIT0;
        }

        lux = OPT_getLux();
        if (lux < DAY_LUX) {
            LED_on();
        }
        else {
            LED_off();
        }
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
