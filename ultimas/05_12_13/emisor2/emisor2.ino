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
  Mirf.cePin = 7;             
  Mirf.csnPin = 8;           
  Mirf.spi = &MirfHardwareSpi;
  Mirf.init();
  Mirf.setRADDR((byte *)"clie1");
  Mirf.payload = sizeof(rate);
  Mirf.config();
}
 
void loop(){
 
  Mirf.setTADDR((byte *)"serv1");
  
  x=analogRead(PIN_ANALOG_X);
  y=analogRead(PIN_ANALOG_Y);

  pwm(x,y,P);
  
  for(int i=0;i<4;i++){rate[i]=0;} 
  
  if(P[0]>0)rate[0]=P[0];
  else rate[1]=-P[0];
  if(P[1]>0)rate[2]=P[1];
  else rate[3]=-P[1]; 
               
 Serial.print(P[0]);
 Serial.print("  ");
 Serial.print(P[1]);
 Serial.println();
  
 
  Mirf.send((byte *) &rate);

  while(Mirf.isSending()){   
  }
  
  Mirf.setRADDR((byte *)"clie1");

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
  Serial.println(rate2[3]);
  
  delay(400);
 
} 


void pwm(int x,int y, int* P){
 

       y=1023-y;

       if(x<=509){x=map(x,0,509,-p,0);}
       else{x=map(x,510,1023,1,p);}
       if(y<=509){y=map(y,0,509,-p,0);}
       else{y=map(y,510,1023,1,p);} 
   
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





