
int velocidades[2];
int ibyte;

void setup() {
  // initialize both serial ports:
  Serial.begin(9600);
  pinMode(9, OUTPUT);   //m2r
  pinMode(10, OUTPUT);   //m2a
  pinMode(11, OUTPUT);   //m1r
  pinMode(12, OUTPUT);   //m1a

}

void loop() {
  
  //Recepcionando los valores de angulo del brazo robotico 
  //enviados por la PC ; sistema de vision
  // TX0 , RX0
 if(Serial.available()>0)
  {
    ibyte=Serial.read();
      if(ibyte=='S'){ 
      while(Serial.available()==0){};
        int i=0;
        for(i=0;i<2;i=i+1){
         velocidades[i]=Serial.read();
          while(Serial.available()==0){};
         } 
    } 
  }
  
      Serial.print('S');
      Serial.print((char)velocidades[0]);
      Serial.print((char)velocidades[1]);  
      
      analogWrite(10,velocidades[1]);
      analogWrite(9,0);
      analogWrite(12,0);
      analogWrite(11,velocidades[0]);
      delay(20);
}
