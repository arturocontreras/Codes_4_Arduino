
#define pulxrev 60
#define pipi 3.1416

int encoder1=0;//Analogico 1
int encoder2=0;//Analogico 0
int cambio=0;
int dir=0;
///////////////////////////////////////////
unsigned long startTime;
unsigned long elapsedTime;
unsigned long oldTime;
unsigned long lastTime;

double Input, Output, Setpoint_m1;
double freq_pulsos;
double freq;
double errSum =0;
double dInput =0;
double lastInput=0;
double kp,ki,kd;
long referencia=0;
long carrera=0;
int max_dutty=0;
int ref_ant=0;
long car_ant=0;
double velocidad;
int SampleTime = 10; 
int val;


void Compute()
{
  unsigned long now = millis();
  int timeChange = (now - lastTime);
  if(timeChange>=SampleTime)
  {
  // Calcula todas las variables de errores.
      
  double error = referencia-velocidad;
  
  errSum += error;
  
  double dInput = (velocidad - lastInput);
  
  // Calculamos la función de salida del PID.
  Output=  kp * error + ki * errSum - kd * dInput;
  
  //saturacion
  if(Output<0) Output=0;
  if(Output>100) Output=100;
  Output=(Output*255)/100;
  
  // Guardamos el valor de algunas variables para el próximo ciclo de cálculo.
  lastInput = velocidad; 
  
  lastTime = now;
  
    Serial.print((char)referencia);
    Serial.print((char)velocidad);
  }
}

void SetTunings(double Kp, double Ki, double Kd)
{
double SampleTimeInSec = ((double)SampleTime)/1000;
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
  //SetTunings(5, 4, 0); //kp,ki,kd
  //SetTunings(6, 5, 0); //kp,ki,kd
  SetTunings(6.5, 5.5, 0); //kp,ki,kd

  attachInterrupt(0, blink, RISING); //pin2
  elapsedTime=0;
  referencia=0;
}


void loop() {

    if(Serial.available()>0)
  {
    val =Serial.read();
    if(val== 1) referencia=20;
    else if(val== 2) referencia=50;
    else if(val== 3) referencia=100;
    else if(val== 4 ) referencia=150;
    else if(val== 5 ) referencia=200;
    else if(val== 6 ) referencia=250;
    else if(val== 7 ) referencia=ref_ant+10;
    else if(val== 8 ) referencia=ref_ant-10;
    else referencia=0;
    ref_ant=referencia;
    
    referencia = map(referencia,20,250,4,57);

    encoder1=0;
  }

    Compute(); 
    analogWrite(4,Output);    
    analogWrite(3,0);       
        

}

void blink()
{
  if(digitalRead(9)==LOW)  encoder1+=1;
  else encoder1-=1;
  
  elapsedTime= micros() - oldTime;
  oldTime = micros();
  freq_pulsos = 1000000/elapsedTime;
  freq = freq_pulsos/60; //rev/seg
  velocidad = freq ;//RPM
  //velocidad= 2*pipi*freq; //2*pi*f , es la velocidad angular
 // velocidad=map(elapsedTime,200,4000,250,10);
  /* if(elapsedTime>=1415 && elapsedTime < 4000) velocidad=-0.0105*elapsedTime+50;
   else if (elapsedTime>=519 && elapsedTime < 1415)velocidad=-0.0838*elapsedTime+153.76;
   else if (elapsedTime>=0 && elapsedTime < 519)velocidad=-0.574*elapsedTime+408.16;
   else velocidad=0; */
   
}


