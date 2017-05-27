//*****************************************************************************
//
// hello.c - Simple hello world example.
//
// Copyright (c) 2012-2017 Texas Instruments Incorporated.  All rights reserved.
// Software License Agreement
// 
// Texas Instruments (TI) is supplying this software for use solely and
// exclusively on TI's microcontroller products. The software is owned by
// TI and/or its suppliers, and is protected under applicable copyright
// laws. You may not combine this software with "viral" open-source
// software in order to form a larger program.
// 
// THIS SOFTWARE IS PROVIDED "AS IS" AND WITH ALL FAULTS.
// NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT
// NOT LIMITED TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE. TI SHALL NOT, UNDER ANY
// CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL, OR CONSEQUENTIAL
// DAMAGES, FOR ANY REASON WHATSOEVER.
// 
// This is part of revision 2.1.4.178 of the EK-TM4C123GXL Firmware Package.
//
//*****************************************************************************

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include "string.h"
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
#include "driverlib/ssi.h"
#include "driverlib/interrupt.h"
#include "inc/hw_gpio.h"
#include "driverlib/timer.h"
//#include "utils/cmdline.h"
//#include "utils/uartstdio.h"
//#include "ff.h"
//#include "diskio.h"

#include "mylib/ADC.h"
#include "mylib/display.h"
#include "mylib/uart.h"
#include "mylib/switchgain.h"
//#include "mylib/mytimer.h"
#include "mylib/display.h"
#include "mylib/mypwm.h"
#include "mylib/led.h"
#include "mySDcard.h"


#define MIN_10   0
#define MIN_1    1
#define SEC_10   2
#define SEC_1    3
#define HALFSEC  4
#define ENTERKEY 5

void SW1_IntHandler(void);
void modeChange(void);
void Timer0IntHandler(void);
void initTimer(void);



float loggingFreq[] = {0.5, 1, 2, 5, 10, 60, 120, 300, 600};

uint8_t measure_mode, pb_mode;


uint8_t mode_level = 1;
uint8_t frequency_opt = 0;
uint8_t brightness_opt = 1;
char brightness_opt_str[5] = "\0";
uint8_t freq_flag = 0;
uint8_t cursor_pos = 0;
uint8_t duration_red_pressed = 0;
uint8_t duration_green_pressed = 0;
uint8_t logging_pressed = 0;
uint8_t set_duration[5] = {0,0,0,0,0};
uint8_t set_cursor_duration[]={5,6,8,9,11,15};

float loggingDuration=0;
char loggingDurationString[100] = "\0";
char int2str_duration[10] = "\0";
// for timer
uint32_t g_ui32Flags=0;
uint32_t ToggleLED2 = 0;
int numTick;
uint8_t loggingCounter = 0;
uint8_t counter =0;
uint8_t LED2Counter =0;


//*****************************************************************************
//
// Configure SSI0 in master Freescale (SPI) mode.  This example will send out
// 3 bytes of data, then wait for 3 bytes of data to come in.  This will all be
// done using the polling method.
//
//*****************************************************************************
int
main(void)
{
//---------------------------------------VARIABLES---------------------------------------//
    uint32_t readVal[3];

    float measuredADCVal;
    char displayADCVal[17]="\0";
    char tmp[17]="\0"; // not really using just for buffer
    int i,tmpSet;
//------------------------------------------SETUP----------------------------------------//
    SysCtlClockSet(SYSCTL_SYSDIV_8|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN);
//    SysCtlClockSet(SYSCTL_SYSDIV_8|SYSCTL_USE_PLL|SYSCTL_XTAL_10MHZ|SYSCTL_OSC_MAIN);
    initUART0();
    initUART1();
    initADC();
    initLCD();
    initMux();


    initPWM();
    // Enable the GPIO port that is used for the on-board LED.
    initTimer();
    initLED();

    initSDcard();
    writeSD();




//---------------------------- Enable processor interrupts-------------------------------//
    ROM_IntMasterEnable();

//---------------------------------PB & INTERRUPT SETUP----------------------------------//
    // PB setup
//    HWREG(GPIO_PORTA_BASE+GPIO_O_LOCK) = GPIO_LOCK_KEY;
//
//    HWREG(GPIO_PORTA_BASE+GPIO_O_CR) |= GPIO_PIN_7;
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);        // Enable port F
    GPIOPinTypeGPIOInput(GPIO_PORTA_BASE, GPIO_PIN_7);  // Init PF4 as input
    GPIOPadConfigSet(GPIO_PORTA_BASE, GPIO_PIN_7,
        GPIO_STRENGTH_4MA, GPIO_PIN_TYPE_STD_WPU);  // Enable weak pullup resistor for PF4

    // Interrupt setup
    GPIOIntDisable(GPIO_PORTA_BASE, GPIO_PIN_7);        // Disable interrupt for PF4 (in case it was enabled)
    GPIOIntClear(GPIO_PORTA_BASE, GPIO_PIN_7);      // Clear pending interrupts for PF4
    GPIOIntRegister(GPIO_PORTA_BASE, SW1_IntHandler);     // Register our handler function for port F
    GPIOIntTypeSet(GPIO_PORTA_BASE, GPIO_PIN_7,
        GPIO_FALLING_EDGE);             // Configure PF4 for falling edge trigger
    GPIOIntEnable(GPIO_PORTA_BASE, GPIO_PIN_7);     // Enable interrupt for PF4



    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);        // Enable port F
    GPIOPinTypeGPIOInput(GPIO_PORTA_BASE, GPIO_PIN_6);  // Init PF4 as input
    GPIOPadConfigSet(GPIO_PORTA_BASE, GPIO_PIN_6,
        GPIO_STRENGTH_4MA, GPIO_PIN_TYPE_STD_WPU);  // Enable weak pullup resistor for PF4

    // Interrupt setup
    GPIOIntDisable(GPIO_PORTA_BASE, GPIO_PIN_6);        // Disable interrupt for PF4 (in case it was enabled)
    GPIOIntClear(GPIO_PORTA_BASE, GPIO_PIN_6);      // Clear pending interrupts for PF4
    GPIOIntRegister(GPIO_PORTA_BASE, SW1_IntHandler);     // Register our handler function for port F
    GPIOIntTypeSet(GPIO_PORTA_BASE, GPIO_PIN_6,
        GPIO_FALLING_EDGE);             // Configure PF4 for falling edge trigger
    GPIOIntEnable(GPIO_PORTA_BASE, GPIO_PIN_6);     // Enable interrupt for PF4


//    // Enable the GPIO port that is used for the on-board LED.
//    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);
//    // Enable the GPIO pins for the LED (PF1 & PF2).
//    GPIOPinTypeGPIOOutput(GPIO_PORTE_BASE, GPIO_PIN_2);

//---------------------------------SETUP DISPLAY & MEASUREMENT MODE-----------------------//
    // set to display hellow world
    setCursorPositionLCD(0,5);

    printLCD("HELLO");
    setCursorPositionLCD(1,5);
    printLCD("WORLD");
    SysCtlDelay(30000);

    clearLCD();

    // initialise screen
    pb_mode = DURATION;
    setModeDisplay(pb_mode);
    brightness_opt = 3;
    setPWM(LED,brightness_opt);// initilise brightness
    setCursorPositionLCD(0,15);
    printSpecialChar(brightness_opt);
    modeChange();
    SetMuxDCAC(pb_mode);

//-------------------------------device power up LED-------------------------------------//
    GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_3, 1 << 3);



//----------------------------------------START-------------------------------------------//
   while(1){
//       setBlockCursorLCD();
//       setCursorPositionLCD(0,0);
//       homeLCD();
//       for (i = 0; i<16; i++){
//       setCursorPositionLCD(0,i);
       SysCtlDelay(10);

//       }
       if ((logging_pressed == 1 )&&(loggingCounter >= (loggingDuration)*4)){ // check if logging duration is over and RESET the counter and flag
           loggingCounter = 0;
           logging_pressed = 0;
       }

       if ((counter >= ((loggingFreq[frequency_opt]*2)))&& (ToggleLED2 ==1)){ // check if the frequency is over and RESET the counter and read the measurements

           ToggleLED2 = ToggleLED2^1;
           //GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2, g_ui32Flags << 2);
           GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_0, ToggleLED2);
       }
       if (counter >= ((loggingFreq[frequency_opt]*4))){ // check if the frequency is over and RESET the counter and read the measurements
           counter=0;
           freq_flag = 1;
           //
           // Use the flags to Toggle the LED for this timer
           //
           ToggleLED2 = ToggleLED2^1;
           //GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2, g_ui32Flags << 2);
           GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_0, ToggleLED2);
       }

 //          UARTprintf("freq_flag : %d \n",freq_flag);
            // send 0x38 to read the ADC
            WriteADC(0x38);
            memset(readVal,0,sizeof(readVal));
            ReadADC(readVal);
     //       UARTprintf("Read1'%x'\n ", readVal[0]);
     //       UARTprintf("Read2'%x'\n ", readVal[1]);
            readVal[3] = ((readVal[0]<<8)|readVal[1]);
//            UARTprintf("Read3'%d'\n ",readVal[3] );
            // convert the read value to ADC range [ 0 - 2.5V ]
            measuredADCVal = convertADC2range (readVal, measure_mode);

            if (freq_flag == 1){

                switch(measure_mode){

                case CURRENT_10:
                    if ((measuredADCVal < 9.9 )&& (measuredADCVal > -9.9 )){
                    }else {
                        measure_mode = CURRENT_200;
                    }
                    // if mode_level =2 -> start logging
                    break;
                case CURRENT_200:
                    if ((measuredADCVal < 9.9) &&( measuredADCVal > -9.9 )){
                        measure_mode = CURRENT_10;
                    }else if (measuredADCVal > 200){
                        // OL display
                    }
                    // if mode_level =2 -> start logging
                    break;
                case VOLTAGE_1:
                    if ((measuredADCVal < 0.9 )&& (measuredADCVal > -0.9 )){
                    }else {
                        measure_mode = VOLTAGE_5;
                    }
                    // if mode_level =2 -> start logging
                    break;
                case VOLTAGE_5:
                    if ((measuredADCVal < 5) &&( measuredADCVal > -5 )){
                        if((measuredADCVal < 0.9 )&&( measuredADCVal > -0.9)){
                            measure_mode = VOLTAGE_1;
                        }
                    }else {
                        measure_mode = VOLTAGE_12;
                    }
                    // if mode_level =2 -> start logging
                    break;
                case VOLTAGE_12:
                    if ((measuredADCVal < 0.9 )&&( measuredADCVal > -0.9 )){
                        measure_mode = VOLTAGE_1;
                    }else if ((measuredADCVal < 5) && (measuredADCVal > -5 )){
                        measure_mode =  VOLTAGE_5;
                    }else if (measuredADCVal > 11.9){
                        // display OL
                    }
                    // if mode_level =2 -> start logging
                    break;
                case RESISTANCE_1K:
                    if ((measuredADCVal < 999 )&& (measuredADCVal > -999 )){
                    }else {
                        measure_mode = RESISTANCE_1M;
                    }
                    if ((pb_mode == CONTINUITY) && measuredADCVal < 5){
                        setPWM(BUZZER,HIGH);
                    }
                    // if mode_level =2 -> start logging
                    break;
                case RESISTANCE_1M:
                    if ((measuredADCVal < 0.9) &&( measuredADCVal > -0.9 )){
                        measure_mode = RESISTANCE_1K;
                    }else if (measuredADCVal > 1000){ // 100k
                        // OL display
                    }
                    // if mode_level =2 -> start logging
                    break;
                case LOGIC:
                    if (measuredADCVal>1.25){
                        setPWM(BUZZER,HIGH);
                        strcpy(displayADCVal, " HIGH     ");

                    }else if (measuredADCVal>0.5){
                        setPWM(BUZZER,LOW);
                        strcpy(displayADCVal, "  LOW     ");

                    }else{
                        setPWM(BUZZER,OFF);
                        strcpy(displayADCVal, " FLOAT    ");

                    }
                    //           UARTprintf("%s \n",displayADCVal);
                    break;
                case SETBRIGHT:
                    if (mode_level == 2){
                        if(brightness_opt < 5) {
                            brightness_opt++;
                        }else{
                            brightness_opt = 1;
                        }
                        measuredADCVal = brightness_opt;
                        setPWM(LED,brightness_opt);
                        setCursorPositionLCD(0,15);
                        printSpecialChar(brightness_opt);
                        mode_level = 1;
                    }

                    break;

                case SETFREQ:

                    if ((mode_level == 2) && (frequency_opt < 9)) {
                        frequency_opt++;
                        counter=0;

                    }else if (frequency_opt >= 9){
                        frequency_opt = 0;
                    }
                    measuredADCVal = loggingFreq[frequency_opt];
                    mode_level = 1;

                    break;
                case SETPERIOD:
                    if ((mode_level == 2)&& (duration_red_pressed ==1)) {
                        if (cursor_pos <5){
                            cursor_pos++;
                        }else{
                            cursor_pos = 0;
                        }
                        duration_red_pressed = 0;
                    }

                    if (duration_green_pressed == 2){
                        switch(cursor_pos){
                        case MIN_10:
                            //                   tmpSet = set_duration[0];
                            //                   UARTprintf("tmpSet: %d \n",tmpSet);
                            set_duration[0] = (++set_duration[0])%10;
                            break;
                        case MIN_1:
                            set_duration[1] = (++set_duration[1])%10;
                            break;
                        case SEC_10:
                            set_duration[2] = (++set_duration[2])%6;
                            break;
                        case SEC_1:
                            set_duration[3] = (++set_duration[3])%10;

                            break;
                        case HALFSEC:
                            set_duration[4] /= 5;
                            set_duration[4] = (++set_duration[4])%2;
                            set_duration[4] *= 5;
                            break;
                        case ENTERKEY:
                            duration_green_pressed = 0;
                            duration_red_pressed = 0;
                            mode_level = 1;

                            loggingDuration = (float)((set_duration[0]*600+set_duration[1]*60+set_duration[2]*10+set_duration[3])+(float)set_duration[4]/10);

                            break;
                        }

                        UARTprintf("set_duration :");
                        for (i=0;i<5;i++){
                            UARTprintf(" %d ",set_duration[i]);
                        }
                        UARTprintf("\n");
                    }

                    //mode_level = 1;
                    break;

                default:
                    break;
                }


                SetGain(measure_mode);
                SysCtlDelay(30);

                if ((measure_mode == LOGIC)){ // don't need to convert number to string
                    setDiaplyValue(measure_mode , measuredADCVal, tmp);
                    setCursorPositionLCD(1,5);
                    printLCD(displayADCVal);

                }else if (measure_mode == SETBRIGHT ) {

                    itoa(brightness_opt,displayADCVal,10);
                    for (i=1;i<16;i++){
                        displayADCVal[i] = ' ';
                    }
                    setCursorPositionLCD(1,10);
                    printLCD(displayADCVal);
                }else if (measure_mode == SETPERIOD){
                    if(duration_green_pressed>0){
                        if(cursor_pos <5){
                            itoa(set_duration[cursor_pos],displayADCVal,10);
                            setCursorPositionLCD(1,set_cursor_duration[cursor_pos]);
                            printLCD(displayADCVal);
                            setCursorPositionLCD(1,set_cursor_duration[cursor_pos]);
                            setBlockCursorLCD();
                        }else {
                            setCursorPositionLCD(1,set_cursor_duration[cursor_pos]);
                            printSpecialChar(ENTER);
                            setCursorPositionLCD(1,set_cursor_duration[cursor_pos]);
                            setBlockCursorLCD();
                        }
                        duration_green_pressed =1;
                    }else {
                        cursorOffLCD();       // Cursor invisible
                    }

                }else{
                    // base on the mode, scale the readADC value to display value
                    setDiaplyValue(measure_mode , measuredADCVal, displayADCVal);
                    // display value on ADC
                    setCursorPositionLCD(1,5);
                    printLCD(displayADCVal);
                }
                //UARTprintf("measure_mode %d \n",measure_mode);
                if (measure_mode == SETBRIGHT){
                   // UARTprintf("In brightness mode\n");
                    memset(brightness_opt_str,0,sizeof(brightness_opt_str));
                    itoa(brightness_opt,brightness_opt_str,10);
                    UARTSendMeasurement(pb_mode,measure_mode,brightness_opt_str);

                }else if (measure_mode == SETPERIOD){
                   // UARTprintf("In setting period\n");
                    memset(loggingDurationString,0,sizeof(loggingDurationString));
                    ftoa(loggingDuration,loggingDurationString);
                    UARTSendMeasurement(pb_mode,measure_mode,loggingDurationString);
                }else {
                  //  UARTprintf("In displaying mode\n"); -------------------------------------->UARTprintf screwed up the normal UARTSend function
                    UARTSendMeasurement(pb_mode,measure_mode,displayADCVal);
                    //UARTSend(displayADCVal);
                }
                UARTprintf("\n");
                if (logging_pressed == 1){
                    UARTprintf("display: %s \n",displayADCVal);
                }
                freq_flag = 0;
            }
   }
}
void modeChange(void){
    uint8_t i;
    cursorOffLCD();       // Cursor invisible
    setPWM(BUZZER,OFF);
    switch(pb_mode){
    case AC_CURRENT:
        // change mux

        measure_mode = CURRENT_10;
        break;
    case DC_CURRENT:
        measure_mode = CURRENT_10;
        break;
    case AC_VOLTAGE:
        measure_mode = VOLTAGE_12;
        break;
    case DC_VOLTAGE:
        measure_mode = VOLTAGE_12;
        break;
    case RESISTANCE:
        measure_mode = RESISTANCE_1K;
        break;
    case CONTINUITY:
        measure_mode = RESISTANCE_1K;
        break;
    case LOGIC:
        measure_mode = LOGIC;
        break;
    case FREQ:
        measure_mode = SETFREQ;
        break;
    case DURATION:
        measure_mode = SETPERIOD;
        for(i=0;i<5;i++){
            itoa(set_duration[i],int2str_duration,10);
            setCursorPositionLCD(1,set_cursor_duration[i]);
            printLCD(int2str_duration);
        }
        break;
    case BRIGHTNESS:
        measure_mode = SETBRIGHT;
        break;
    }


    SetMuxDCAC(pb_mode); // set up the mux
    SetInputRelay(pb_mode);
    setModeDisplay(pb_mode);
    SetADCSwitch(pb_mode);
}
void SW1_IntHandler(void)
{

    if (GPIOIntStatus(GPIO_PORTA_BASE, false) & GPIO_PIN_7) {
        if (mode_level == 1 && (logging_pressed == 0)) {
            // change mode when PB is pressed
            if(pb_mode<10){
                pb_mode++;
            }else{
                pb_mode =1;
            }
            modeChange();
            freq_flag = 1;

//            SetMuxDCAC(pb_mode);

 //           UARTprintf("RED PRESSED\n " );
        } else if((mode_level == 2)&& (pb_mode == DURATION)){
            duration_red_pressed = 1;
        }
        GPIOIntClear(GPIO_PORTA_BASE, GPIO_PIN_7);  // Clear interrupt flag
    }

    if (GPIOIntStatus(GPIO_PORTA_BASE, false) & GPIO_PIN_6) {

           mode_level = 2;
           freq_flag = 1;
           if(pb_mode == DURATION){
               duration_green_pressed++;
           }else if((pb_mode == FREQ)||(pb_mode == BRIGHTNESS)){
           }else {
               mode_level = 1;
               logging_pressed^= 1;
               counter = 0;
               loggingCounter = 0;
           }
//           UARTprintf("GREEN PRESSED\n " );
           GPIOIntClear(GPIO_PORTA_BASE, GPIO_PIN_6);  // Clear interrupt flag
       }
}
//*****************************************************************************
//
// This function sets up UART0 to be used for a console to display information
// as the example is running.
//
//*****************************************************************************
void
initTimer(void)
{

    numTick = SysCtlClockGet();
    // Enable the GPIO port that is used for the on-board LED.
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    // Enable the GPIO pins for the LED (PF1 & PF2).
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_2);

    // Enable the peripherals used by this example.
    SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);

    // Enable processor interrupts.
    IntMasterEnable();
    // Configure the one 32-bit periodic timers.
    TimerConfigure(TIMER0_BASE, TIMER_CFG_PERIODIC);
    // 1 second is 2M counts as the clock is set up to be 2MHz
    // to be more general, 1s is equal to SysCtlClockGet() much number of counts
    // number of count = SysCtlClockGet()* required time in second
    numTick = SysCtlClockGet()*0.25;
    TimerLoadSet(TIMER0_BASE, TIMER_A, numTick);

    // Setup the interrupts for the timer timeouts.
    IntEnable(INT_TIMER0A);
    TimerIntEnable(TIMER0_BASE, TIMER_TIMA_TIMEOUT);
    // Enable the timers.
    TimerEnable(TIMER0_BASE, TIMER_A);


}
//*****************************************************************************
//
// The interrupt handler for the first timer interrupt.
//
//*****************************************************************************
void
Timer0IntHandler(void)
{

    //
    // Clear the timer interrupt.
    //
    ROM_TimerIntClear(TIMER0_BASE, TIMER_TIMA_TIMEOUT);

    counter++;
    loggingCounter++;
    LED2Counter++;

}
