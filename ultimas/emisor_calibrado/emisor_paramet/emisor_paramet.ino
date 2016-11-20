//emisor nrf24l01 con Mirf


#include <SPI.h>
#include <Mirf.h>
#include <nRF24L01.h>
#include <MirfHardwareSpiDriver.h>


#define  p 255
#define  k 150

#define PIN_ANALOG_X  1 
#define PIN_ANALOG_Y  0 
int x,y;
int P[2];


int rate[]={0,0,0,0};
 
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
               
// Serial.print(P[0]);
//Serial.print("  ");
//Serial.print(P[1]);
// Serial.println();
  
 
  Mirf.send((byte *) &rate);

  while(Mirf.isSending()){   
  }
 
} 


void pwm(int x,int y, int* P){
 

       x=1023-x;

       if(x<=493){x=map(x,0,493,-p,0);}
       else{x=map(x,494,1023,1,p);}
       if(y<=531){y=map(y,0,531,-p,0);}
       else{y=map(y,532,1023,1,p);} 
   
       if(y<5&&y>-100)y=0;
       if(x<5&&x>-5)x=0;
//   Serial.print("  ");
//  
          Serial.println(x);
//Serial.print("  ");
Serial.println(y);
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
       *(P+1)=map(p-x,p,0,p,k);         
       }
       else if(y<x&&y>0){
       *P=x;
       *(P+1)=map(y-p,0,-p,k,-p);         
       }       
       else if(x>=-y&&y<0){
       *P=-x;
       *(P+1)=map(y+p,p,0,p,-k);         
       }      
       else if(x<-y&&x>0){
       *P=y;
       *(P+1)=map(x-p,0,-p,-k,-p);         
       } 
       else if(x>=y&&x<0){
       *P=map(-p-x,-p,0,-p,-k);
       *(P+1)=y;         
       } 
       else if(x<y&&y<0){
       *P=map(y+p,0,p,-k,p);
       *(P+1)=x;         
       } 
       else if(x<=-y&&y>0){
       *P=map(y-p,-p,0,-p,k);
       *(P+1)=-x;         
       } 
       else if(x>-y&&x<0){
       *P=map(x+p,0,p,k,p);
       *(P+1)=y;         
       }

       }




