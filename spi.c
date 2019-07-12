#include "spi.h"

void InitializeSPI()
{	
	/* Note that the SPI functionality is being implemented in software 
	 * (that is, "bit banging").  As such, the USCI module is not being used.
	 */
	SET_USCIA0_MOSI_AS_AN_OUTPUT;
	SET_SPI_SCK_AS_AN_OUTPUT;
    INITIALIZE_SPI_SCK;
}

void SPISendByte(unsigned int SendValue)
{
	unsigned short k;
	unsigned int LocalSendValue;

	LocalSendValue = (SendValue << 2); //10 BIT ADC - 8 BITS OF SPI
	// Turns 00110100 into 11010000 for example

	for (k = 0; k < 8; k++){
	    // Toggle SPI Clock: (HIGH XOR 1) -> LOW, and (LOW XOR 1) -> HIGH
	    // Known as a LEADING CLOCK
	    TOGGLE_SPI_SCK; TOGGLE_SPI_SCK;

		// Assign a value to the MOSI based on the value of the MSB.
		if (LocalSendValue & 0x80) {
			WRITE_LOGIC_1_TO_SLAVE;
		}
		else {
			WRITE_LOGIC_0_TO_SLAVE;
		}
		
		// Left-shift local copy of data to send.
		LocalSendValue <<= 1;

	}
	WRITE_LOGIC_0_TO_SLAVE;

}
