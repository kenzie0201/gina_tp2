#ifndef LIB_SWITCHGAIN_H_
#define LIB_SWITCHGAIN_H_

#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "inc/hw_gpio.h"
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
#include "display.h"




void initMux(void);
void SetMuxDCAC(int mode);
void SetGain(int mode);
void SetInputRelay(int mode);
void SetADCSwitch(int mode);




// voltage range mode
// mode 1: 1V
// mode 2: 5V
// mode 3: 12V


#endif /* LIB_SWITCHGAIN_H_ */
