#include <hidef.h> 
#include "derivative.h" 


#define LED_Blue PTBD_PTBD4 /* Se define el nombre del puerto B4 */
#define LED_Red  PTBD_PTBD5 /* Se define el nombre del puerto B5 */

unsigned int valor_ADC;


void interrupt VectorNumber_Vadc adc_isr(void)
{
  valor_ADC = ADCR;  	      // lee el resultado (limpia la bandera de interrupción)
}

void main(void) 
{
	/*Configuración incial*/	
  SOPT1 = 0x52;	           /*Desactivamos el watchdog */    
  
  ICSSC = NV_FTRIM;		   /* configuración del registro FTRIM*/
  ICSTRM = NV_ICSTRM;	   /* configuración del registro TRIM */
  ICSC2 = 0;		       /* configuración del reloj interno, se divide entre 1 (por defecto se divide entre 2)*/
  
  ADCCFG_ADLSMP = 1; 		// Habilita tiempo de muestreo largo
  ADCCFG_MODE = 0x02;		// Modo de 10-bit, la resolución mas alta disponible
  ADCCFG_ADIV = 0x03;		// Se divide la fuente de reloj en 8
  ADCCFG_ADICLK = 0x01;		// Seleccionamos la fuente de reloj como Bus clock dividida entre  2
  
  APCTL1_ADPC0 = 1;		    // ADP0 en modo analógico 
  
  
  ADCSC1_AIEN = 1;			//Interrupciones activadas
  ADCSC1_ADCO = 1;			//Modo continuo activado
  ADCSC1_ADCH = 0x00;		//Canal AD0
  
  PTBDD_PTBDD4 = 1;			// PTB4 y PTB5 como salidas
  PTBDD_PTBDD5 = 1;
  
  EnableInterrupts;		    // Habilita interrupciones (CCR:I=0)
  
while(1){
    if (valor_ADC>428) LED_Blue = 1;
    	else LED_Blue = 0;
    if (valor_ADC>768) LED_Red = 1;
        else LED_Red = 0;
  }

}
