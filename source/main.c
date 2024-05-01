/*
 * Nombre de la tarea: Registros Internos
 * Materia: Diseño de Microcontroldores
 * Autor: Alejandro Orozco Romo
 * Descripcion: Programa en C para la K64 tal cada vez que se presione
  				el SW2 el led RGB cambia de color con la siguiente secuencia:
 					• Amarillo
					• Rojo
					• Morado
					• Azul
					• Verde
				Y cuando se presiona el SW3 el LED RGB cambia de color con la
				siguiente secuencia:
					• Verde
					• Azul
					• Morado
					• Rojo
					• Amarillo
				El encendido/apagado de pines tiene ser con PTOR, PCOR o PSOR,
				no se puede usar el PDOR.
 * Fecha de Creacion: 27/04/2024
 */

/*BIBLIOTECAS*/
#include <stdio.h>
#include <stdint.h>
#include "MK64F12.h"

/*DECLARACION DE FUNCIONES*/
void delay(uint16_t delay);

/*DECLARACION DE TIPOS DEFINIDOS*/
typedef unsigned short int uint_16_t;
typedef unsigned char uint_8_t;

/*FUNCION PRINCIPAL*/
int main(void) {

	/* Variables */
	int SW2 =0;
	int SW3 =0;

	/* Flujo del Programa */

	/*Activating the GPIOB and GPIOE clock gating*/
	SIM->SCGC5 = 0x2400 | (1 << 11)| (1 << 9); //11 y 9, bits correspondientes

	/**Pin control configuration of GPIOB pin22 and pin21 as GPIO*/
	//LED RGB
	PORTB->PCR[21] = 0x00000100; //BLUE
	PORTB->PCR[22] = 0x00000100; //RED
	PORTE->PCR[26] = 0x00000100; //GREEN

	//SW2
	PORTC->PCR[6] = 0x00000100;
	//SW3
	PORTA->PCR[4] = 0x00000100;

	// a high level turn off leds
	/* Se usa PSOR (Port Set Output Register)*/
	GPIOB->PSOR = (1 << 21) | (1 << 22);
	GPIOE->PSOR = (1 << 26 );

	/*Se usa PTOR ( Port Toggle Output Register ), ya que invierte el estado
	  de los bits*/
	GPIOC->PTOR = (0X40);
	GPIOA->PTOR = (0X10);

	/**Configures GPIOB pin21 as output*/
	GPIOB->PDDR = 0x00200000;
	/**Configures GPIOB pin22 as output*/
	GPIOB->PDDR |= 0x00400000;
	/**Configures GPIOE pin26 as output*/
	GPIOE->PDDR |= 0x04000000;


    while(1) {
        //Capturamos todos los bits de cada registro
    	SW2 = GPIOC->PDIR;
    	SW3 = GPIOA->PDIR;
    	//Mascaras
    	SW2 = SW2 & (0x40);
    	SW3  &= (0x10);

    	//si presionamos SW2
    	if(0x00 == SW2)
    	{
    		//YELLOW
    		GPIOB->PTOR = (0x00400000);/**Red led on*/
    		GPIOE->PTOR = (0x04000000);/**Green led on*/
    		delay(65000);
    		GPIOB->PTOR = 0x00400000;/**Red led off*/
    		GPIOE->PTOR = 0x04000000;/**Green led off*/
    		delay(65000);
    		//RED
    	    GPIOB->PTOR = (0x00400000);/**Red led on*/
    	    delay(65000);
    	    GPIOB->PTOR = 0x00400000;/**Red led off*/
    	    delay(65000);
    		//PURPLE
    		GPIOB->PTOR = (0x00400000);/**Red led on*/
    		GPIOB->PTOR = (0x00200000);/**Blue led on*/
    		delay(65000);
    		GPIOB->PTOR = 0x00400000;/**Red led off*/
    	    GPIOB->PTOR = 0x00200000;/**Blue led off*/
    	    delay(65000);
    		//BLUE
    	    GPIOB->PTOR =(0x00200000);/**Blue led on*/
    	    delay(65000);
    	    GPIOB->PTOR = 0x00200000;/**Blue led off*/
    	    delay(65000);
    	    //GREEN
    	    GPIOE->PTOR = (0x04000000);/**Green led on*/
    	    delay(65000);
    	    GPIOE->PTOR = 0x04000000;/**Green led off*/
    	    delay(65000);
    	}

    	//si presionamos SW2
    	else if(0x00 == SW3)
    	{
    		//GREEN
    		GPIOE->PTOR = (0x04000000);/**Green led on*/
    		delay(65000);
    		GPIOE->PTOR = 0x04000000;/**Green led off*/
    		delay(65000);
    		//BLUE
    	    GPIOB->PTOR = (0x00200000);/**Blue led on*/
    	    delay(65000);
    	    GPIOB->PTOR = 0x00200000;/**Blue led off*/
    	    delay(65000);
    	    //PURPLE
    	    GPIOB->PTOR = (0x00400000);/**Red led on*/
    	    GPIOB->PTOR = (0x00200000);/**Blue led on*/
    	    delay(65000);
    	    GPIOB->PTOR = 0x00400000;/**Red led off*/
    	    GPIOB->PTOR = 0x00200000;/**Blue led off*/
    	    delay(65000);
    		//RED
    		GPIOB->PTOR = (0x00400000);/**Red led on*/
    		delay(65000);
    		GPIOB->PTOR = 0x00400000;/**Red led off*/
    		delay(65000);
    		//YELLOW
    		GPIOB->PTOR = (0x00400000);/**Red led on*/
    		GPIOE->PTOR = (0x04000000);/**Green led on*/
    		delay(65000);
    		GPIOB->PTOR = 0x00400000;/**Red led off*/
    		GPIOE->PTOR = 0x04000000;/**Green led off*/
    		delay(65000);
    	}
    }
    /* Fin del progama */
    return 0 ;
}


////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////

/* DESCRIPCION DE LA FUNCION */
void delay(uint16_t delay)
{
	volatile uint16_t counter;

	for(counter=delay; counter > 0; counter--)
	{
		__asm("nop");
	}
}


