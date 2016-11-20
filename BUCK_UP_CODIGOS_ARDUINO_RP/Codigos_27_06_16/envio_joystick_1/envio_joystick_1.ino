#include <SoftwareSerial.h>

//#define maximo 70

SoftwareSerial mySerial(8, 7); // RX, TX

#define joy1 A0 //solo se usa eje y //IZQUIERDA
#define joy2 A3 //DERECHA

//VALORES DE LOS JOYSTICK EN CERO
#define u1 498 
#define u2 522

int joy_an1,joy_an2;
//int u1,u2; //umbrales, valores por defecto
int val1,val2;
int V1F,V1B,V2F,V2B; //valores de velocidad a enviar al receptor
int maximo = 70;
///////////////////////////////////////////

void setup() {
  // initialize both serial ports:
  Serial.begin(115200);
  mySerial.begin(115200); //XBEE
}

void loop() {
  
  joy_an1=analogRead(joy1);
  joy_an2=analogRead(joy2);
  
  //para testeo
//  Serial.print(joy_an1);
//  Serial.print("  ");
//  Serial.println(joy_an2);

  if(digitalRead(3)==HIGH)
  maximo = 20;
  else 
  maximo = 50;
 
  //Joystick 1
  val1 = joy_an1-u1;
  if(val1 >= 0){
    V1F = map(val1,0,1023-u1,0,maximo);
    V1B = 0;
  }
  else{
    V1F = 0;
    V1B = map(-val1,0,u1,0,maximo);
  }

  //Joystick 2
  val2 = joy_an2-u2;
  if(val2 >= 0){
    V2F = map(val2,0,1023-u2,0,maximo);
    V2B = 0;
  }
  else{
    V2F = 0;
    V2B = map(-val2,0,u2,0,maximo);
  }

  Serial.print(V1F);
  Serial.print("  ");
  Serial.print(V1B);
  Serial.print("  ");
  Serial.print(V2F);
  Serial.print("  ");
  Serial.println(V2B);

  mySerial.print("x");
  mySerial.print((char)V1F);
  mySerial.print((char)V1B);
  mySerial.print((char)V2F);
  mySerial.print((char)V2B);
 
  delay(200);

}
