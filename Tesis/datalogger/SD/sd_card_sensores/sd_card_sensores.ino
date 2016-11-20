//SPI: 50 (MISO), 51 (MOSI), 52 (SCK), 53 (SS).
#include <SPI.h>
#include <SD.h>


const int chipSelect = 53;
long t_ini = 0;
char contador;

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
}

void loop() {
  // make a string for assembling the data to log:
  String dataString = "";

  if((millis() - t_ini)> 5000){
    contador++;
    int sensor = analogRead(A0);
    dataString += String(t_ini/1000);
    dataString += ";";
    dataString += String(sensor);
  
    // open the file. note that only one file can be open at a time,
    // so you have to close this one before opening another.
    char nombre[] = "00000000.csv";
    nombre[0] = 'd';
    nombre[1] = 'a';
    nombre[2] = contador + '0';
   //nombre[2] = 't';
   // nombre[3] = 'a';
    nombre[4] = contador + '0';
    nombre[6] = contador + '0';

    File dataFile = SD.open( nombre, FILE_WRITE);
  
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
