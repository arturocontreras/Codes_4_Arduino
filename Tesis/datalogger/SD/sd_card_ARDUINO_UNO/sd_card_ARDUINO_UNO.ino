//SPI:  (MISO) 12, 11 (MOSI), 13 (SCK), 4 (SS).
//ARDUINO UNO
#include <SPI.h>
#include <SD.h>

const int chipSelect = 4;
// Declaracion de variables
int tempC,luminosidad;
int tempPin = 0; // Definimos la entrada en pin A0
int LDRPin = 1; // Definimos la entrada en pin A0
int contador = 4;
long t_ini = 0;

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  Serial.print("Initializing SD card...");

  // see if the card is present and can be initialized:
  if (!SD.begin(chipSelect)) {
    Serial.println("Card failed, or not present");
    // don't do anything more:
    return;
  }
  Serial.println("card initialized.");
  
  contador = 4;
}

void loop() {
  // make a string for assembling the data to log:
  String dataString = "";

  if((millis() - t_ini)> 2000){
   
    tempC = analogRead(tempPin); 
    luminosidad= analogRead(LDRPin); 
    // Convierte el valor a temperatura
    tempC = (5.0 * tempC * 100.0)/1024.0; 
    
    dataString += String(tempC);
    dataString += "  ;  ";
    dataString += String(luminosidad);
  
    char nombre[] = "00000000.csv";
      nombre[0] = 'd';
      nombre[1] = 'a';
      nombre[2] = contador + '0';
     //nombre[2] = 't';
     // nombre[3] = 'a';
      nombre[4] = contador + '0';
      nombre[6] = contador + '0';
    // open the file. note that only one file can be open at a time,
    // so you have to close this one before opening another.
    File dataFile = SD.open(nombre, FILE_WRITE);
  
    // if the file is available, write to it:
    if (dataFile) {
      dataFile.println(dataString);
      dataFile.close();
      // print to the serial port too:
      Serial.println(dataString);
    }
    // if the file isn't open, pop up an error:
    else {
      Serial.println("error opening datalog.txt");
    }
    
  t_ini = millis();
  }
}
