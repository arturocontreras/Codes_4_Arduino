
int encoder1=0;//Analogico 1
int encoder2=0;//Analogico 0
int cambio=0;
int dir=0;
///////////////////////////////////////////
unsigned long startTime;
unsigned long elapsedTime;

void setup() {
  // initialize both serial ports:
  Serial.begin(115200);
 //pines motor
  pinMode(8, INPUT);   //m2r
  pinMode(9, INPUT);   //m2a

}

void loop() {

  int valor=0;
  valor= digitalRead(8);
  dir=digitalRead(9);
  if(digitalRead(8)==HIGH && cambio==1){
    if(digitalRead(9)==LOW)encoder1+=1;
    else encoder1-=1;
    cambio=0;
  }
  if(digitalRead(8)==LOW){
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

startTime = millis();

 Serial.println(encoder1);

elapsedTime= millis() - startTime;
Serial.print("  ");
Serial.println((long)elapsedTime);

 delay(0.01);

}
