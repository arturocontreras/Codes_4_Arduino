#include <SoftwareSerial.h>

SoftwareSerial mySerial(10, 11); // RX, TX

int ibyte,val;
int sizes;
char datas[10];
char data[400];
boolean flag1 = false;
float latitud,longitud;



void setup()
{
  // Initialize the serial port.
  Serial.begin(9600);
  mySerial.begin(9600);
  
     for (int j=0;j<400;j=j+1){
     
     data[j] = 0.0000000000000000f;  

     }
}

// Our main program loop.
void loop()
{
    
//********************************************************Recepcion de tarea a realizar , vector de acuerdo al tamaño del array que llega **************************************************

//recepcion del Matlab
   if(mySerial.available()>0)
    {
      val=mySerial.read();
        if(val=='x'){
        while(mySerial.available()==0){};
        sizes=(int)mySerial.read();
        while(mySerial.available()==0){};
          int i=0;
          for(i=0;i<sizes;i=i+1){
           data[i]=mySerial.read();
            while(mySerial.available()==0 && (char)data[i]!='y'){
           };
           }
          
           flag1 = true;     
         }            
   }
   
   
    if(flag1){
     for (int j=0;j<sizes;j=j+8){
       
     latitud  = integracion_gps((int)data[j],(int)data[j+1],(int)data[j+2],(int)data[j+3]);
     longitud = integracion_gps((int)data[j+4],(int)data[j+5],(int)data[j+6],(int)data[j+7]);
     Serial.print("     ");
     Serial.print((int)data[j]);
     Serial.print(" ");
     Serial.print((int)data[j+1]);
     Serial.print(" ");
     Serial.print((int)data[j+2]);
     Serial.print(" ");
     Serial.print((int)data[j+3]);
     Serial.print(" ");
     Serial.print((int)data[j+4]);
     Serial.print(" ");
     Serial.print((int)data[j+5]);
     Serial.print(" ");
     Serial.print((int)data[j+6]);
     Serial.print(" ");
     Serial.println((int)data[j+7]);
     
     Serial.print("P");
     Serial.print(j/8 +1);
     Serial.print(":  Latitud =  ");
     Serial.print(latitud , 6);
     Serial.print("   Longitud =  ");
     Serial.println(longitud , 6 );
     }
     
     flag1 = false;
   }
   
      if(Serial.available()>0)
    {
      ibyte=(int)Serial.read();
      encontrar(ibyte-48);      
    }
   

}

float integracion_gps(int a , int b , int c , int d){

return -((float)a+(float)b/100.0000000000+(float)c/10000.0000000000+(float)d/1000000.0000000000);  
  
}

void encontrar(int indice){

  int jj = 8*indice-8; //inicio

     latitud  = integracion_gps((int)data[jj],(int)data[jj+1],(int)data[jj+2],(int)data[jj+3]);
     longitud = integracion_gps((int)data[jj+4],(int)data[jj+5],(int)data[jj+6],(int)data[jj+7]);

     Serial.print("Latitud =  ");
     Serial.print(latitud , 10);
     Serial.print("   Longitud =  ");
     Serial.println(longitud , 10);
      
}     
