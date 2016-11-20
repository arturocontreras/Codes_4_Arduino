
//los pines para los motores , giro hacia adelante son:
//analogWrite(10,255); m2
//analogWrite(11,255); m1

// Reference the I2C Library
#include <Wire.h>
// Reference the HMC5883L Compass Library
#include <HMC5883L.h>
 
#include <SPI.h>
#include <Mirf.h>
#include <nRF24L01.h>
#include <MirfHardwareSpiDriver.h>

#define k 1
// Store our compass as a variable.
HMC5883L compass;
// Record any errors that may occur in the compass.
int error = 0;

int rate[9];
int rate2[9];
int tarea[9];
float lat,lon; //COORDENADAS OBJETIVO RECIBIDOS DESDE LA INTERFAZ
float A[2],F[2]; //COORDENADAS ACTUAL Y FINAL
float v1=150,v2=150;//señales de salida(control)
float alpha,beta,phi;

int ibyte,llegada;
int datas[10];
unsigned long lastTime;

// Out setup routine, here we will configure the microcontroller and compass.
void setup()
{
  // Initialize the serial port.
  Serial.begin(9600);
  Serial1.begin(9600);
  Serial2.begin(9600);

  Mirf.cePin = 48;             //ce pin on Mega 2560, REMOVE THIS LINE IF YOU ARE USING AN UNO
  Mirf.csnPin = 49;            //csn pin on Mega 2560, REMOVE THIS LINE IF YOU ARE USING AN UNO
  Mirf.spi = &MirfHardwareSpi;
  Mirf.init();
  Mirf.setTADDR((byte *)"serv1");
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
  rate2[0]=datas[0];
  rate2[1]=datas[1];
  rate2[2]=datas[2];
  rate2[3]=datas[3];
  
  rate2[4]=datas[4];
  rate2[5]=datas[5];
  rate2[6]=datas[6];
  rate2[7]=datas[7];
  rate2[8]=1; //si es 1 detecto imagen objetivo , si es 0 no detecta aun onjetivo. aun onjetivo.
 
 Serial2.print('S');
 Serial2.print((char)rate2[0]);
 Serial2.print((char)rate2[1]);  
 Serial2.print((char)rate2[2]);
 Serial2.print((char)rate2[3]);  
 Serial2.print((char)rate2[4]);
 Serial2.print((char)rate2[5]);  
 Serial2.print((char)rate2[6]);
 Serial2.print((char)rate2[7]);
 Serial2.print((char)rate2[8]);  
  
      if(Serial2.available()>0)
  {
    llegada=Serial2.read();
      if(llegada=='B'){ 
      while(Serial2.available()==0){};
        int i=0;
        for(i=0;i<9;i=i+1){
         tarea[i]=Serial2.read();
          while(Serial2.available()==0){};
         } 
     } 

 }  

  Serial.print(tarea[0]);
  Serial.print("  ");
  Serial.print(tarea[1]);
  Serial.print("  ");
  Serial.print(tarea[2]);
  Serial.print("  ");
  Serial.print(tarea[3]);  
  Serial.print("  ");
  Serial.print(tarea[4]);
  Serial.print("  ");
  Serial.print(tarea[5]);
  Serial.print("  ");
  Serial.print(tarea[6]);
  Serial.print("  ");
  Serial.print(tarea[7]);
  Serial.print("  ");
  Serial.println(tarea[8]);   
  
   if(Serial1.available()>0)
  {
    ibyte=Serial1.read();
      if(ibyte=='S'){ 
      while(Serial1.available()==0){};
        int i=0;
        for(i=0;i<10;i=i+1){
         datas[i]=Serial1.read();
          while(Serial1.available()==0){};
         } 
     } 


}

//************************ADQUISICION DE DATA DEL MAGNETOMETRO  *********************************************************************************

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

//************************EJECUCION DEL ALGORITMO DE NAVEGACION *********************************************************************************
 A[1]=integracion_gps(datas[4],datas[5],datas[6],datas[7]);
 A[0]=integracion_gps(datas[0],datas[1],datas[2],datas[3]);
 
 
 F[1]=lon;
 F[0]=lat;
 
 beta=atan((F[0]-A[0])/(F[1]-A[1]))*57.29582790879777;//en sexagesimales
 beta=90-beta;//segun el sentido de norte y sentido horario
 
 alpha=headingDegrees;
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
}

float integracion_gps(int a , int b , int c , int d){

return -((float)a+(float)b/100.000000+(float)c/10000.000000+(float)d/1000000.000000);  
  
}


