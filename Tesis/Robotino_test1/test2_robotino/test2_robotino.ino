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
long uc = 0;//Señal control
int error_ant = 0; //memoria de error
long tiempo_ant = 0; //memoria de tiempo
long dT = 0; //Variación de tiempo para el controlador
int Ki = 4;
int Kp = 2;

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

//************************************RECEPCION SET_POINT******************************************************************************
     if(Serial3.available()) {
      // get the new byte:
     
     int inChar = (char)Serial3.read(); 
     Serial.println(inChar);
     
      if (inChar == 49) {
      Serial3.println("set_point = 0");
      set_point = 40;
      val = 0;
      } 
      else if (inChar == 50){
      Serial3.println("set_point = 90");
      set_point = 90;
      val = 0;
      } 
      else if (inChar == 51){
      Serial3.println("set_point = 180");
      set_point = 180;
      val = 0;
      } 
      else if (inChar == 52){
      Serial3.println("set_point = 270");
      set_point = 270;
      val = 0;
      
      } 
      else if (inChar == 53){
      Serial3.println("set_point = 300");
      val = 300;
      
      } 

      else if (inChar == 54){
      Serial3.println("Ki = 0");
      Ki = 0;
      } 

      else if (inChar == 55){
      Serial3.println("Ki = 1");
      Ki = 1;
      } 

      else if (inChar == 56){
      Serial3.println("Ki = 2 ");
      Ki = 2;
      } 
    }

//************************************LECTURA MAGNETOMETRO******************************************************************************
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

  //************************************RUTINA DE CONTROL ******************************************************************************
  dT = millis()-tiempo_ant;
  error = set_point - headingDegrees;
  uc = Kp*error + Ki*(error + error_ant)*dT; //Control proporcional integral PI
  error_ant = error; //Guardando error anterior
  tiempo_ant = millis();
  
  if(uc > 100) uc = 100; //Saturación
  else if(uc < 0) uc = -uc;
  
  if(abs(error) < 5) {
    val=300; //Se considera una tolerancia de 5°
    Serial3.println("LLego");
  }
  else{
     Serial3.println(headingDegrees);
  }

 if(headingDegrees < set_point && val!=300){
  Serial3.print("derecha  ");  
  analogWrite(M1F,uc);
  analogWrite(M1B,0);
  analogWrite(M2F,0);
  analogWrite(M2B,uc);
 }

 else if(headingDegrees > set_point && val!=300){
  Serial3.print("izquierda  ");  
  analogWrite(M1F,0);
  analogWrite(M1B,uc);
  analogWrite(M2F,uc);
  analogWrite(M2B,0);
 }
 else{
  Serial3.println("ROBOT STOP");
  analogWrite(M1F,0);
  analogWrite(M1B,0);
  analogWrite(M2F,0);
  analogWrite(M2B,0);
  }

}
