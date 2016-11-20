
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

TCCR3B = TCCR3B & B11111000 | B00000010;    // Pines 2/3/5 set timer 3 divisor to 8 for PWM frequency of  3921.16 Hz ----> Queda!
TCCR4B = TCCR4B & B11111000 | B00000010;    // Pines 6/7/8 set timer 4 divisor to  8 for PWM frequency of  3921.16 Hz
TCCR2B = TCCR2B & B11111000 | B00000010;    // Pines 9/10 set timer 2 divisor to 8 for PWM frequency of  3921.16 Hz  
TCCR1B = TCCR1B & B11111000 | B00000010;    // Pines 11/12 set timer 1 divisor to 8 for PWM frequency of  3921.16 Hz
//TCCR0B = TCCR0B & B11111000 | B00000011;  // Pines 4/13 set timer 0 divisor to    64 for PWM frequency of   976.56 Hz (Default)
//https://arduino-info.wikispaces.com/Arduino-PWM-Frequency
}

void loop() {
  
//ejecucion de pwms
for(int j = 0;j<=250;j+=10){
analogWrite(M1F,j);
analogWrite(M1B,0);
analogWrite(M2F,j);
analogWrite(M2B,0);
analogWrite(M3F,j);
analogWrite(M3B,0);
analogWrite(M4F,j);
analogWrite(M4B,0);
delay(100);
Serial.print("I-1:  ");
Serial.print(calculo_corriente(I_M1));
Serial.print("  I-2:  ");
Serial.print(calculo_corriente(I_M2));
Serial.print("  I-3:  ");
Serial.print(calculo_corriente(I_M3));
Serial.print("  I-4:  ");
Serial.println(calculo_corriente(I_M4));

}

for(int j = 250;j>=0;j-=10){
analogWrite(M1F,j);
analogWrite(M1B,0);
analogWrite(M2F,j);
analogWrite(M2B,0);
analogWrite(M3F,j);
analogWrite(M3B,0);
analogWrite(M4F,j);
analogWrite(M4B,0);
delay(100);
Serial.print("I-1:  ");
Serial.print(calculo_corriente(I_M1));
Serial.print("  I-2:  ");
Serial.print(calculo_corriente(I_M2));
Serial.print("  I-3:  ");
Serial.print(calculo_corriente(I_M3));
Serial.print("  I-4:  ");
Serial.println(calculo_corriente(I_M4));
}

analogWrite(M1F,0);
analogWrite(M1B,0);
analogWrite(M2F,0);
analogWrite(M2B,0);
analogWrite(M3F,0);
analogWrite(M3B,0);
analogWrite(M4F,0);
analogWrite(M4B,0);

delay(2000);

//for(int j = 255;j>=0;j-=10){
for(int j = 0;j<=250;j+=10){
analogWrite(M1F,0);
analogWrite(M1B,j);
analogWrite(M2F,0);
analogWrite(M2B,j);
analogWrite(M3F,0);
analogWrite(M3B,j);
analogWrite(M4F,0);
analogWrite(M4B,j);
delay(100);
Serial.print("I-1:  ");
Serial.print(calculo_corriente(I_M1));
Serial.print("  I-2:  ");
Serial.print(calculo_corriente(I_M2));
Serial.print("  I-3:  ");
Serial.print(calculo_corriente(I_M3));
Serial.print("  I-4:  ");
Serial.println(calculo_corriente(I_M4));
}

for(int j = 250;j>=0;j-=10){
analogWrite(M1F,0);
analogWrite(M1B,j);
analogWrite(M2F,0);
analogWrite(M2B,j);
analogWrite(M3F,0);
analogWrite(M3B,j);
analogWrite(M4F,0);
analogWrite(M4B,j);
delay(100);
Serial.print("I-1:  ");
Serial.print(calculo_corriente(I_M1));
Serial.print("  I-2:  ");
Serial.print(calculo_corriente(I_M2));
Serial.print("  I-3:  ");
Serial.print(calculo_corriente(I_M3));
Serial.print("  I-4:  ");
Serial.println(calculo_corriente(I_M4));
}

analogWrite(M1F,0);
analogWrite(M1B,0);
analogWrite(M2F,0);
analogWrite(M2B,0);
analogWrite(M3F,0);
analogWrite(M3B,0);
analogWrite(M4F,0);
analogWrite(M4B,0);

delay(2000);

}

float calculo_corriente(int analog){

  sensorValue_sin_offset = analog-510;
  corriente_voltaje = sensorValue_sin_offset*5000.0/1023.0;
  corriente = corriente_voltaje/20.0;

  return corriente;
}

