
int Encoder_m1=A1;//Analogico 1
int Encoder_m2=A0;//Analogico 0
int Input1,Input2;
///////////////////////////////////////////

void setup() {
  // initialize both serial ports:
  Serial.begin(9600);
 //pines motor
  pinMode(9, OUTPUT);   //m2r
  pinMode(10, OUTPUT);   //m2a
  pinMode(11, OUTPUT);   //m1r
  pinMode(12, OUTPUT);   //m1a
}

void loop() {
  //ejecucion de pwms
  analogWrite(10,255);
  analogWrite(11,255);
  // Rutina del controlador PID
  Input1=analogRead(Encoder_m1);
  Input2=analogRead(Encoder_m2);
  //para testeo
  Serial.print(Input1);
  Serial.print("  ");
  Serial.println(Input2);
 
  delay(200);

}
