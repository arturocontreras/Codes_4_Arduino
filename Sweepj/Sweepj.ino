// Sweep
// by BARRAGAN <http://barraganstudio.com> 
// This example code is in the public domain.


#include <Servo.h> 
 
Servo myservo;  // create servo object to control a servo 
                // a maximum of eight servo objects can be created 
Servo myservo2; 
Servo myservo3; 

int pos = 0;    // variable to store the servo position 
 
void setup() 
{ 
  myservo.attach(8);  // attaches the servo on pin 9 to the servo object 
  myservo2.attach(7);
  myservo3.attach(6);
} 
 
 
void loop() 
{ 
  for(pos = 0; pos < 180; pos += 1)  // goes from 0 degrees to 180 degrees 
  {                                  // in steps of 1 degree 
    myservo.write(pos);
    myservo2.write(pos); // tell servo to go to position in variable 'pos' 
    myservo3.write(pos); 
    delay(15);                       // waits 15ms for the servo to reach the position 
  } 
  for(pos = 180; pos>=1; pos-=1)     // goes from 180 degrees to 0 degrees 
  {                                
    myservo.write(pos); 
    myservo2.write(pos);     // tell servo to go to position in variable 'pos' 
    myservo3.write(pos); 
    delay(15);                       // waits 15ms for the servo to reach the position 
  } 
} 
