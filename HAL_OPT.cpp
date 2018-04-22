/*
 * HAL_OPT.cpp
 *
 *  Created on: Apr 19, 2018
 *      Author: jorge
 */

#include <driverlib.h>
#include "HAL_I2C.hpp"
#include "HAL_OPT.hpp"

void OPT_init()
{
    /* Specify slave address for OPT3001 */
    I2C_setslave(OPT3001_SLAVE_ADDRESS);

    /* Set Default configuration for OPT3001*/
    I2C_write16(CONFIG_REG, DEFAULT_CONFIG_100);
}

unsigned int OPT_readManufacturerId()
{
    /* Specify slave address for OPT3001 */
    I2C_setslave(OPT3001_SLAVE_ADDRESS);

    return I2C_read16(MANUFACTUREID_REG);
}
unsigned int OPT_readDeviceId()
{
    /* Specify slave address for OPT3001 */
    I2C_setslave(OPT3001_SLAVE_ADDRESS);

    return I2C_read16(DEVICEID_REG);
}
unsigned int OPT_readConfigReg()
{
    /* Specify slave address for OPT3001 */
    I2C_setslave(OPT3001_SLAVE_ADDRESS);

    return I2C_read16(CONFIG_REG);
}
unsigned int OPT_readLowLimitReg()
{
    /* Specify slave address for OPT3001 */
    I2C_setslave(OPT3001_SLAVE_ADDRESS);

    return I2C_read16(LOWLIMIT_REG);
}
unsigned int OPT_readHighLimitReg()
{
    /* Specify slave address for OPT3001 */
    I2C_setslave(OPT3001_SLAVE_ADDRESS);

    return I2C_read16(HIGHLIMIT_REG);
}
unsigned long int OPT_getLux()
{
    /* Specify slave address for OPT3001 */
    I2C_setslave(OPT3001_SLAVE_ADDRESS);

    uint16_t exponent = 0;
    uint32_t result = 0;
    int16_t raw;
    raw = I2C_read16(RESULT_REG);
    /*Convert to LUX*/
    //extract result & exponent data from raw readings
    result = raw&0x0FFF;
    exponent = (raw>>12)&0x000F;
    //convert raw readings to LUX
    switch(exponent){
    case 0: //*0.015625
        result = result>>6;
        break;
    case 1: //*0.03125
        result = result>>5;
        break;
    case 2: //*0.0625
        result = result>>4;
        break;
    case 3: //*0.125
        result = result>>3;
        break;
    case 4: //*0.25
        result = result>>2;
        break;
    case 5: //*0.5
        result = result>>1;
        break;
    case 6:
        result = result;
        break;
    case 7: //*2
        result = result<<1;
        break;
    case 8: //*4
        result = result<<2;
        break;
    case 9: //*8
        result = result<<3;
        break;
    case 10: //*16
        result = result<<4;
        break;
    case 11: //*32
        result = result<<5;
        break;
    }
    return result;
}



