//**********************Proyecto domotico ---- Controlador receptor ******************************************************

//Orden asumido, cambiar cuando tenga el orden correcto
//a Abrir ventana
//b Cerrar ventana
//c Abrir puerta
//d Cerrar puerta
//e Abrir persiana
//f Cerrar persiana
//g Prender calefaccion
//h Apagar calefaccion
//i Prender luces
//j Apagar luces
//k Alarma

#include <Stepper.h>

#define calefaccion 44
#define luces 45
#define alarma 46
#define pasos1 200
#define pasos2 200
#define pasos3 200

int ibyte,val;
char comando;
boolean flag;
const int stepsPerRevolution = 200; //número de pasos por vuelta del motor de pasos

Stepper mventana(stepsPerRevolution, 22, 23, 24, 25);
Stepper mpuerta(stepsPerRevolution, 26, 27, 28, 29);
Stepper mpersiana(stepsPerRevolution, 30, 31, 32, 33);

void setup() {

mventana.setSpeed(60); //Seteando velocidad de los stepper
mpuerta.setSpeed(60);
mpersiana.setSpeed(60);

pinMode(calefaccion, OUTPUT);
pinMode(luces, OUTPUT);
pinMode(alarma, OUTPUT);

Serial.begin(9600); //PC para pruebas
Serial2.begin(9600); //Módulo Bluetooth

}

void loop() {


if(Serial2.available()>0){
   val=Serial2.read();
   if(val=='x'){
   while(Serial2.available()==0){};
   comando=Serial2.read();
   Serial.println(comando);
   flag = true;     
    }            
}
   
if(flag){
  
  switch (comando){
    
    case 'a':
    Serial.println("Abrir ventana ");
    mventana.step(pasos1);
    break;
    
    case 'b':
    Serial.println("Cerrar ventana");
    mventana.step(-pasos1);
    break;
  
    case 'c':
    Serial.println("Abrir puerta");
    mpuerta.step(pasos2);
    break;
  
    case 'd':
    Serial.println("Cerrar puerta");
    mpuerta.step(-pasos2);
    break;
  
    case 'e':
    Serial.println("Abrir persiana");
    mpersiana.step(pasos3);
    break;
    
    case 'f':
    Serial.println("Cerrar persiana");
    mpersiana.step(-pasos3);
    break;
    
    case 'g':
    Serial.println("calefaccion on");
    digitalWrite(calefaccion, HIGH);
    break;
    
    case 'h':
    Serial.println("calefaccion off");
    digitalWrite(calefaccion, LOW);
    break;
  
    case 'i':
    Serial.println("Luces on");
    digitalWrite(luces, HIGH);
    break;
  
    case 'j':
    Serial.println("Luces off");
    digitalWrite(luces, LOW);
    break;
  
    case 'k':
    Serial.println("alarma");
    digitalWrite(luces, HIGH);
    delay(3000);
    digitalWrite(luces, LOW);
    break;
  
  }

  flag = false;

}   

}


