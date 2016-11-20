#include "TinyGPS.h"

TinyGPS gps;

#define GPS_TX_DIGITAL_OUT_PIN 5
#define GPS_RX_DIGITAL_OUT_PIN 6

long startMillis;
long secondsToFirstLocation = 0;
unsigned long chars = 0;

#define DEBUG

float latitude = 0.0;
float longitude = 0.0;
bool newData = false;
int sensorValue=0;

void setup()
{

  Serial.begin(9600); 
  
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
    Serial.println("");
    
    newData = false;
   }
   
}

//--------------------------------------------------------------------------------------------

void serialEvent3() { //Evento en el Serial3
 while (Serial3.available())
    {
      int c = Serial3.read();
    //  Serial.print((char)Serial3.read()); // if you uncomment this you will see the raw data from the GPS
      ++chars;
      if (gps.encode(c)) // Did a new valid sentence come in?
        newData = true;
  }
}

