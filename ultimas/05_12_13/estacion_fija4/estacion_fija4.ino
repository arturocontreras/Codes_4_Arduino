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
const int buttonPin = 3;     // the number of the pushbutton pin
int buttonState = 0;         // variable for reading the pushbutton status

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
  pinMode(buttonPin, INPUT);  
}
 
void loop(){
 
   buttonState = digitalRead(buttonPin);

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
  
  if(buttonState == LOW) {      
  
  Mirf.setTADDR((byte *)"serv1");
  

  for(int i=0;i<4;i++){rate[i]=8;} 
  

  Mirf.send((byte *) &rate);

  while(Mirf.isSending()){   
  }
  
   }
  delay(1000);
  
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





