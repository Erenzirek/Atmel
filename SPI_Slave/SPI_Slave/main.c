/*

main.c
Created: 7/18/2023 4:42:21 PM
Author: erenz
*/
#define F_CPU 4000000UL
#include <avr/io.h>
#define SS PORTB2 // Define SS' pin
#define MISO PORTB4 // Define MISO pin

void SPI_SlaveInit() // Function to initialize SPI Slave mode
{
	PORTB = (1 << MISO); // Set MISO pin as output
	SPCR = (1 << SPE); // Enable SPI
}

char SPI_SlaveReceive() // Function to receive data in SPI Slave mode
{
	while (!(SPSR & (1 << SPIF))); // Wait until reading is complete
	return SPDR; // Return the content of the SPI data register
}

int main(void)
{
	char rData; // Received data variable
	DDRD = 0xFF; // Set all bits of PORTD as output
	SPI_SlaveInit(); // Initialize SPI in Slave mode
	while (1)
	{
		rData = SPI_SlaveReceive(); // Receive data via SPI
		PORTD = rData; // Write the received data to PORTD
		SPSR |= (1 << SPIF); // Clear the interrupt flag
	}
}