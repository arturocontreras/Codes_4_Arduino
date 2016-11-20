// receptor nrf24l01 con Mirf
 
#include <SPI.h>
#include <Mirf.h>
#include <nRF24L01.h>
#include <MirfHardwareSpiDriver.h>
 
int rate[9];
int rate2[9];

 
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
  
  Mirf.setRADDR((byte *)"clie1");
  if(Mirf.dataReady()){

  rate[Mirf.payload];
  while(!Mirf.dataReady()){
  }
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
  }
  
 
  rate2[0]=4500.22;
  rate2[1]=46;
  rate2[2]=47;
  rate2[3]=25;
  
  rate2[4]=77;
  rate2[5]=76;
  rate2[6]=75;
  rate2[7]=4;
  rate2[8]=0;
  
  Mirf.setTADDR((byte *)"serv1");

  Mirf.send((byte *) &rate2);

  while(Mirf.isSending()){   
  }
  
  delay(20);
  

}

