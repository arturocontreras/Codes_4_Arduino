 #include <EtherCard.h>

// ethernet interface mac address, must be unique on the LAN
static byte mymac[] = { 0x74,0x69,0x69,0x2D,0x30,0x31  };
static byte myip[] = { 192,168,0,17};

byte Ethernet::buffer[500]; 
BufferFiller bfill;                   

void setup () {
  if (ether.begin(sizeof Ethernet::buffer, mymac, 53) == 0)
    Serial.println( "Failed to access Ethernet controller");
  ether.staticSetup(myip);

  Serial.begin(9600);
}

static word homePage() {
  long t = millis() / 1000;
  long val = analogRead(A0);
  word h = t / 3600;
  byte m = (t / 60) % 60;
  byte s = t % 60;
  bfill = ether.tcpOffset();
  bfill.emit_p(PSTR(
    "<html>"
    "<meta http-equiv='refresh' content='1'/>"
      "<head><title>"
       "Servidor Arduino"
      "</title></head>"
    "<body>"
    "<h3>"
      "<center>"
      
        "<font color= green size=14>"
         "CONTROL-BOT V0.1"
        "</font>"
      
      "</center>"
    "</h3>"
    "<p><em>"
      "<font color= blue size=4>"
      "Control de robots y domotica.<br />"
      "Usted puede controlar.<br />"
      "</font>"
    "</em></p>"
    "</body>"
    "<h1>"
      "<center>"
      
        "$D$D:$D$D:$D$D <br />"
        "<font color= blue size=8>"
     
         "intensidad de luz: $D <br />"

         "Robot"
        "</font>"
        
      "</center>"
      
    "</h1>"
    
      "<center>"
        "<button>"
        "LED1"
        "</button>"
//         "<button onClick=location.href='./?LED=ON\' style='margin:auto;background-color: #84B1FF;color: snow;padding: 10px;border: 1px solid #3F7CFF;width:65px;'>"
         "<input>"
           "LED2"
         "</input>"
        
      "</center>"
     
"</html>"
),
      h/10, h%10, m/10, m%10, s/10, s%10 , val);
      
  return bfill.position();
}

void loop () {
  word len = ether.packetReceive();
  word pos = ether.packetLoop(len);
  
  if (pos)  // check if valid tcp data is received
    ether.httpServerReply(homePage()); // send web page data

    Serial.println(analogRead(A0));
}


