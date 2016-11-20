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
int rate2[]={0,0,0,0,0,0,0,0,0};
  
void setup(){
 
  Serial.begin(9600);
  Mirf.cePin = 48;             
  Mirf.csnPin = 49;           
  Mirf.spi = &MirfHardwareSpi;
  Mirf.init();
  Mirf.setTADDR((byte *)"clie1");
  Mirf.payload = sizeof(rate);
  Mirf.config();
}
 
void loop(){

  
   for(int i=0;i<9;i++){rate[i]=3;} 
  
 // Mirf.setTADDR((byte *)"serv1");
  Mirf.send((byte *) &rate);
  while(Mirf.isSending()){   
  }
  
    
//    Mirf.setRADDR((byte *)"clie1");
//    if(Mirf.dataReady()){
//       Mirf.getData((byte *) &rate);
//       delay(5);
//       Mirf.setTADDR((byte *)"serv1");
//       Mirf.send((byte *) &rate);
//       while(Mirf.isSending()){   
//       }
//   }
 
   delay(20);
 
} 


