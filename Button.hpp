/*
 * Button.hpp
 *
 *  Created on: Apr 12, 2018
 *      Author: daniel
 */

#ifndef BUTTON_HPP_
#define BUTTON_HPP_

#include "msp.h"
#define BUTTONS1 0
#define BUTTONS2 1


class Button
{
public:
    Button();
    virtual ~Button();
    Button(int i_iButton);

    bool Pressed();

protected:
    uint16_t m_u16SelectedButton;
    void ConfigureButton();
};

#endif /* BUTTON_HPP_ */
