/*  Title:	Fireflies in a Jar
	Author:	Jason Schorr
	Date:	12/12/2010
	Ver:	1.0
*/

/* 	TO DO LIST 
	
	* Use interrupts instead of sleep times.
	* Remove double blink function to one with a parameter
	* Add support for photoresistor 
	* Cleanup pwm functions (blink)
*/


#include <avr/io.h>
#include <avr/sleep.h>
#include <util/delay.h>

void blink(){
	for (int i = 255 ; i > 1 ; i-- ){ // For loop (down counter 255 - 0 )
		OCR0A = i; // Update Output Compare Register (PWM 0 - 255)
		_delay_ms(10);
	}

	for (int i = 0 ; i < 255 ; i++ ){ // For loop (Up counter 0 - 255)
		OCR0A = i; // Update Output Compare Register (PWM 0 - 255)
 		_delay_ms(10);
	}
}


void blink2(){
	for (int i = 255 ; i > 1 ; i-- ){ // For loop (down counter 255 - 0 )
		OCR0B = i; // Update Output Compare Register (PWM 0 - 255)
		
		_delay_ms(10);
	}

	for (int i = 0 ; i < 255 ; i++ ){ // For loop (Up counter 0 - 255)
		OCR0B = i; // Update Output Compare Register (PWM 0 - 255)
 		_delay_ms(10);
	}
}

int main (void){

	// OC0A on PB0 & PB1
	DDRB |= (1 << 0) | (1 << 1); 

 
	TCCR0A |= ((1 << COM0A1) | (1 << COM0A0) // Set OC0A on Compare Match, clear OC0A at TOP
				| (1 << COM0B1) | (1 << COM0B0) // Set OC0B on Compare Match, clear OC0B at TOP
	 			| (1 << WGM01) | (1 << WGM00)); // WGM01 - WGM00 (set fast PWM)
 
	OCR0A = 255; 
	OCR0B = 255; 

	TCCR0B |= (1 << CS01); // Start timer at Fcpu / 8
	
	uint8_t rand = 0;

	while(1){
	_delay_ms(3000);
	blink();
	_delay_ms(1500);
	blink2();
	_delay_ms(900);
	}
}
 
