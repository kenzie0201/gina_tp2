#ifndef LIB_MYPWM_H_
#define LIB_MYPWM_H_


#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_memmap.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/pwm.h"
#include "driverlib/sysctl.h"
#include "driverlib/uart.h"
#include "utils/uartstdio.h"

void initPWM(void);
void setPWM(int mode, int state);



#define LOW         0
#define HIGH        1
#define OFF         2
#define LEVEL_1     1
#define LEVEL_2     2
#define LEVEL_3     3
#define LEVEL_4     4
#define LEVEL_5     5
#define BUZZER      0
#define LED         1


#endif /* LIB_MYPWM_H_ */
