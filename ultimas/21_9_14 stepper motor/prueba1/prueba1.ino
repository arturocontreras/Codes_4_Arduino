/*
 * MotorKnob
 *
 * A stepper motor follows the turns of a potentiometer
 * (or other sensor) on analog input 0.
 *
 * http://www.arduino.cc/en/Reference/Stepper
 * This example code is in the public domain.
 */

#include <Stepper.h>

// change this to the number of steps on your motor
#define STEPS 200

// create an instance of the stepper class, specifying
// the number of steps of the motor and the pins it's
// attached to
Stepper stepper(STEPS, 5, 6, 7, 8);

// the previous reading from the analog input
int previous = 0;
int referencia=0;
int  ref_ant=0;

void setup()
{
  // set the speed of the motor to 30 RPMs
  Serial.begin(115200);
  pinMode(5, OUTPUT);   // sets the pin as output
  pinMode(6, OUTPUT);   // sets the pin as output
  pinMode(7, OUTPUT);   // sets the pin as output
  pinMode(8, OUTPUT);   // sets the pin as output
  stepper.setSpeed(80);
  
}

void loop()
{
  // get the sensor value
   if(Serial.available()>0)
  { 
    referencia=Serial.read();
    if(referencia=='1') referencia=200;
    else if(referencia=='2') referencia=500;
    else if(referencia=='3') referencia=2000;
    else if(referencia=='4') referencia=5000;
    else if(referencia=='5') referencia=ref_ant+10;
    else if(referencia=='6') referencia=ref_ant-10;
    else referencia=0;
    ref_ant=referencia;

  }
  // move a number of steps equal to the change in the
  // sensor reading
  stepper.step(referencia - previous);
  int variacion = referencia - previous;
  Serial.println(referencia );
  // remember the previous value of the sensor
  previous = referencia;
}
