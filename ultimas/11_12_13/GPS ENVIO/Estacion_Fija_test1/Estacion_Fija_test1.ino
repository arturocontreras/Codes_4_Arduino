//emisor nrf24l01 con Mirf


#include <SPI.h>
#include <Mirf.h>
#include <nRF24L01.h>
#include <MirfHardwareSpiDriver.h>

#define  p 255

#define PIN_ANALOG_X  1 
#define PIN_ANALOG_Y  0 
int x,y;
int P[2];
int ibyte,indicador;

int rate[]={0,0,0,0,0,0,0,0,0};
int rate2[]={0,0,0,0,0,0,0,0,0};

void setup(){
 
  Serial.begin(9600);
  Mirf.cePin = 7;             
  Mirf.csnPin = 8;           
  Mirf.spi = &MirfHardwareSpi;
  Mirf.init();
  Mirf.setRADDR((byte *)"clie1");
  Mirf.payload = sizeof(rate2);
  Mirf.config();
 
   
 }
// 
void loop(){

  rate2[Mirf.payload];
  while(!Mirf.dataReady()){
  }
  Mirf.getData((byte *) &rate2);

  Serial.print(rate2[0]);
  Serial.print("  ");
  Serial.print(rate2[1]);
  Serial.print("  ");
  Serial.print(rate2[2]);
  Serial.print("  ");
  Serial.print(rate2[3]);  
  Serial.print("  ");
  Serial.print(rate2[4]);
  Serial.print("  ");
  Serial.print(rate2[5]);
  Serial.print("  ");
  Serial.print(rate2[6]);
  Serial.print("  ");
  Serial.print(rate2[7]);
  Serial.print("  ");
  Serial.println(rate2[8]);  
  
  delay(20);

 
} 



