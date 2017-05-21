#include "mypwm.h"



void initPWM(void){
    uint32_t period = 300; //20ms (16Mhz /8/ 8pwm_divider) 800 Hz



       //Configure PWM Clock divide system clock by 8
       SysCtlPWMClockSet(SYSCTL_PWMDIV_8);

       // Enable the peripherals used by this program.
        SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC);
        SysCtlPeripheralEnable(SYSCTL_PERIPH_PWM0);

        //Configure PC4 - LED
        //Configure PC5 - Buzzer
        GPIOPinConfigure(GPIO_PC4_M0PWM6);
        GPIOPinConfigure(GPIO_PC5_M0PWM7);
        GPIOPinTypePWM(GPIO_PORTC_BASE, GPIO_PIN_4 | GPIO_PIN_5 );

        //Configure PWM Options
        //PWM_GEN_3 Covers M0PWM6 and M0PWM7
        PWMGenConfigure(PWM0_BASE, PWM_GEN_3, PWM_GEN_MODE_DOWN | PWM_GEN_MODE_NO_SYNC);

        //Set the Period (expressed in clock ticks)
        PWMGenPeriodSet(PWM0_BASE, PWM_GEN_3, period);

        //Set PWM duty
        PWMPulseWidthSet(PWM0_BASE, PWM_OUT_6,0);
        PWMPulseWidthSet(PWM0_BASE, PWM_OUT_7,200);

        // Enable the PWM generator
        PWMGenEnable(PWM0_BASE, PWM_GEN_3);

        // Turn on the Output pins
        PWMOutputState(PWM0_BASE, PWM_OUT_6_BIT | PWM_OUT_7_BIT, true);
}
void setPWM(int mode, int state){
    if((mode == BUZZER) && (state == LOW)){
        //Set the Period (expressed in clock ticks)
        PWMGenPeriodSet(PWM0_BASE, PWM_GEN_3, 600);
        PWMPulseWidthSet(PWM0_BASE, PWM_OUT_6,300);
    }else if ((mode == BUZZER) && (state == HIGH)){
        PWMGenPeriodSet(PWM0_BASE, PWM_GEN_3, 300);
        PWMPulseWidthSet(PWM0_BASE, PWM_OUT_6,150);
    }else if ((mode == BUZZER) && (state == OFF)){
        PWMGenPeriodSet(PWM0_BASE, PWM_GEN_3, 300);
        PWMPulseWidthSet(PWM0_BASE, PWM_OUT_6,0);
    }else if(mode == LED){
        PWMGenPeriodSet(PWM0_BASE, PWM_GEN_3, 300);

        if (state ==LEVEL_1){
            PWMPulseWidthSet(PWM0_BASE, PWM_OUT_7,1);
        }else if ((mode == LED) && (state == LEVEL_2)){
            PWMPulseWidthSet(PWM0_BASE, PWM_OUT_7,40);
        }else if ((mode == LED) && (state == LEVEL_3)){
            PWMPulseWidthSet(PWM0_BASE, PWM_OUT_7,80);
        }else if ((mode == LED) && (state == LEVEL_4)){
            PWMPulseWidthSet(PWM0_BASE, PWM_OUT_7,160);
        }else if ((mode == LED) && (state == LEVEL_5)){
            PWMPulseWidthSet(PWM0_BASE, PWM_OUT_7,200);
        }


    }


}
