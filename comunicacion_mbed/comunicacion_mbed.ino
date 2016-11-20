#include <Servo.h> 
 
Servo myservo1;  // create servo object to control a servo 
                // a maximum of eight servo objects can be created 
Servo myservo2;  

int ibyte;
int velocidades[6];
int pos1=0,pos2=0,pos1_ant=0,pos2_ant=0,pos=0;
///////////////////////////////////////////

void setup() {
  // initialize both serial ports:
  Serial.begin(9600);
  Serial1.begin(9600);
  //pines de servo
    myservo1.attach(7);  // attaches the servo on pin 9 to the servo object 
    myservo2.attach(8);
}

void loop() {
  

//Recepcionando los valores de velocidad setpoint , enviados por 
//el controlador de navegacion
// TX1 , RX1
 if(Serial1.available()>0)
  {
    ibyte=Serial1.read();
      if(ibyte=='S'){ 
      while(Serial1.available()==0){};
        int i=0;
        for(i=0;i<7;i=i+1){
         velocidades[i]=Serial1.read();
          while(Serial1.available()==0){};
         } 
     } 
     

  Serial.print(velocidades[0]);
  Serial.print("  ");
  Serial.print(velocidades[1]);
  Serial.print("  ");
  Serial.print(velocidades[2]);
  Serial.print("  ");
  Serial.print(velocidades[3]);
  Serial.print("  ");
  Serial.print(velocidades[4]);
  Serial.print("  ");
  Serial.println(velocidades[5]);
  
  pos1 = map(velocidades[0], 0, 255, 0, 179); 
  pos2 = map(velocidades[1], 0, 255, 0, 179);
   
     
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
  
//  delay(1000);

}
}
