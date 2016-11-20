int ibyte,val;
int sizes;
char datas[10];
char data[400];
boolean flag1 = false;
float latitud,longitud;

void setup()
{
  // Initialize the serial port.
  Serial.begin(115200);//mientras mas rapido mejor
  Serial2.begin(115200); //Configurar de acuerdo a la velocidad del XBEE
  
     for (int j=0;j<400;j=j+1){
     
     data[j] = 0;  

     }
}

// Our main program loop.
void loop()
{
    
//********************************************************Recepcion de tarea a realizar , vector de acuerdo al tamaño del array que llega **************************************************

//recepcion del SCADA
   if(Serial2.available()>0)
    {
      val=Serial2.read();
        if(val=='x'){
        while(Serial2.available()==0){};
        sizes=(int)Serial2.read();
        while(Serial2.available()==0){};
          int i=0;
          for(i=0;i<sizes;i=i+1){
           data[i]=Serial2.read();
            while(Serial2.available()==0 && (char)data[i]!='y'){
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

float res =(float)a+(float)b/100+(float)c/10000+(float)d/1000000;

return -res;
}

void encontrar(int indice){

  int jj = 8*indice-8; //inicio

     latitud  = integracion_gps((int)data[jj],(int)data[jj+1],(int)data[jj+2],(int)data[jj+3]);
     longitud = integracion_gps((int)data[jj+4],(int)data[jj+5],(int)data[jj+6],(int)data[jj+7]);

     Serial.print("Latitud =  ");
     Serial.print(latitud , 6);
     Serial.print("   Longitud =  ");
     Serial.println(longitud , 6);
      
}     
