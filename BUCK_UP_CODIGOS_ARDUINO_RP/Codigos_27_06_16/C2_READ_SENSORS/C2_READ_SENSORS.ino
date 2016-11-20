  #include <avr/wdt.h>
  #include "TimerOne.h"
  
  int sensado1, sensado2, sensado3, sensado4, sensado5, sensado6;
  int contador_tiempo;
  long tiempo;
  int T1, T2, T3, T4, T5, T6;
  boolean flag;
  
  #define sensor1 A0
  #define sensor2 A1
  #define sensor3 A2
  #define sensor4 A3
  #define sensor5 A4
  #define sensor6 A5
  
  void setup(){
    wdt_disable(); // Desactivar el watchdog mientras se configura
    T1 = 700;
    T2 = 500;
    T3 = 300;
    T4 = 100;
    T5 = 200;
    T6 = 1000;
    
    cli();//stop interrupts
  
    Timer1.initialize(100000);         // initialize timer1, en microsegundos, cada 100ms
    Timer1.attachInterrupt(interrupcion);  // attaches callback() as a timer overflow interrupt
    sei();//allow interrupts
      
    Serial.begin(9600);
    
    wdt_enable(WDTO_2S); // Configurar a dos segundos

  }
  
  void loop(){
    wdt_reset();
    read_sensors();
  }
  
  void interrupcion(){ //cada 100ms
    contador_tiempo++;
    tiempo = 100*contador_tiempo;
    flag = true;
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
        Serial.print("Temp mide: ");
        Serial.println(sensado4);
      }
      if(multiplo_tiempo(tiempo,T5)){
        sensado5 = lectura5();
        Serial.print("humedad mide: ");
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
  
  int lectura1(){ //humedad suelo
    int acumulador1 = 0;
    for(int i = 1; i <=4 ; i++ ){
      acumulador1 += analogRead(sensor1);
      delay(5);
    }   
    return (int)acumulador1/4;
  }
  
  int lectura2(){ //radiacion solar
    int acumulador2 = 0;
    for(int i = 1; i <=4 ; i++ ){
      acumulador2 += analogRead(sensor2);
      delay(5);
    }
    return (int)acumulador2/4;
  }
  
  int lectura3(){ //pH solar
    int acumulador3 = 0;
    for(int i = 1; i <=4 ; i++ ){
      acumulador3 += analogRead(sensor3);
      delay(5);
    }
    return (int)acumulador3/4;
  }
  
  int lectura4(){  //temperatura ambiente
     float acumulador4 = 0;
     acumulador4 = read_temp_amb();
     return (int)acumulador4;
  }
  
  int lectura5(){ //humedad ambiente
    float acumulador5 = 0;
    acumulador5 = read_hum_amb();
    return (int)acumulador5;
  }
  
  int lectura6(){
    int acumulador6 = 0;
    for(int i = 1; i <=4 ; i++ ){
      acumulador6 += analogRead(sensor6);
      delay(5);
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


