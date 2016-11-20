

// Reference the I2C Library
#include <Wire.h>
// Reference the HMC5883L Compass Library
#include <HMC5883L.h>
 
#include <SPI.h>
#include <Mirf.h>
#include <nRF24L01.h>
#include <MirfHardwareSpiDriver.h>

// Store our compass as a variable.
HMC5883L compass;
// Record any errors that may occur in the compass.
int error = 0;

int rate[9];
int rate2[9];
float lat,lon;

int ibyte;
int velocidades[11];

// Out setup routine, here we will configure the microcontroller and compass.
void setup()
{
  // Initialize the serial port.
  Serial.begin(9600);
  Serial1.begin(9600);

  Mirf.cePin = 48;             //ce pin on Mega 2560, REMOVE THIS LINE IF YOU ARE USING AN UNO
  Mirf.csnPin = 49;            //csn pin on Mega 2560, REMOVE THIS LINE IF YOU ARE USING AN UNO
  Mirf.spi = &MirfHardwareSpi;
  Mirf.init();
  Mirf.setRADDR((byte *)"serv1");
  Mirf.payload = sizeof(rate);
  Mirf.config();
  
  Wire.begin(); // Start the I2C interface.
  
  compass = HMC5883L(); // Construct a new HMC5883 compass.
  error = compass.SetScale(1.3); // Set the scale of the compass.
  
  error = compass.SetMeasurementMode(Measurement_Continuous); // Set the measurement mode to Continuous
}

// Our main program loop.
void loop()
{
  
    if(Serial1.available()>0)
  {
    ibyte=Serial1.read();
      if(ibyte=='S'){ 
      while(Serial1.available()==0){};
        int i=0;
        for(i=0;i<11;i=i+1){
         velocidades[i]=Serial1.read();
          while(Serial1.available()==0){};
         } 
     } 
    

  Serial.print(velocidades[0]);
  Serial.print("  ");
  Serial.print(velocidades[1]);
  Serial.print("  ");
  Serial.print(velocidades[2]);
  Serial.print("  ");
  Serial.print(velocidades[3]);
  Serial.print("  ");
  Serial.print(velocidades[4]);
  Serial.print("  ");
  Serial.print(velocidades[5]);
  Serial.print("  ");
  Serial.print(velocidades[6]);
  Serial.print("  ");
  Serial.print(velocidades[7]);
  Serial.print("  ");
  Serial.print(velocidades[8]);
  Serial.print("  ");
  Serial.print(velocidades[9]);
  Serial.print("  ");
  Serial.println(velocidades[10]);

//  delay(1000);

}
  
  Mirf.setRADDR((byte *)"clie1");
  if(Mirf.dataReady()){

  rate[Mirf.payload];
  while(!Mirf.dataReady()){
  }
  Mirf.getData((byte *) &rate);
  
    int suma=rate[0]+rate[1]+rate[2]+rate[3]+rate[4]+rate[5]+rate[6]+rate[7];
    if( suma<800 && suma>0){
    lat=-((float)rate[0]+(float)rate[1]/100.000000+(float)rate[2]/10000.000000+(float)rate[3]/1000000.000000);
    lon=-((float)rate[4]+(float)rate[5]/100.000000+(float)rate[6]/10000.000000+(float)rate[7]/1000000.000000);
    Serial.print(lat);
    Serial.print("  ");
    Serial.println(lon);
    }
  }
  
 
  rate2[0]=4500;
  rate2[1]=46;
  rate2[2]=47;
  rate2[3]=25;
  
  rate2[4]=77;
  rate2[5]=76;
  rate2[6]=75;
  rate2[7]=4;
  rate2[8]=0;
  
  Mirf.setTADDR((byte *)"serv1");

  Mirf.send((byte *) &rate2);

  while(Mirf.isSending()){   
  }
  
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

 Serial.println(headingDegrees);
  
  delay(10);




}


