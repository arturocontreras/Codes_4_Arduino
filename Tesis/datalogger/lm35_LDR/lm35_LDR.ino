// Declaracion de variables
float tempC,luminosidad;
int tempPin = 0; // Definimos la entrada en pin A0
int LDRPin = 1; // Definimos la entrada en pin A0

void setup()
{
    // Abre puerto serial y lo configura a 9600 bps
    Serial.begin(9600);
}
void loop()
{
    // Lee el valor desde el sensor
    tempC = analogRead(tempPin); 
    luminosidad= analogRead(LDRPin); 
    // Convierte el valor a temperatura
    tempC = (5.0 * tempC * 100.0)/1024.0; 

    // Envia el dato al puerto serial
    Serial.print(tempC);
    Serial.print(" grados Celsius  ");
    Serial.print(luminosidad);
    Serial.print(" lux \n");

    // Espera cinco segundo para repetir el loop
    delay(1000);
}
