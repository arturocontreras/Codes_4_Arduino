
int encoder1=0;//Analogico 1
int encoder2=0;//Analogico 0
int cambio=0;
int dir=0;
///////////////////////////////////////////

void setup() {
  // initialize both serial ports:
  Serial.begin(9600);
 //pines motor
  pinMode(8, INPUT);   //m2r
  pinMode(9, INPUT);   //m2a

}

void loop() {

  int valor=0;
  valor= digitalRead(8);
  dir=digitalRead(9);
  while(valor==HIGH && cambio==1){
    if(dir==LOW)encoder1+=1;
    else encoder1-=1;
    cambio=0;
  }
  if(valor==LOW){
    cambio=1;
  }
  
int error = 300-encoder1;
if(encoder1 < 300) {
analogWrite(2,error);
analogWrite(3,0);}
else {
analogWrite(2,0);
analogWrite(3,error);
}

 Serial.println(encoder1);
 //delay(5);

}
