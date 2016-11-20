// I assume you know how to connect the DS1302.
// DS1302:  CE pin    -> Arduino Digital 23
//          I/O pin   -> Arduino Digital 20
//          SCLK pin  -> Arduino Digital 21

#include <DS1302.h>

// Init the DS1302
DS1302 rtc(23, 20, 21);

void setup()
{
  // Set the clock to run-mode, and disable the write protection
  rtc.halt(false);
  rtc.writeProtect(false);
  
  // Setup Serial connection
  Serial.begin(9600);

  // SETEAR FECHA DE INICIO, SOLO LA PRIMERA VEZ
//  rtc.setDOW(FRIDAY);        // Set Day-of-Week to FRIDAY
//  rtc.setTime(9, 17, 0);     // Set the time to 12:00:00 (24hr format)
//  rtc.setDate(20, 9, 2015);   // Set the date to August 6th, 2010
}

void loop()
{
  // Send Day-of-Week
  Serial.print(rtc.getDOWStr());
  Serial.print(" ");
  
  // Send date
  Serial.print(rtc.getDateStr());
  Serial.print(" -- ");

  // Send time
  Serial.println(rtc.getTimeStr());
  
  // Wait one second before repeating :)
  delay (1000);
}