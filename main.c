//*********************************************************************
// Universidad del Valle de Guatemala
// IE2023: Programación de Microcontroladores
// Autor: Alan Gomez
// Proyecto: POST_LAB_4_C.c
// Descripción: Cuarto POST-Laboratorio de Programación de Microcontroladores con lenguaje C.
// Hardware: ATmega328p
// Created: 6/4/2024
//*********************************************************************
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

volatile uint8_t contador = 0; // Declarar contador como volatile para uso en interrupción

void setup(void);

//Tabla 7E,28,5D,6D,2B,67,77,2C,7F,2F,3F,73,56,79,57,17

int main(void) {
    cli(); // Deshabilitar Interrupciones

    // Habilitar interrupciones de pin change para los pines PC0 y PC3
	PCMSK1 |= ((1 << PCINT11) | (1 << PCINT8)); // Habilitar interrupciones para PCINT11 y PCINT8
    PCICR |= (1 << PCIE1); // PCINT1 8-14 Grupo 1

    setup(); // Configurar Puertos
    sei(); // Habilitar Interrupciones Globales

    while (1) {
        // Programa principal
		//Displays
		//D1
		PORTB |= (1 << PB1);// Encender transistor en PB1
		PORTD = 0b01010000;// Mostrar primier display
		_delay_ms(1);
		PORTB &= ~(1 << PB1);// Apagar transistor en PB1
		_delay_ms(1);
		//D2
		PORTB |= (1 << PB2);// Encender transistor en PB2
		PORTD = 0b00100000;// Mostrar segundo display
		_delay_ms(1);
		PORTB &= ~(1 << PB2);// Apagar transistor en PB2
		_delay_ms(1);
		
		// Actualizar el puerto D con el valor del contador
		//Nota para autor: El problema de los Leds se debia
		//a que ciertos led tenian la caracteristica que provocaban 
		//una conección a tierra ¨Artificial¨.
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


