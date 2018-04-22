/*
 * HAL_I2C.hpp
 *
 *  Created on: Apr 19, 2018
 *      Author: jorge
 *      Prototipos de capa de abstraccion de hardware para I2C
 */

#ifndef HAL_I2C_HPP_
#define HAL_I2C_HPP_

void Init_I2C_GPIO(void);
void I2C_init(void);
int I2C_read16(unsigned char);
void I2C_write16(unsigned char pointer, unsigned int writeByte);
void I2C_setslave(unsigned int slaveAdr);

#endif /* HAL_I2C_HPP_ */
