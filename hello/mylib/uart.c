#include "uart.h"
int test =1;
void UARTIntHandler(void);

void UARTSendMeasurement(uint8_t pb_mode, uint8_t measure_mode, char * readVal){
    char pb[20] = "\0";
    char measure[1] = "\0";

    itoa ((int)pb_mode,pb,10);
    strcat(pb,",");
    itoa ((int)measure_mode,measure,10);
    strcat(pb,measure);
    strcat(pb,",");
    UARTSend(pb);
//    UARTCharPut(UART0_BASE, ',');

//    UARTSend(measure);
//    UARTCharPut(UART0_BASE, ',');
    UARTSend(readVal);
    UARTSend("\n");
}
//*****************************************************************************
//
// Send a string to the UART.  This function sends a string of characters to a
// particular UART module.
//
//*****************************************************************************
void
UARTSend(const char *pui8Buffer)
{
    uint32_t ui32Count;
    ui32Count = strlen(pui8Buffer);
    //
    // Loop while there are more characters to send.
    //
    while(ui32Count--)
    {
        //
        // Write the next character to the UART.
        //
        UARTCharPutNonBlocking(UART0_BASE, *pui8Buffer++);
    }
}
//*****************************************************************************
//
// This function sets up UART0 to be used for a console to display information
// as the example is running.
//
//*****************************************************************************
void
InitConsole(void)
{
    //
    // Enable lazy stacking for interrupt handlers.  This allows floating-point
    // instructions to be used within interrupt handlers, but at the expense of
    // extra stack usage.
    //
    ROM_FPUEnable();
    ROM_FPULazyStackingEnable();

//-------------------------SETUP UART0----------------------------------------//
    //
    // Enable GPIO port A which is used for UART0 pins.
    // TODO: change this to whichever GPIO port you are using.
    //
 if(test==1){
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);

    //
    // Configure the pin muxing for UART0 functions on port A0 and A1.
    // This step is not necessary if your part does not support pin muxing.
    // TODO: change this to select the port/pin you are using.
    //
    GPIOPinConfigure(GPIO_PA0_U0RX);
    GPIOPinConfigure(GPIO_PA1_U0TX);

    //
    // Enable UART0 so that we can configure the clock.
    //
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);

    //
    // Use the internal 16MHz oscillator as the UART clock source.
    //
    UARTClockSourceSet(UART0_BASE, UART_CLOCK_PIOSC);

    //
    // Select the alternate (UART) function for these pins.
    // TODO: change this to select the port/pin you are using.
    //
    GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);





    // Interrupt setup
    GPIOIntDisable(GPIO_PORTA_BASE,  GPIO_PIN_0);        // Disable interrupt for PF4 (in case it was enabled)
    GPIOIntClear(GPIO_PORTA_BASE, GPIO_PIN_0);      // Clear pending interrupts for PF4
    GPIOIntRegister(GPIO_PORTA_BASE, UARTIntHandler);     // Register our handler function for port F
    GPIOIntTypeSet(GPIO_PORTA_BASE, GPIO_PIN_0,
                   GPIO_RISING_EDGE);             // Configure PF4 for falling edge trigger
    GPIOIntEnable(GPIO_PORTA_BASE, GPIO_PIN_0);     // Enable interrupt for PF4

    //
    // Initialize the UART for console I/O.
    //
    UARTStdioConfig(0, 115200, 16000000);

 }
//------------------SETUP UART1-------------------------------------//
 else{
 //
 // Enable the GPIOB peripheral
 //
 SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
 //
 // Wait for the GPIOB module to be ready.
 //
 while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOB))
 {
 }
 //
 // Enable UART1 functionality on GPIO Port B pins 0 and 1.
 //
 GPIOPinConfigure(GPIO_PB0_U1RX);
 GPIOPinConfigure(GPIO_PB1_U1TX);


 //
 // Enable UART0 so that we can configure the clock.
 //
 SysCtlPeripheralEnable(SYSCTL_PERIPH_UART1);

 //
 // Use the internal 16MHz oscillator as the UART clock source.
 //
 UARTClockSourceSet(UART1_BASE, UART_CLOCK_PIOSC);
 //
 // Configure GPIO Port B pins 0 and 1 to be used as UART1.
 //

 GPIOPinTypeUART(GPIO_PORTB_BASE, GPIO_PIN_0 | GPIO_PIN_1);

 //
 // Initialize the UART for console I/O.
 //
 UARTStdioConfig(1, 9600, 16000000);
 }
}

//*****************************************************************************
//
// The UART interrupt handler.
//
//*****************************************************************************
void
UARTIntHandler(void)
{
    unsigned char rxChar;

        // Loop while there are characters in the receive FIFO.
            while(UARTCharsAvail(UART0_BASE))
            {
                rxChar = UARTCharGetNonBlocking(UART0_BASE);

                // Read the next character from the UART and write it back to the UART.
                UARTCharPutNonBlocking(UART0_BASE,rxChar);
                UARTprintf("%c",rxChar );

                //
                // Blink the LED to show a character transfer is occurring.
                //
                GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2, GPIO_PIN_2);

                //
                // Delay for 1 millisecond.  Each SysCtlDelay is about 3 clocks.
                //
                SysCtlDelay(SysCtlClockGet() / (1000 * 3));

                //
                // Turn off the LED
                //
                GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2, 0);

            }

            GPIOIntClear(GPIO_PORTA_BASE, GPIO_PIN_0);  // Clear interrupt flag


}
