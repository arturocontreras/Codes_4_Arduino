int sensorValue_sin_offset = 0;
int corriente_analog = 0;
float voltaje = 12.0;
float corriente_voltaje = 0;
float corriente = 0;
float consumo = 0;
void setup() {
   
 //pines motor
 Serial.begin(9600);
 pinMode(3, OUTPUT);
 pinMode(2, OUTPUT);
 // TCCR2B = 0;// same for TCCR2B
 // TCCR2B |= (0 << CS20)|(0 << CS21)|(1 << CS22);   
 // TCCR2B = _BV(CS22);

//TCCR3B = TCCR3B & B11111000 | B00000100; // set timer 3 divisor to     256 for PWM frequency of   122.55 Hz
TCCR3B = TCCR3B & B11111000 | B00000010;    // set timer 3 divisor to     8 for PWM frequency of  3921.16 Hz ----> Queda!
//TCCR3B = TCCR3B & B11111000 | B00000001;    // set timer 3 divisor to     1 for PWM frequency of 31372.55 Hz

  
}

void loop() {
  
//ejecucion de pwms
for(int j = 0;j<=250;j+=10){
analogWrite(3,j);
analogWrite(2,0);
delay(100);
Serial.print("Corriente:  ");
Serial.println(calculo_corriente(analogRead(A0)));
}

for(int j = 250;j>=0;j-=10){
analogWrite(3,j);
analogWrite(2,0);
delay(100);
Serial.print("Corriente:  ");
Serial.println(calculo_corriente(analogRead(A0)));
}

analogWrite(3,0);
analogWrite(2,0);

delay(2000);

//for(int j = 255;j>=0;j-=10){
for(int j = 0;j<=250;j+=10){
analogWrite(3,0);
analogWrite(2,j);
delay(100);
Serial.print("Corriente:  ");
Serial.println(calculo_corriente(analogRead(A0)));
}

for(int j = 250;j>=0;j-=10){
analogWrite(3,0);
analogWrite(2,j);
delay(100);
Serial.print("Corriente:  ");
Serial.println(calculo_corriente(analogRead(A0)));
}

analogWrite(3,0);
analogWrite(2,0);

delay(2000);

}

float calculo_corriente(int analog){

  sensorValue_sin_offset = analog-510;
  corriente_voltaje = sensorValue_sin_offset*5000.0/1023.0;
  corriente = corriente_voltaje/20.0;

  return corriente;
}

