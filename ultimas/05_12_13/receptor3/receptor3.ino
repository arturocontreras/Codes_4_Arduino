// receptor nrf24l01 con Mirf
 
#include <SPI.h>
#include <Mirf.h>
#include <nRF24L01.h>
#include <MirfHardwareSpiDriver.h>
 
int rate[4];
 
void setup(){
 
  Serial.begin(9600);
  
  Mirf.cePin = 48;             //ce pin on Mega 2560, REMOVE THIS LINE IF YOU ARE USING AN UNO
  Mirf.csnPin = 49;            //csn pin on Mega 2560, REMOVE THIS LINE IF YOU ARE USING AN UNO
  Mirf.spi = &MirfHardwareSpi;
  Mirf.init();
  Mirf.setTADDR((byte *)"serv1");
  Mirf.payload = sizeof(rate);
  Mirf.config();
}
 
void loop(){
  

  for(int i=0;i<4;i++){rate[i]=3;} 
  
  Mirf.setTADDR((byte *)"serv1");
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
 

