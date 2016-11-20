//Encoder
#define ppv1 120.0
#define ppv2 120.0
#define ppv3 120.0
#define ppv4 120.0
//100 es real
//Motor pines
#define M1F 6
#define M1B 7
#define M2F 5
#define M2B 4
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
long t_op = 0;
boolean enable1,enable2,enable3,enable4,enable5;

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
  //https://arduino-info.wikispaces.com/Arduino-PWM-Frequency
  
  //pines de interrupcion como entrada
  pinMode(chA_m1, INPUT);
  pinMode(chA_m2, INPUT);
  
  //attachInterrupt(0, blink, CHANGE); //pin2
  attachInterrupt(inte1, cal_v1, RISING);
  attachInterrupt(inte2, cal_v2, RISING); //pin2
  
  //Seteo de controladores
  SetTunings1(0.1, 9, 0); //kp,ki,kd
  SetTunings2(0.1, 9, 0);
  
  //Valores iniciales de variables
  elapsedTime1=0;
  elapsedTime2=0;
  
  //Inicialización de setpoints
  setpoint[0] = 100; //[0 100 200] = [-100 0 100]
  setpoint[1] = 100;
  t_op=millis();
  
}


void loop() {
    //Recepcion de las referencias de velocidad   
    Recepcion_setpoints();
    Compute();  
    Output_pwm();    
    
    if((millis() - t_op)<4000){ //Avanza
    setpoint[0] = 110;
    setpoint[1] = 110;
    }
    else if((millis() - t_op)>4000 && (millis() - t_op)<8000){ //Gira derecha
    setpoint[0] = 110;
    setpoint[1] = 10;
    }
    else if((millis() - t_op)>=8000 && (millis() - t_op)<12000){ //Avanza
    setpoint[0] = 110;
    setpoint[1] = 110;
    }
    else if((millis() - t_op)>=12000 && (millis() - t_op)<16000){ //Gira derecha
    setpoint[0] = 10;
    setpoint[1] = 110;
    }
    else if((millis() - t_op)>=16000 && (millis() - t_op)<20000){ //Avanza
    setpoint[0] = 110;
    setpoint[1] = 110;
    }
    else{
    setpoint[0] = 100;
    setpoint[1] = 100;
    }
    
    
    
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
  
  }
  
void Compute()
{
unsigned long now = millis();
int timeChange = (now - lastTime);
//Serial.println((int)timeChange);
if(timeChange>=SampleTime)
{
// Calcula todas las variables de errores.
double error1 = Setpoint_m1 - Input1;
double error2 = Setpoint_m2 - Input2;

errSum1 += error1;
errSum2 += error2;

double dInput1 = (Input1 - lastInput1);
double dInput2 = (Input2 - lastInput2);

// Calculamos la función de salida del PID.
Output1= kp1 * error1 + ki1 * errSum1 - kd1 * dInput1;
Output2= kp2 * error2 + ki2 * errSum2 - kd2 * dInput2;

//saturacion
if(Output1<0) Output1=0;
if(Output1>100) Output1=100;
Output1=(Output1*255)/100;

if(Output2<0) Output2=0;
if(Output2>100) Output2=100;
Output2=(Output2*255)/100;

// Guardamos el valor de algunas variables para el próximo ciclo de cálculo.
lastInput1 = Input1;
lastInput2 = Input2;

lastTime = now;
}
}

void SetTunings1(double Kp, double Ki, double Kd)
{
  double SampleTimeInSec = ((double)SampleTime)/1000;
  kp1 = Kp;
  ki1 = Ki * SampleTimeInSec;
  kd1 = Kd / SampleTimeInSec;
}

void SetTunings2(double Kp, double Ki, double Kd)
{
  double SampleTimeInSec = ((double)SampleTime)/1000;
  kp2 = Kp;
  ki2 = Ki * SampleTimeInSec;
  kd2 = Kd / SampleTimeInSec;
}


void Output_pwm(){

    Compute(); 
   
    if (setpoint[0]==100 ){ //Colocar  a (Wr1) el valor de 100 por defecto.
    analogWrite(M1F,0);
    analogWrite(M1B,0);
    }
    
    if (setpoint[1]==100 ){ //Colocar  a (Wr2)  el valor de 100 por defecto.
    analogWrite(M2F,0);
    analogWrite(M2B,0);
    }
    
    if (setpoint[0]>100){  //Hacia adelante
    analogWrite(M1F, Output1);
    analogWrite(M1B, 0);
    }
    
    if (setpoint[1]>100){  //Hacia adelante
    analogWrite(M2F, Output2);
    analogWrite(M2B, 0);
    }
    
    if (setpoint[0]<100){  //Hacia atrás
    analogWrite(M1F, 0);
    analogWrite(M1B, Output1);
    }
    
    if (setpoint[1]<100){ //Hacia atrás
    analogWrite(M2F, 0);
    analogWrite(M2B, Output2);
    } 
     
    Serial.print(referencia);
    Serial.print("      ");
    Serial.print(Input1,4);
    Serial.print("      ");
    Serial.println(Input2,4);
      
    if((micros()-oldTime1)>50000){
     Input1=0;
     analogWrite(M1F,0);
     analogWrite(M1B,0);
    }
    
    if((micros()-oldTime2)>50000){
     Input2=0;
     analogWrite(M2F,0);
     analogWrite(M2B,0);
    }        
}

void Recepcion_setpoints(){
   if(Serial.available()>0)
  {
      referencia=Serial.read();
      if(referencia=='1') referencia=6;
      else if(referencia=='2') referencia=20;
      else if(referencia=='3') referencia=30;
      else if(referencia=='4') referencia=40;
      else if(referencia=='5') referencia=60; //Velocidad maxima del motor
      else if(referencia=='6') referencia=80;
      else if(referencia=='7') referencia=100;
      else referencia=0;
      ref_ant=referencia;
      
      Setpoint_m1 = referencia;
      Setpoint_m2 = referencia;
      
      if(referencia <=10) {
        SampleTime = 20;
        SetTunings1(0.1, 9, 0);
        SetTunings2(0.1, 9, 0);
      
      }
      else {
        SampleTime = 20; 
        SetTunings1(0.1, 9, 0);//kp,ki,kd
        SetTunings2(0.1, 9, 0);  
      }
      
  }
  
  if (setpoint[0]>100){  //Hacia adelante
  Setpoint_m1 = setpoint[0] -100;
  }
  
  if (setpoint[1]>100){  //Hacia adelante
  Setpoint_m2 = setpoint[1] -100;
  }
  
  if (setpoint[0]<100){  //Hacia atrás
  Setpoint_m1 = setpoint[0];
  }
  
  if (setpoint[1]<100){ //Hacia atrás
  Setpoint_m2 = setpoint[1];
  }
  
}


void medir_corrientes(){
  float total_current =calculo_corriente(I_M1) + calculo_corriente(I_M2)+calculo_corriente(I_M3)+calculo_corriente(I_M4);  
}

float calculo_corriente(int analog){

  sensorValue_sin_offset = analog-510;
  corriente_voltaje = sensorValue_sin_offset*5000.0/1023.0;
  corriente = corriente_voltaje/20.0;
  if(corriente<0) corriente = 0;
  return corriente;
}
