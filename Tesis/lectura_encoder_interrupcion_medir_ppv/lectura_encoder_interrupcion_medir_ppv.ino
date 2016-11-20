//Encoder
#define ppv1 120.0
#define ppv2 120.0
#define ppv3 120.0
#define ppv4 120.0

//Motor pines
#define M1F 6
#define M1B 7
#define M2F 4
#define M2B 5
#define M3F 11
#define M3B 10
#define M4F 9
#define M4B 8

#define vmax 150 //RPMs

//Encoder pines 
#define chA_m1 0
#define chA_m2 0
#define chA_m3 0
#define chA_m4 0

//Interrupciones externas encoder
#define inte1 2
#define inte2 3
#define inte3 0
#define inte4 1

//--------Corrientes -----------------------------
#define I_M1 analogRead(A3)
#define I_M2 analogRead(A2)
#define I_M3 analogRead(A1)
#define I_M4 analogRead(A0)

//Calculo de velocidades por el encoder
unsigned long elapsedTime1,elapsedTime2,elapsedTime3,elapsedTime4;
unsigned long oldTime1,oldTime2,oldTime3,oldTime4;
float velocidad1,velocidad2,velocidad3,velocidad4 ;

//Variables para el controlador
unsigned long lastTime;
double Input1,Input2,Input3,Input4, Output1,Output2,Output3,Output4, Setpoint_m1,Setpoint_m2,Setpoint_m3,Setpoint_m4;
double errSum1,errSum2,errSum3,errSum4, lastInput1,lastInput2,lastInput3,lastInput4;
double kp,ki,kd;
double kp1,kp2,kp3,kp4,ki1,ki2,ki3,ki4,kd1,kd2,kd3,kd4;
int SampleTime = 15; 

//Variables adicionales de comando
long referencia=0;
int max_dutty=0;
int ref_ant=0;

//Recepcion de las referencias
int val;
char setpoint[2];

//Sensor de corriente
int sensorValue_sin_offset = 0;
int corriente_analog = 0;
float voltaje = 12.0;
float corriente_voltaje = 0;
float corriente = 0;

long contador = 0;

void setup() {
  
  Serial.begin(115200);
  Serial1.begin(115200);

 //pines motor  como salida
  pinMode(M1F, OUTPUT);   
  pinMode(M1B, OUTPUT);
  pinMode(M2F, OUTPUT);   
  pinMode(M2B, OUTPUT);
  pinMode(M3F, OUTPUT);   
  pinMode(M3B, OUTPUT);
  pinMode(M4F, OUTPUT);   
  pinMode(M4B, OUTPUT);

  //configuracion de frecuencia de PWM  
  TCCR3B = TCCR3B & B11111000 | B00000011;    // Pines 2/3/5 set timer 3 divisor to 8 for PWM frequency of  3921.16 Hz ----> Queda!
  TCCR4B = TCCR4B & B11111000 | B00000011;    // Pines 6/7/8 set timer 4 divisor to  8 for PWM frequency of  3921.16 Hz
  TCCR2B = TCCR2B & B11111000 | B00000011;    // Pines 9/10 set timer 2 divisor to 8 for PWM frequency of  3921.16 Hz  
  TCCR1B = TCCR1B & B11111000 | B00000011;    // Pines 11/12 set timer 1 divisor to 8 for PWM frequency of  3921.16 Hz
  TCCR0B = TCCR0B & B11111000 | B00000011;  // Pines 4/13 set timer 0 divisor to    64 for PWM frequency of   976.56 Hz (Default)
  
    //attachInterrupt(0, blink, CHANGE); //pin2
  attachInterrupt(inte1, cal_v1, RISING);
  attachInterrupt(inte2, cal_v2, RISING); //pin2
  attachInterrupt(inte3, cal_v3, RISING); //pin2
  attachInterrupt(inte4, cal_v4, RISING); //pin2
  
  delay(5000);
  
}

void loop() {
  Serial.print(velocidad2);
  Serial.print(" ");
  Serial.println(contador);
  analogWrite(M4F,30);
  delay(50);
}


void cal_v1()
{
  elapsedTime1 = micros() - oldTime1; 
  oldTime1 = micros();
  velocidad1   = 60000000.0/(elapsedTime1*ppv1);
  Input1 = map(velocidad1,0,vmax,0,100);
   
}

void cal_v2()
{  
  elapsedTime2 = micros() - oldTime2; 
  oldTime2 = micros();
  velocidad2   = 60000000.0/(elapsedTime2*ppv2);
  Input2 = map(velocidad2,0,vmax,0,100);
  
   if(digitalRead(31)==0) 
  contador++;
  else contador--;

}

void cal_v3()
{
  elapsedTime3 = micros() - oldTime3; 
  oldTime3 = micros();
  velocidad3   = 60000000.0/(elapsedTime3*ppv3);
  Input3 = map(velocidad3,0,vmax,0,100);

}

void cal_v4()
{
  elapsedTime4 = micros() - oldTime4; 
  oldTime4 = micros();
  velocidad4   = 60000000.0/(elapsedTime4*ppv4);
  Input4 = map(velocidad4,0,vmax,0,100);
  
 

}


