// receptor nrf24l01 con Mirf
 
#include <SPI.h>
#include <Mirf.h>
#include <nRF24L01.h>
#include <MirfHardwareSpiDriver.h>
 
int rate[9];
int rate2[9];
 
void setup(){
 
  Serial.begin(9600);
  
  Mirf.cePin = 7;             //ce pin on Mega 2560, REMOVE THIS LINE IF YOU ARE USING AN UNO
  Mirf.csnPin = 8;            //csn pin on Mega 2560, REMOVE THIS LINE IF YOU ARE USING AN UNO
  Mirf.spi = &MirfHardwareSpi;
  Mirf.init();
  Mirf.setRADDR((byte *)"serv1");
  Mirf.payload = sizeof(rate);
  Mirf.config();
}
 
void loop(){
  
 

 Mirf.setRADDR((byte *)"clie1");
  
  while(!Mirf.dataReady()){}
  Mirf.getData((byte *) &rate2);

//  Serial.print('A');
//  Serial.print((char)rate2[0]);
//  Serial.print((char)rate2[1]);
//  Serial.print((char)rate2[2]);  
//  Serial.print((char)rate2[3]);
//  Serial.print((char)rate2[4]);
//  Serial.print((char)rate2[5]);
//  Serial.print((char)rate2[6]);
//  Serial.print((char)rate2[7]); 

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
   
  rate[0]=8;
  rate[1]=9;
  rate[2]=20;
  rate[3]=22;
  
  rate[4]=33;
  rate[5]=44;
  rate[6]=55;
  rate[7]=66;
  rate[8]=45; //si es 1 detecto imagen objetivo , si es 0 no detecta aun onjetivo.
  
  Mirf.send((byte *) &rate);

  while(Mirf.isSending()){   
  }  
  
  
  delay(20);
 

}
 

