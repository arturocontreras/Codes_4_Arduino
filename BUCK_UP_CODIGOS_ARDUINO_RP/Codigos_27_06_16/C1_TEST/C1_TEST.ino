
#include <SoftwareSerial.h>


//SoftwareSerial mySerial(53, 52); // RX, TX

void setup() {
  // initialize both serial ports:
  Serial3.begin(115200);//XBEE
  Serial1.begin(115200);//Comunicacion con C1
}

void loop() {
  
//
  if(Serial3.available()>0)
  {    
    Serial.write(Serial3.read());
  }
  

}
