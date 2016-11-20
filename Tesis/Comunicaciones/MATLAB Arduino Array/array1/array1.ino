int ibyte,val;
int datas[10];
int data[9];

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
        if(val=='S'){
        while(Serial1.available()==0){};
          int i=0;
          for(i=0;i<9;i=i+1){
           data[i]=Serial1.read();
            while(Serial1.available()==0 && (char)data[i]!='J'){
           };
           } 
         }  
   }
   
   for (int j=0;j<9;j=j+1){
   
   Serial.println((char)data[j]);
   }
}   
