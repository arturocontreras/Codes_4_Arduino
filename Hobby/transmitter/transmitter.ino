
#include <VirtualWire.h>

char *controller;
void setup() {

pinMode(13,OUTPUT);
vw_set_ptt_inverted(true); //
vw_set_tx_pin(3);
vw_set_rx_pin(2);
vw_setup(4000);// speed of data transfer Kbps

vw_rx_start();       // Start the receiver PLL running

}

void loop(){
controller="1"  ;
vw_send((uint8_t *)controller, strlen(controller));
vw_wait_tx(); // Wait until the whole message is gone
digitalWrite(13,1);
delay(2000);

uint8_t buf[VW_MAX_MESSAGE_LEN];
    uint8_t buflen = VW_MAX_MESSAGE_LEN;

    if (vw_get_message(buf, &buflen)) // Non-blocking
    {
      if(buf[0]=='1'){

  
   digitalWrite(13,1);
      }  
   if(buf[0]=='0'){
  digitalWrite(13,0);
    }

}

}
