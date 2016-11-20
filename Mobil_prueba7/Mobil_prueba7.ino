
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
float v1=150,v2=150;//señales de salida(control)
float alpha,beta,phi;

int ibyte;
int datas[10];
unsigned long lastTime;

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
//  unsigned long now = millis();
// int timeChange = (now - lastTime);
// Serial.println((int)timeChange);
//
// lastTime=now;

//************************ADQUISICION DE TAREA DE NAVEGACION(COORDENADA GPS FINAL) Y VISION  *********************************************************************************

  
  Mirf.setRADDR((byte *)"clie1");
  if(Mirf.dataReady()){
   Serial.print(lat);
    Serial.print("  ");
    Serial.println(lon);
    
  rate[Mirf.payload];
  while(!Mirf.dataReady()){
  }
  Mirf.getData((byte *) &rate);
  
    int suma=rate[0]+rate[1]+rate[2]+rate[3]+rate[4]+rate[5]+rate[6]+rate[7];
    if( suma<800 && suma>0){
    //lat=-((float)rate[0]+(float)rate[1]/100.000000+(float)rate[2]/10000.000000+(float)rate[3]/1000000.000000);
    lat= integracion_gps(rate[0],rate[1],rate[2],rate[3]);
    //lon=-((float)rate[4]+(float)rate[5]/100.000000+(float)rate[6]/10000.000000+(float)rate[7]/1000000.000000);
    lon= integracion_gps(rate[4],rate[5],rate[6],rate[7]);
    
    Serial.print(lat);
    Serial.print("  ");
    Serial.println(lon);
  
    }
  }
  
  //************************ENVIO DE COORDENADAS(GPS) ACTUAL  *********************************************************************************
 
  rate2[0]=datas[0];
  rate2[1]=datas[1];
  rate2[2]=datas[2];
  rate2[3]=datas[3];
  
  rate2[4]=datas[4];
  rate2[5]=datas[5];
  rate2[6]=datas[6];
  rate2[7]=datas[7];
  rate2[8]=1; //si es 1 detecto imagen objetivo , si es 0 no detecta aun onjetivo.
  
  Mirf.setTADDR((byte *)"serv1");

  Mirf.send((byte *) &rate2);

  while(Mirf.isSending()){   
  }
  


  
}

float integracion_gps(int a , int b , int c , int d){

return -((float)a+(float)b/100.000000+(float)c/10000.000000+(float)d/1000000.000000);  
  
}


