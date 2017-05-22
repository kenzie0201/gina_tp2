#include "led.h"




void initLED(void){
    // set up LED1 PB3
    // set up LED2 PB6 -> PE0 instead unless desolder the resistor on the tiva board

    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);    // enable port B
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);    // enable port E

    GPIOPinTypeGPIOOutput(GPIO_PORTE_BASE, GPIO_PIN_0); // enable PE0 output
    GPIOPinTypeGPIOOutput(GPIO_PORTB_BASE, GPIO_PIN_3); // enable PE0 output

    GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_0, 0);
    GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_3, 0 << 3);
}




