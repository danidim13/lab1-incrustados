/*
 * StateMachine.cpp
 *
 *  Created on: May 2, 2018
 *      Author: daniel
 */

#include <StateMachine.hpp>
#include "LED.hpp"
#include "HAL_OPT.hpp"
#include "audio.h"

StateMachine::StateMachine()
{
    this->m_iCurrentState = RESET;

    // TODO Auto-generated constructor stub

}

StateMachine::~StateMachine()
{
    // TODO Auto-generated destructor stub
}

void StateMachine::TransLightOn()
{
    // Prender el LED y activar el countdown
    m_iCurrentState = LIGHT_ON;
    LED_on();
    TIMER32_2->LOAD = 117185; // 10 segundos
}

void StateMachine::TransLightOff()
{
    m_iCurrentState = LIGHT_OFF;
    LED_off();
}

void StateMachine::Run() {
    while (true) {
        switch (m_iCurrentState) {

        case RESET:
        {
            StartupBlink();
            if (OPT_getLux() >= DAY_LUX){
                TransLightOff();
            } else {
                TransLightOn();
            }
            break;
        }


        case LIGHT_OFF:
        {
            if (OPT_getLux() < DAY_LUX){
                if (HighAudioLevel()) {
                    TransLightOn();
                }
            }
            break;
        }
        case LIGHT_ON:
        {
            _delay_cycles(15000);  //15000 ciclos = 5ms
            break;
        }
        default:{
            m_iCurrentState = RESET;
            break;
        }
        }
    }
}

void StateMachine::ButtonPressed()
{
    if (m_iCurrentState == LIGHT_ON) {
        TransLightOff();
    } else if (m_iCurrentState == LIGHT_OFF) {
        TransLightOn();
    }
    ResetAudioBuffer();
}


void StateMachine::CountdownFinished()
{
    if (m_iCurrentState == LIGHT_ON) {
        TransLightOff();
    }
}
