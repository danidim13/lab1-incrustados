#include "msp.h"
#include "configuracion.h"
#include "Button.hpp"
#include "audio.h"
#include "HAL_OPT.hpp"
#include "LED.hpp"
#include "StateMachine.hpp"




/**
 * main.c
 */

StateMachine g_pMainControl;

int main(void)
{
    //uint32_t csregister = 0x0;

    WDTCTL = WDTPW | WDTHOLD;                    /* Stop watchdog timer */

    ConfigPorts();
    ConfigADC();
    ConfigSensorLuz();
    ConfigButton();
    ConfigTimer();
    LED_off();

    // Empezar conversión
    ADC14->CTL0 = ADC14->CTL0 | ADC14_CTL0_SC;


    g_pMainControl.Run();

    return 0;
}
