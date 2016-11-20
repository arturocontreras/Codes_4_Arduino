
int sensorPin = A0;    // select the input pin for the potentiometer
int ledPin = 13;      // select the pin for the LED
int sensorValue = 0;  // variable to store the value coming from the sensor

void setup() {
  // declare the ledPin as an OUTPUT:

 Serial.begin(9600);
 pinMode(3, OUTPUT);
 // TCCR2B = 0;// same for TCCR2B
 // TCCR2B |= (0 << CS20)|(0 << CS21)|(1 << CS22);   
 // TCCR2B = _BV(CS22);

  TCCR3B = TCCR3B & B11111000 | B00000100; // set timer 3 divisor to     8 for PWM frequency of  490.20 Hz
  //https://arduino-info.wikispaces.com/Arduino-PWM-Frequency
}

void loop() {
  // read the value from the sensor:
analogWrite(2, 220 );
analogWrite(3, 255);
delay(2000);    
analogWrite(2, 255);
analogWrite(3, 0);
delay(1000);

}
