char val,ibyte;
int x1;
int x2;
int data[9];
int rate[9];
int out[2];
int indicador;

void setup()
{
Serial.begin(9600); // Iniciamos el puerto serie a 9600 SIEMPRE, SIEMPRE ,SIEMPRE hay que empezar por esto.
Serial2.begin(9600);
}

void loop()
{
  
  //recepcion del XBEE
 if(Serial2.available()>0)
  {
    val=Serial2.read();
      if(val=='S'){
      while(Serial2.available()==0){};
        int i=0;
        for(i=0;i<9;i=i+1){
         data[i]=Serial2.read();
          while(Serial2.available()==0){
            if(Serial2.read=='J') break;
           // Serial.print("atorado");
         };
         } 
       }  
   
   //enviando al monitor serial
   Serial.print(data[0]);
   Serial.print(" ");
   Serial.print(data[1]);
   Serial.print(" ");
   Serial.print(data[2]);
   Serial.print(" ");
   Serial.print(data[3]);
   Serial.print(" ");
   Serial.print(data[4]);
   Serial.print(" ");
   Serial.print(data[5]);
   Serial.print(" ");
   Serial.print(data[6]);
   Serial.print(" ");
   Serial.print(data[7]);
   Serial.print(" ");
   Serial.println(data[8]);
   
 }     


   Serial2.print((char)11);
   Serial2.print((char)98);
   Serial2.print((char)96);
   Serial2.print((char)74);
   Serial2.print((char)76);
   Serial2.print((char)92);
   Serial2.print((char)40);
   Serial2.print((char)13);
   Serial2.print((char)1);
   delay(200);

   
}



  
