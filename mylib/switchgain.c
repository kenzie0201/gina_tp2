#include "switchgain.h"


void initMux(void){

    // set up pins for digital pot
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);    // enable port F
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2); // enable PF2 PF3 output


    GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_1|GPIO_PIN_2, 0);
//    GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_2|GPIO_PIN_3, 2);



}
// this will be used for mux
void SetMuxDCAC(int mode){
    switch(mode){
    case DC_CURRENT:
        GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, 6);
        break;
    case AC_CURRENT:
        GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, 4);
        break;
    case DC_VOLTAGE:
        GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, 2);
        break;
    case AC_VOLTAGE:
        GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, 0);
        break;
//    case VOLTAGE_12:
//        GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, 2);
//        break;
    }
}

void RangeSwitchV(int ADCval){



}
int RangeSwitchA(int ADCval){

    return(0);
}
