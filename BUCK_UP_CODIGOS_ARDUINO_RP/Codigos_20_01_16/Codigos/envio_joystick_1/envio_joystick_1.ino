#include <SoftwareSerial.h>

SoftwareSerial mySerial(10, 11); // RX, TX

#define joy1 A0 //solo se usa eje y
#define joy2 A1

//VALORES DE LOS JOYSTICK EN CERO
#define u1 500 
#define u2 500

int joy_an1,joy_an2;
//int u1,u2; //umbrales, valores por defecto
int val1,val2;
int V1F,V1B,V2F,V2B; //valores de velocidad a enviar al receptor
///////////////////////////////////////////

void setup() {
  // initialize both serial ports:
  Serial.begin(9600);
  mySerial.begin(9600); //XBEE
}

void loop() {
  
  joy_an1=analogRead(joy1);
  joy_an2=analogRead(joy2);
  
  //para testeo
  Serial.print(joy_an1);
  Serial.print("  ");
  Serial.println(joy_an2);

  //Joystick 1
  val1 = joy_an1-u1;
  if(val1 >= 0){
    V1F = map(val1,0,1023-u1,0,255);
    V1B = 0;
  }
  else{
    V1F = 0;
    V1B = map(-val1,0,u1,0,255);
  }

  //Joystick 2
  val2 = joy_an2-u2;
  if(val2 >= 0){
    V2F = map(val2,0,1023-u2,0,255);
    V2B = 0;
  }
  else{
    V2F = 0;
    V2B = map(-val2,0,u2,0,255);
  }

  Serial.print(V1F);
  Serial.print("  ");
  Serial.print(V1B);
  Serial.print("  ");
  Serial.print(V2F);
  Serial.print("  ");
  Serial.print(V2B);

  mySerial.print("x");
  mySerial.print(V1F);
  mySerial.print(V1B);
  mySerial.print(V2F);
  mySerial.print(V2B);
 
  delay(10);

}
