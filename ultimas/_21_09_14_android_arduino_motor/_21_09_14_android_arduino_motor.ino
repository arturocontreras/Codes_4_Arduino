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
int ref_ant=0;

void SetTunings(double Kp, double Ki, double Kd)
{
double SampleTimeInSec = 5/1000;
kp = Kp;
ki = Ki * SampleTimeInSec;
kd = Kd / SampleTimeInSec;
}

void setup() {
  // initialize both serial ports:
  Serial1.begin(9600);
  Serial.begin(115200);
 //pines motor
  pinMode(2, INPUT);   //m2r
  //attachInterrupt(0, blink, CHANGE); //pin2
  SetTunings(1.5, 1.2, 0); //kp,ki,kd
  attachInterrupt(0, blink, RISING); //pin2
}




void loop() {

  if(Serial1.available()>0)
  {
    referencia=Serial1.read();
 
  }
  
  long error = referencia-encoder1;
  errSum += error;
  dInput = encoder1 - lastInput;
  
  Output=  kp * error + ki * errSum ;
 
   if(abs(error)>10) max_dutty=250;
    else  max_dutty=250;
     
      if(Output >=0) {
        if(Output >255) Output =255;
        Output=map(Output,0,255,0,max_dutty);
        analogWrite(4,Output);
        analogWrite(3,0);
      }
      else if(Output <0) { 
        if(Output <-255) Output =-255;
        Output=map(-Output,0,255,0,max_dutty);
        analogWrite(4,0);
        analogWrite(3,Output);
      }

  lastInput = encoder1;
  
//analogWrite(4,50);
 Serial.print(encoder1);
 Serial.print(" ");
 Serial.println(referencia);
}

void blink()
{
  
 // elapsedTime= micros() - oldTime;
  if(digitalRead(9)==LOW)  encoder1+=1;
  else encoder1-=1;
 // oldTime = micros();
}
