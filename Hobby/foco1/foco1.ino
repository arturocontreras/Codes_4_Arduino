
// set pin numbers:
const int foco =  2;      // the number of the LED pin

// variables will change:
int buttonState = 0;         // variable for reading the pushbutton status

void setup() {
  // initialize the LED pin as an output:
  pinMode(foco, OUTPUT);      
}

void loop(){

   
    digitalWrite(foco, HIGH);  

    delay(3000);
    
    digitalWrite(foco, LOW); 
    
    delay(3000);

}
