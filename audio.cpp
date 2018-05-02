#include "audio.h"
#include <stdlib.h>

bool g_bHighAudio = false;


/**
 * Almacena el valor absoluto de los datos leidos del sensor.
 * 432 mediciones --> 50.0112 ms
 */
//static const int RAW_BUFF_S = 432;
//static CircularBuffer<uint16_t> g_u16pRawData(RAW_BUFF_S);

static uint32_t g_u32Avg432MicReadings = 0;
static int g_iMicReadCount = 0;
static const int RAW_BUFF_S = 432;

/**
 * Almacena el promedio de las últimas X mediciones.
 * Cada valor equivale a Y ms, para un total de
 * 100 valores --> 5.0112 s (20 valores --> 1 s)
 */
static const int PROM_BUFF_S = 100;
static CircularBuffer<uint32_t> g_u32pPromData(PROM_BUFF_S);
static const int PRIMER_SEG = PROM_BUFF_S/5;


static const int MIC_ZERO = 8192;



bool HighAudioLevel()
{
    bool l_bResult = false;

    if (g_u32pPromData.full()) {

        uint32_t l_iTotal = 0;
        uint32_t l_iPrimer = 0;

        for (int i = 0; i < PROM_BUFF_S; i++ ) {
            l_iTotal += g_u32pPromData[i];

            // Como los elementos se añaden por el final
            // los últimos corresponden al primer segundo
            if (i >= (PROM_BUFF_S - PRIMER_SEG)) {
                l_iPrimer += g_u32pPromData[i];
            }

        }
        l_iTotal = l_iTotal/PROM_BUFF_S;
        l_iPrimer = l_iPrimer/PRIMER_SEG;

        l_bResult = (10*l_iPrimer > (12*l_iTotal));
    }
    return l_bResult;
}

void ResetAudioBuffer()
{
    g_u32pPromData.clear();
}
extern "C"
{
    /**
     * Manejador de la interrupcion del ADC.
     * Recordar que se genera una medición cada 116 us.
     */
    void ADC14_IRQHandler(void)
    {
        __disable_irq();
        uint16_t ADC14Result = ADC14->MEM[0];
        ADC14->CLRIFGR0 = ADC14_CLRIFGR0_CLRIFG0;
        ADC14->CTL0 = ADC14->CTL0 | ADC14_CTL0_SC; // Start

        int32_t signed_result = ADC14Result;
        signed_result -= MIC_ZERO;

        //g_u16pRawData.push_back(abs(signed_result));
        g_u32Avg432MicReadings += (uint32_t) abs(signed_result);
        g_iMicReadCount++;

        // Si ya llenamos el buffer calculamos el promedio
        if (g_iMicReadCount == RAW_BUFF_S) {

            uint32_t sum = g_u32Avg432MicReadings/RAW_BUFF_S;
            g_u32pPromData.push_back(sum);
            g_u32Avg432MicReadings = 0;
            g_iMicReadCount = 0;
        }

        /*
        // Cada segundo prender/apagar el led
        if (g_u16AdcCount >= 8621) {
            P1->OUT ^= BIT0;
            g_u16AdcCount = 0;
        }
        */
        __enable_irq();
        return;
    }
}
