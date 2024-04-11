//*********************************************************************
// Universidad del Valle de Guatemala
// IE2023: Programación de Microcontroladores
// Autor: Alan Gomez
// Proyecto: POST_LAB_4_C.c
// Descripción: Cuarto POST-Laboratorio de Programación de Microcontroladores con lenguaje C.
// Hardware: ATmega328p
// Created: 6/4/2024
//*********************************************************************
//Speed
#define F_CPU 16000000;

#include <avr/io.h>
#include <avr/interrupt.h>// Interrupciones
#include <util/delay.h>// Delay


volatile uint8_t contador = 0; // Declarar contador como volatile para uso en interrupción

void setup(void);// Establecer pines
void initADC(void);// ADC

<<<<<<< Updated upstream
=======
const uint8_t mylist[] = { 7E,28,5D,6D,2B,67,77,2C,7F,2F,3F,73,56,79,57,17};

>>>>>>> Stashed changes
int main(void) {
	//Interrupciones+-
.    cli(); // Deshabilitar Interrupciones
    // Habilitar interrupciones de pin change para los pines PC0 y PC3
		PCMSK1 |= ((1 << PCINT11) | (1 << PCINT8)); // Habilitar interrupciones para PCINT11 y PCINT8
		PCICR |= (1 << PCIE1); // PCINT1 8-14 Grupo 1 
	
		setup(); // Configurar Puertos
		
		DDRD |= 0xFF;
		PORTD = 0;
		UCSR0B = 0;
		
	sei();// Habilitar Interrupciones Globales

    while (1) {
        // Programa principal
		//Displays
		//D1
		PORTB |= (1 << PB1);// Encender transistor en PB1
<<<<<<< Updated upstream
		PORTD = 0b00000001;// Mostrar primier display
=======
		ADCSRA |= (1<<ADSC);
>>>>>>> Stashed changes
		_delay_ms(1);
		PORTB &= ~(1 << PB1);// Apagar transistor en PB1
		_delay_ms(1);
		//D2
		PORTB |= (1 << PB2);// Encender transistor en PB2
		PORTD = 0b00000001;// Mostrar segundo display
		_delay_ms(1);
		PORTB &= ~(1 << PB2);// Apagar transistor en PB2
		_delay_ms(1);
<<<<<<< Updated upstream
		
		// Actualizar el puerto D con el valor del contador
=======
>>>>>>> Stashed changes
		PORTB |= (1 << PB0);// Encender transistor en PB0
		PORTD = contador;// Mostrar valor de contador
		_delay_ms(1);
		PORTB &= ~(1 << PB0);// Apagar transistor en PB0
		_delay_ms(1);
    }
}

void setup(void) {
    // Configurar pines PB0 a PB2 como salidas para los transistores
    DDRB |= 0b00000111;

    // Configurar PC3 y PC0 como entradas con pull-up habilitado para los botones
    DDRC &= ~((1 << DDC3) | (1 << DDC0)); // Configurar como entrada
    PORTC |= ((1 << PORTC3) | (1 << PORTC0)); // Habilitar resistencias de pull-up en PC3 y PC0

    // Configurar pines PD0 a PD7 como salidas para los LEDs
    DDRD |= 0b11111111;
}

ISR(PCINT1_vect) {
	_delay_ms(10);
    // Verificar si la interrupción fue causada por PCINT11 (PC3)
    if (PINC & (1 << PINC3)) {
        contador++; // Incrementar contador si el botón en PC3 fue presionado
    }
    // Verificar si la interrupción fue causada por PCINT8 (PC0)
    if (PINC & (1 << PINC0)) {
        contador--; // Decrementar contador si el botón en PC0 fue presionado
	}
	contador = (contador > 255) ? 0 : contador;// Si contador Overflow 255 se resetea el contador
	contador = (contador < 0) ? 255 : contador;// Si contador Underflow 0 se setea a 255
}
<<<<<<< Updated upstream
=======

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
	
	if(ADCH < 32){
		contador = 0;
	}
	else if((ADCH < 32) && (ADCH < 64)){
		contador = 1;
	}
	else if((ADCH <64) && (ADCH < 96)){
		contador = 2;
	}
	/*else if((ADCH <) && (ADCH < )){
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
	}*/
	else
	{
		contador = 0;
	}
	
	
	PORTD = mylist[contador];// Cargar valor a puerto
	ADCSRA |= (1<<ADIF);
	
}
>>>>>>> Stashed changes
