#define F_CPU 4000000UL
#include <avr/io.h>

#define SS PORTB2 // Definition of SS pin
#define MOSI PORTB3 // Definition of MOSI pin
#define MISO PORTB4 // Definition of MISO pin
#define SCK PORTB5 // Definition of SCK pin

void SPI_MasterInit() // Function to initialize SPI Master mode
{
	DDRB |= (1 << SS) | (1 << MOSI) | (1 << SCK); // Set SS, MOSI, and SCK as outputs
	SPCR = (1 << SPE) | (1 << MSTR) | (1 << SPR0); // Enable SPI and set as master
	// Prescaler: fclk/16
}

void SPI_MasterTransmit(char cData) // Function to transmit data in SPI Master mode
{
	SPDR = cData; // Transmit the data
	while (!(SPSR & (1 << SPIF))); // Wait until the SPI flag becomes 1
}

int main(void)
{
	DDRD = 0x00; // Set Port D as input
	PORTD = 0xFF; // Enable pull-up resistors
	SPI_MasterInit(); // Initialize SPI in Master mode
	
	while (1)
	{
		SPI_MasterTransmit(PIND); // Transmit the value read from Port D
	}
}