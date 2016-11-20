char val;
int x1;
int x2;
int set_point[4];
int out[2];

void setup()
{
Serial.begin(9600); // Iniciamos el puerto serie a 9600 SIEMPRE, SIEMPRE ,SIEMPRE hay que empezar por esto.
Serial1.begin(9600);
Serial3.begin(9600);

pinMode(13,OUTPUT);
}

void loop()
{
  
  //recepcion del XBEE
  if(Serial1.available()>0)
  {
    val=Serial1.read();
      if(val=='S'){
      while(Serial1.available()==0){};
        int i=0;
        for(i=0;i<4;i=i+1){
         set_point[i]=Serial1.read();
          while(Serial1.available()==0){};
         } 
       }  
   
   //enviando al monitor serial
   Serial.print(set_point[0]);
   Serial.print(" ");
   Serial.print(set_point[1]);
   Serial.print(" ");
   Serial.print(set_point[2]);
   Serial.print(" ");
   Serial.println(set_point[3]);
   
 }     
  analogWrite(4,set_point[0]);
  analogWrite(5,set_point[1]);;  
  analogWrite(6,set_point[2]);
  analogWrite(7,set_point[3]);
  
  analogWrite(8,set_point[0]);
  analogWrite(9,set_point[1]);;  
  analogWrite(10,set_point[2]);
  analogWrite(11,set_point[3]);
   
}



  
