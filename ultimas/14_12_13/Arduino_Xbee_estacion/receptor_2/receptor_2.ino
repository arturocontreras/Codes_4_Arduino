char val;
int x1;
int x2;
int set_point[4];
int out[2];

void setup()
{
Serial.begin(9600); // Iniciamos el puerto serie a 9600 SIEMPRE, SIEMPRE ,SIEMPRE hay que empezar por esto.
Serial1.begin(9600);
}

void loop()
{
  
  //recepcion del XBEE
  if(Serial1.available()>0)
  {
    val=Serial1.read(); 
   //enviando al monitor serial
   Serial.println(val);
   
 }     

   Serial1.print((char)20);
   Serial1.print((char)21);
   Serial1.print((char)22);
   Serial1.print((char)23);
   Serial1.print((char)24);
   Serial1.print((char)25);
   Serial1.print((char)26);
   Serial1.print((char)27);
   Serial1.print((char)28);
   delay(100);

   
}



  
