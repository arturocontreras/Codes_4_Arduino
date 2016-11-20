
#include <VirtualWire.h>

const int led_pin = 13;
const int transmit_pin = 2;
const int receive_pin = 5;
const int transmit_en_pin = 8;
// Declaracion de variables
int tempC,luminosidad,comando;

void setup()
{

    delay(1000);
    Serial.begin(9600);  // Debugging only
    // Initialise the IO and ISR
    vw_set_tx_pin(transmit_pin);
    vw_set_rx_pin(receive_pin);
    vw_set_ptt_pin(transmit_en_pin);
    vw_set_ptt_inverted(true); // Required for DR3100
    vw_setup(2000);       // Bits per sec

    vw_rx_start();       // Start the receiver PLL running
    pinMode(led_pin, OUTPUT);
}

byte count = 1;

void loop()
{
  char msg[2] = {'a','b'};

  if (Serial.available()) {
    comando = Serial.read();
    Serial.write(comando);
  }
  
  msg[1] = comando-48;
  digitalWrite(led_pin, HIGH); // Flash a light to show transmitting
  vw_send((uint8_t *)msg, 2);
  vw_wait_tx(); // Wait until the whole message is gone
  digitalWrite(led_pin, LOW);

  delay(100);
    
}
