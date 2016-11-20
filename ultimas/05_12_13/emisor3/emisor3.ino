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


int rate[]={0,0,0,0};
int rate2[]={0,0,0,0};
  
void setup(){
 
  Serial.begin(9600);
  Mirf.cePin = 48;             
  Mirf.csnPin = 49;           
  Mirf.spi = &MirfHardwareSpi;
  Mirf.init();
  Mirf.setRADDR((byte *)"clie1");
  Mirf.payload = sizeof(rate);
  Mirf.config();
}
 
void loop(){
 

 Mirf.setRADDR((byte *)"clie1");
  
  while(!Mirf.dataReady()){}
  Mirf.getData((byte *) &rate2);
  
  Serial.print(rate2[0]);
  Serial.print("  ");
  Serial.print(rate2[1]);
  Serial.print("  ");
  Serial.print(rate2[2]);
  Serial.print("  ");
  Serial.println(rate2[3]);
   
  delay(20);
  
 
} 


