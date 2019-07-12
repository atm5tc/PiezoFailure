#include <msp430.h>
#include "LED.h"
#include "ADC.h"
#include "spi.h"
#include "timerA.h"
#define TRUE 1

// Global Variables
int y; // Filter output
int x[NUMBER_OF_SAMPLES]; // Array to hold input samples
unsigned int n; // Index that indicates location to place current sample input
unsigned int CurrentSample;

// Function prototypes
void ConfigureClockModule(void);
void InitializeSampleBuffer(void);

void main(void)
{
	// Stop the watchdog timer, and configure the clock module.
	WDTCTL = WDTPW + WDTHOLD;

	// Initialize LED Pin Port Directions and turn LED1 ON, LED2 OFF
    InitializeLEDPortPins();
    // Decide upon the preferred crystalline oscillator
  	ConfigureClockModule();
    ConfigureADC();
    InitializeSPI();
    // Configure timer A to generate the required interrupt.
    ConfigureTimerA();

    _enable_interrupts();
    //_BIS_SR(LPM0_bits + GIE);   // Enter Low Power Mode 0 (LPM0) and enable interrupts
  	while (1){
  	    // Infinite loop
  	}
}

void ConfigureClockModule(void)
{
    // Configure Digitally Controlled Oscillator (DCO) using factory calibrations.
	DCOCTL  = CALDCO_1MHZ;
	BCSCTL1 = CALBC1_1MHZ;
}
