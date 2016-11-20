  
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
    
   
  Serial2.begin(9600);
  }
  
  void loop(){
    
    envio_serial();
    delay(200);
    
  }
  
  void envio_serial(){
    
        Serial2.print('x');
        Serial2.print((char)33);
        Serial2.print((char)34);
        Serial2.print((char)35);
        
  }
  


