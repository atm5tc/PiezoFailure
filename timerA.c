#include "timerA.h"
#include "LED.h"

extern unsigned int CurrentSample;

void ConfigureTimerA(void)
{
    TA0CTL = (MC_0 | TACLR);
    TA0CTL |= (TASSEL_2 | MC_1 | ID_0);
    TA0CCR0 = 249; //62500 //125
    TA0CCTL0 |= CCIE;
}

#pragma vector = TIMER0_A0_VECTOR
// Timer_A interrupt service routine
__interrupt void Timer1_A0(void)
{
    //
    //TOGGLE_LED2;
    // Start conversion
    ADC10CTL0 |= ADC10SC;

    // Wait for ADC conversion to complete.
    while (ADC10CTL1 & ADC10BUSY);

    // Read the current sample value from the ADC.
    //CurrentSample = ADC10MEM;
    SPISendByte(ADC10MEM); // Least Significant Byte
}

