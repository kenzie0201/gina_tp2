#include "sdcard.h"

void sdcard_init(void) {
//    int i = 0;
//
//    SysCtlPeripheralEnable(SYSCTL_PERIPH_SSI1);
//
//    // GPIO PINS NEED TO BE CHECKED
//    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
//
//    // INIT CORRECT PINS AS PER ABOVE
//    GPIOPinConfigure(GPIO_PF2_SSI1CLK);
//    GPIOPinConfigure(GPIO_PF0_SSI1RX);
//    GPIOPinConfigure(GPIO_PF1_SSI1TX);//
//    //Return to standard SPI operation - Reconfigure the pin & set it to SSI mode
//             GPIOPinConfigure(GPIO_PF3_SSI1FSS);
//             GPIOPinTypeSSI(GPIO_PORTF_BASE, GPIO_PIN_3);
///*
//    // For initialisation the CS Pin needs to stay high
//    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_3);
//    GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3, 0x2); // Set Pin 2 High
//*/
//    // INIT CORRECT PINS AS PER ABOVE
//    GPIOPinTypeSSI(GPIO_PORTF_BASE, GPIO_PIN_2 | GPIO_PIN_1
//            | GPIO_PIN_0);
//
//
//    SSIConfigSetExpClk(SSI1_BASE, SysCtlClockGet(), SSI_FRF_MOTO_MODE_0,
//                       SSI_MODE_MASTER, 400000, 16);
//
//
//    SSIEnable(SSI1_BASE);
//    SysCtlDelay(300000);

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

    // SD Card requires at least 74 clock pulses being sent before it is ready
    // 10 bytes = 80 pulses


//    //Return to standard SPI operation - Reconfigure the pin & set it to SSI mode
//    GPIOPinConfigure(GPIO_PF3_SSI1FSS);
//    GPIOPinTypeSSI(GPIO_PORTF_BASE, GPIO_PIN_1);
//
//
//    /***************
//     * Debug the output
//     */
//
//    // SD Card requires at least 74 clock pulses being sent before it is ready
//    // 10 bytes = 80 pulses
//    for ( i = 0; i <= 9; i++) {
//        // SPI_SEND(DUMMY_CHAR)
//        SSIDataPut(SSI1_BASE, DUMMY_CHAR);
//        while(SSIBusy(SSI1_BASE)) {
//        }
//    }
}


// Command Token Format - 6 Bytes
// Start Bit [47] = 0 | Transmission Bit [46] = 1 | Command Bit Pattern [45:40] |
        //Argument [39:8] | CRC7 [7:1] | End Bit [0] = 1

void sdcard_go_idle(void) {
    int i;
    for ( i = 0; i <= 9; i++) {
           // SPI_SEND(DUMMY_CHAR)
           SSIDataPut(SSI0_BASE, DUMMY_CHAR);
           while(SSIBusy(SSI0_BASE)) {
           }
       }
}


