// Reference the I2C Library
#include <Wire.h>
// Reference the HMC5883L Compass Library
#include <HMC5883L.h>
#include <Math.h>

// Store our compass as a variable.
HMC5883L compass;
// Record any errors that may occur in the compass.
int error = 0;
int set_point = 0;
int val = 0;

#define M1F 8
#define M1B 9
#define M2F 10
#define M2B 11

void setup() {
  // put your setup code here, to run once:
//pinMode(M1F, OUTPUT);
//pinMode(M1B, OUTPUT);
//pinMode(M2F, OUTPUT);
//pinMode(M2B, OUTPUT);

Serial.begin(9600);  
Serial3.begin(9600);  

Wire.begin(); // Start the I2C interface.
compass = HMC5883L(); // Construct a new HMC5883 compass.
error = compass.SetScale(1.3); // Set the scale of the compass.
  
error = compass.SetMeasurementMode(Measurement_Continuous); // Set the measurement mode to Continuous
}

void loop() {

     if(Serial3.available()) {
      // get the new byte:
     
     int inChar = (char)Serial3.read(); 
     Serial.println(inChar);
     
      if (inChar == 49) {
      Serial.println("set_point = 0");
      set_point = 40;
      val = 0;
      } 
      else if (inChar == 50){
      Serial.println("set_point = 90");
      set_point = 90;
      val = 0;
      } 
      else if (inChar == 51){
      Serial.println("set_point = 180");
      set_point = 180;
      val = 0;
      } 
      else if (inChar == 52){
      Serial.println("set_point = 270");
      set_point = 270;
      val = 0;
      
      } 
      else if (inChar == 53){
      Serial.println("set_point = 300");
      val = 300;
      
      } 
    }

  MagnetometerRaw raw = compass.ReadRawAxis();
  // Retrived the scaled values from the compass (scaled to the configured scale).
  MagnetometerScaled scaled = compass.ReadScaledAxis();
  
  // Values are accessed like so:
  int MilliGauss_OnThe_XAxis = scaled.XAxis;// (or YAxis, or ZAxis)

  // Calculate heading when the magnetometer is level, then correct for signs of axis.
  float heading = atan2(scaled.YAxis, scaled.XAxis);

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

  error = abs(set_point - headingDegrees);
  if(error < 5) {
    val=300; //Se considera una tolerancia de 5°
    Serial3.println("LLego");
  }
  else{
     Serial3.println(headingDegrees);
  }


 if(headingDegrees < set_point && val!=300){
  Serial3.print("derecha  ");  
  analogWrite(M1F,100);
  analogWrite(M1B,0);
  analogWrite(M2F,0);
  analogWrite(M2B,100);
 }

 else if(headingDegrees > set_point && val!=300){
  Serial3.print("izquierda  ");  
  analogWrite(M1F,0);
  analogWrite(M1B,100);
  analogWrite(M2F,100);
  analogWrite(M2B,0);
 }
 else{
  Serial.println("ROBOT STOP");
  analogWrite(M1F,0);
  analogWrite(M1B,0);
  analogWrite(M2F,0);
  analogWrite(M2B,0);
  }

}
