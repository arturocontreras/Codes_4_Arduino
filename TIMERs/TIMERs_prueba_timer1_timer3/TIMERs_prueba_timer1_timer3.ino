
#include "TimerThree.h"
#include "TimerOne.h"

boolean flag1=true;
boolean flag2=true;


void setup()
{
  pinMode(12, OUTPUT);      
  pinMode(A15, OUTPUT);

  cli();//stop interrupts

  Timer1.initialize(1000000);         // initialize timer1, en microsegundos
 // Timer1.pwm(9, 512);                // setup pwm on pin 9, 50% duty cycle
  Timer1.attachInterrupt(callback1);  // attaches callback() as a timer overflow interrupt
  
  Timer3.initialize(1000000);         // initialize timer1, en microsegundos
 // Timer1.pwm(9, 512);                // setup pwm on pin 9, 50% duty cycle
  Timer3.attachInterrupt(callback2);  // attaches callback() as a timer overflow interrupt
  
  sei();//allow interrupts
    
  Serial.begin(9600);


}
 
void callback1()
{
  flag1=!flag1;

  if(flag1) digitalWrite(12, HIGH);
  else      digitalWrite(12, LOW);
}

void callback2()
{
  flag2=!flag2;

  if(flag2) digitalWrite(A15, HIGH);
  else      digitalWrite(A15, LOW);
}
 
 
void loop()
{
  // your program here...
}
