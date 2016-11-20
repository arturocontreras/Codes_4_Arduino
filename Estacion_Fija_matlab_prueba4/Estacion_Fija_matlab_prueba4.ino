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
  Mirf.payload = sizeof(rate);
  Mirf.config();
 
   
 }
// 
void loop(){

 
     if(Serial.available()>0)
{
   while(indicador==0) 
  { 
    ibyte=Serial.read();
      if(ibyte=='S'){ 
      while(Serial.available()==0){};
        int i=0;
        for(i=0;i<9;i=i+1){
         rate[i]=Serial.read();
          while(Serial.available()==0){};
         } 
      } 

       
     delay(20);

      Serial.print('S');
      Serial.print((char)rate[0]);
      Serial.print((char)rate[1]);  
      Serial.print((char)rate[2]);
      Serial.print((char)rate[3]);  
      Serial.print((char)rate[4]);
      Serial.print((char)rate[5]);  
      Serial.print((char)rate[6]);
      Serial.print((char)rate[7]);
      Serial.print((char)rate[8]);
      indicador=rate[8];

      
      }
      
  }

//indicador=0;
//  rate[0]=22;
//  rate[1]=23;
//  rate[2]=24;
//  rate[3]=25;
//  
//  rate[4]=32;
//  rate[5]=33;
//  rate[6]=34;
//  rate[7]=35;
//  rate[8]=1;
  
  Mirf.setTADDR((byte *)"serv1");
  Mirf.send((byte *) &rate);
  while(Mirf.isSending()){   
  }
 
 delay(20);
 Mirf.setRADDR((byte *)"clie1");
 
 if(Mirf.dataReady()){
  rate[Mirf.payload];
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
  
 }
 
  delay(50);

 
} 


void pwm(int x,int y, int* P){
 

       x=1023-x;

       if(x<=509){x=map(x,0,509,-p,0);}
       else{x=map(x,510,1023,1,p);}
       if(y<=529){y=map(y,0,529,-p,0);}
       else{y=map(y,530,1023,1,p);} 
   
       if(y<5&&y>-5)y=0;
       if(x<5&&x>-5)x=0;
//    Serial.print(x);
//    Serial.print("  ");
//    Serial.print(y);
//    Serial.println();   
       

       
       
       if(x==0&&y==0){                        //centro
       *P=0;
       *(P+1)=0;         
       }
       else if(x==0){                         //eje y
       *P=y;
       *(P+1)=y; 
       }  
       else if(y==0){                         //eje x
       *P=x;
       *(P+1)=-x;       
       }   
       else if(y>=x&&x>0){
       *P=y;
       *(P+1)=map(p-x,255,0,255,100);         
       }
       else if(y<x&&y>0){
       *P=x;
       *(P+1)=map(y-p,0,-255,100,-255);         
       }       
       else if(x>=-y&&y<0){
       *P=-x;
       *(P+1)=map(y+p,255,0,255,-100);         
       }      
       else if(x<-y&&x>0){
       *P=y;
       *(P+1)=map(x-p,0,-255,-100,-255);         
       } 
       else if(x>=y&&x<0){
       *P=map(-p-x,-255,0,-255,-100);
       *(P+1)=y;         
       } 
       else if(x<y&&y<0){
       *P=map(y+p,0,255,-100,255);
       *(P+1)=x;         
       } 
       else if(x<=-y&&y>0){
       *P=map(y-p,-255,0,-255,100);
       *(P+1)=-x;         
       } 
       else if(x>-y&&x<0){
       *P=map(x+p,0,255,100,255);
       *(P+1)=y;         
       }

       }






