
#include <SoftwareSerial.h>


SoftwareSerial mySerial(53, 52); // RX, TX

void setup() {
  // initialize both serial ports:
  Serial2.begin(115200);//XBEE
  mySerial.begin(115200); 
  Serial1.begin(115200);//Comunicacion con C1
}

void loop() {
  
//
  if(Serial1.available()>0)
  {    
    Serial2.write(Serial1.read());
  }
  
      
//  Serial2.print(49);
//  Serial2.print(48);
//  Serial2.print(47);

  
 // delay(1000);


}
