
int pin = 13;
volatile int estado = LOW;
int contador=0;

void setup()
{
  pinMode(pin, OUTPUT);
  attachInterrupt(1, parpadeo, CHANGE);
  Serial.begin(9600);

}

void loop()
{
  digitalWrite(pin, estado);

  delay(2000);
}

void parpadeo()
{
  Serial.println("hola webon");
}

