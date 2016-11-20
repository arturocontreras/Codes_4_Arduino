
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
  rate2[0]=33;
  rate2[1]=55;
  rate2[2]=77;
  rate2[3]=44;
  
  rate2[4]=55;
  rate2[5]=22;
  rate2[6]=44;
  rate2[7]=33;
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
  
  delay(1000);

}

float integracion_gps(int a , int b , int c , int d){

return -((float)a+(float)b/100.000000+(float)c/10000.000000+(float)d/1000000.000000);  
  
}


