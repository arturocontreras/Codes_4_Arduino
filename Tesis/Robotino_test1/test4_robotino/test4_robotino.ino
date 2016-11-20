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
int Kp = 1;
float yaw = 0;
boolean start = true;

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

 do{
  yaw = get_yaw();
  go_yaw(90); 
 //Serial3.println("Bucle");
 } while(abs(error) > 5);
 
 
 delay(4000);

 avanzar();

 delay(4000);

 yaw = get_yaw();
 error = set_point - yaw;
 while(abs(error) > 5){ 
 yaw = get_yaw();
 go_yaw(180);
 //Serial3.println("Bucle");
 }

 delay(4000);

 avanzar();

 delay(4000);


 yaw = get_yaw();
 error = set_point - yaw;
 while(abs(error) > 5){
 yaw = get_yaw();
 go_yaw(270); 
 //Serial3.println("Bucle");
 }

 delay(4000);

 avanzar();

 delay(4000);


 yaw = get_yaw();
 error = set_point - yaw;
 while(abs(error) > 5){
 yaw = get_yaw();
 go_yaw(40); 
 //Serial3.println("Bucle");
 }

 delay(4000);

 avanzar();

 delay(4000);


}


float get_yaw(){
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

  return headingDegrees;
}

void go_yaw(int yaw_deseado){
  
  error = yaw_deseado - yaw;
  if(start == true) {
    if(error > 0){
      if(abs(error)<=180){
          error = yaw_deseado - yaw;
          uc = Kp*error;
          if(uc > 100) uc = 100; //Saturación
          else if(uc < 0) uc = -uc;
          
          Serial3.print("derecha  "); 
          Serial3.print(yaw); 
          Serial3.print("    "); 
          Serial3.println(yaw_deseado);  
          analogWrite(M1F,uc);
          analogWrite(M1B,0);
          analogWrite(M2F,0);
          analogWrite(M2B,uc);
      }
  
      else{
          error = 360-(yaw_deseado - yaw);
          uc = Kp*error;
          if(uc > 100) uc = 100; //Saturación
          else if(uc < 0) uc = -uc;
          
          Serial3.print("izquierda  ");  
          Serial3.print(yaw); 
          Serial3.print("    "); 
          Serial3.println(yaw_deseado);
          analogWrite(M1F,0);
          analogWrite(M1B,uc);
          analogWrite(M2F,uc);
          analogWrite(M2B,0);
      }
    }
    
    else{

      if(abs(error)<=180){
          error = yaw_deseado - yaw;
          uc = Kp*error;
          if(uc > 100) uc = 100; //Saturación
          else if(uc < 0) uc = -uc;
          
          Serial3.print("izquierda  ");
          Serial3.print(yaw); 
          Serial3.print("    "); 
          Serial3.println(yaw_deseado);
          analogWrite(M1F,0);
          analogWrite(M1B,uc);
          analogWrite(M2F,uc);
          analogWrite(M2B,0);
          
      }
  
      else{
          error = 360-(yaw_deseado - yaw);
          uc = Kp*error;
          if(uc > 100) uc = 100; //Saturación
          else if(uc < 0) uc = -uc;
          
          Serial3.print("derecha  ");
          Serial3.print(yaw); 
          Serial3.print("    "); 
          Serial3.println(yaw_deseado);  
          analogWrite(M1F,uc);
          analogWrite(M1B,0);
          analogWrite(M2F,0);
          analogWrite(M2B,uc);
      }
      
    }

  
  }

}

void avanzar(){
  analogWrite(M1F,100);
  analogWrite(M1B,0);
  analogWrite(M2F,100);
  analogWrite(M2B,0);

  delay(500);

  analogWrite(M1F,0);
  analogWrite(M1B,0);
  analogWrite(M2F,0);
  analogWrite(M2B,0);
  
}

