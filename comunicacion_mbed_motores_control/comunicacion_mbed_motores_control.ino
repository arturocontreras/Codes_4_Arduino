
int ibyte;
int Encoder_m1=A1;//Analogico 1
int Encoder_m2=A0;//Analogico 0
//int Input1,Input2;
int m1a=0;
///////////////////////////////////////////
unsigned long lastTime;
double Input1,Input2, Output1,Output2, Setpoint_m1,Setpoint_m2;
double errSum1,errSum2,lastInput1,lastInput2;
double kp1, ki1, kd1;
int SampleTime = 30; // Tiempo de muestreo de 1 segundo.


void Compute()
{
unsigned long now = millis();
int timeChange = (now - lastTime);
if(timeChange>=SampleTime)
{
// Calcula todas las variables de errores.
double error1 = Setpoint_m1 - Input1;
errSum1 += error1;


double dInput1 = (Input1 - lastInput1);

// Calculamos la función de salida del PID para el motor1.
Output1= kp1 * error1 + ki1 * errSum1 - kd1 * dInput1;

// Guardamos el valor de algunas variables para el próximo ciclo de cálculo.
lastInput1 = Input1; //motor1

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



void setup() {
  // initialize both serial ports:
  Serial.begin(9600);
  SetTunings_m1(1, 2, 1);
}

void loop() {
     
//  Setpoint_m1=80;
//  
//    // Rutina del controlador PID
////  Input1=(analogRead(Encoder_m1)-267)/2.15;
//   Input1=(analogRead(Encoder_m1)-267)/2.15;
//  if(Input1<0)Input1=0;
//  
//  Compute();
//  m1a=Output1;
  //saturacion de la señal de control
  //*******************************
  if(m1a>250)m1a=250;
  if(m1a<0)m1a=0;
  analogWrite(10,150);
  analogWrite(12,0);
  analogWrite(11,150);
  delay(3000);
  analogWrite(10,200);
  analogWrite(12,200);
  analogWrite(11,0);
    delay(4000);

  Serial.println("SetPoint   velocidad  control");
  Serial.print(Setpoint_m1);
  Serial.print("     ");
  Serial.print(Input1);//motor1
  Serial.print("     ");
  Serial.println(m1a);//motor1
  delay(50);
}
