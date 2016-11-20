// Sweep
// by BARRAGAN <http://barraganstudio.com> 
// This example code is in the public domain.


#include <Servo.h> 
 
Servo myservo;  // create servo object to control a servo 
                // a maximum of eight servo objects can be created 
 
int pos = 0;    // variable to store the servo position 
int angulo = 0;
int ibyte,val;

void setup() 
{ 
  myservo.attach(7);  // attaches the servo on pin 9 to the servo object 
  Serial.begin(9600);
} 
 
 
void loop() 
{ 
  if(Serial.available()>0)
    {
      val=Serial.read();
        if(val=='x'){
        while(Serial.available()==0){};
        angulo=(int)Serial.read();
        while(Serial.available()==0 && Serial.read()!='y'){};            
         }
       
     myservo.write(angulo);
     }
     
   
} 
