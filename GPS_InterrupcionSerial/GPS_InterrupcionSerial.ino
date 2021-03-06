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

  Serial.begin(9600); // Serial is GPS
  
  Serial1.begin(9600);
  
  // prevent controller pins 5 and 6 from interfering with the comms from GPS
  pinMode(GPS_TX_DIGITAL_OUT_PIN, INPUT);
  pinMode(GPS_RX_DIGITAL_OUT_PIN, INPUT);
  
  startMillis = millis();
  Serial1.println("Starting");
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
    
    Serial1.print("Location: ");
    Serial1.print(latitude, 6);
    Serial1.print(" , ");
    Serial1.print(longitude, 6);
    Serial1.println("");
    
    newData = false;
   }
   
   sensorValue = analogRead(A0); 
    
    Serial1.print("Sensor: ");
    Serial1.println(sensorValue);   
}

//--------------------------------------------------------------------------------------------

void serialEvent() {
 while (Serial.available())
    {
      int c = Serial.read();
//      Serial.print((char)c); // if you uncomment this you will see the raw data from the GPS
      ++chars;
      if (gps.encode(c)) // Did a new valid sentence come in?
        newData = true;
    }
}

