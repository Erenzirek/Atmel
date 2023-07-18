#define F_CPU 1000000UL
#include <avr/io.h>
#include <util/delay.h>

#define forward PORTD2 // forward is assigned to PORTD2.
#define stop PORTD1    // stop is assigned to PORTD1.
#define backward PORTD0 // backward is assigned to PORTD0.

int main(void)
{
	DDRB = 0xFF; // Set port B as output.
	DDRD = 0x00; // Set port D as input.

	while (1)
	{
		if (PIND & (1 << forward)) // If the forward button is pressed:
		{
			_delay_ms(10);      // Delay for 10 milliseconds.
			PORTB = 0b00000101; // Activate motor driver A. Input - 1 = HIGH, Input - 2 = LOW
		}
		if (PIND & (1 << stop)) // If the stop button is pressed:
		{
			_delay_ms(10);      // Delay for 10 milliseconds.
			PORTB = 0b00000100; // Activate motor driver A. Input - 1 = Input - 2 = LOW
		}
		if (PIND & (1 << backward)) // If the backward button is pressed:
		{
			_delay_ms(10);      // Delay for 10 milliseconds.
			PORTB = 0b00000110; // Activate motor driver A. Input - 1 = LOW, Input - 2 = HIGH
		}
	}
}