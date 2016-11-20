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
  Mirf.setRADDR((byte *)"clie1");
  Mirf.payload = sizeof(rate);
  Mirf.config();
}
 
void loop(){
  
  Mirf.setRADDR((byte *)"clie1");

  rate[Mirf.payload];
  while(!Mirf.dataReady()){
  }
  Mirf.getData((byte *) &rate);
 
  analogWrite(8,rate[0]);
  analogWrite(9,rate[1]);  
  analogWrite(10,rate[2]);
  analogWrite(11,rate[3]);
  
  Serial.print(rate[0]);
  Serial.print("  ");
  Serial.print(rate[1]);
  Serial.print("  ");
  Serial.print(rate[2]);
  Serial.print("  ");
  Serial.println(rate[3]);
  
  Mirf.setTADDR((byte *)"serv1");

 Mirf.send((byte *) &rate);

  while(Mirf.isSending()){   
  }
  
  delay(100);
}
