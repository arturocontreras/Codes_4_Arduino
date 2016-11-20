//**********************Proyecto domotico ---- Controlador receptor ******************************************************

//Orden asumido, cambiar cuando tenga el orden correcto
//a Abrir puerta
//b Cerrar puerta
//c Abrir ventana
//d Cerrar ventana
//e prender luces
//f apagar luces
//g abrir persiana
//h cerrar persiana
//i encender calefaccion
//j apagar calefaccion
//k Alarma

#include <Stepper.h>

#define calefaccion 32
#define luces 33
#define alarma 34
#define pasos1 200
#define pasos2 200
#define pasos3 200

int ibyte,val;
char comando;
boolean flag;
const int stepsPerRevolution = 200; //número de pasos por vuelta del motor de pasos

Stepper mventana(stepsPerRevolution, 38, 39, 40, 41);
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
Serial3.begin(38400); //Módulo Bluetooth

}

void loop() {


if(Serial3.available()>0){
   val=Serial3.read();
   //Serial.println(val);
   if(val=='x'){
   while(Serial3.available()==0){};
   comando=Serial3.read();
   //Serial.println(comando);
   flag = true;     
    }            
}
   
if(flag){
  
  switch (comando){
    
    case 'a':
    Serial.println("Abrir puerta ");
    mpuerta.step(pasos1);
    break;
    
    case 'b':
    Serial.println("Cerrar puerta");
    mpuerta.step(-pasos1);
    break;
  
    case 'c':
    Serial.println("Abrir ventana");
    mventana.step(pasos2);
    break;
  
    case 'd':
    Serial.println("Cerrar ventana");
    mventana.step(-pasos2);
    break;
  
    case 'e':
    Serial.println("Luces on");
    digitalWrite(luces, HIGH);
    

    break;
    
    case 'f':
    Serial.println("Luces off");
    digitalWrite(luces, LOW);
    
    break;
    
    case 'g':
    Serial.println("Abrir persiana");
    mpersiana.step(pasos3);
    
    break;
    
    case 'h':
    Serial.println("Cerrar persiana");
    mpersiana.step(-pasos3);
   
    break;
  
    case 'i':
    Serial.println("calefaccion on");
    digitalWrite(calefaccion, HIGH);
    
    break;
  
    case 'j':
    Serial.println("calefaccion off");
    digitalWrite(calefaccion, LOW);
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


