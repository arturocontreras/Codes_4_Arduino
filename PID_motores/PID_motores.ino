
int ibyte;
int velocidades[2];
int m1a=0;
int m1r=0;
int m2a=0;
int m2r=0;//señal para motores
int Encoder_m1=A1;//Analogico 1
int Encoder_m2=A0;//Analogico 0

///////////////
unsigned long lastTime;
double Input1,Input2, Output1,Output2, Setpoint_m1,Setpoint_m2;
double errSum1,errSum2,lastInput1,lastInput2;
double kp1, ki1, kd1;
double kp2, ki2, kd2;
int SampleTime = 1000; // Tiempo de muestreo de 1 segundo.
//////////////

void Compute()
{
unsigned long now = millis();
int timeChange = (now - lastTime);
if(timeChange>=SampleTime)
{
// Calcula todas las variables de errores.
double error1 = Setpoint_m1 - Input1;
errSum1 += error1;
double error2 = Setpoint_m2 - Input2;
errSum2 += error2;

double dInput1 = (Input1 - lastInput1);
double dInput2 = (Input2 - lastInput2);

// Calculamos la función de salida del PID para el motor1.
Output1= kp1 * error1 + ki1 * errSum1 - kd1 * dInput1;

// Calculamos la función de salida del PID para el motor2.
Output2= kp2 * error2 + ki2 * errSum2 - kd2 * dInput2;

// Guardamos el valor de algunas variables para el próximo ciclo de cálculo.
lastInput1 = Input1; //motor1
lastInput2 = Input2; //motor2

lastTime = now;
}
}

void SetTunings_m1(double Kp, double Ki, double Kd) //sintonizando controlador del motor1
{
double SampleTimeInSec = ((double)SampleTime)/1000;
kp1 = Kp;
ki1 = Ki * SampleTimeInSec;
kd1 = Kd / SampleTimeInSec;
}

void SetTunings_m2(double Kp, double Ki, double Kd) //sintonizando controlador del motor2
{
double SampleTimeInSec = ((double)SampleTime)/1000;
kp2 = Kp;
ki2 = Ki * SampleTimeInSec;
kd2 = Kd / SampleTimeInSec;
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
  SetTunings_m1(100, 1, 10);
  SetTunings_m2(100, 1, 10);
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
 Setpoint_m2=velocidades[1];
 
//modelo del movil
// RL1---RL2 
// M1 --- M2

//para testeo
Serial.print((char)Setpoint_m1);
Serial.print((char)Setpoint_m2);
  
// Rutina del controlador PID
Input1=analogRead(Encoder_m1);
Input2=analogRead(Encoder_m2);
Compute();
m1a=Output1;
m2a=Output2;

//ejecucion de pwms
analogWrite(10,m2a);
analogWrite(12,m1a);
}
