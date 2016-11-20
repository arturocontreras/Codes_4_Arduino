int encoder1=0;//Analogico 1
int encoder2=0;//Analogico 0
int cambio=0;
int dir=0;
///////////////////////////////////////////
unsigned long startTime;
unsigned long elapsedTime;
unsigned long oldTime;

double Input, Output, Setpoint_m1;
double errSum =0;
double dInput =0;
double lastInput=0;
double kp,ki,kd;
long referencia=0;
int max_dutty=0;

void SetTunings(double Kp, double Ki, double Kd)
{
double SampleTimeInSec = 5/1000;
kp = Kp;
ki = Ki * SampleTimeInSec;
kd = Kd / SampleTimeInSec;
}

void setup() {
  // initialize both serial ports:
  Serial.begin(115200);
 //pines motor
  pinMode(2, INPUT);   //m2r
  //attachInterrupt(0, blink, CHANGE); //pin2
  attachInterrupt(0, blink, RISING); //pin2
}




void loop() {

// Serial.println(encoder1);
  Serial.println(elapsedTime);
  analogWrite(3,100);
}

void blink()
{
  
  elapsedTime= micros() - oldTime;
  if(digitalRead(9)==LOW)  encoder1+=1;
  else encoder1-=1;
  oldTime = micros();
}
