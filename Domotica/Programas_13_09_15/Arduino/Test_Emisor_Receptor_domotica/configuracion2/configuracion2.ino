#include "SoftwareSerial.h"
#define pc Serial
SoftwareSerial blue_emisor(2, 3);

void setup() {

blue_emisor.begin(38400);
pc.begin(38400);
}

void loop() {
  
  if (pc.available()) {
     blue_emisor.write(pc.read());
  }

  if (blue_emisor.available()) {
    pc.write(blue_emisor.read());
  }


}
