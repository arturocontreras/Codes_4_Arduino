

// Reference the I2C Library
#include <Wire.h>
// Reference the HMC5883L Compass Library
#include <HMC5883L.h>

// Store our compass as a variable.
HMC5883L compass;
// Record any errors that may occur in the compass.
int error = 0;

// Out setup routine, here we will configure the microcontroller and compass.
void setup()
{
  // Initialize the serial port.
  Serial.begin(9600);
  Wire.begin(); // Start the I2C interface.
  compass = HMC5883L(); // Construct a new HMC5883 compass.
  error = compass.SetScale(1.3); // Set the scale of the compass.
  
  error = compass.SetMeasurementMode(Measurement_Continuous); // Set the measurement mode to Continuous
}

// Our main program loop.
void loop()
{
  // Retrive the raw values from the compass (not scaled).
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
  float x=headingDegrees;

  float x_cal=calibracion(x);
  
  x_cal= x_cal+95;
  if( x_cal<0){
  x_cal= x_cal+360;}
 Serial.print(x);
 Serial.print("  ");
 Serial.println(x_cal);


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


