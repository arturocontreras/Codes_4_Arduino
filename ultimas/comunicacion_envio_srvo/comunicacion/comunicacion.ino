
#include <Servo.h> 
 
Servo myservo1;  // create servo object to control a servo 
                // a maximum of eight servo objects can be created 
Servo myservo2;  

int ibyte;
int pos1=0,pos2=0,pos1_ant=0,pos2_ant=0,pos=0;
int angulo[2];

void setup()
{
  Serial.begin(9600);
  //delay(2500);
    pinMode(9, OUTPUT);   // sets the pin as output
    myservo1.attach(7);  // attaches the servo on pin 9 to the servo object 
    myservo2.attach(8);
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
    
     pos1 = map(angulo[0], 0, 255, 0, 179); 
     pos2 = map(angulo[1], 0, 255, 0, 179);
   
     
     if(pos1>=pos1_ant){
                for(pos = pos1_ant; pos < pos1; pos += 1)  // goes from 0 degrees to 180 degrees 
                {                                  // in steps of 1 degree 
                   myservo1.write(pos);              // tell servo to go to position in variable 'pos' 
                  delay(30);                       // waits 15ms for the servo to reach the position 
                } 
     }
     else{
                for(pos = pos1_ant; pos > pos1; pos -= 1)  // goes from 0 degrees to 180 degrees 
                {                                  // in steps of 1 degree 
                  myservo1.write(pos);              // tell servo to go to position in variable 'pos' 
                  delay(30);                       // waits 15ms for the servo to reach the position 
                } 
               
     }
  
 
         if(pos2>=pos2_ant){
                for(pos = pos2_ant; pos < pos2; pos += 1)  // goes from 0 degrees to 180 degrees 
                {                                  // in steps of 1 degree 
                   myservo2.write(pos);              // tell servo to go to position in variable 'pos' 
                  delay(30);                       // waits 15ms for the servo to reach the position 
                } 
     }
     else{
                for(pos = pos2_ant; pos > pos2; pos -= 1)  // goes from 0 degrees to 180 degrees 
                {                                  // in steps of 1 degree 
                  myservo2.write(pos);              // tell servo to go to position in variable 'pos' 
                  delay(30);                       // waits 15ms for the servo to reach the position 
                } 
               
     }
        
  pos1_ant=pos1;
  pos2_ant=pos2;
  

  }

}
