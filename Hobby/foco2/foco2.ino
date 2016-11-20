
// set pin numbers:
const int foco =  2;      // the number of the LED pin

// variables will change:
int buttonState = 0;         // variable for reading the pushbutton status

void setup() {
  // initialize the LED pin as an output:
  Serial.begin(9600);
  Serial1.begin(9600);

  pinMode(foco, OUTPUT);
  digitalWrite(foco, HIGH);  
  
}

void loop(){

    if(Serial1.available()) {
      // get the new byte:
      int inChar = (char)Serial1.read(); 
      
      if (inChar == 1) {
        
        digitalWrite(foco, LOW); //encender
        
      } 
      else if (inChar == 2){
    
      digitalWrite(foco, HIGH); 
      
      } 
    }

}
