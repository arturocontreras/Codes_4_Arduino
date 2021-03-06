// ---------------------------------------------------------------------------
// Example NewPing library sketch that does a ping about 20 times per second.
// ---------------------------------------------------------------------------

#include <NewPing.h>

#define TRIGGER_PIN  2  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN     3  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 300 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.
const int ledPin =  12;      // the number of the LED pin
const int focoPin =  11;      // the number of the LED pin
int contador=0;
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.

void setup() {
  Serial.begin(115200); // Open serial monitor at 115200 baud to see ping results.
   pinMode(ledPin, OUTPUT);    
   pinMode(focoPin, OUTPUT);    

}

void loop() {
  delay(600);                      // Wait 50ms between pings (about 20 pings/sec). 29ms should be the shortest delay between pings.
  unsigned int uS = sonar.ping(); // Send ping, get ping time in microseconds (uS).
  Serial.print("Ping: ");
  Serial.print(uS / US_ROUNDTRIP_CM); // Convert ping time to distance in cm and print result (0 = outside set distance range)
  Serial.println("cm");
  
  if(uS / US_ROUNDTRIP_CM < 250){ 
   digitalWrite(ledPin, HIGH);
   contador++;
   }

  else{
   digitalWrite(ledPin, LOW);
   digitalWrite(focoPin, HIGH);}
   
   if(contador%2 !=0)
   digitalWrite(focoPin, HIGH);
   else
   digitalWrite(focoPin, LOW);
}
