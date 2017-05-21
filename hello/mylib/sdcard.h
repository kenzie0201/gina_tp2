#ifndef LIB_SDCARD_H_
#define LIB_SDCARD_H_

#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_memmap.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/ssi.h"
#include "driverlib/sysctl.h"
#include "driverlib/uart.h"
#include "utils/uartstdio.h"

void sdcard_init(void);
void sdcard_go_idle(void);

//          CMD     Bit Pattern
#define     CMD0    000000 // GO_IDLE_STATE

#define DUMMY_CHAR  0xFA

#endif /*LIB_SDCARD_H_*/
