//Encoder
#define ppv1 120.0
#define ppv2 120.0
#define ppv3 120.0
#define ppv4 120.0
//100 es real
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
long t_op = 0;
boolean enable1,enable2,enable3,enable4,enable5;

void setup() {
  
  Serial.begin(115200);
  Serial1.begin(9600);

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
  pinMode(chA_m3, INPUT);
  pinMode(chA_m4, INPUT);
  
  //attachInterrupt(0, blink, CHANGE); //pin2
  //attachInterrupt(inte1, cal_v1, RISING);
  //attachInterrupt(inte2, cal_v2, RISING); //pin2
  //attachInterrupt(inte3, cal_v3, RISING); //pin2
  //attachInterrupt(inte4, cal_v4, RISING); //pin2
  
  //Seteo de controladores
  SetTunings1(0.1, 9, 0); //kp,ki,kd
  SetTunings2(0.1, 9, 0);
  SetTunings3(0.1, 9, 0);
  SetTunings4(0.1, 9, 0);
  
  //Valores iniciales de variables
  elapsedTime1=0;
  elapsedTime2=0;
  elapsedTime3=0;
  elapsedTime4=0; 
  
  //Inicialización de setpoints
  setpoint[0] = 100; //[0 100 200] = [-100 0 100]
  setpoint[1] = 100;
  delay(5000);
  t_op=millis();
  
}


void loop() {
    //Recepcion de las referencias de velocidad   
    Recepcion_setpoints();
    //Output_pwm();    
    //Compute();  
    
//    //medir_corrientes();
//    if((millis() - t_op)<4000){ //Avanza
//    setpoint[0] = 110;
//    setpoint[1] = 110;
//    }
//    else if((millis() - t_op)>4000 && (millis() - t_op)<8000){ //Gira derecha
//    setpoint[0] = 110;
//    setpoint[1] = 10;
//    }
//    else if((millis() - t_op)>8000 && (millis() - t_op)<12000){ //Avanza
//    setpoint[0] = 110;
//    setpoint[1] = 110;
//    }
//    else if((millis() - t_op)>12000 && (millis() - t_op)<16000){ //Gira derecha
//    setpoint[0] = 110;
//    setpoint[1] = 10;
//    }
//    else if((millis() - t_op)>16000 && (millis() - t_op)<2000){ //Avanza
//    setpoint[0] = 110;
//    setpoint[1] = 110;
//    }
//    else{
//    setpoint[0] = 100;
//    setpoint[1] = 100;
//    }
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
double error3 = Setpoint_m3 - Input3;
double error4 = Setpoint_m4 - Input4;

errSum1 += error1;
errSum2 += error2;
errSum3 += error3;
errSum4 += error4;

double dInput1 = (Input1 - lastInput1);
double dInput2 = (Input2 - lastInput2);
double dInput3 = (Input3 - lastInput3);
double dInput4 = (Input4 - lastInput4);

// Calculamos la función de salida del PID.
Output1= kp1 * error1 + ki1 * errSum1 - kd1 * dInput1;
Output2= kp2 * error2 + ki2 * errSum2 - kd2 * dInput2;
Output3= kp3 * error3 + ki3 * errSum3 - kd3 * dInput3;
Output4= kp4 * error4 + ki4 * errSum4 - kd4 * dInput4;

//saturacion
if(Output1<0) Output1=0;
if(Output1>100) Output1=100;
Output1=(Output1*255)/100;

if(Output2<0) Output2=0;
if(Output2>100) Output2=100;
Output2=(Output2*255)/100;

if(Output3<0) Output3=0;
if(Output3>100) Output3=100;
Output3=(Output3*255)/100;

if(Output4<0) Output4=0;
if(Output4>100) Output4=100;
Output4=(Output4*255)/100;

// Guardamos el valor de algunas variables para el próximo ciclo de cálculo.
lastInput1 = Input1;
lastInput2 = Input2;
lastInput3 = Input3;
lastInput4 = Input4;

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

void SetTunings3(double Kp, double Ki, double Kd)
{
  double SampleTimeInSec = ((double)SampleTime)/1000;
  kp3 = Kp;
  ki3 = Ki * SampleTimeInSec;
  kd3 = Kd / SampleTimeInSec;
}

void SetTunings4(double Kp, double Ki, double Kd)
{
  double SampleTimeInSec = ((double)SampleTime)/1000;
  kp4 = Kp;
  ki4 = Ki * SampleTimeInSec;
  kd4 = Kd / SampleTimeInSec;
}

void Output_pwm(){

    //Compute(); 
   
  if (setpoint[0]==100 ){ //Colocar  a (Wr1) el valor de 100 por defecto.
  analogWrite(M1F,0);
  analogWrite(M1B,0);
  analogWrite(M3F,0);
  analogWrite(M3B,0);
  }
  
  if (setpoint[1]==100 ){ //Colocar  a (Wr2)  el valor de 100 por defecto.
  analogWrite(M2F,0);
  analogWrite(M2B,0);
  analogWrite(M4F,0);
  analogWrite(M4B,0);
  }
  
  if (setpoint[0]>100){  //Hacia adelante
  analogWrite(M1F, Output1);
  analogWrite(M1B, 0);
  analogWrite(M3F, Output3);
  analogWrite(M3B, 0);
  }
  
  if (setpoint[1]>100){  //Hacia adelante
  analogWrite(M2F, Output2);
  analogWrite(M2B, 0);
  analogWrite(M4F, Output4);
  analogWrite(M4B, 0);
  }
  
  if (setpoint[0]<100){  //Hacia atrás
  analogWrite(M1F, 0);
  analogWrite(M1B, Output1);
  analogWrite(M3F, 0);
  analogWrite(M3B, Output3);
  }
  
  if (setpoint[1]<100){ //Hacia atrás
  analogWrite(M2F, 0);
  analogWrite(M2B, Output2);
  analogWrite(M4F, 0);
  analogWrite(M4B, Output4);
  }
        
//    Serial.print(referencia);
//    Serial.print("      ");
//    Serial.print(Input1,4);
//    Serial.print("      ");
//    Serial.print(Input2,4);
//    Serial.print("      ");
//    Serial.print(Input3,4);
//    Serial.print("      ");
//    Serial.println(Input4,4);
      
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
    
    if((micros()-oldTime3)>50000){
     Input3=0;
     analogWrite(M3F,0);
     analogWrite(M3B,0);
    }
    
    if((micros()-oldTime4)>50000){
     Input4=0;
     analogWrite(M4F,0);
     analogWrite(M4B,0);
    }
    

}

void Recepcion_setpoints(){
   if(Serial1.available()>0)
  {
      referencia=Serial1.read();
      if(referencia=='w'){ 
        analogWrite(M1F, 60);
        analogWrite(M1B, 0);
        analogWrite(M2F, 60);
        analogWrite(M2B, 0);
        analogWrite(M3F, 60);
        analogWrite(M3B, 0);
        analogWrite(M4F, 60);
        analogWrite(M4B, 0);
        delay(200);
        Serial.print("adelante");
      }
      
      else if(referencia=='s') { 
        analogWrite(M1F, 0);
        analogWrite(M1B, 60);
        analogWrite(M2F, 0);
        analogWrite(M2B, 60);
        analogWrite(M3F, 0);
        analogWrite(M3B, 60);
        analogWrite(M4F, 0);
        analogWrite(M4B, 60);
         delay(200);

      }
      
      else if(referencia=='a'){ 
        analogWrite(M1F, 0);
        analogWrite(M1B, 200);
        analogWrite(M2F, 200);
        analogWrite(M2B, 0);
        analogWrite(M3F, 0);
        analogWrite(M3B, 200);
        analogWrite(M4F, 200);
        analogWrite(M4B, 0);
        delay(200);
      }
      
      else if(referencia=='d') { 
        analogWrite(M1F, 200);
        analogWrite(M1B, 0);
        analogWrite(M2F, 0);
        analogWrite(M2B, 200);
        analogWrite(M3F, 200);
        analogWrite(M3B, 0);
        analogWrite(M4F, 0);
        analogWrite(M4B, 200);
        delay(200);

      }
      
      else if(referencia=='e') { 
        analogWrite(M1F, 250);
        analogWrite(M1B, 0);
        analogWrite(M2F, 210);
        analogWrite(M2B, 0);
        analogWrite(M3F, 250);
        analogWrite(M3B, 0);
        analogWrite(M4F, 210);
        analogWrite(M4B, 0);
        delay(200);

      }
      
      else if(referencia=='x') { 
        analogWrite(M1F, 0);
        analogWrite(M1B, 250);
        analogWrite(M2F, 0);
        analogWrite(M2B, 210);
        analogWrite(M3F, 0);
        analogWrite(M3B, 250);
        analogWrite(M4F, 0);
        analogWrite(M4B, 210);
        delay(200);

      }
      
      else { 
        analogWrite(M1F, 0);
        analogWrite(M1B, 0);
        analogWrite(M2F, 0);
        analogWrite(M2B, 0);
        analogWrite(M3F, 0);
        analogWrite(M3B, 0);
        analogWrite(M4F, 0);
        analogWrite(M4B, 0);
        delay(200);

      }
      
        analogWrite(M1F, 0);
        analogWrite(M1B, 0);
        analogWrite(M2F, 0);
        analogWrite(M2B, 0);
        analogWrite(M3F, 0);
        analogWrite(M3B, 0);
        analogWrite(M4F, 0);
        analogWrite(M4B, 0);
        
      if(referencia <=10) {
        SampleTime = 20;
        SetTunings1(0.1, 9, 0);
        SetTunings2(0.1, 9, 0);
        SetTunings3(0.1, 9, 0);
        SetTunings4(0.1, 9, 0);
      
      }
      else {
        SampleTime = 20; 
        SetTunings1(0.1, 9, 0);//kp,ki,kd
        SetTunings2(0.1, 9, 0);
        SetTunings3(0.1, 9, 0);
        SetTunings4(0.1, 9, 0);    
      }
      
     Serial1.flush();

      
  }
  
  if (setpoint[0]>100){  //Hacia adelante
  Setpoint_m1 = setpoint[0] -100;
  Setpoint_m3 = Setpoint_m1;
  }
  
  if (setpoint[1]>100){  //Hacia adelante
  Setpoint_m2 = setpoint[1] -100;
  Setpoint_m4 = Setpoint_m2;
  }
  
  if (setpoint[0]<100){  //Hacia atrás
  Setpoint_m1 = setpoint[0];
  Setpoint_m3 = Setpoint_m1;
  }
  
  if (setpoint[1]<100){ //Hacia atrás
  Setpoint_m2 = setpoint[1];
  Setpoint_m4 = Setpoint_m2;
  }

  
}


void medir_corrientes(){
  float total_current =calculo_corriente(I_M1) + calculo_corriente(I_M2)+calculo_corriente(I_M3)+calculo_corriente(I_M4);
  
  //Serial.println(total_current);
  
//  Serial.print(calculo_corriente(I_M1));
//  Serial.print("  I2: ");
//  Serial.print(calculo_corriente(I_M2));
//  Serial.print("  I3: ");
//  Serial.print(calculo_corriente(I_M3));
//  Serial.print("  I4: ");
//  Serial.println(calculo_corriente(I_M4));
}

float calculo_corriente(int analog){

  sensorValue_sin_offset = analog-510;
  corriente_voltaje = sensorValue_sin_offset*5000.0/1023.0;
  corriente = corriente_voltaje/20.0;
  if(corriente<0) corriente = 0;
  return corriente;
}
