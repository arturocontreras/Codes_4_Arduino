#define ppv 320.0

int encoder1=0;//Analogico 1
int encoder2=0;//Analogico 0
int cambio=0;
int dir=0;
///////////////////////////////////////////
unsigned long startTime;
unsigned long elapsedTime;
unsigned long oldTime;
float velocidad =0;
long contador = 0;

void setup() {
  // initialize both serial ports:
  Serial.begin(115200);
 //pines motor
  pinMode(2, INPUT);   //m2r
  pinMode(3, INPUT);   //m2r
  //attachInterrupt(0, blink, CHANGE); //pin2
  attachInterrupt(0, blink, RISING); //pin2
  elapsedTime = 0;//para la velocidad inicial = 0
}

void loop() {

// Serial.println(encoder1);
  if((micros() - oldTime)>100000) {
    elapsedTime = 0;
    velocidad = 0;
  }
  if(elapsedTime != 0){
    velocidad   = 60000000.0/(elapsedTime*ppv);
   }
  
  Serial.print(velocidad);
  Serial.print(" RPM   ");
  Serial.println(contador);
  analogWrite(9,80);
}

void blink()
{
  
  elapsedTime = micros() - oldTime; 
  oldTime = micros();
  if(digitalRead(3)==1) 
  contador++;
  else contador--;
}
