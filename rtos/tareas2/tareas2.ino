/*
 DuinOS MoreComplexBlinkingAndSound
 
 Blinks two LEDs and play sound.
 
 The circuit:
 * 1 LED connected from digital pin 14 (8)
 * 2 LED connected from digital pin 15 (9)
 * Speaker connected from digital pin 16 (10)

 Created 2010.06.30 (yyyy.mm.dd)
 by Michael Grigorev aka CHERTS
 
 */

#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(7, 6, 5, 4, 3, 2);


int ledPinRed =  8;
int ledPinGreen =  9;
int SoundPin = 10;
int ledPinBlue = 11;
const int analogInPin = A0;  // Analog input pin that the potentiometer is attached to
const int analogOutPin = 12; // Analog output pin that the LED is attached to

int numTones = 10;
int tones[] = {261, 277, 294, 311, 330, 349, 370, 392, 415, 440};

unsigned int greenDelay = 200;
unsigned int redDelay = 400;
unsigned int blueDelay = 100;
int sensorValue = 0;        // value read from the pot
int outputValue = 0;        // value output to the PWM (analog out)


declareTaskLoop(redLED);
declareTaskLoop(greenLED);
declareTaskLoop(PlaySound);
declareTaskLoop(blueLED);
declareTaskLoop(pantalla);
declareTaskLoop(sensado);

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

taskLoop(PlaySound)
{
//  tone(SoundPin, 1245, 480);
//  delay(480);
//  tone(SoundPin, 932, 240);
//  delay(240);
//  tone(SoundPin, 1245, 960);
//  delay(120);
//  tone(SoundPin, 831, 240);
//  delay(240);
//  tone(SoundPin, 932, 480);
//  delay(480);
//  tone(SoundPin, 622, 720);
//  delay(240);
//  tone(SoundPin, 784, 120);
//  delay(120);
//  tone(SoundPin, 932, 120);
//  delay(120);
//  tone(SoundPin, 1245, 240);
//  delay(240);
//  tone(SoundPin, 932, 240);
//  delay(240);
//  tone(SoundPin, 1397, 240);
//  delay(240);
//  tone(SoundPin, 1245, 960);
//  delay(120);
//  tone(SoundPin, 1109, 360);
//  delay(360);
//  tone(SoundPin, 1047, 120);
//  delay(120);
//  tone(SoundPin, 932, 120);
//  delay(120);
//  tone(SoundPin, 831, 360);
//  delay(360);
//  tone(SoundPin, 932, 960);

   for (int i = 0; i < SoundPin; i++)
  {
  tone(SoundPin, tones[i]);
  delay(500);
  }
  //noTone(SoundPin);

  //suspend();
}

taskLoop(blueLED)
{
  digitalWrite(ledPinBlue, HIGH);
  delay(blueDelay);
  digitalWrite(ledPinBlue, LOW);
  delay(blueDelay);
}

taskLoop(pantalla)
{
//  //lcd.noBlink();
//  lcd.print("hello, world!");
//  delay(3000);
//   // Turn on the blinking cursor:
//  //lcd.blink();
//  lcd.print("bye, world!");
//  delay(3000);

 for (int positionCounter = 0; positionCounter < 13; positionCounter++) {
    // scroll one position left:
    lcd.scrollDisplayLeft(); 
    // wait a bit:
    delay(150);
  }

  // scroll 29 positions (string length + display length) to the right
  // to move it offscreen right:
  for (int positionCounter = 0; positionCounter < 29; positionCounter++) {
    // scroll one position right:
    lcd.scrollDisplayRight(); 
    // wait a bit:
    delay(150);
  }
  
    // scroll 16 positions (display length + string length) to the left
    // to move it back to center:
  for (int positionCounter = 0; positionCounter < 16; positionCounter++) {
    // scroll one position left:
    lcd.scrollDisplayLeft(); 
    // wait a bit:
    delay(150);
  }
  
  // delay at the end of the full loop:
  delay(1000);
  
  
}

taskLoop(sensado)
{
// read the analog in value:
  sensorValue = analogRead(analogInPin);            
  // map it to the range of the analog out:
  outputValue = map(sensorValue, 0, 1023, 0, 255);  
  // change the analog out value:
  analogWrite(analogOutPin, outputValue);           

  // print the results to the serial monitor:
  Serial.print("sensor = " );                       
  Serial.print(sensorValue);      
  Serial.print("\t output = ");      
  Serial.println(outputValue);   

  // wait 2 milliseconds before the next loop
  // for the analog-to-digital converter to settle
  // after the last reading:
  delay(200);                   
  
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
  createTaskLoop(PlaySound, NORMAL_PRIORITY);
  createTaskLoop(blueLED, NORMAL_PRIORITY);
  createTaskLoop(pantalla, NORMAL_PRIORITY);
  createTaskLoop(sensado, NORMAL_PRIORITY);
  //This initializes the main loop's with a different priority (default is LOW_PRIORITY):
  //initMainLoopPriority(NORMAL_PRIORITY);
  
    lcd.begin(16, 2);
  // Print a message to the LCD.
    lcd.print("hello, world!");
}


// This is the main loop() method, wich runs over and over again,
// as long as the Arduino has power. Is a LOW_PRIORITY taskLoop:
void loop()                     
{
  // Stop the task of redLED in 10 seconds
  delay(10000);
  suspendTask(redLED);
  // Start the task of redLED in 10 seconds
  delay(10000);
  resumeTask(redLED);
}
