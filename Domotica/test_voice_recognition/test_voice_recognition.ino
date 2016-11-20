const int focoPin =  11;      // the number of the LED pin
int greenPin = 9; // G petal on RGB LED module connected to digital pin 9
int bluePin = 10; // B petal on RGB LED module connected to digital pin 10
byte com = 0; //reply from voice recognition
 
void setup() 
{ 
Serial.begin(9600);
Serial3.begin(9600);

pinMode(focoPin, OUTPUT);    

//pinMode(ledPin, OUTPUT); // sets the ledPin to be an output
//pinMode(redPin, OUTPUT); // sets the redPin to be an output
//pinMode(greenPin, OUTPUT); // sets the greenPin to be an output
//pinMode(bluePin, OUTPUT); // sets the bluePin to be an output

delay(2000);
Serial3.write(0xAA);
Serial3.write(0x37);
delay(1000);

Serial3.write(0xAA);
Serial3.write(0x21);
} 
 
void loop() // run over and over again
{ 


  while(Serial3.available())
  {
    com = Serial3.read();
    Serial.println(com);
    
    switch(com)
    {
    case 0x11:
    Serial.println("perro");
    break;
     
    case 0x12:
    Serial.println("gato");
    
    break;
     
    case 0x13:
    Serial.println("cuy");
    break;
     
    case 0x14:
    Serial.println("apagar");
    digitalWrite(focoPin, LOW);
    
    break;
     
    case 0x15:
    Serial.println("prender");
    digitalWrite(focoPin, HIGH);
    break;
     
    }
  }
 
//delay(50);

//Serial3.write(0xAA);
//Serial3.write(0x22);

while(Serial3.available())
  {
    com = Serial3.read();
    Serial.println(com);
    
    switch(com)
    {
    case 0x21:
    Serial.println("persianas cerradas");
    break;
     
    case 0x22:
    Serial.println("persianas abiertas");
    
    break;
     
    case 0x23:
    Serial.println("persianas abiertas la mitas");
    break;
     
    case 0x24:
    Serial.println("calefacción prendida");
    digitalWrite(focoPin, HIGH);

    break;
     
    case 0x25:
    Serial.println("calefaccion apagada");
    digitalWrite(focoPin, LOW);

    break;
     
    }
  }
  
 // delay(50);

 
} 
 

