//*----------------------------------------------------
//  Universidad:		Universidad Tecnica Nacional(UTN)
//  Curso:		Aplicaciones de Microcontroladores
//  Desarrollado por:	Daniela Méndez Porras y Keylor García Jirón
//  Nombre del proyecto:	Practicas_PIC_16F887A
//  Fecha                 06/12/2021
//  Nombre del archivo:	P7.2) Modificación comunicación serial PC-Tarjeta V2 
//  --------------------------------------------------*/


#include "local_libraries/global_config_params.h"
#include "local_libraries/uart.h"
#include "local_libraries/eeprom.h"
#include "local_libraries/lcd.h"

LCD lcd={&PORTD, 2, 3, 4, 5, 6, 7};
int counter, lectura, cuenta=0, cont;
char str_buff[10];

int serial(void){
    while(1){ // Infinity loop
        if(uart_data_ready()){
            counter = uart_read();
        } else{
            //Nothing
        }
        break;
    }//EOW
    return 0;
}

void setup(void){
     //Config puertos
   TRISA= 0x06; //0b11111111; definir si va como entrada o salida
   PORTA = 0x00; // inicializar el puerto
   TRISB= 0x00; //como salida
   PORTB = 0x00; // inicializar el puerto
   TRISD= 0x00; //como salida
   PORTD = 0x00; // inicializar el puerto
   ADCON1bits.PCFG=0x07; //habilita entradas digitales
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
        cuenta++;
        itoa(str_buff, cuenta, 10);//conversion de int a string
        if(cuenta>59){
            cuenta=0;//se reinicia a 0
        }
        if(cuenta<10){
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
         
        serial();//se va a la subrutina de serial
    if(counter==97){//0x62 o a
        counter=0;
        cont++;
    } 
    if(cont==1){
        PORTBbits.RB1=1;//enciende led
    }
    if(cont==2){
        PORTBbits.RB1=0;//enciende led
        cont=0;
    } 
        
    }//end while
}//end main



