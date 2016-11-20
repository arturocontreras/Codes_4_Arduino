#define A  2
#define B  3
#define C  4
#define D  5
#define tiempo 5 
boolean enable = false;
long contador = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
     
  Serial.begin(9600);
  Serial.println("Esperamos 1 seg");
  delay(1000);

  //interrupts();
  //attachInterrupt(digitalPinToInterrupt(18), blink, CHANGE);
}

void loop() {

}

void abre(int pasos){

  for(int i = 0; i <= pasos; i++){
    digitalWrite(A, HIGH);
    digitalWrite(B, HIGH);
    digitalWrite(C, HIGH);
    digitalWrite(D, HIGH);
    delay(tiempo);
    
    digitalWrite(A, HIGH);
    digitalWrite(B, LOW);
    digitalWrite(C, HIGH);
    digitalWrite(D, HIGH);
    delay(tiempo);
    
    digitalWrite(A, HIGH);
    digitalWrite(B, LOW);
    digitalWrite(C, HIGH);
    digitalWrite(D, LOW);
    delay(tiempo);
  //  
    digitalWrite(A, HIGH);
    digitalWrite(B, HIGH);
    digitalWrite(C, HIGH);
    digitalWrite(D, LOW);
  
    delay(tiempo);
  }

  apagar();
}

void cierra(int pasos){

  for(int i = 0; i <= pasos; i++){
    
    digitalWrite(A, HIGH);
    digitalWrite(B, HIGH);
    digitalWrite(C, HIGH);
    digitalWrite(D, LOW);
  
    delay(tiempo);

    digitalWrite(A, HIGH);
    digitalWrite(B, LOW);
    digitalWrite(C, HIGH);
    digitalWrite(D, LOW);
    delay(tiempo);

    digitalWrite(A, HIGH);
    digitalWrite(B, LOW);
    digitalWrite(C, HIGH);
    digitalWrite(D, HIGH);
    delay(tiempo);

    digitalWrite(A, HIGH);
    digitalWrite(B, HIGH);
    digitalWrite(C, HIGH);
    digitalWrite(D, HIGH);
    delay(tiempo);
    

  }

  apagar();
}

void serialEvent(){

  int inChar = (char)Serial.read(); 
     
      if (inChar == 49) {
      Serial.println("abre");
      abre(50);
      } 

      if (inChar == 50) {
      Serial.println("cierra");
      cierra(50);
      } 

      if (inChar == 51) {
      Serial.println("rutina");
      enable = true;
      rutina();
      } 

      if (inChar == 52) {
      Serial.flush();
      Serial.print("ingresa angulo a  girar: ");
      while(!Serial.available()){};
      int inChar = Serial.read(); 
      Serial.println(inChar);
      cierra(inChar);
      } 


      
      
}

void rutina(){

  Serial.flush();
  do{
  abre(50);
  Serial.println("CW");
  delay(1000);

  cierra(50);
  Serial.println("CCW");
  delay(1000);}

  while(!Serial.available());
}

void apagar(){
  
    digitalWrite(A, LOW);
    digitalWrite(B, LOW);
    digitalWrite(C, LOW);
    digitalWrite(D, LOW);
}

void blink(){

    enable = false;
    digitalWrite(A, LOW);
    digitalWrite(B, LOW);
    digitalWrite(C, LOW);
    digitalWrite(D, LOW);
}

