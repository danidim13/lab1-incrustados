/*
 * StateMachine.hpp
 *
 *  Created on: May 2, 2018
 *      Author: daniel
 */

#ifndef STATEMACHINE_HPP_
#define STATEMACHINE_HPP_




class StateMachine
{
public:

    StateMachine();
    virtual ~StateMachine();

    void Run();
    void ButtonPressed();
    void CountdownFinished();



private:
    void TransLightOn();
    void TransLightOff();
    const int DAY_LUX = 200;
    enum States {
        RESET,
        LIGHT_OFF,
        LIGHT_ON,
    };
    //bool m_bCountingDown;
    int m_iCurrentState;

};

extern StateMachine g_pMainControl;

#endif /* STATEMACHINE_HPP_ */
