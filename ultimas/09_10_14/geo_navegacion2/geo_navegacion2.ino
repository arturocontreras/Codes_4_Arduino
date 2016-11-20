#include "TinyGPS.h"
#include <Wire.h>
#include <HMC5883L.h>

TinyGPS gps;
HMC5883L compass;

#define GPS_TX_DIGITAL_OUT_PIN 5
#define GPS_RX_DIGITAL_OUT_PIN 6
#define DEBUG
#define k 2
#define PIN_INDICADOR 53

long startMillis;
long secondsToFirstLocation = 0;
float latitude = 0.0;
float longitude = 0.0;
float x = 0.0;
float A[2],F[2]; //COORDENADAS ACTUAL Y FINAL
int error = 0;
float alpha,beta,phi; //variables de navegación
float v1=150,v2=150;//señales de salida(control)


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
  pinMode(53, OUTPUT);   //m2r
  
  Wire.begin(); // Start the I2C interface.
  compass = HMC5883L(); // Construct a new HMC5883 compass.
  error = compass.SetScale(1.3); // Set the scale of the compass.
  
  error = compass.SetMeasurementMode(Measurement_Continuous); // Set the measurement mode to Continuous
  
  startMillis = millis();
  Serial.println("Starting");
}

void loop()
{
  
//******************* LECTURA DEL SENSORES ************************************************************************
 read_gps();
 x=read_compass();

 float x_cal=calibracion(x);  

 Serial.print("Orientacion Magnetometro ");
 Serial.print(x);
 Serial.print("  Orientacion Calibrada ");
 Serial.println(x_cal);
  
 A[1]=longitude; //Coordenada actual
 A[0]=latitude ;//Coordenada actual
 
 //******************* COMIENZA EL ALGORITMO ************************************************************************
 if(A[0]!=0 && A[1]!=0){
 //myled = 1;//indica si el GPS esta enviando valores buenos
 digitalWrite(PIN_INDICADOR, HIGH);   // sets the LED on
 F[1]=-76.924013; //Coordenada objetivo
 F[0]=-11.989674; //Coordenada objetivo
 
 beta=atan2((F[0]-A[0]),(F[1]-A[1]))*57.29582790879777;//en sexagesimales
 beta=90-beta;//segun el sentido de norte y sentido horario
 
   if(beta<0) beta=beta+360;
   
 float alpha=x_cal;
  
 alpha= alpha+65;
    if( alpha<0){
    alpha= alpha+360;}
    else if (alpha>360) alpha=alpha-360;
 
  phi=beta-alpha;     

  //primero sin considerar obstaculos:
  v1=150+k*phi;//asumiendo k=3;
  v2=150-k*phi;//asumiendo k=3;
  
  //Saturacion de las velocidades:
    if(v1>250) v1=250;
    if(v1<0) v1=0;
  
  //Saturacion de las velocidades:
    if(v2>250) v2=250;
    if(v2<0) v2=0;
 
  float sq_radius;
  sq_radius= sq(F[0]-A[0])+sq(F[1]-A[1]);

    if(sq_radius < sq(0.00003)){                  //si estan dentro de la vecindad ,  aprox para r=1.2m , r=0.000032
      analogWrite(10,0);
      analogWrite(11,0);
      Serial.println("El robor se encuentra dentro de la vecindad");    
    }
    else{  
      analogWrite(10,v2);
      analogWrite(11,v1);
      delay(500);
    
    }
    
//******************* PRINT DE VARIABLES DE NAVEGACIÓN ************************************************************************

  Serial.print("alpha   ");
  Serial.print(alpha);
  Serial.print("  beta  ");
  Serial.print(beta);
  Serial.print("  phi  ");
  Serial.print(phi);
  Serial.print("  v1phi  ");
  Serial.print(v1);
  Serial.print("  v2phi  ");
  Serial.println(v2);
 
 }
 else {
  digitalWrite(PIN_INDICADOR, LOW);   // sets the LED off
  Serial.println("Esperando comunicacion con Satelites ...");
 }
 
 
}
  
  
//******************* FUNCIONES UTILIZADAS ************************************************************************

void read_gps(){
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


float read_compass(){
  
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
  
  return headingDegrees;
  
}

