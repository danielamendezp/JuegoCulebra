//*----------------------------------------------------
//  Universidad:		Universidad Tecnica Nacional(UTN)
//  Curso:		Aplicaciones de Microcontroladores
//  Desarrollado por:	Daniela Méndez Porras y Keylor García Jirón
//  Nombre del proyecto:	Practicas_PIC_16F887A
//  Fecha                 06/12/2021
//  Nombre del archivo:	P7.1) Comunicación serial PC-Tarjeta 
//  --------------------------------------------------*/


#include "local_libraries/global_config_params.h"
#include "local_libraries/uart.h"
#include "local_libraries/lcd.h"

LCD lcd={&PORTD, 2, 3, 4, 5, 6, 7};
int cont=0;
char str_buff[10];

void setup(void){
     //Config puertos
   TRISD = 0x00; //0b00000000; output salida
   PORTD = 0x00;//se inicializa el puerto
   TRISC = 0x80; //RC6/RX como salida y RC7/TX como entrada 
   PORTC = 0x00;//se inicializa el puerto
   uart_init(8929);//Uart inicializacion
   lcd_init(&lcd);
   lcd_clear(&lcd);
   
} //END SETUP
 
int main(void){
   setup();    // Call function configuration
    while(1){//se mantiene en la interrupcion de alta prioridad
        uart_write_text(str_buff);//Enviar el valor del contador
        uart_write_text(" ");//se separan por espacios
        cont++;
        itoa(str_buff, cont, 10);//conversion de int a string
        if(cont>59){
            cont=0;//se reinicia a 0
        }
        if(cont<10){
            lcd_cursor(&lcd, 1,7);//se borran numeros que sobran en la lcd
            lcd_print(&lcd, " ");
        }
        lcd_cursor(&lcd, 0,2);
        lcd_print(&lcd, "Lectura UART");//se coloca el mensaje
        lcd_cursor(&lcd, 1,6);//se envia el valor del contador
        lcd_print(&lcd, str_buff);
        lcd_cursor(&lcd, 1,8);
        lcd_print(&lcd, "s");
         __delay_ms(500);
    }//end while
}//end main

