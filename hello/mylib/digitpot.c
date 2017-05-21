
#include "digitpot.h"

void initPot(void)
{

    //SysCtlClockSet(SYSCTL_SYSDIV_8 | SYSCTL_USE_OSC | SYSCTL_OSC_MAIN |
    //               SYSCTL_XTAL_16MHZ);

    SysCtlPeripheralEnable(SYSCTL_PERIPH_SSI2);


    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
    SysCtlDelay(3);

    GPIOPinConfigure(GPIO_PB4_SSI2CLK);
    GPIOPinConfigure(GPIO_PB5_SSI2FSS);
    GPIOPinConfigure(GPIO_PB6_SSI2RX);
    GPIOPinConfigure(GPIO_PB7_SSI2TX);

    GPIOPinTypeSSI(GPIO_PORTB_BASE, GPIO_PIN_7 | GPIO_PIN_6 | GPIO_PIN_5 |
                   GPIO_PIN_4);

    // GPIOPinTypeGPIOOutput(GPIO_PORTA_BASE, GPIO_PIN_3); // make it so i can modify the pin...
    // GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_3, 0); // set pin to low...

    SSIConfigSetExpClk(SSI2_BASE, 9000000, SSI_FRF_MOTO_MODE_3,
                       SSI_MODE_MASTER, 1000000, 16);



    SSIEnable(SSI2_BASE);


    // set the spi to read register mode
    // 0b 0000 00nn nnnn nnnn
    // 0b 0000 0000 1000 0000


    SysCtlDelay(300000);

}
void WritePot(int data){

    SSIDataPut(SSI2_BASE, data);
    // Wait until SSI0 is done transferring all the data in the transmit FIFO.
    while(SSIBusy(SSI2_BASE))
    {
    }

}
void ReadPot(uint32_t* input){
    // Wait until SSI0 is done transferring all the data in the transmit FIFO.
    while(SSIBusy(SSI2_BASE))
    {
    }
    SSIDataPut(SSI2_BASE, 0x00);
    SSIDataGetNonBlocking(SSI2_BASE, &input[0]);
    while(SSIBusy(SSI2_BASE))
    {
    }
    SSIDataPut(SSI2_BASE, 0x00);
    SSIDataGetNonBlocking(SSI2_BASE, &input[1]);


}
void SetPot(int mode){
    switch(mode){
    case CURRENT_10:
        WritePot(3); // pot set to 202 ohms
        break;
    case CURRENT_200:
        WritePot(124); // pot set to 5k ohms
        break;
    case VOLTAGE_1:
        WritePot(128); // pot set to 5.16k ohms
        break;
    case VOLTAGE_5:
        WritePot(23); // pot set to 1k ohms or write 26 to set pot to 1k
        break;
    case VOLTAGE_12:
        WritePot(9); // pot set to 431 ohms
        break;
    case RESISTANCE_1K:
        WritePot(254);   // pot set to 820 ohms
        break;
    case RESISTANCE_1M:
        WritePot(0);  // pot set to 8.2 ohms
        break;

    }


}
