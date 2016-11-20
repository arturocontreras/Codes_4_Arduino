
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
float lat,lon; //COORDENADAS OBJETIVO RECIBIDOS DESDE LA INTERFAZ
float A[2],F[2]; //COORDENADAS ACTUAL Y FINAL
float v1=150,v2=150;//seÃ±ales de salida(control)
float alpha,beta,phi;

int ibyte,llegada;
int datas[10];
unsigned long lastTime;

// Out setup routine, here we will configure the microcontroller and compass.
void setup()
{
  // Initialize the serial port.
  Serial.begin(9600);
  Serial2.begin(9600); //RX 17 , TX 16

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
  Mirf.send((byte *) &rate2);

  while(Mirf.isSending()){   
  }  
  
  delay(50);
  
  while(!Mirf.dataReady()){}
  Mirf.getData((byte *) &rate);

  Serial.print(rate[0]);
  Serial.print("  ");
  Serial.print(rate[1]);
  Serial.print("  ");
  Serial.print(rate[2]);
  Serial.print("  ");
  Serial.print(rate[3]);  
  Serial.print("  ");
  Serial.print(rate[4]);
  Serial.print("  ");
  Serial.print(rate[5]);
  Serial.print("  ");
  Serial.print(rate[6]);
  Serial.print("  ");
  Serial.print(rate[7]);
  Serial.print("  ");
  Serial.println(rate[8]);   
  
  Serial2.print('B');
  Serial2.print((char)rate[0]);
  Serial2.print((char)rate[1]);
  Serial2.print((char)rate[2]);
  Serial2.print((char)rate[3]);  
  Serial2.print((char)rate[4]);
  Serial2.print((char)rate[5]);
  Serial2.print((char)rate[6]);
  Serial2.print((char)rate[7]);
  Serial2.print((char)rate[8]);   
  
   if(Serial2.available()>0)
{
    llegada=Serial2.read();
      if(llegada=='S'){ 
      while(Serial2.available()==0){};
        int i=0;
        for(i=0;i<9;i=i+1){
         rate2[i]=Serial2.read();
          while(Serial2.available()==0){};
         } 
       }   
  }

  
}

float integracion_gps(int a , int b , int c , int d){

return -((float)a+(float)b/100.000000+(float)c/10000.000000+(float)d/1000000.000000);  
  
}



