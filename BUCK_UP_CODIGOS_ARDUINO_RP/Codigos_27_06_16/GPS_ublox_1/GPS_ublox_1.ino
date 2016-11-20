#include "TinyGPS.h"

TinyGPS gps;

#define GPS_TX_DIGITAL_OUT_PIN 5
#define GPS_RX_DIGITAL_OUT_PIN 6

long startMillis;
long secondsToFirstLocation = 0;
unsigned long chars = 0;
long tiemposend = 0;

#define DEBUG

float latitude = 0.0;
float longitude = 0.0;
bool newData = false;
int sensorValue=0;
long tiempo = 0;


//****

int a1,b1,c1,d1,a2,b2,c2,d2;
float N1,N2;

//****
void setup()
{

  Serial.begin(9600); 
  Serial1.begin(115200);
  Serial3.begin(9600);// Serial is GPS
  
  // prevent controller pins 5 and 6 from interfering with the comms from GPS
  pinMode(GPS_TX_DIGITAL_OUT_PIN, INPUT);
  pinMode(GPS_RX_DIGITAL_OUT_PIN, INPUT);
  
  startMillis = millis();
  Serial.println("Starting");
}

void loop()
{
  chars = 0;
  unsigned short sentences, failed;
  
    if (newData)
    {     
    unsigned long age;
    gps.f_get_position(&latitude, &longitude, &age);
    
    latitude == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : latitude;
    longitude == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : longitude;
    
    Serial.print("Location: ");
    Serial.print(latitude, 6);
    Serial.print(" , ");
    Serial.print(longitude, 6);
    Serial.print("  ..  ");
    Serial.println(millis()-tiempo);
    
    N1=-latitude*100;
    N2=-longitude*100;
     
    a1=N1/100;
    b1=N1-a1*100;
    c1=N1*100-(a1*10000+b1*100);
    d1=N1*10000-(a1*1000000+b1*10000+c1*100);
    
    a2=N2/100;
    b2=N2-a2*100;
    c2=N2*100-(a2*10000+b2*100);
    d2=N2*10000-(a2*1000000+b2*10000+c2*100);
    
    //tiempo = millis();
    newData = false;
    
    coordenadasToC1();
    
   }
   
//   if(millis()-tiemposend > 1000){ //Envio cada 1s
//        coordenadasToC1();
//        tiemposend = millis();
//   }
   
}

//--------------------------------------------------------------------------------------------

void serialEvent3() { //Evento en el Serial3
      tiempo = millis();

 while (Serial3.available())
    {
      int c = Serial3.read();
    //  Serial.print((char)Serial3.read()); // if you uncomment this you will see the raw data from the GPS
      ++chars;
      if (gps.encode(c)) // Did a new valid sentence come in?
        newData = true;
  }
}

void coordenadasToC1(){
    
    Serial.print(a1);
    Serial.print(" ");
    Serial.print(b1);
    Serial.print(" ");
    Serial.print(c1);
    Serial.print(" ");
    Serial.print(d1);
    Serial.print(" ");
    Serial.print(a2);
    Serial.print(" ");
    Serial.print(b2);
    Serial.print(" ");
    Serial.print(c2);
    Serial.print(" ");
    Serial.print(d2);
    Serial.print(" ");
    Serial.println(latitude + longitude,6);
    
    Serial1.print('x');
    Serial1.print((char)a1);
    Serial1.print((char)b1);
    Serial1.print((char)c1);
    Serial1.print((char)d1);
    Serial1.print((char)a2);
    Serial1.print((char)b2);
    Serial1.print((char)c2);
    Serial1.print((char)d2);
    
}

