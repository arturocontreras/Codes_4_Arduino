
#include "TimerThree.h"
#include "TimerOne.h"

boolean flag=true;
boolean flag1=true;

boolean flag2=true;
boolean flag3=true;

int contador1=0;
int contador2=0;


void setup()
{
  pinMode(8, OUTPUT);      
  pinMode(A15, OUTPUT);
  pinMode(A14, OUTPUT);      
  pinMode(A0, OUTPUT);
  
  cli();//stop interrupts
   //set timer0 interrupt at 1kHz
  TCCR0A = 0;// set entire TCCR0A register to 0
  TCCR0B = 0;// same for TCCR0B
  TCNT0  = 0;//initialize counter value to 0
  // set compare match register for 2khz increments
  OCR0A = 255;// = (16*10^6) / (2000*64) - 1 (must be <256) //antes para 2KHz estaba con 124
  // turn on CTC mode
  TCCR0A |= (1 << WGM01);
  // Set CS01 and CS00 bits for 64 prescaler
  TCCR0B |= (1 << CS01) | (1 << CS00);   
  // enable timer compare interrupt
  TIMSK0 |= (1 << OCIE0A);
  
 //set timer2 interrupt every 1ms
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
  
  Timer1.initialize(1000000);         // initialize timer1, en microsegundos
 // Timer1.pwm(9, 512);                // setup pwm on pin 9, 50% duty cycle
  Timer1.attachInterrupt(callback1);  // attaches callback() as a timer overflow interrupt
  
  Timer3.initialize(1000000);         // initialize timer1, en microsegundos
 // Timer1.pwm(9, 512);                // setup pwm on pin 9, 50% duty cycle
  Timer3.attachInterrupt(callback3);  // attaches callback() as a timer overflow interrupt
  
  sei();//allow interrupts
    
  Serial.begin(9600);


}
 
void callback1()
{
  flag1=!flag1;

  if(flag1) digitalWrite(8, HIGH);
  else      digitalWrite(8, LOW);
}

void callback3()
{
  flag3=!flag3;

  if(flag3) digitalWrite(A15, HIGH);
  else      digitalWrite(A15, LOW);
}
 
ISR(TIMER0_COMPA_vect) {
   
  //flag1=!flag1;
  contador1++;
  if(contador1==1000){ //como la interrupcion es cada 1ms, para que parpadee cada 1s -- entonces el contador tiene que ser 1000
    if(flag) digitalWrite(A14, HIGH);
    else      digitalWrite(A14, LOW);
    
    contador1=0;
    flag=!flag;
  }
}    

ISR(TIMER2_COMPA_vect) {
   
  //flag1=!flag1;
  contador2++;
  if(contador2==1000){ //como la interrupcion es cada 1ms, para que parpadee cada 1s -- entonces el contador tiene que ser 1000
    if(flag2) digitalWrite(A0, HIGH);
    else      digitalWrite(A0, LOW);
    
    contador2=0;
    flag2=!flag2;
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
