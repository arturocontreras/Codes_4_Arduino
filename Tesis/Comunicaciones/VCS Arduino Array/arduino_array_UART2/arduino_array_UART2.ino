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
  
     for (int j=0;j<8;j=j+1){
     
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
        if(val=='z'){
        while(Serial1.available()==0){};
          int i=0;
          for(i=0;i<8;i=i+1){
           data[i]=Serial1.read();
            while(Serial1.available()==0 && (char)data[i]!='y'){
           };
           }
          
           flag1 = true;     
         }            
   }
   
   
    if(flag1){
     for (int j=0;j<8;j++){
     Serial.print((int)data[j]);
     Serial.print("     ");
     }
     Serial.println("");
     flag1 = false;
   }

   

}

