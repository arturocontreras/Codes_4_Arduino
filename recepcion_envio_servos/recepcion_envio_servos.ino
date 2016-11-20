
#include <Servo.h> 
 
Servo myservo;  // create servo object to control a servo 
                // a maximum of eight servo objects can be created 
                
int ibyte;
int pos=0;
int angulo[2];

void setup()
{
  Serial.begin(9600);
  //delay(2500);
    pinMode(9, OUTPUT);   // sets the pin as output
    myservo.attach(10);  // attaches the servo on pin 9 to the servo object 

}

void loop()
{
  
  if(Serial.available()>0)
  {
    ibyte=Serial.read();
      if(ibyte=='S'){
      while(Serial.available()==0){};
        int i=0;
        for(i=0;i<2;i=i+1){
         angulo[i]=Serial.read();
          while(Serial.available()==0){};
         } 
       }  
       
    Serial.print((char)angulo[0]);
    Serial.print((char)angulo[1]);
    analogWrite(9,ibyte);
    pos = map(ibyte, 0, 255, 0, 179);    
    myservo.write(pos);              // tell servo to go to position in variable 'pos' 

  }

}
