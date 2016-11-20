
#include <Servo.h> 
 
Servo servo1;  // create servo object to control a servo 
Servo servo2;  // create servo object to control a servo 
Servo servo3;  // create servo object to control a servo 
Servo servo4;  // create servo object to control a servo             
Servo servo5;  // create servo object to control a servo 
Servo servo6;  // create servo object to control a servo

//SVB1 -- SVB2/SVB3 -- SVB4 --SVB5--SVB6 //SERVO DE BRAZO

int ibyte;
int pos=0;
int angulo[2];
int velocidades[2];


void setup() {
  // initialize both serial ports:
  Serial.begin(9600);
  Serial1.begin(9600);
  //pines de servo
  servo1.attach(2);  // attaches the servo on pin 10 to the servo object 
  servo2.attach(3);  // attaches the servo on pin 10 to the servo object 
  servo3.attach(4);  // attaches the servo on pin 10 to the servo object 
  servo4.attach(5);  // attaches the servo on pin 10 to the servo object 
  servo5.attach(6);  // attaches the servo on pin 10 to the servo object 
  servo6.attach(7);  // attaches the servo on pin 10 to the servo object 

}

void loop() {
  
  //Recepcionando los valores de angulo del brazo robotico 
  //enviados por la PC ; sistema de vision
  // TX0 , RX0
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
  } 
     
//Recepcionando los valores de velocidad setpoint , enviados por 
//el controlador de navegacion
// TX1 , RX1
 if(Serial1.available()>0)
  {
    ibyte=Serial1.read();
      if(ibyte=='S'){ 
      while(Serial1.available()==0){};
        int i=0;
        for(i=0;i<2;i=i+1){
         velocidades[i]=Serial1.read();
          while(Serial1.available()==0){};
         } 
     }  
  }

}
