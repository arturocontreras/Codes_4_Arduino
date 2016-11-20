
int ibyte;
int velocidades[2];
int pos1=0,pos2=0,pos1_ant=0,pos2_ant=0,pos=0;
///////////////////////////////////////////

void setup() {
  // initialize both serial ports:
  Serial.begin(9600);
  Serial1.begin(9600);
  pinMode(9, OUTPUT);   //m2r
  pinMode(10, OUTPUT);   //m2a
  pinMode(11, OUTPUT);   //m1r
  pinMode(12, OUTPUT);   //m1a

}

void loop() {
  

//Recepcionando los valores de velocidad setpoint , enviados por 
//el controlador de navegacion
// TX1 , RX1
 if(Serial1.available()>0)
  {
    ibyte=Serial1.read();
      if(ibyte=='S'){ 
      while(Serial1.available()==0){};
        int i=0;
        for(i=0;i<2;i=i+1){
         velocidades[i]=Serial1.read();
          while(Serial1.available()==0){};
         } 
     } 
    

  Serial.print(velocidades[0]);
  Serial.print("  ");
  Serial.println(velocidades[1]);

  analogWrite(10,velocidades[1]);
  analogWrite(9,0);
  analogWrite(12,0);
  analogWrite(11,velocidades[0]);
//  delay(1000);

}
}
