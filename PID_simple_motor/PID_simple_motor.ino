
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
int SampleTime = 100; // Tiempo de muestreo de 1 segundo.
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
if(Output>250) Output=250;
if(Output<0)  Output=0;
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
  SetTunings(5, 0.2, 0.1);
}

void loop() {
  

//Asignacion de variables
 Setpoint_m1=100;
// Setpoint_m2=velocidades[1];
 
//modelo del movil
// RL1---RL2 
// M1 --- M2

//para testeo
  
// Rutina del controlador PID
Input=analogRead(Encoder_m1);
Compute();
m1a=Output;
//ejecucion de pwms
analogWrite(11,m1a);

Serial.print(Input);
Serial.print("  ");
Serial.println(m1a);

}
