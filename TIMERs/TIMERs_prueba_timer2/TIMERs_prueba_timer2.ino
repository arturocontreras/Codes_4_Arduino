
#include "TimerThree.h"
#include "TimerOne.h"


boolean flag1=true;
boolean flag2=true;
int contador=0;

void setup()
{
  pinMode(8, OUTPUT);
  pinMode(A15, OUTPUT);

  cli();//stop interrupts
 //set timer2 interrupt every 128us
  TCCR2A = 0;// set entire TCCR2A register to 0
  TCCR2B = 0;// same for TCCR2B
  TCNT2  = 0;//initialize counter value to 0
  // set compare match register for 7.8khz increments
  OCR2A = 255;// = (16*10^6) / (7812.5*8) - 1 (must be <256)
  // turn on CTC mode
  TCCR2A |= (1 << WGM21);
  // Set CS21 bit for 8 prescaler
  //TCCR2B |= (1 << CS21); 
  // Set CS21 bit for 64 prescaler
  TCCR2B |= (1 << CS22)|(0 << CS21)|(0 << CS20);    
  // enable timer compare interrupt
  TIMSK2 |= (1 << OCIE2A);
  
  sei();//allow interrupts
    
  Serial.begin(9600);


}
 

ISR(TIMER2_COMPA_vect) {
   
  //flag1=!flag1;
  contador++;
  if(contador==1000){ //como la interrupcion es cada 1ms, para que parpadee cada 1s -- entonces el contador tiene que ser 1000
    if(flag1) digitalWrite(8, HIGH);
    else      digitalWrite(8, LOW);
    
    contador=0;
    flag1=!flag1;
  }
}    

 
void loop()
{
  // your program here...
  Serial.println("Ejecutando proceso1");
  delay(1000);
  Serial.println("Ejecutando proceso2");
  delay(1000);

}
