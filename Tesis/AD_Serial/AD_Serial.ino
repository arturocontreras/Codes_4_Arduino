  
  #include "TimerOne.h"
  #include "TimerThree.h"

  char val,ibyte;
  int sensado1, sensado2, sensado3, sensado4, sensado5, sensado6;
  int contador_tiempo;
  long tiempo;
  long T1, T2, T3, T4, T5, T6;
  boolean flag, envio_enable;
  int data[17];
  
  #define sensor1 A0
  #define sensor2 A1
  #define sensor3 A2
  #define sensor4 A3
  #define sensor5 A4
  #define sensor6 A5
  
  void setup(){
    
    T1 = 2000;
    T2 = 5000;
    T3 = 3000;
    T4 = 7000;
    T5 = 8000;
    T6 = 10000;
    
    cli();//stop interrupts
  
    Timer1.initialize(1000000);         // initialize timer1, en microsegundos, cada 100ms
    Timer1.attachInterrupt(interrupcion1);  // attaches callback() as a timer overflow interrupt
    
    Timer3.initialize(500000);         // initialize timer1, en microsegundos
    // Timer1.pwm(9, 512);                // setup pwm on pin 9, 50% duty cycle
    Timer3.attachInterrupt(interrupcion2);  // attaches callback() as a timer overflow interrupt
  
    sei();//allow interrupts
    
    Serial.begin(9600);
    Serial1.begin(9600);
    Serial2.begin(9600);
  }
  
  void loop(){
    
    recepcion_serial();
    read_sensors();
    envio_rt();
    
  }
  
  void interrupcion1(){ //cada 100ms

    contador_tiempo++;
    tiempo = 100*contador_tiempo;
    flag = true;

  }
  
  void interrupcion2(){ //cada 500ms

    envio_enable = true;
   
  }
  
  void recepcion_serial(){
    
   Timer1.stop();
   Timer3.stop();
   if(Serial2.available()>0)
   {
     val=Serial2.read();
     if(val=='x'){
       while(Serial2.available()==0){};
       int i=0;
       for(i=0;i<17;i=i+1){
         data[i]=Serial2.read();
         while(Serial2.available()==0 && (char)data[i]!='y'){
         };
       } 
     } 
     
   for(int j=0; j< 17; j++){
     Serial.print(data[j]);
     Serial.print("  ");
   }
   
  }
   
   Timer1.resume();
   Timer3.start();
   //interrupts();
    
  }
  
  void envio_rt(){
    
    if(envio_enable){
      Serial1.println("Latitud   ");
      Serial1.println("Longitud  ");
      Serial1.println("Yaw  ");
      Serial1.println("Nivel tanque  ");
      Serial1.println("Ultrasonico   ");
      Serial1.println("Corriente consumida   ");
      Serial1.println("Voltaje bateria   ");
      Serial1.println("Temperatura circuito   ");
      Serial1.println("Emergencia  ");
      
      envio_enable = false;
    }
    
  }
  void read_sensors(){
    //Trabajaremos con interrupción timer 1
    if(flag){ 
      
      if(multiplo_tiempo(tiempo,T1)){
        sensado1 = lectura1();
        Serial.print("Sensor1 mide:  ");
        Serial.println(sensado1);
      }
      if(multiplo_tiempo(tiempo,T2)){
        sensado2 = lectura2();
        Serial.print("Sensor2 mide: ");
        Serial.println(sensado2);
      }
      if(multiplo_tiempo(tiempo,T3)){
        sensado3 = lectura3();
        Serial.print("Sensor3 mide: ");
        Serial.println(sensado3);
      }
      if(multiplo_tiempo(tiempo,T4)){
        sensado4 = lectura4();
        Serial.print("Sensor4 mide: ");
        Serial.println(sensado4);
      }
      if(multiplo_tiempo(tiempo,T5)){
        sensado5 = lectura5();
        Serial.print("Sensor5 mide: ");
        Serial.println(sensado5);
      }
      if(multiplo_tiempo(tiempo,T6)){
        sensado6 = lectura6();
        Serial.print("Sensor6 mide: ");
        Serial.println(sensado6);
      }
      
      flag = false;
    }
  
  }
  
  //Se van a tomar 4 muestras que se van a promediar
  //El mínimo tiempo de intervalo de cada lectura es 100ms
  
  int lectura1(){
    long acumulador1 = 0;
    for(int i = 1; i <=4 ; i++ ){
      acumulador1 += analogRead(sensor1);
      delay(50);
    }   
    return (int)acumulador1/4;
  }
  
  int lectura2(){
    long acumulador2 = 0;
    for(int i = 1; i <=4 ; i++ ){
      acumulador2 += analogRead(sensor2);
      delay(50);
    }
    return (int)acumulador2/4;
  }
  
  int lectura3(){
    long acumulador3 = 0;
    for(int i = 1; i <=4 ; i++ ){
      acumulador3 += analogRead(sensor3);
      delay(50);
    }
    return (int)acumulador3/4;
  }
  
  int lectura4(){
    long acumulador4 = 0;
    for(int i = 1; i <=4 ; i++ ){
      acumulador4 += analogRead(sensor4);
      delay(50);
    }
    return (int)acumulador4/4;
  }
  
  int lectura5(){
    long acumulador5 = 0;
    for(int i = 1; i <=4 ; i++ ){
      acumulador5 += analogRead(sensor5);
      delay(50);
    }
    return (int)acumulador5/4;
  }
  
  int lectura6(){
    long acumulador6 = 0;
    for(int i = 1; i <=4 ; i++ ){
      acumulador6 += analogRead(sensor6);
      delay(50);
    }
    return (int)acumulador6/4;
  }
  
  boolean multiplo_tiempo(long tiempo , int T){
    
    int cociente, resto;
    cociente = tiempo/T;
    resto = tiempo - cociente*T;
    if(resto == 0)
      return true;
    else
      return false;   
  }
  



