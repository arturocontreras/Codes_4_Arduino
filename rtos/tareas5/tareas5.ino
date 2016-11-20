
#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(7, 6, 5, 4, 3, 2);


int ledPinRed =  8;
int ledPinGreen =  9;
int SoundPin = 10;
int ledPinBlue = 11;
const int analogInPin = A0;  // Analog input pin that the potentiometer is attached to
const int analogOutPin = 12; // Analog output pin that the LED is attached to
const int analogInPin2 = A1;  // Analog input pin that the potentiometer is attached to
const int analogInPin3 = A2;
const int analogInPin4 = A3;

int numTones = 10;
int tones[] = {
  261, 277, 294, 311, 330, 349, 370, 392, 415, 440};

unsigned int greenDelay = 200;
unsigned int redDelay = 400;
unsigned int blueDelay = 100;
int sensorValue = 0;        // value read from the pot
int sensorValue2 = 0;        // value read from the pot
int sensorValue3 = 0;        // value read from the pot
int sensorValue4 = 0;        // value read from the pot
int outputValue = 0;        // value output to the PWM (analog out)


declareTaskLoop(redLED);
declareTaskLoop(greenLED);
declareTaskLoop(blueLED);
declareTaskLoop(sensado);

taskLoop(redLED)
{
  digitalWrite(ledPinRed, HIGH);
  delay(redDelay);
  digitalWrite(ledPinRed, LOW);
  delay(redDelay);
  Serial.print("Hola  " );                         
  Serial.print("\t a todas = ");      
  Serial.println("\t las pendejas = " );                       

}


taskLoop(greenLED)
{
  digitalWrite(ledPinGreen, HIGH);
  delay(greenDelay);
  digitalWrite(ledPinGreen, LOW);
  delay(greenDelay);
}



taskLoop(blueLED)
{
  digitalWrite(ledPinBlue, HIGH);
    sensorValue3 = analogRead(analogInPin3);   

  delay(blueDelay);
  digitalWrite(ledPinBlue, LOW);
  delay(blueDelay);
}

taskLoop(sensado)
{
  //// read the analog in value:

  sensorValue = analogRead(analogInPin); 
  sensorValue2 = analogRead(analogInPin2);   
  // sensorValue4 = analogRead(analogInPin4);   
  // map it to the range of the analog out:
  //outputValue = map(sensorValue, 0, 150, 0, 255);  

  //  //analogWrite(analogOutPin, outputValue);           
  //
  ////  // print the results to the serial monitor:
  Serial.print("sensor1 = " );                       
  Serial.print(sensorValue);      
  Serial.print("\t sensor2 = ");      
  Serial.print(sensorValue2);
  Serial.print("\t sensor3 = " );                       
  Serial.println(sensorValue3); 
  //  Serial.print("\t sensor4 = " );                       
  //  Serial.println(sensorValue4); 
  ///
  ////
  ////  // wait 2 milliseconds before the next loop
  //  // for the analog-to-digital converter to settle
  ////  // after the last reading:
  delay(500);     
  //  lcd.clear();

}
// The setup() method runs once, when the sketch starts
void setup()   
{                
  // Initialize the digital pins as outputs:
  Serial.begin(9600); 

  pinMode(ledPinRed, OUTPUT);
  pinMode(ledPinGreen, OUTPUT);
  pinMode(ledPinBlue, OUTPUT);

  createTaskLoop(redLED, NORMAL_PRIORITY);
  createTaskLoop(greenLED, NORMAL_PRIORITY);
  createTaskLoop(blueLED, NORMAL_PRIORITY);
  createTaskLoop(sensado, NORMAL_PRIORITY);
  //This initializes the main loop's with a different priority (default is LOW_PRIORITY):
  //initMainLoopPriority(NORMAL_PRIORITY);

  lcd.begin(16, 2);
}


// This is the main loop() method, wich runs over and over again,
// as long as the Arduino has power. Is a LOW_PRIORITY taskLoop:
void loop()                     
{
  // Stop the task of redLED in 10 seconds
  lcd.print(sensorValue);
  delay(500);     
  lcd.clear();
}  


