// receptor nrf24l01 con Mirf
 
#include <SPI.h>
#include <Mirf.h>
#include <nRF24L01.h>
#include <MirfHardwareSpiDriver.h>
 
int rate[4];
int rate2[4];

void setup(){
 
  Serial.begin(9600);
  
  Mirf.cePin = 48;             //ce pin on Mega 2560, REMOVE THIS LINE IF YOU ARE USING AN UNO
  Mirf.csnPin = 49;            //csn pin on Mega 2560, REMOVE THIS LINE IF YOU ARE USING AN UNO
  Mirf.spi = &MirfHardwareSpi;
  Mirf.init();
  Mirf.setRADDR((byte *)"serv1");
  Mirf.payload = sizeof(rate);
  Mirf.config();
}
 
void loop(){

     if(!Mirf.isSending() && Mirf.dataReady()){
   
    /*
     * Get load the packet into the buffer.
     */
    
    
  
    Mirf.getData((byte *) &rate2);
    
      Serial.print(rate2[0]);
      Serial.print("  ");
      Serial.print(rate2[1]);
      Serial.print("  ");
      Serial.print(rate2[2]);
      Serial.print("  ");
      Serial.println(rate2[3]);
     
    Mirf.setTADDR((byte *)"clie1");
    
    /*
     * Send the data back to the client.
     */
     
    Mirf.send((byte *) &rate2);
  }
    
 
}
