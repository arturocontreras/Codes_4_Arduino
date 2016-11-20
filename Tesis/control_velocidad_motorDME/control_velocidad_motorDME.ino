#define ppv 24.0

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
double errSum =0;
double dInput =0;
double lastInput=0;
double kp,ki,kd;
long referencia=0;
long carrera=0;
int max_dutty=0;
int ref_ant=0;
long car_ant=0;
float velocidad;
int SampleTime = 5; 
double freq_pulsos;
double freq;



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
  SetTunings(4, 2, 0.01); //kp,ki,kd
  attachInterrupt(0, blink, RISING); //pin2
  elapsedTime=0;
}


void loop() {

    if(Serial.available()>0)
  {
      referencia=Serial.read();
      if(referencia=='1') referencia=20;
      else if(referencia=='2') referencia=50;
      else if(referencia=='3') referencia=100;
      else if(referencia=='4') referencia=150;
      else if(referencia=='5') referencia=200;
      else if(referencia=='6') referencia=250;
      else if(referencia=='7') referencia=ref_ant+10;
      else if(referencia=='8') referencia=ref_ant-10;
      else referencia=0;
      ref_ant=referencia;
      
//      referencia = map(referencia,20,250,4,57);
      encoder1=0;
      
      if(referencia <=10) {
      SampleTime = 2;
      SetTunings(0.1, 4, 0); //kp,ki,kd
      
      }
      else {
      SampleTime = 15;
      SetTunings(0.2, 8, 0); //kp,ki,kd    
      }
      
  }

    Compute(); 
    analogWrite(9,Output);
    analogWrite(3,0);       
        
    Serial.print(referencia);
    Serial.print("              ");
    Serial.print(velocidad,4);
    Serial.print("           ");
    Serial.println(Output);
      
//    if((micros()-oldTime)>50000){
//      velocidad=0;
//    }
    
    analogWrite(9,0);
    analogWrite(3,0);
}

void blink()
{
  elapsedTime = micros() - oldTime; 
  oldTime = micros();
  velocidad   = 60000000.0/(elapsedTime*ppv*20.0);
   
}


