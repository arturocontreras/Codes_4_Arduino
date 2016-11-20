const int analogInPin = A0;  // Analog input pin that the potentiometer is attached to
const int analogOutPin = 9; // Analog output pin that the LED is attached to

int sensorValue = 0;        // value read from the pot
int outputValue = 0;        // value output to the PWM (analog out)

void setup() {
  // initialize serial communications at 9600 bps:
  Serial.begin(9600); 
  Serial1.begin(9600);
}

void loop() {
  // read the analog in value:
  sensorValue = map(analogRead(analogInPin),0,1023,0,255);                   
  
  // print the results to the serial monitor:
  //Serial.print("sensor = " );                       
  Serial.print((char)sensorValue);  
  Serial1.print((char)sensorValue);     

  // wait 2 milliseconds before the next loop
  // for the analog-to-digital converter to settle
  // after the last reading:
  delay(200);                     
}
