
int sensorPin = A0;    // select the input pin for the potentiometer
int ledPin = 13;      // select the pin for the LED
int sensorValue = 0;  // variable to store the value coming from the sensor

void setup() {
  // declare the ledPin as an OUTPUT:
 Serial.begin(9600);
 pinMode(3, OUTPUT);
 
}

void loop() {
  // read the value from the sensor:
  sensorValue = analogRead(sensorPin);
  sensorValue = map(sensorValue,0,1023,0,1000);
//  Serial.print("Dutty =  ");
//  Serial.println(sensorValue);
  digitalWrite(3, LOW);
  delayMicroseconds(sensorValue);        // pauses for 50 microseconds      
  digitalWrite(3, HIGH);
  delayMicroseconds(1000-sensorValue);        // pauses for 50 microseconds      
}
