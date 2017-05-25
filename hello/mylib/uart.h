#ifndef LIB_UART_H_
#define LIB_UART_H_

#include <stdint.h>
#include <stdbool.h>
#include <string.h>
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
#include "inc/hw_ints.h"
#include "driverlib/interrupt.h"
#include "display.h"


void InitConsole(void);
void UARTSend(const char *pui8Buffer);
void UARTSendMeasurement(uint8_t pb_mode, uint8_t measure_mode, char * readVal);

#endif /* LIB_UART_H_ */
