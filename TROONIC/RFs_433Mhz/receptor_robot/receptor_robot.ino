
#include <VirtualWire.h>

const int led_pin = 13;
const int transmit_pin = 7;
const int receive_pin = 6;
const int transmit_en_pin = 3;

void setup()
{
    delay(1000);
    Serial.begin(9600);	// Debugging only
    Serial.println("setup");

    // Initialise the IO and ISR
    vw_set_tx_pin(transmit_pin);
    vw_set_rx_pin(receive_pin);
    vw_set_ptt_pin(transmit_en_pin);
    vw_set_ptt_inverted(true); // Required for DR3100
    vw_setup(2000);	 // Bits per sec

    vw_rx_start();       // Start the receiver PLL running

    pinMode(led_pin, OUTPUT);
}

void loop()
{
    uint8_t buf[VW_MAX_MESSAGE_LEN];
    uint8_t buflen = VW_MAX_MESSAGE_LEN;

    if (vw_get_message(buf, &buflen)) // Non-blocking
    {
	  int i;
    digitalWrite(led_pin, HIGH); // Flash a light to show received good message
	  // Message with a good checksum received, dump it.
	  Serial.print("Got: ");
	
	  for (i = 0; i < buflen; i++)
	  {
	    Serial.print((char)buf[i], DEC);
	    Serial.print(' ');
	  }
	  Serial.println();
    digitalWrite(led_pin, LOW);
    }

    if(buf[0]==97){
      switch(buf[1]){
        case 1: Serial.println("STOP");
        digitalWrite(37,LOW);
        break;

        case 2: Serial.println("ADELANTE");
        digitalWrite(37,HIGH);
        break;

        case 3: Serial.println("ATRAS");
        break;
        
        case 4: Serial.println("DERECHA");
        break;

        case 5: Serial.println("IZQUIEDA");
        break;
        
      }
     
     }

    
}
