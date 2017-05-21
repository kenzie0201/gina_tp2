#include "uart.h"
#include "ADC.h"

void initADC(void)
{

    SysCtlClockSet(SYSCTL_SYSDIV_8 | SYSCTL_USE_OSC | SYSCTL_OSC_MAIN |
                   SYSCTL_XTAL_16MHZ);




//    UARTprintf("SSI ->\n");
//    UARTprintf("  Mode: SPI\n");
//    UARTprintf("  Data: 8-bit\n\n");


    SysCtlPeripheralEnable(SYSCTL_PERIPH_SSI0);


    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    SysCtlDelay(3);

    GPIOPinConfigure(GPIO_PA2_SSI0CLK);
    GPIOPinConfigure(GPIO_PA3_SSI0FSS);
    GPIOPinConfigure(GPIO_PA4_SSI0RX);
    GPIOPinConfigure(GPIO_PA5_SSI0TX);

    GPIOPinTypeSSI(GPIO_PORTA_BASE, GPIO_PIN_5 | GPIO_PIN_4 | GPIO_PIN_3 |
                   GPIO_PIN_2);

    // GPIOPinTypeGPIOOutput(GPIO_PORTA_BASE, GPIO_PIN_3); // make it so i can modify the pin...
    // GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_3, 0); // set pin to low...

    SSIConfigSetExpClk(SSI0_BASE, SysCtlClockGet(), SSI_FRF_MOTO_MODE_3,
                       SSI_MODE_MASTER, 1000000, 8);

    SSIEnable(SSI0_BASE);




//    GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_2|GPIO_PIN_3, 2);
    // set the spi to read register mode
    WriteADC(0x20);
    WriteADC(0xA5);
    WriteADC(0x10);
    WriteADC(0x44);
    SysCtlDelay(300000);



}
void WriteADC(char data){

    SSIDataPut(SSI0_BASE, data);
    // Wait until SSI0 is done transferring all the data in the transmit FIFO.
    while(SSIBusy(SSI0_BASE))
    {
    }

}
void ReadADC(uint32_t* input){
    // Wait until SSI0 is done transferring all the data in the transmit FIFO.
    while(SSIBusy(SSI0_BASE))
    {
    }
    SSIDataPut(SSI0_BASE, 0x00);
    SSIDataGetNonBlocking(SSI0_BASE, &input[0]);
    while(SSIBusy(SSI0_BASE))
    {
    }
    SSIDataPut(SSI0_BASE, 0x00);
    SSIDataGetNonBlocking(SSI0_BASE, &input[1]);
}
float convertADC2range (uint32_t* ADCval, int mode) {
    float convertADCVal;
    convertADCVal = (float)((ADCval[3]*2.5776)/65535);
    convertADCVal = convertADCVal-1.25;
    switch(mode){
    case CURRENT_10:
        convertADCVal = convertADCVal/0.125;
        break;
    case CURRENT_200:
        convertADCVal = convertADCVal/0.00625;
        break;
    case VOLTAGE_1:
        convertADCVal = convertADCVal/1.25;
        break;
    case VOLTAGE_5:
        convertADCVal = convertADCVal*4;
        break;
    case VOLTAGE_12:
        convertADCVal = convertADCVal*48/5;
        break;
    case RESISTANCE_1K:
        convertADCVal = (convertADCVal+1.25)*1000/2.5;
        break;
    case RESISTANCE_1M:
        convertADCVal = (convertADCVal+1.25)*100/2.5;
        break;
    case LOGIC:
        convertADCVal = convertADCVal+1.25;

    }
    return convertADCVal;

}
