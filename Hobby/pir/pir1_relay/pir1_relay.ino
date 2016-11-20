
const int ledPin =  2;      // the number of the LED pin

// Variables will change :
int ledState = LOW;             // ledState used to set the LED
int ledState2 = LOW;  

// Generally, you should use "unsigned long" for variables that hold time
// The value will quickly become too large for an int to store
unsigned long previousMillis = 0;        // will store last time LED was updated

// constants won't change :
const long interval = 2000;           // interval at which to blink (milliseconds)

void setup() {
  // set the digital pin as output:
  Serial.begin(9600);
  pinMode(2, OUTPUT);
  pinMode(3, INPUT);
}

void loop()
{

    if (digitalRead(3) == HIGH){
      Serial.println("Movimiento");
      digitalWrite(2, HIGH);}
    else{
      digitalWrite(2, LOW);
    }

}

