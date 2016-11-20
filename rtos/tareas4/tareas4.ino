
#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(7, 6, 5, 4, 3, 2);


int ledPinRed =  8;
int ledPinGreen =  9;
int ledPinBlue = 11;
unsigned int greenDelay = 200;
unsigned int redDelay = 400;
unsigned int blueDelay = 100;

const int analogInPin1 = A0;  // Analog input pin that the potentiometer is attached to
const int analogInPin2 = A1;  // Analog input pin that the potentiometer is attached to
const int analogInPin3 = A2;  // Analog input pin that the potentiometer is attached to
const int analogInPin4=  A3;  // Analog input pin that the potentiometer is attached to
const int analogInPin5 = A4;  // Analog input pin that the potentiometer is attached to
const int analogInPin6 = A5;  // Analog input pin that the potentiometer is attached to
int sensorValue1 = 0;        // value read from the pot
int sensorValue2 = 0;        // value read from the pot
int sensorValue3 = 0;        // value read from the pot
int sensorValue4 = 0;        // value read from the pot
int sensorValue5 = 0;        // value read from the pot
int sensorValue6 = 0;        // value read from the pot


declareTaskLoop(sensado1);
declareTaskLoop(sensado2);
//declareTaskLoop(sensado3);
//declareTaskLoop(sensado4);
declareTaskLoop(sensado5);
//declareTaskLoop(sensado6);

taskLoop(redLED)
{
  digitalWrite(ledPinRed, HIGH);
  delay(redDelay);
  digitalWrite(ledPinRed, LOW);
  delay(redDelay);
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
  delay(blueDelay);
  digitalWrite(ledPinBlue, LOW);
  delay(blueDelay);
}

taskLoop(sensado1)
{
// read the analog in value:
  sensorValue1 = analogRead(analogInPin1);            
  delay(5000);     

}

taskLoop(sensado2)
{
// read the analog in value:
  sensorValue2 = analogRead(analogInPin2);            
  delay(5000);     

}
//
//taskLoop(sensado3)
//{
//// read the analog in value:
//  sensorValue3 = analogRead(analogInPin3);             
//  delay(5000);     
//
//}

//taskLoop(sensado4)
//{
//// read the analog in value:
//  sensorValue4 = analogRead(analogInPin4);              
//  delay(5000);     
//
//}

taskLoop(sensado5)
{
// read the analog in value:
  sensorValue5 = analogRead(analogInPin5);              
  delay(5000);     

}
//
//taskLoop(sensado6)
//{
//// read the analog in value:
//  sensorValue6 = analogRead(analogInPin6);            
//  delay(5000);     
//
//}

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
  createTaskLoop(sensado1, NORMAL_PRIORITY);
  createTaskLoop(sensado2, NORMAL_PRIORITY);
//  createTaskLoop(sensado3, NORMAL_PRIORITY);
//  createTaskLoop(sensado4, NORMAL_PRIORITY);
  createTaskLoop(sensado5, NORMAL_PRIORITY);
//  createTaskLoop(sensado6, NORMAL_PRIORITY);
  
  //This initializes the main loop's with a different priority (default is LOW_PRIORITY):
  //initMainLoopPriority(NORMAL_PRIORITY);
  
   lcd.begin(16, 2);
}


// This is the main loop() method, wich runs over and over again,
// as long as the Arduino has power. Is a LOW_PRIORITY taskLoop:
void loop()                     
{
  // Stop the task of redLED in 10 seconds
  lcd.print(sensorValue1);
  delay(500);     
  lcd.clear();
  
  
  Serial.print("sensor1 = " );                       
  Serial.println(sensorValue1);
  Serial.print("sensor2 = " );                       
  Serial.println(sensorValue2);   
//  Serial.print("sensor3 = " );                       
//  Serial.println(sensorValue3);   
//  Serial.print("sensor4 = " );                       
//  Serial.println(sensorValue4);   
  Serial.print("sensor5 = " );                       
  Serial.println(sensorValue5);   
//  Serial.println("sensor6 = " );                       
//  Serial.print(sensorValue6);    
  
  delay(500); 
}  

