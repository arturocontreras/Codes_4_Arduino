// These constants won't change.  They're used to give names
// to the pins used:
#define dt 0.2

const int analogInPin = A0;  // Analog input pin that the potentiometer is attached to
const int analogOutPin = 9; // Analog output pin that the LED is attached to

int sensorValue = 0;        // value read from the pot
int sensorValue_sin_offset = 0;
int outputValue = 0;        // value output to the PWM (analog out)
int corriente_analog = 0;
float voltaje = 12.0;
float corriente_voltaje = 0;
float corriente = 0;
float consumo = 0;

void setup() {
  // initialize serial communications at 9600 bps:
  Serial.begin(115200);
}

void loop() {
  // read the analog in value:
  sensorValue = analogRead(analogInPin);
  sensorValue_sin_offset = sensorValue-509;
  corriente_voltaje = sensorValue_sin_offset*5000.0/1023.0;
  corriente = corriente_voltaje/20.0;
  consumo += corriente*dt/3600.0; //pasando a horas
  // print the results to the serial monitor:
  
  Serial.print("Corriente = " );
  Serial.print(corriente);
  Serial.print(" A   " );
  Serial.print(consumo,6);
  Serial.println(" Ah" );
  
  // wait 200 milliseconds
  delay(200);
}
