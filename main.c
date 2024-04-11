//*********************************************************************
// Universidad del Valle de Guatemala
// IE2023: Programación de Microcontroladores
// Autor: Alan Gomez
// Proyecto: POST_LAB_4_C.c
// Descripción: Cuarto POST-Laboratorio de Programación de Microcontroladores con lenguaje C.
// Hardware: ATmega328p
// Created: 6/4/2024
//*********************************************************************
#define F_CPU 16000000

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

volatile uint8_t contador = 0; // Declarar contador como volatile para uso en interrupción.
volatile float counter = 0;// Contador de Lista.
volatile uint8_t PP1 = 0;// Intervalos de mostreo de tabla
volatile uint8_t PP2 = 0;// Intervalos de mostreo de tabla

void setup(void);
void initADC(void);

//Tabla
const uint8_t mylist[] = {0x7E, 0x28, 0x5D, 0x6D, 0x2B, 0x67, 0x77, 0x2C, 0x7F, 0x2F, 0x3F, 0x73, 0x56, 0x79, 0x57, 0x17};

int main(void) {
	setup(); // Configurar Puertos
	
    cli(); // Deshabilitar Interrupciones
	
	//INTERRUPCIONES
    // Habilitar interrupciones de pin change para los pines PC0 y PC3
	PCMSK1 |= ((1 << PCINT11) | (1 << PCINT8)); // Habilitar interrupciones para PCINT11 y PCINT8
    PCICR |= (1 << PCIE1); // PCINT1 8-14 Grupo 1
	
	//ADC
	DDRD |=0xFF;
	PORTD = 0;
	UCSR0B = 0;
	initADC();
	
    sei(); // Habilitar Interrupciones Globales

    while (1) {
        // Programa principal
		
		//Displays
		//D1
		PORTB |= (1 << PB1);// Encender transistor en PB1
		//ADC
		PORTD = mylist[PP1];// Cargar valor a puerto
		_delay_ms(1);
		PORTB &= ~(1 << PB1);// Apagar transistor en PB1
		_delay_ms(1);
		//D2
		PORTB |= (1 << PB2);// Encender transistor en PB2
		PORTD = mylist[PP2];// Cargar valor a puerto
		_delay_ms(1);
		PORTB &= ~(1 << PB2);// Apagar transistor en PB2
		_delay_ms(1);
		ADCSRA |= (1<<ADSC);
		
		//Leds
		PORTB |= (1 << PB0);// Encender transistor en PB0
		PORTD = 0;// Limpiamos salida de leds
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

void initADC(void){
	//reiniciamos
	ADMUX = 0;
	// Seleccionamos ADC6
	ADMUX = 0b110;
	//Referencia AVCC = 5V
	ADMUX |= (1<<REFS0);
	ADMUX &= ~(1<<REFS1);
	//Justificacion a la izquierda
	ADMUX |= (1<<ADLAR);
	
	ADCSRA =0;
	//Habilitamos la interrupcion del ADC
	ADCSRA |= (1<<ADIE);
	//Habilitamos prescaller de 16M/128 Fadc = 125kHz
	ADCSRA |= (1<<ADPS2) | (1<<ADPS1) | (1<<ADPS0);
	//Habilitando el ADC
	ADCSRA |= (1<<ADEN);

}

ISR(ADC_vect){
	//counter = 0.2493*ADCH;

	ADCSRA |= (1<<ADIF);
}

