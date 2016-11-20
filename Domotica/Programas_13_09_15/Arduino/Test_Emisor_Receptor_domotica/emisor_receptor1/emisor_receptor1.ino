#define blue Serial3
#define pc Serial 
#define blue2 Serial2
#define state1 9

void setup() {

blue.begin(38400);
blue2.begin(38400);
pc.begin(38400);
pinMode(state1,OUTPUT);
digitalWrite(state1,HIGH);


blue.write("AT");
blue.write("\n");
blue.write("\r");


delay(3000);

blue.write("AT+LINK=3014,10,91158");
blue.write("\n");
blue.write("\r");


delay(3000);
  
}

void loop() {
  blue.write("aaaak");

   if (blue2.available()) {
    pc.write(blue2.read());
  }


}
