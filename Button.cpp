/*
 * Button.cpp
 *
 *  Created on: Apr 12, 2018
 *      Author: daniel
 */

#include <Button.hpp>
#include <stdio.h>

Button::Button()
{
    // Usar boton S1 por defecto
    m_u16SelectedButton = BIT1;
    ConfigureButton();
    // TODO Auto-generated constructor stub

}

Button::~Button()
{
    // TODO Auto-generated destructor stub
}

Button::Button(int i_iButton)
{

    if (i_iButton == BUTTONS1) {
        m_u16SelectedButton = BIT1;
    } else if (i_iButton == BUTTONS2) {
        m_u16SelectedButton = BIT4;
    } else {
        m_u16SelectedButton = 0;
    }

    ConfigureButton();

}

bool Button::Pressed() {
    int l_result = P1->IN & m_u16SelectedButton;
    return l_result == 0;
}

void Button::ConfigureButton()
{
    // Configurar resistencia pullup y puerto como entrada
    P1->DIR &= ~m_u16SelectedButton;
    P1->REN |= m_u16SelectedButton;
    P1->OUT |= m_u16SelectedButton;

}

