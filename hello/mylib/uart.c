#include "uart.h"


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
    UARTSend('\n');
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
        UARTCharPutNonBlocking(UART0_BASE, *pui8Buffer);
        UARTCharPutNonBlocking(UART1_BASE, *pui8Buffer);
        *pui8Buffer++;
    }
}
//*****************************************************************************
//
// This function sets up UART0 to be used for a console to display information
// as the example is running.
//
//*****************************************************************************
void
initUART0(void)
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
    //
    // Enable the UART interrupt.
    //
    IntEnable(INT_UART0);
    UARTIntEnable(UART0_BASE, UART_INT_RX | UART_INT_RT);

//    // Interrupt setup
//    GPIOIntDisable(GPIO_PORTA_BASE,  GPIO_PIN_0);        // Disable interrupt for PF4 (in case it was enabled)
//    GPIOIntClear(GPIO_PORTA_BASE, GPIO_PIN_0);      // Clear pending interrupts for PF4
//    GPIOIntRegister(GPIO_PORTA_BASE, UARTIntHandler);     // Register our handler function for port F
//    GPIOIntTypeSet(GPIO_PORTA_BASE, GPIO_PIN_0,
//                   GPIO_RISING_EDGE);             // Configure PF4 for falling edge trigger
//    GPIOIntEnable(GPIO_PORTA_BASE, GPIO_PIN_0);     // Enable interrupt for PF4

    //
    // Initialize the UART for console I/O.
    //
    UARTStdioConfig(0, 115200, 16000000);

}
//*****************************************************************************
//
// This function sets up UART0 to be used for a console to display information
// as the example is running.
//
//*****************************************************************************
void
initUART1(void)
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

    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);

    //
    // Configure the pin muxing for UART0 functions on port A0 and A1.
    // This step is not necessary if your part does not support pin muxing.
    // TODO: change this to select the port/pin you are using.
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
    // Select the alternate (UART) function for these pins.
    // TODO: change this to select the port/pin you are using.
    //
    GPIOPinTypeUART(GPIO_PORTB_BASE, GPIO_PIN_0 | GPIO_PIN_1);
    //
    // Enable the UART interrupt.
    //
    IntEnable(INT_UART1);
    UARTIntEnable(UART1_BASE, UART_INT_RX | UART_INT_RT);

//    // Interrupt setup
//    GPIOIntDisable(GPIO_PORTA_BASE,  GPIO_PIN_0);        // Disable interrupt for PF4 (in case it was enabled)
//    GPIOIntClear(GPIO_PORTA_BASE, GPIO_PIN_0);      // Clear pending interrupts for PF4
//    GPIOIntRegister(GPIO_PORTA_BASE, UARTIntHandler);     // Register our handler function for port F
//    GPIOIntTypeSet(GPIO_PORTA_BASE, GPIO_PIN_0,
//                   GPIO_RISING_EDGE);             // Configure PF4 for falling edge trigger
//    GPIOIntEnable(GPIO_PORTA_BASE, GPIO_PIN_0);     // Enable interrupt for PF4

    //
    // Initialize the UART for console I/O.
    //
    UARTStdioConfig(1, 9600, 16000000);

}



