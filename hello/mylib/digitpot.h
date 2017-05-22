#ifndef LIB_DIGITPOT_H_
#define LIB_DIGITPOT_H_

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

void initPot(void);
void WritePot(int data);
void ReadPot(uint32_t* input);
void SetPot(int mode);

#define CURRENT_10         0
#define CURRENT_200        1
#define VOLTAGE_1          2
#define VOLTAGE_5          3
#define VOLTAGE_12         4
#define RESISTANCE_1K      5
#define RESISTANCE_1M      6
#define LOGIC              7
#define SETFREQ            8
#define SETPERIOD          9
#define CONT               10
#define SETBRIGHT          11

#endif /* LIB_DIGITPOT_H_ */
