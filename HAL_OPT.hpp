/*
 * HAL_OPT.hpp
 *
 *  Created on: Apr 19, 2018
 *      Author: jorge
 *
 */

#ifndef HAL_OPT_HPP_
#define HAL_OPT_HPP_

/*CONSTANTS*/
#define OPT3001_SLAVE_ADDRESS 0x44

#define OPT_INTERRUPT_PIN 11
#define RESULT_REG 0x00
#define CONFIG_REG 0x01
#define LOWLIMIT_REG 0x02
#define HIGHLIMIT_REG 0x03
#define MANUFACTUREID_REG 0x7E
#define DEVICEID_REG 0x7F

#define DEFAULT_CONFIG 0xCC10 // 800ms
#define DEFAULT_CONFIG_100 0xC410 // 100ms

/* CONFIG REGISTER BITS: RN3 RN2 RN1 RN0 CT M1 M0 OVF CRF FH FL L Pol ME FC1 FC0
RN3 to RN0 = Range select:
1100 by default, enables auto-range
CT = Conversion time bit
0 = 100ms conversion time
1 = 800ms conversion time (default)
M1 to M0 = Mode bits
00 = Shutdown mode
01 = Single shot mode
10 = Continuous conversion (default)
11 = Continuous conversion
OVF (Bit 8) – Overflow flag. When set the conversion result is overflown.
CRF (Bit 7) – Conversion ready flag. Sets at end of conversion. Clears by read or write of the Configuration register.
FH (Bit 6) – Flag high bit. Read only. Sets when result is higher that TH register. Clears when Config register is
read or when Latch bit is ‘0’ and the result goes bellow TH register.
FL (Bit 5) – Flag low bit. Read only. Sets when result is lower that TL register. Clears when Config register is read
or when Latch bit is ‘0’ and the result goes above TL register.
L (Bit 4) – Latch bit. Read/write bit. Default ‘1’, Controls Latch/transparent functionality of FH and FL bits. When
L = 1 the Alert pin works in window comparator mode with Latched functionality When L = 0 the Alert pin
works in transparent mode and the two limit registers provide the hysteresis.
Pol (Bit 3) – Polarity. Read/write bit. Default ‘0’, Controls the active state of the Alert pin. Pol = 0 means Alert
active low.
ME (Bit 2) – Exponent mask. In fixed range modes masks the exponent bits in the result register to “0000”.
FC1 to FC0 - Fault count bits. Read/write bits. Default “00” - the first fault will trigger the alert pin.
*/

void OPT_init(void);
unsigned long int OPT_getLux(void);
unsigned int OPT_readManufacturerId(void);
unsigned int OPT_readDeviceId(void);
unsigned int OPT_readConfigReg(void);
unsigned int OPT_readLowLimitReg(void);
unsigned int OPT_readHighLimitReg(void);

#endif /* HAL_OPT_HPP_ */
