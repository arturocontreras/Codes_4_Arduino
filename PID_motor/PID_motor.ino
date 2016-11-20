
int ibyte;
int velocidades[2];
int m1a=0;
int m1r=0;
int m2a=0;
int m2r=0;//señal para motores
int Encoder_m1=A1;

///////////////
unsigned long lastTime;
double Input, Output, Setpoint_m1;
double errSum, lastInput;
double kp, ki, kd;
int SampleTime = 1000; // Tiempo de muestreo de 1 segundo.
//////////////

void Compute()
{
unsigned long now = millis();
int timeChange = (now - lastTime);
if(timeChange>=SampleTime)
{
// Calcula todas las variables de errores.
double error = Setpoint_m1 - Input;
errSum += error;
double dInput = (Input - lastInput);

// Calculamos la función de salida del PID.
Output= kp * error + ki * errSum - kd * dInput;
// Guardamos el valor de algunas variables para el próximo ciclo de cálculo.
lastInput = Input;
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

///////////////////////////////////////////

void setup() {
  // initialize both serial ports:
  Serial.begin(9600);
  Serial1.begin(9600);
  //pines motor
  pinMode(9, OUTPUT);   //m2r
  pinMode(10, OUTPUT);   //m2a
  pinMode(11, OUTPUT);   //m1r
  pinMode(12, OUTPUT);   //m1a
  SetTunings(100, 1, 10);
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
  }
  
//Asignacion de variables
 Setpoint_m1=velocidades[0];
// Setpoint_m2=velocidades[1];
 
//modelo del movil
// RL1---RL2 
// M1 --- M2

//para testeo
Serial.print((char)m1a);
Serial.print((char)m2a);
  
// Rutina del controlador PID
Input=analogRead(Encoder_m1);
Compute();
m1a=Output;
//ejecucion de pwms
analogWrite(12,m1a);
}
