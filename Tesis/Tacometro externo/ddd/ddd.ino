
// These constants won't change.  They're used to give names
// to the pins used:
const int analogInPin = A0;  // Analog input pin that the potentiometer is attached to
const int analogOutPin = 9; // Analog output pin that the LED is attached to

int sensorValue = 0;        // value read from the pot
int outputValue = 0;        // value output to the PWM (analog out)
long t_ini = 0;
long t_fin = 0;
double freq = 0;
double periodo = 0;
double RPM = 0;
int flag = 0;

void setup() {
  // initialize serial communications at 9600 bps:
  Serial.begin(115200);
}

void loop() {
  // read the analog in value:
  sensorValue = analogRead(analogInPin);

  if(sensorValue > 500 && flag == 1){

    t_fin = millis();
    periodo = t_fin - t_ini;
    RPM = 60000.00 / periodo;
    Serial.print("W = " );
    Serial.print(RPM);
    Serial.println("  RPMs" );

    t_ini = millis();
    flag = 0;
    
  }
    else if(sensorValue > 5 && sensorValue < 500 )
  {
    
    flag = 1;
      
  }
    



}
