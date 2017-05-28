#include "switchgain.h"


void initMux(void){
    // unlock PD7
    HWREG(GPIO_PORTD_BASE+GPIO_O_LOCK) = GPIO_LOCK_KEY;
    HWREG(GPIO_PORTD_BASE+GPIO_O_CR) |= GPIO_PIN_7;

    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);    // enable port B
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC);    // enable port C
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);    // enable port D
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);    // enable port E
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);    // enable port F

    GPIOPinTypeGPIOOutput(GPIO_PORTB_BASE, GPIO_PIN_5|GPIO_PIN_4); // enable PB4 PB5 output
    GPIOPinTypeGPIOOutput(GPIO_PORTC_BASE, GPIO_PIN_7|GPIO_PIN_6); // enable PC6 PC7 output
    GPIOPinTypeGPIOOutput(GPIO_PORTD_BASE, GPIO_PIN_7|GPIO_PIN_6); // enable PD6 PD7 output
    GPIOPinTypeGPIOOutput(GPIO_PORTE_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3); // enable PE1 PE2 PE3 output
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_4); // enable PF4output


//    GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_1|GPIO_PIN_2, 0);
//    GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_2|GPIO_PIN_3, 2);



}
// this will be used for AD/DC PORTC PC6 PC7 PD6
void SetMuxDCAC(int mode){
    switch(mode){
    case DC_CURRENT:
        GPIOPinWrite(GPIO_PORTC_BASE,GPIO_PIN_6, 64);
        GPIOPinWrite(GPIO_PORTD_BASE,GPIO_PIN_6, 0);
//        UARTprintf("setting DC CURRENT\n");
        break;
    case AC_CURRENT:
        GPIOPinWrite(GPIO_PORTC_BASE,GPIO_PIN_6, 0);
        GPIOPinWrite(GPIO_PORTD_BASE,GPIO_PIN_6, 0);
//        UARTprintf("setting AC CURRENT\n");
        break;
    case DC_VOLTAGE:
        GPIOPinWrite(GPIO_PORTC_BASE,GPIO_PIN_6, 64); // 0
        GPIOPinWrite(GPIO_PORTD_BASE,GPIO_PIN_6, 64); // 1
//        UARTprintf("setting DC VOLTAGE\n");
        break;
    case AC_VOLTAGE:
        GPIOPinWrite(GPIO_PORTC_BASE,GPIO_PIN_6, 0);
        GPIOPinWrite(GPIO_PORTD_BASE,GPIO_PIN_6, 64);
//        UARTprintf("setting AC VOLTAGE\n");
        break;
    }
}
// this will be used for AD/DC PORTC PC6 PC7 PD6
void SetInputRelay(int mode){
    if ((mode == AC_VOLTAGE)||(mode == DC_VOLTAGE)){
        GPIOPinWrite(GPIO_PORTE_BASE,GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, 2);
    }else if ((mode == RESISTANCE)||(mode == CONTINUITY)){
        GPIOPinWrite(GPIO_PORTE_BASE,GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, 8);
    }else if (mode == LOGIC){
        GPIOPinWrite(GPIO_PORTE_BASE,GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, 4);
    }
}
// this will be used for AD/DC PORTC PC6 PC7 PD6
void SetGain(int mode){
    switch(mode){
    case CURRENT_10:
        GPIOPinWrite(GPIO_PORTB_BASE,GPIO_PIN_5|GPIO_PIN_4, 32);
//        UARTprintf("setting CURRENT_10\n");
        break;
    case CURRENT_200:
        GPIOPinWrite(GPIO_PORTB_BASE,GPIO_PIN_5|GPIO_PIN_4, 48);
//        UARTprintf("setting CURRENT_200\n");
        break;
    case VOLTAGE_1:
        GPIOPinWrite(GPIO_PORTB_BASE,GPIO_PIN_5|GPIO_PIN_4, 0);
 //       UARTprintf("setting VOLTAGE_1\n");
        break;
    case VOLTAGE_5:
        GPIOPinWrite(GPIO_PORTB_BASE,GPIO_PIN_5|GPIO_PIN_4, 16);
 //       UARTprintf("setting VOLTAGE_5\n");
        break;
    case VOLTAGE_12:
        GPIOPinWrite(GPIO_PORTB_BASE,GPIO_PIN_5|GPIO_PIN_4, 32);
 //       UARTprintf("setting VOLTAGE_12\n");
        break;
    case RESISTANCE_1K:
        GPIOPinWrite(GPIO_PORTC_BASE,GPIO_PIN_7, 0);
 //       UARTprintf("setting RESISTANCE_1K\n");
        break;
    case RESISTANCE_1M:
        GPIOPinWrite(GPIO_PORTC_BASE,GPIO_PIN_7, 128);
 //       UARTprintf("setting RESISTANCE_1M\n");
        break;
    }
}
// this will be used for AD/DC PORTC PC6 PC7 PD6
void SetADCSwitch(int mode){
    if ((mode == DC_CURRENT)||(mode == DC_VOLTAGE)){
        GPIOPinWrite(GPIO_PORTD_BASE,GPIO_PIN_7, 0);
        GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_4, 0);
    }else if ((mode == AC_CURRENT)||(mode == AC_VOLTAGE)){
        GPIOPinWrite(GPIO_PORTD_BASE,GPIO_PIN_7, 128);
        GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_4, 0);
    }else if ((mode == RESISTANCE)||(mode == CONTINUITY)){
        GPIOPinWrite(GPIO_PORTD_BASE,GPIO_PIN_7, 0);
        GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_4, 16);
    }else if (mode == LOGIC){
        GPIOPinWrite(GPIO_PORTD_BASE,GPIO_PIN_7, 128);
        GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_4, 16);
    }
}
