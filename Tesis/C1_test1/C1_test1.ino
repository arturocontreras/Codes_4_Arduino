  
  #include "TimerOne.h"
  #include "TimerThree.h"

  char val,ibyte;
  int sensado1, sensado2, sensado3, sensado4, sensado5, sensado6;
  int contador_tiempo;
  long tiempo;
  long T1, T2, T3, T4, T5, T6;
  boolean flag, envio_enable;
  //int data[17];
  
  //
  int sizes;
  char data[400];
  boolean flag1 = false;
  float latitud,longitud;
  //
  
  #define sensor1 A0
  #define sensor2 A1
  #define sensor3 A2
  #define sensor4 A3
  #define sensor5 A4
  #define sensor6 A5
  
  void setup(){
    
    
    Serial.begin(9600);
    Serial1.begin(9600);
    Serial2.begin(9600);
    

  }
  
  void loop(){
    recepcion_serial();
    delay(10);
    
  }
  
 
  
 void recepcion_serial(){
  
   if(Serial2.available()>0)
   {
     val=Serial2.read(); 
     
     Serial.print(val);     

  }
   
}
  
  
