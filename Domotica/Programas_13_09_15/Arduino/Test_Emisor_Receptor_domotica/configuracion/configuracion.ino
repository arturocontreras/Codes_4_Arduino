#define pc Serial 
#define blue_emisor Serial3
#define blue_receptor Serial2
#define state1 9

void setup() {

blue_emisor.begin(38400);
blue_receptor.begin(38400);
pc.begin(38400);
pinMode(state1,OUTPUT);
digitalWrite(state1,HIGH);
}

void loop() {
  
  if (pc.available()) {
    blue_emisor.write(pc.read());
  }

  if (blue_emisor.available()) {
    pc.write(blue_emisor.read());
  }


}
