
//This is a character buffer that will store the data from the serial port
char rxData[20];
char rxIndex=0;

//Variables to hold the speed and RPM data.
int vehicleSpeed=0;
int vehicleRPM=0;

void setup(){
  
  Serial.begin(9600); // Serial monitor
  Serial1.begin(9600); //para la comunicacion OBD

  //Wait for a little while before sending the reset command to the OBD-II-UART
  delay(1500);
  //Reset the OBD-II-UART
  Serial1.println("ATZ");
  //Wait for a bit before starting to send commands after the reset.
  delay(2000);

  //Delete any data that may be in the serial port before we begin.
  Serial1.flush();
}


void loop(){
  //Delete any data that may be in the serial port before we begin.  
  Serial1.flush();
  //Query the OBD-II-UART for the Vehicle Speed
  Serial1.println("010D");
  getResponse();
  getResponse();
  //Convert the string data to an integer
  vehicleSpeed = strtol(&rxData[6],0,16);
  //Print the speed data to the lcd
  Serial.print(vehicleSpeed);
  Serial.print(" km/h");
  delay(100);

  //Delete any data that may be left over in the serial port.
  Serial1.flush();

  //Query the OBD-II-UART for the Vehicle rpm
  Serial1.println("010C");
  //Get the response from the OBD-II-UART board
  getResponse();
  getResponse();
  //Convert the string data to an integer
  //NOTE: RPM data is two bytes long, and delivered in 1/4 RPM from the OBD-II-UART
  vehicleRPM = ((strtol(&rxData[6],0,16)*256)+strtol(&rxData[9],0,16))/4;
  //Print the rpm data to the lcd
  Serial.print(vehicleRPM); 
  Serial.print(" RPM");
  //Give the OBD bus a rest
  delay(100);

}
//The getResponse function collects incoming data from the UART into the rxData buffer
// and only exits when a carriage return character is seen. Once the carriage return
// string is detected, the rxData buffer is null terminated (so we can treat it as a string)
// and the rxData index is reset to 0 so that the next string can be copied.
void getResponse(void){
  char inChar=0;
  //Keep reading characters until we get a carriage return
  while(inChar != '\r'){
    //If a character comes in on the serial port, we need to act on it.
    if(Serial1.available() > 0){
      //Start by checking if we've received the end of message character ('\r').
      if(Serial1.peek() == '\r'){
        //Clear the Serial buffer
        inChar=Serial1.read();
        //Put the end of string character on our data string
        rxData[rxIndex]='\0';
        //Reset the buffer index so that the next character goes back at the beginning of the string.
        rxIndex=0;
      }
      //If we didn't get the end of message character, just add the new character to the string.
      else{
        //Get the new character from the Serial port.
        inChar = Serial1.read();
        //Add the new character to the string, and increment the index variable.
        rxData[rxIndex++]=inChar;
      }
    }
  }
}

