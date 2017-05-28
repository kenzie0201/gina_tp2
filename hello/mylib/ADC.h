#ifndef LIB_ADC_H_
#define LIB_ADC_H_

#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/debug.h"
#include "driverlib/fpu.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/rom.h"
#include "driverlib/sysctl.h"
#include "driverlib/uart.h"
#include "utils/uartstdio.h"
#include "driverlib/ssi.h"
#include "uart.h"
#include "digitpot.h"

void initADC(void);
void WriteADC(char data);
void ReadADC(uint32_t* input);
float convertADC2range (uint32_t* ADCval, int mode);
float convertADC2rangeAC (uint32_t* ADCval, int mode);

#endif /* LIB_ADC_H_ */
