#ifndef LIB_MYSDCARD_H_
#define LIB_MYSDCARD_H_

#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include "inc/hw_memmap.h"
#include "inc/hw_gpio.h"
#include "inc/hw_types.h"
#include "driverlib/fpu.h"
#include "driverlib/gpio.h"
#include "driverlib/interrupt.h"
#include "driverlib/pin_map.h"
#include "driverlib/rom.h"
#include "driverlib/sysctl.h"
#include "driverlib/systick.h"
#include "driverlib/uart.h"
#include "utils/cmdline.h"
#include "utils/uartstdio.h"
#include "ff.h"
#include "diskio.h"
#include "mylib/display.h"

void initSDcard(void);
void openFile(void);
void writeSD(char *data);
void closeFile(void);

#endif /* LIB_MYSDCARD_H_ */
