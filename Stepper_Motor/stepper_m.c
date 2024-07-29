//<<<<<> Mehran Tamjidi <<<<>>>> 

#include <mega16.h>
#asm
   .equ __lcd_port=0x1B ;PORTA
#endasm
#include <lcd.h>
#include <delay.h>  
#include <stdio.h> 
#define  Up     PIND.2
#define  Down   PIND.1
#define  Start  PIND.0
float grade=0.0;                       
unsigned char state=0; 
//___________________________________Display
void display_lcd(){
char display_buffer[33];
lcd_clear();   
sprintf(display_buffer,"Degree=%+3.1f\xdf",grade);
lcd_gotoxy(0,1);
lcd_putsf("Rotation=~"); 
if(state==1) lcd_putsf("Right");    
if(state==2) lcd_putsf("Left ");   
lcd_gotoxy(0,0);   
lcd_puts(display_buffer);   
}
//_____________________________________
void stepper_m(){    
unsigned int i,pulse; 
unsigned char x,y; 
x=0b01110111;    
if(grade<0.0){ 
 pulse=grade/-1.8;
 state=2;
 display_lcd();
 for(i=0;i<pulse;i++){
  PORTB=x;
  y=x;
  x=x>>1;
  y=y<<7;
  x=(x|y);
  delay_ms(50);
 } 
} 
else{
 state=1;
 pulse=grade/1.8;   
 display_lcd();  
 for(i=0;i<pulse;i++){
  PORTB=x;
  y=x;
  x=x<<1;
  y=y>>7;
  x=(x|y);
  delay_ms(50);
  }  
 }  
} 
//__________________________________up
void inc_degree(){
if(grade<360) {
grade+=1.8; 
display_lcd();
delay_ms(200); 
 }
}
//__________________________________Down
void dec_degree(){
if(grade>-360){
grade-=1.8; 
display_lcd();
delay_ms(200);
 }
}   
//___________________________________
void main(){ 
DDRB=0xFF; 
DDRD=0X00;   
lcd_init(16);
display_lcd();
while (1){
if(Up==0)    inc_degree(); 
if(Down==0)  dec_degree(); 
if(Start==0) stepper_m(); 
      };
}
