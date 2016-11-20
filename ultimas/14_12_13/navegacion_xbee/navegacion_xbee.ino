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

#define k 4
// Store our compass as a variable.
HMC5883L compass;
// Record any errors that may occur in the compass.
int error = 0;

int rate[9];
int rate2[9];
float lat,lon; //COORDENADAS OBJETIVO RECIBIDOS DESDE LA INTERFAZ
float A[2],F[2]; //COORDENADAS ACTUAL Y FINAL
float v1=150,v2=150;//señales de salida(control)
float alpha,beta,phi;

int ibyte,val;
int datas[10];
int data[9];
unsigned long lastTime;

// Out setup routine, here we will configure the microcontroller and compass.
void setup()
{
  // Initialize the serial port.
  Serial.begin(9600);
  Serial1.begin(9600);
  Serial2.begin(9600);

    //pines motor
  pinMode(9, OUTPUT);   //m2r
  pinMode(10, OUTPUT);   //m2a
  pinMode(11, OUTPUT);   //m1r
  pinMode(12, OUTPUT);   //m1a


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
    
//Recepcion de tarea a realizar , navegacion y vision

//recepcion del XBEE
 if(Serial2.available()>0)
  {
    val=Serial2.read();
      if(val=='S'){
      while(Serial2.available()==0){};
        int i=0;
        for(i=0;i<9;i=i+1){
         data[i]=Serial2.read();
          while(Serial2.available()==0 && (char)data[i]!='J'){
         };
         } 
       }  
   
   //enviando al monitor serial
   Serial.println("Aca esta tu tarea , robot");
   Serial.print(data[0]);
   Serial.print(" ");
   Serial.print(data[1]);
   Serial.print(" ");
   Serial.print(data[2]);
   Serial.print(" ");
   Serial.print(data[3]);
   Serial.print(" ");
   Serial.print(data[4]);
   Serial.print(" ");
   Serial.print(data[5]);
   Serial.print(" ");
   Serial.print(data[6]);
   Serial.print(" ");
   Serial.print(data[7]);
   Serial.print(" ");
   Serial.println(data[8]);
   
 }     
//Recepcion de la data de los sensores , provienen del mbed

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
  Serial.print(datas[0]);
  Serial.print("  ");
  Serial.print(datas[1]);
  Serial.print("  ");
  Serial.print(datas[2]);
  Serial.print("  ");
  Serial.print(datas[3]);
  Serial.print("  ");
  Serial.print(datas[4]);
  Serial.print("  ");
  Serial.print(datas[5]);
  Serial.print("  ");
  Serial.print(datas[6]);
  Serial.print("  ");
  Serial.print(datas[7]);
  Serial.print("  ");
  Serial.print(datas[8]);
  Serial.print("  ");
  Serial.println(datas[9]);

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

  //float declinationAngle = 0.0457;
  float declinationAngle = 0.02118;
  heading += declinationAngle;
  
  // Correct for when signs are reversed.
  if(heading < 0)
    heading += 2*PI;
    
  // Check for wrap due to addition of declination.
  if(heading > 2*PI)
    heading -= 2*PI;
   
  // Convert radians to degrees for readability.
  float headingDegrees = heading * 180/M_PI; 
  
  delay(10);

 
//************************EJECUCION DEL ALGORITMO DE NAVEGACION *********************************************************************************
 A[1]=integracion_gps(datas[4],datas[5],datas[6],datas[7]);
 A[0]=integracion_gps(datas[0],datas[1],datas[2],datas[3]);
 
 
 F[1]=-76.924013;
 F[0]=-11.989674;
 
// F[1]=-80;
// F[0]=-14;
 
 beta=atan2((F[0]-A[0]),(F[1]-A[1]))*57.29582790879777;//en sexagesimales
 float atangente=beta;

 Serial.print("atangente2   "); 
 Serial.print(atangente);
  Serial.print("    ");
 beta=90-beta;//segun el sentido de norte y sentido horario
 if(beta<0) beta=beta+360;
 Serial.print("beta  "); 
 Serial.println(beta);
 
  float x=headingDegrees;
  
  float alpha=calibracion(x);
  
  alpha= alpha+80;
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

  Serial.print("alpha   ");
  Serial.print(alpha);
  Serial.print("  beta  ");
  Serial.print(beta);
  Serial.print("  phi  ");
  Serial.print(phi);
  Serial.print("  v1phi  ");
  Serial.print(v1);
  Serial.print("  v2phi  ");
  Serial.print(v2);
  Serial.print("  v1ult  ");
  Serial.print(datas[8]);
  Serial.print("  v2ult  ");
  Serial.println(datas[9]);
  
float sq_radius;
sq_radius= sq(F[0]-A[0])+sq(F[1]-A[1]);
if(sq_radius < sq(0.00005)){                  //si estan dentro de la vecindad ,  aprox para r=3m , r=0.000032
analogWrite(10,0);
analogWrite(11,0);
Serial.println("El robor se encuentra dentro de la vecindad");    
}
else{


if(datas[8]!=250 || datas[9]!=250){
Serial.print("Hay Obstaculo");
Serial.print("  v1= ");
Serial.print(datas[8]);
Serial.print("  v2= ");
Serial.println(datas[9]);
//
analogWrite(10,datas[9]);
analogWrite(11,datas[8]);

delay(500);
}
else{
analogWrite(10,v2);
analogWrite(11,v1);
}

}


//envio de las coordenadas a la estacion fija
  
   Serial.println("Estoy Fuera :) ");

   Serial2.print((char)datas[0]);
   Serial2.print((char)datas[1]);
   Serial2.print((char)datas[2]);
   Serial2.print((char)datas[3]);
   Serial2.print((char)datas[4]);
   Serial2.print((char)datas[5]);
   Serial2.print((char)datas[6]);
   Serial2.print((char)datas[7]);
   Serial2.print((char)1);

}

float integracion_gps(int a , int b , int c , int d){

return -((float)a+(float)b/100.000000+(float)c/10000.000000+(float)d/1000000.000000);  
  
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


