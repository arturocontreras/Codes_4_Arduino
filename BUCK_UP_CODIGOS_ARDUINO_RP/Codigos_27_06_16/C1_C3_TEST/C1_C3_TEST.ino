#include <SoftwareSerial.h>
#define vel 15

SoftwareSerial mySerial(53, 52); // RX, TX

void setup() {
  // initialize both serial ports:
  Serial2.begin(115200);  //de XBEE
  mySerial.begin(115200); //C3
  Serial1.begin(115200);  //C2
  Serial.begin(115200);
}

void loop() {
  

  if(Serial2.available()>0) {   
    //mySerial.write(Serial2.read()); //Con esto se envia directamente los valores del joystick al C3
    char bytes = Serial2.read();
    switch(bytes){
    case 'w':
      Serial.println("s");
      mySerial.print("x");
      mySerial.print((char)vel);
      mySerial.print((char)0);
      mySerial.print((char)vel);
      mySerial.print((char)0); 
      break;
    case 's':
      Serial.println("s");
      mySerial.print("x");
      mySerial.print((char)0);
      mySerial.print((char)vel);
      mySerial.print((char)0);
      mySerial.print((char)vel); 
      break;
    case 'a':
      Serial.println("s");
      mySerial.print("x");
      mySerial.print((char)0);
      mySerial.print((char)vel);
      mySerial.print((char)vel);
      mySerial.print((char)0); 
      break;
    case 'd':
      Serial.println("s");
      mySerial.print("x");
      mySerial.print((char)vel);
      mySerial.print((char)0);
      mySerial.print((char)0);
      mySerial.print((char)vel); 
      break;
    case 'q':
      Serial.println("s");
      mySerial.print("x");
      mySerial.print((char)0);
      mySerial.print((char)0);
      mySerial.print((char)0);
      mySerial.print((char)0); 
      break;
    }
      
    
  }
    
  Serial1.println("Hallo");
  delay(100);
  
}
