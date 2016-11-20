int ibyte,val;
char datas[10];
char data[16];
boolean flag1 = false;

void setup()
{
  // Initialize the serial port.
  Serial.begin(9600);
  Serial1.begin(9600);
  
}

// Our main program loop.
void loop()
{
    
//********************************************************Recepcion de tarea a realizar , navegacion y vision **************************************************

//recepcion del Matlab
   if(Serial1.available()>0)
    {
      val=Serial1.read();
        if(val=='x'){
        while(Serial1.available()==0){};
          int i=0;
          for(i=0;i<16;i=i+1){
           data[i]=Serial1.read();
            while(Serial1.available()==0 && (char)data[i]!='y'){
           };
           }
          
           flag1 = true;     
         }       
     
   }
   
   if(flag1){
     for (int j=0;j<16;j=j+1){
     
     Serial.println((int)data[j]);
     }
     
     flag1 = false;
   }
}   
