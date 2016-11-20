#include "TinyGPS.h"
#include <Wire.h>
#include <HMC5883L.h>

TinyGPS gps;
HMC5883L compass;

#define GPS_TX_DIGITAL_OUT_PIN 5
#define GPS_RX_DIGITAL_OUT_PIN 6

long startMillis;
long secondsToFirstLocation = 0;

#define DEBUG

float latitude = 0.0;
float longitude = 0.0;
int error = 0;

void setup()
{
  #ifdef DEBUG
  Serial.begin(19200);
  #endif
  
  // Serial1 is GPS
  Serial1.begin(9600);
  
  // prevent controller pins 5 and 6 from interfering with the comms from GPS
  pinMode(GPS_TX_DIGITAL_OUT_PIN, INPUT);
  pinMode(GPS_RX_DIGITAL_OUT_PIN, INPUT);
  
  Wire.begin(); // Start the I2C interface.
  compass = HMC5883L(); // Construct a new HMC5883 compass.
  error = compass.SetScale(1.3); // Set the scale of the compass.
  
  error = compass.SetMeasurementMode(Measurement_Continuous); // Set the measurement mode to Continuous
  
  startMillis = millis();
  Serial.println("Starting");
}

void loop()
{
  readLocation();
  
  MagnetometerRaw raw = compass.ReadRawAxis();
  MagnetometerScaled scaled = compass.ReadScaledAxis();  
  int MilliGauss_OnThe_XAxis = scaled.XAxis;
  float heading = atan2(scaled.YAxis, scaled.XAxis);
  
 // float heading = atan2(scaled.YAxis, scaled.XAxis);

  float declinationAngle = 0.0457;
  heading += declinationAngle;
  
  // Correct for when signs are reversed.
  if(heading < 0)
    heading += 2*PI;
    
  // Check for wrap due to addition of declination.
  if(heading > 2*PI)
    heading -= 2*PI;
   
  // Convert radians to degrees for readability.
  float headingDegrees = heading * 180/M_PI; 
  float x=headingDegrees;
  
  float x_cal=calibracion(x);
  
  x_cal= x_cal+95;
  if( x_cal<0){
  x_cal= x_cal+360;}
  Serial.print("Orientacion Magnetometro ");
  Serial.print(x);
  Serial.print("  Orientacion Calibrada ");
  Serial.println(x_cal);
  
  
}

//--------------------------------------------------------------------------------------------
void readLocation(){
  bool newData = false;
  unsigned long chars = 0;
  unsigned short sentences, failed;

  // For one second we parse GPS data and report some key values
  for (unsigned long start = millis(); millis() - start < 1000;)
  {
    while (Serial1.available())
    {
      int c = Serial1.read();
//      Serial.print((char)c); // if you uncomment this you will see the raw data from the GPS
      ++chars;
      if (gps.encode(c)) // Did a new valid sentence come in?
        newData = true;
    }
  }
  
  if (newData)
  {
    // we have a location fix so output the lat / long and time to acquire
    if(secondsToFirstLocation == 0){
      secondsToFirstLocation = (millis() - startMillis) / 1000;
      Serial.print("Acquired in:");
      Serial.print(secondsToFirstLocation);
      Serial.println("s");
    }
    
    unsigned long age;
    gps.f_get_position(&latitude, &longitude, &age);
    
    latitude == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : latitude;
    longitude == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : longitude;
    
    Serial.print("Location: ");
    Serial.print(latitude, 6);
    Serial.print(" , ");
    Serial.print(longitude, 6);
    Serial.println("");
  }
  
  if (chars == 0){
    // if you haven't got any chars then likely a wiring issue
    Serial.println("Check wiring");
  }
  else if(secondsToFirstLocation == 0){
    // still working
  }
}

float calibracion(float x){
  float y;
  if(0<=x && x<14) y=330+2.1428*x;
  else if(14<=x && x<55) y=1.0944*x-12.573;
  else if(55<=x && x<220) y=0.2864*x+26.716;  
  else if(220<=x && x<350) y=1.7357*x-289.15;
  else if(350<=x && x<=360) y=315+1.5*(x-350);
  return y;
}

