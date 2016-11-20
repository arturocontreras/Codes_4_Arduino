int ibyte=0;

void setup()
{
  Serial.begin(9600);
  //delay(2500);
    pinMode(9, OUTPUT);   // sets the pin as output

}

void loop()
{
  
  if(Serial.available()>0)
  {
    ibyte=Serial.read();
    Serial.print((char)ibyte);
    analogWrite(9,ibyte);
  }

}
