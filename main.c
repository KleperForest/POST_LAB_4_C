//*********************************************************************
// Universidad del Valle de Guatemala
// IE2023: Programación de Microcontroladores
// Autor: Alan Gomez
// Proyecto: LAB_1_IN.asm
// Descripción: Cuarto Laboratorio de Programación de Microcontroladores con lenguaje C.
// Hardware: ATmega328p
// Created: 5/4/2024
//*********************************************************************

#define F_CPU 16000000// Speed del Atmega

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

void setup(void);
void initADC(void);


const uint8_t mylist[] = {7E,12,5D,57,33,67,6F,52,7F,73,7B,2F,56,1F,6D,69};
//Tabla en hexadecimal

uint8_t contador = 0; // Inicializar contador a 0

int main(void) {
	setup();
	
	cli();
	
	DDRD |= 0xFF;
	PORTD = 0;
	UCSR0B = 0;
	
	initADC();
	
	sei();
	
	// Bucle principal
	while (1) {
		PORTB |= (1 << PB1);// encender transistor
		ADCSRA |= (1<<ADSC);
		_delay_ms(200);
		}

}

void setup(void){
	// Configurar pines PB0 a PB1 como salidas para los LEDs
	DDRB |= 0b00000011;
}

void initADC(void){
	ADMUX = 0b0110;// Lectura en ADC6
	// referencia AVCC = 5V
	ADMUX |= (1<<REFS0);
	ADMUX &= ~(1<<REFS1);
	//Justificacion a al izquierda
	ADMUX |= (1<<ADLAR);
	
	ADCSRA = 0;
	// Habilitamos la interrupcion del ADC
	ADCSRA |= (1<<ADIE);
	// Habilitamos prescaler de 16M/128 Fadc = 125kHz
	ADCSRA |= (1<<ADPS2) | (1<<ADPS1) | (1<<ADPS0);
	// Habilitando el ADC
	ADCSRA |= (1<<ADEN);	
	
}

ISR(ADC_vect){
	
	if(ADCH <){
		contador = 0;
	}
	else if((ADCH <) && (ADCH < )){
		contador = 1;
	}	
	else if((ADCH <) && (ADCH < )){
		contador = 2;
	}
	else if((ADCH <) && (ADCH < )){
		contador = 3;
	}
	else if((ADCH <) && (ADCH < )){
		contador = 4;
	}
	else if((ADCH <) && (ADCH < )){
		contador = 5;
	}
	else if((ADCH <) && (ADCH < )){
		contador = 6;
	}
	else if((ADCH <) && (ADCH < )){
		contador = 7;
	}
	else if((ADCH <) && (ADCH < )){
		contador = 8;
	}
	else if((ADCH <) && (ADCH < )){
		contador = 9;
	}
	else if((ADCH <) && (ADCH < )){
		contador = 10;
	}
	else if((ADCH <) && (ADCH < )){
		contador = 11;
	}
	else if((ADCH <) && (ADCH < )){
		contador = 12;
	}
	else if((ADCH <) && (ADCH < )){
		contador = 13;
	}
	else if((ADCH <) && (ADCH < )){
		contador = 14;
	}
	else if((ADCH <) && (ADCH < )){
		contador = 15;
	}
	else
	{
		contador = 0;
	}
	
	
	PORTD = mylist[contador];// Cargar valor a puerto
	ADCSRA |= (1<<ADIF);
	
}