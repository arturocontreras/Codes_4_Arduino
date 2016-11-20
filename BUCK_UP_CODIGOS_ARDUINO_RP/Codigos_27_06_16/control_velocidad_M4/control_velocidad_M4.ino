#define ppv 120.0
//--------Corrientes -----------------------------
#define I_M1 analogRead(A3)
#define I_M2 analogRead(A2)
#define I_M3 analogRead(A1)
#define I_M4 analogRead(A0)

//------Pines PWM Motores -------------------------
#define M1F 7
#define M1B 6
#define M2F 5
#define M2B 4
#define M3F 11
#define M3B 10
#define M4F 9
#define M4B 8

int sensorValue_sin_offset = 0;
int corriente_analog = 0;
float voltaje = 12.0;
float corriente_voltaje = 0;
float corriente = 0;

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
  Serial.println("COMPUTANDO");
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
  
  //pines motor
 Serial.begin(115200);
 pinMode(M1F, OUTPUT);
 pinMode(M1B, OUTPUT);
 pinMode(M2F, OUTPUT);
 pinMode(M2B, OUTPUT);
 pinMode(M3F, OUTPUT);
 pinMode(M3B, OUTPUT);
 pinMode(M4F, OUTPUT);
 pinMode(M4B, OUTPUT);

TCCR3B = TCCR3B & B11111000 | B00000011;    // Pines 2/3/5 set timer 3 divisor to 8 for PWM frequency of  3921.16 Hz ----> Queda!
TCCR4B = TCCR4B & B11111000 | B00000011;    // Pines 6/7/8 set timer 4 divisor to  8 for PWM frequency of  3921.16 Hz
TCCR2B = TCCR2B & B11111000 | B00000011;    // Pines 9/10 set timer 2 divisor to 8 for PWM frequency of  3921.16 Hz  
TCCR1B = TCCR1B & B11111000 | B00000011;    // Pines 11/12 set timer 1 divisor to 8 for PWM frequency of  3921.16 Hz
//TCCR0B = TCCR0B & B11111000 | B00000011;  // Pines 4/13 set timer 0 divisor to    64 for PWM frequency of   976.56 Hz (Default)
//https://arduino-info.wikispaces.com/Arduino-PWM-Frequency

 pinMode(2, INPUT);   
 pinMode(3, INPUT);
 //attachInterrupt(0, blink, CHANGE); //pin2
 attachInterrupt(1, blink, RISING); //pin3
 elapsedTime=0;

 SetTunings(0.1, 4, 0.01); //kp,ki,kd
}


void loop() {

    if(Serial.available()>0)
  {
      referencia=Serial.read();
      if(referencia=='1') referencia=20;
      else if(referencia=='2') referencia=50;
      else if(referencia=='3') referencia=100;
      else if(referencia=='4') referencia=150;
      else if(referencia=='5') referencia=200; //Velocidad maxima del motor
      else if(referencia=='6') referencia=ref_ant+10;
      else if(referencia=='7') referencia=ref_ant-10;
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
      SetTunings(0.1, 8, 0); //kp,ki,kd    
      }
      
  }

    Compute(); 
   
    analogWrite(M4F,Output);
    analogWrite(M4B,0);      
        
    Serial.print(referencia);
    Serial.print("              ");
    Serial.print(velocidad,4);
    Serial.print("           ");
    Serial.println(Output);
      
    if((micros()-oldTime)>50000){
     velocidad=0;
     analogWrite(M4F,0);
     analogWrite(M4B,0);
    }
    

}

void blink()
{
  //Serial.println("ENCODER");
  elapsedTime = micros() - oldTime; 
  oldTime = micros();
  velocidad   = 60000000.0/(elapsedTime*ppv);
   
}


