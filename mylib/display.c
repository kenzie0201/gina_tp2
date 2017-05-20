/*
 * LCD Library for Stellaris/Tiva launchpads
 * All rights reserved.
 * Distributed under the BSD License
 * Copyright (c) 2015, Manolis Kiagias
 *
 * Based on ideas and code of the MSP430 Launchpad LCD Library
 * published in Co-Random thoughts blog:
 * http://cacheattack.blogspot.gr/2011/06/quick-overview-on-interfacing-msp430.html
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * --/COPYRIGHT--*/
 /*******************************************************************************/


#include "display.h"
#include "switchgain.h"

unsigned char plusminusmap[8] = {
    0b00100,
    0b00100,
    0b11111,
    0b00100,
    0b00100,
    0b00000,
    0b11111,
    0b00000
};
unsigned char BrightnessLV1[8] = {
    0b10000,
    0b10000,
    0b10000,
    0b10000,
    0b10000,
    0b10000,
    0b10000,
    0b10000
};
unsigned char BrightnessLV2[8] = {
    0b11000,
    0b11000,
    0b11000,
    0b11000,
    0b11000,
    0b11000,
    0b11000,
    0b11000
};
unsigned char BrightnessLV3[8] = {
    0b11100,
    0b11100,
    0b11100,
    0b11100,
    0b11100,
    0b11100,
    0b11100,
    0b11100
};
unsigned char BrightnessLV4[8] = {
    0b11110,
    0b11110,
    0b11110,
    0b11110,
    0b11110,
    0b11110,
    0b11110,
    0b11110
};
unsigned char BrightnessLV5[8] = {
    0b11111,
    0b11111,
    0b11111,
    0b11111,
    0b11111,
    0b11111,
    0b11111,
    0b11111
};
unsigned char enter[8] = {
    0b00001,
    0b00001,
    0b00001,
    0b00101,
    0b01001,
    0b11111,
    0b01000,
    0b00100
};
//
// Pulse the EN bit LOW - HIGH - LOW
// To signal the LCD to accept the data/cmd
//

void pulseLCD()
{
    // Go Low -> High -> Low
    GPIOPinWrite(CMD_PORT_BASE, EN, 0);
    GPIOPinWrite(CMD_PORT_BASE, EN, EN);
    GPIOPinWrite(CMD_PORT_BASE, EN, 0);
}

//
// Set the RS to LOW
// Indicating incoming command
//

void setCmd() {
    GPIOPinWrite(CMD_PORT_BASE, RS,0);
}

//
// Set the RS to HIGH
// Indicating incoming data
//

void setData() {
    GPIOPinWrite(CMD_PORT_BASE, RS,RS);
}

//
// Send data byte in 4 bit mode
// High nibble is sent first
//

void sendByte(char byteToSend, int isData)
{
    if (isData)
        setData();
    else
        setCmd();
    SysCtlDelay(400);
    GPIOPinWrite(DATA_PORT_BASE, ALLDATAPINS, byteToSend >>4);
    pulseLCD();
    GPIOPinWrite(DATA_PORT_BASE, ALLDATAPINS, byteToSend);
    pulseLCD();
}

//
// For 16 columns, 2 rows LCD
// Select row / column for next character output
// Initial values are 0,0
//

void setCursorPositionLCD(char row, char col)
{
    char address;

    if (row == 0)
        address = 0;
    else if (row==1)
        address = 0x40;
    else if (row==2)
        address = 0x14;
    else if (row==3)
        address = 0x54;
    else
        address = 0;

    address |= col;

    sendByte(0x80 | address, FALSE);
}

//
// Clear the LCD
// and return to home position (0,0)
//

void clearLCD(void)
{
    sendByte(0x01, FALSE); // Clear screen
    sendByte(0x02, FALSE); // Back to home
    SysCtlDelay(30000);
}

//
// Return to home position (0,0)
//

void homeLCD(void) {
    sendByte(0x02, FALSE);
    SysCtlDelay(30000);
}


//
// Make block cursor visible
//

void setBlockCursorLCD(void) {
    sendByte(0x0F, FALSE);
}

//
// Make line cursor visible
//

void setLineCursorLCD(void) {
    sendByte(0x0E, FALSE);
}

//
// Display cursor on screen
//

void cursorOnLCD(void) {
    sendByte(0x0E, FALSE);
}

//
// Hide cursor from screen
//

void cursorOffLCD(void) {
    sendByte(0x0C, FALSE);
}

//
// Turn off LCD
//

void displayOffLCD(void) {
    sendByte(0x08, FALSE);
}

//
// Turn on LCD
//

void displayOnLCD(void) {
    sendByte(0x0C, FALSE);
}

//
// Initialize the LCD
// Performs the following functions:
// Activates selected ports
// Designates ports as outputs
// Pulls all output pins to low
// Waits for LCD warmup
// Sets LCD for 4 pin communication
// Sets two lines display
// Hides the cursor
// Sets insert mode
// Clears the screen
//

void initLCD(void)
{
    //
    // set the MSP pin configurations
    // and bring them to low
    //
    SysCtlPeripheralEnable(DATA_PERIPH);
    SysCtlPeripheralEnable(CMD_PERIPH);
    GPIOPinTypeGPIOOutput(DATA_PORT_BASE,  ALLDATAPINS);
    GPIOPinTypeGPIOOutput(CMD_PORT_BASE, ALLCONTROLPINS);
    GPIOPinWrite(DATA_PORT_BASE, ALLDATAPINS ,0);
    GPIOPinWrite(CMD_PORT_BASE, ALLCONTROLPINS ,0);

    //
    // wait for the LCM to warm up and reach
    // active regions. Remember MSPs can power
    // up much faster than the LCM.
    //

    SysCtlDelay(10000);

    //
    // initialize the LCM module
    // Set 4-bit input
    //

    setCmd();
    SysCtlDelay(15000);
    GPIOPinWrite(DATA_PORT_BASE, ALLDATAPINS, 0b0010);
    pulseLCD();
    GPIOPinWrite(DATA_PORT_BASE, ALLDATAPINS, 0b0010);
    pulseLCD();
    sendByte(0x28,FALSE);  // Set two lines
    cursorOffLCD();       // Cursor invisible
    sendByte(0x06, FALSE); // Set insert mode
    clearLCD();

    // load special characters
    buildChar(PLUSMINUS,plusminusmap);
    buildChar(LV1,BrightnessLV1);
    buildChar(LV2,BrightnessLV2);
    buildChar(LV3,BrightnessLV3);
    buildChar(LV4,BrightnessLV4);
    buildChar(LV5,BrightnessLV5);
    buildChar(ENTER,enter);

}

//
// Print the text
// on the screen
//

void printLCD(char *text)
{
    char *c;
    c = text;

    while ((c != 0) && (*c != 0))
    {
        sendByte(*c, TRUE);
        c++;
    }
}
void printSpecialChar(char input){
    sendByte(input, TRUE);
}
void setModeDisplay(int mode){
    if ( (mode == AC_CURRENT)) {
        setCursorPositionLCD(0,0);
        printLCD("CURR:");
        printSpecialChar(PLUSMINUS);

        setCursorPositionLCD(0,11);
        printLCD(" AC ");

        setCursorPositionLCD(1,14);
        printLCD("mA");
    }else if ((mode == AC_VOLTAGE)) {
        setCursorPositionLCD(0,0);
        printLCD("VOLT:");
        printSpecialChar(PLUSMINUS);

        setCursorPositionLCD(0,11);
        printLCD(" AC ");
        setCursorPositionLCD(1,14);
        printLCD(" V");
    }else if ( (mode == DC_CURRENT)) {
        setCursorPositionLCD(0,0);
        printLCD("CURR:");
        printSpecialChar(PLUSMINUS);

        setCursorPositionLCD(0,11);
        printLCD(" DC ");

        setCursorPositionLCD(1,14);
        printLCD("mA");
    }else if ( (mode == DC_VOLTAGE)) {
        setCursorPositionLCD(0,0);
        printLCD("VOLT:");
        printSpecialChar(PLUSMINUS);

        setCursorPositionLCD(0,11);
        printLCD(" DC ");

        setCursorPositionLCD(1,14);
        printLCD(" V");
    }else if ( mode == RESISTANCE){// resistance mode
        setCursorPositionLCD(0,0);
        printLCD("RESIS:");
        setCursorPositionLCD(0,11);
        printLCD("    ");
        setCursorPositionLCD(1,14);
        printLCD("  ");
    }else if ( mode == CONTINUITY){
        setCursorPositionLCD(0,0);
        printLCD("CONTI:");
        setCursorPositionLCD(0,11);
        printLCD("    ");
    }else if ( mode == LOGIC){
        setCursorPositionLCD(0,0);
        printLCD("LOGIC:         ");
    }else if ( mode == BRIGHTNESS){
        setCursorPositionLCD(0,0);
        printLCD("SET BRIGHTNESS ");
        setCursorPositionLCD(1,5);
        printLCD("LEVEL");
    }else if ( mode == FREQ){
        setCursorPositionLCD(0,0);
        printLCD("SET FREQUENCY  ");
    }else if ( mode == DURATION){
        setCursorPositionLCD(0,0);
        printLCD("SET PERIOD     ");
        setCursorPositionLCD(1,7);
        printLCD(":");
        setCursorPositionLCD(1,10);
        printLCD(".");
        setCursorPositionLCD(1,15);
        printSpecialChar(ENTER);


    }
}
void setDiaplyValue(int mode, float readADC, char *displayADC){
    int i =0;

    memset(displayADC,0,sizeof(displayADC));
    switch(mode){
    case CURRENT_10:
        //itoa( (readADC*1), displayADC, 10);

        setCursorPositionLCD(0,6);
        printLCD("10mA ");

        ftoa(readADC,displayADC);
        displayADC[9] = 'm';
        displayADC[10] = 'A';
        break;
    case CURRENT_200:
        setCursorPositionLCD(0,6);
        printLCD("200mA");

        ftoa(readADC,displayADC);
        displayADC[9] = 'm';
        displayADC[10] = 'A';
        break;
    case VOLTAGE_1:
        setCursorPositionLCD(0,6);
        printLCD("1V   ");

        ftoa(readADC,displayADC);
        displayADC[9] = ' ';
        displayADC[10] = 'V';
        break;
    case VOLTAGE_5:
        setCursorPositionLCD(0,6);
        printLCD("5V   ");
        ftoa(readADC,displayADC);
        displayADC[9] = ' ';
        displayADC[10] = 'V';
        break;
    case VOLTAGE_12:
        setCursorPositionLCD(0,6);
        printLCD("12V  ");
        ftoa(readADC,displayADC);
        displayADC[9] = ' ';
        displayADC[10] = 'V';
        break;
    case RESISTANCE_1K:
        setCursorPositionLCD(0,6);
        printLCD(" kOhm");
        ftoa(readADC,displayADC);
        displayADC[9] = ' ';
        displayADC[10] = ' ';
        break;
    case RESISTANCE_1M:
        setCursorPositionLCD(0,6);
        printLCD(" MOhm");
        ftoa(readADC,displayADC);
        displayADC[9] = ' ';
        displayADC[10] = 'k';
        break;
    case LOGIC:
        setCursorPositionLCD(1,14);
        printLCD("    ");
        ftoa(readADC,displayADC);
        break;
    case SETFREQ:
        if (readADC>10){
            readADC = readADC/60;
            ftoa(readADC,displayADC);
            displayADC[4] = 'm';
            displayADC[5] = 'i';
            displayADC[6] = 'n';
            displayADC[7] = 's';
        }else {
            ftoa(readADC,displayADC);
            displayADC[4] = 's';
            displayADC[5] = 'e';
            displayADC[6] = 'c';
            displayADC[7] = ' ';
        }
        for (i=8;i<16;i++){
            displayADC[i] = ' ';
        }
        break;
    case SETPERIOD:

        break;
    case SETBRIGHT:
        break;
    }
}

//*****************************************************************************
// integer to ASCII
//
//*****************************************************************************
void itoa ( int value, char *str, int base )
{

    char tmp[16]="\0";
    int i=0, remainder;
    if(value == 0){
        tmp[i]= 48;
    }
    while(value !=0){
        remainder = value%base;
        value = value/base;
        tmp[i]= remainder+48;
        i++;
    }

    for( i=0; i < strlen(tmp); i++){
        str[i]=tmp[strlen(tmp)-1-i];
    }
}
//*****************************************************************************
// float to ASCII
//
//*****************************************************************************
void ftoa(float f,char *buf)
{
    int pos=0,ix,dp,num;
    if (f<0)
    {
        buf[pos++]='-';
        f = -f;
    }
    dp=0;
    while (f>=10.0)
    {
        f=f/10.0;
        dp++;
    }
    for (ix=1;ix<8;ix++)
    {
            num = (int)f;
            f=f-num;
            if (num>9)
                buf[pos++]='#';
            else
                buf[pos++]='0'+num;
            if (dp==0) buf[pos++]='.';
            f=f*10.0;
            dp--;
    }
}
void buildChar(unsigned char loc,unsigned char *newChar){
    int i;
    if(loc<8){
        sendByte((0x40+(loc*8)),FALSE);
        for(i=0; i<8;i++){
            sendByte(newChar[i], TRUE);
        }
        sendByte(0x80,FALSE);
    }
}

