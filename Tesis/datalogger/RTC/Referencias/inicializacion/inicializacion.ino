#include <Wire.h> 
#include "RTClib.h"

RTC_DS1307 RTC;

void setup () {
Wire.begin(); // Inicia el puerto I2C
RTC.begin(); // Inicia la comunicación con el RTC
//RTC.adjust(DateTime(__DATE__, __TIME__)); // Establece la fecha y hora (Comentar una vez establecida la hora)
RTC.adjust(DateTime(2015, 5, 21, 18, 0, 0));
Serial.begin(9600); // Establece la velocidad de datos del puerto serie
}

void loop(){

}

