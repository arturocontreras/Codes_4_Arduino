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
  Serial1.begin(9600);
  
     for (int j=0;j<400;j=j+1){
     
     data[j] = 0.0000000000000000f;  

     }
}

// Our main program loop.
void loop()
{
    
//********************************************************Recepcion de tarea a realizar , vector de acuerdo al tamaño del array que llega **************************************************

//recepcion del Matlab
   if(Serial1.available()>0)
    {
      val=Serial1.read();
        if(val=='x'){
        while(Serial1.available()==0){};
        sizes=(int)Serial1.read();
        while(Serial1.available()==0){};
          int i=0;
          for(i=0;i<sizes;i=i+1){
           data[i]=Serial1.read();
            while(Serial1.available()==0 && (char)data[i]!='y'){
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
