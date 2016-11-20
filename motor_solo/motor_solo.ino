

void setup() {

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
}
