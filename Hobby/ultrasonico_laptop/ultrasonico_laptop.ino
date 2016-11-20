// ---------------------------------------------------------------------------
// Example NewPing library sketch that does a ping about 20 times per second.
// ---------------------------------------------------------------------------

#include <NewPing.h>

#define TRIGGER_PIN  2  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN     3  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 300 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.
const int ledPin =  12;      // the number of the LED pin
const int focoPin =  11;      // the number of the LED pin
const int buttonPin = 5;     // the number of the pushbutton pin

int contador=1;
boolean foco=true;
int distancia,distancia_ant;

int buttonState = 0;         // variable for reading the pushbutton status


NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.

void setup() {
  Serial.begin(115200); // Open serial monitor at 115200 baud to see ping results.
   pinMode(ledPin, OUTPUT);    
   pinMode(focoPin, OUTPUT);    
   pinMode(buttonPin, INPUT);     
   Serial1.begin(9600);
   distancia_ant=240;
}

void loop() {
  delay(400);                      // Wait 50ms between pings (about 20 pings/sec). 29ms should be the shortest delay between pings.
  unsigned int uS = sonar.ping(); // Send ping, get ping time in microseconds (uS).
  Serial.print("Ping: ");
  Serial.print(uS / US_ROUNDTRIP_CM); // Convert ping time to distance in cm and print result (0 = outside set distance range)
  Serial.println("cm");
  int distancia = uS / US_ROUNDTRIP_CM;
  //if(distancia < 150 && distancia > 100){ 
   if(distancia == 0){ 
   digitalWrite(ledPin, HIGH);
   }

  else{
   digitalWrite(ledPin, LOW);}
   
   if((distancia_ant - distancia)>250){
   contador++;
   if(contador%2 != 0)
   foco = false;
   else
   foco =true;
 
   }
   
   if(Serial1.available()) {
      // get the new byte:
     
     int inChar = Serial1.read(); 
      if (inChar == '1' || inChar == 1) {
        foco = false; 
        Serial.println("Encendera ");

        
      } 
      else if (inChar == '2' || inChar == 2){
      
      foco = true;  
      Serial.println("Apagara");

    }
   }
   buttonState = digitalRead(buttonPin);
   if (buttonState == HIGH) {     
    // turn LED on:    
    Serial.println("Puerta Cerrada"); 
   } 
   else {
    // turn LED off:
    Serial.println("Puerta Abierta");
   }
   
   if(foco){
   digitalWrite(focoPin, LOW);
   delay(500);}
   else{
   digitalWrite(focoPin, HIGH);
   delay(500);}
    
    distancia_ant =distancia;
}
