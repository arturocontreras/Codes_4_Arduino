
#define m1_encoder_B digitalRead(4) 
#define m2_encoder_B digitalRead(5) 
#define m1_pulsoxvuelta 24
#define m2_pulsoxvuelta 24

int current1, current2;

unsigned long oldTime1, oldTime2 ;
unsigned long intervalTime1, intervalTime2;
double freq_pulsos1, freq_pulsos2;
double freq1, freq2;

int encoder1=0; //M1 M2
int encoder2=0; //M3 M4

void setup(){
  
  Serial.begin(9600);
  Serial1.begin(9600);
  
  attachInterrupt(0,m1_encoder_A,RISING); //pin2
  attachInterrupt(1,m2_encoder_A,RISING); //pin3 board

}

void loop(){
  
  analogWrite(6,250);
  analogWrite(7,0);
  
  analogWrite(8,250);
  analogWrite(9,0);
  
  current1 = analogRead(A0);
  current2 = analogRead(A1);
  
  Serial.print("Current1: ");
  Serial.print(current1);
  Serial.print("   Current2: ");
  Serial.print(current2);
  Serial.print("   RPM1: ");
  Serial.print(freq1);
  Serial.print("   RPM2: ");
  Serial.println(freq2);

}

void m1_encoder_A(){
  
  if(m1_encoder_B ==LOW)  encoder1+=1;
  else encoder1-=1;
  
  intervalTime1= micros() - oldTime1;
  oldTime1 = micros();
  freq_pulsos1 = 1000000/intervalTime1;
  freq1 = (freq_pulsos1/m1_pulsoxvuelta)*60; //RPM, 60 para pasar a minutos

}

void m2_encoder_A(){
  
  if(m2_encoder_B ==LOW)  encoder2+=1;
  else encoder2-=1;
  
  intervalTime2= micros() - oldTime2;
  oldTime2 = micros();
  freq_pulsos2 = 1000000/intervalTime2;
  freq2 = (freq_pulsos2/m2_pulsoxvuelta)*60; //RPM, 60 para pasar a minutos
  
}
