//---------------------------//
//----integration Piksi------//
//----Sven Burkart-----------//
//----Christian Leder--------//
//----Projekt HS 2014--------//
//---------------------------//

const unsigned int MAX_INPUT = 200;                    // max anzhalt message bytes (längere messages werden nicht gespeichert)
boolean rtk_flag = false;
void setup() {
                                                       // put your setup code here, to run once:
  
  Serial.begin(115200);                                //usb TX0
  Serial2.begin (115200);                              //GPS TX2
  

}

void loop() {
                                                

  while (Serial2.available () > 0)                 
  {
    processIncomingByte (Serial2.read ());          
  }
}
                                                  
void processIncomingByte (const byte inByte)      
{
  //Serial.println(inByte , HEX);
  
  static byte input_msg [MAX_INPUT];
  static unsigned int input_pos = 0;               
  
  if (inByte == 0x55)
  {
    if (input_pos == 29)
    {
      for( int i = 0 ; i < input_pos ; i++)
      {
        //Serial.print(input_msg [i],HEX);       
        //Serial.print(" ");
      }    
      //Serial.println();                     
      
      if((input_msg[0] == 0x03) && (input_msg[1] == 0x02))
      {
        msg_analyse (input_msg);              
      }
    }
    input_pos = 0;                            
  }
  else
  {
    if (input_pos < (MAX_INPUT - 1))               
    {
      input_msg [input_pos] = inByte;       
      input_pos = input_pos + 1;            
    }
  }
  
}

void msg_analyse (byte byte_msg[29])       
{
  double east = 0;
  double north = 0;
  double dist=0;
  north = bytesToInt (byte_msg[12], byte_msg[11], byte_msg[10], byte_msg[9]);        
  east = bytesToInt (byte_msg[16], byte_msg[15], byte_msg[14], byte_msg[13]);       

  if(((byte)byte_msg[26]&& B00000001) == 0){
    rtk_flag = false;
    //Velocidades = 0;
  }
  else{
     rtk_flag = true;
  }
  
  Serial.print("north ");
  Serial.print(north);
  Serial.print(" ; east ");
  Serial.println(east);
  
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
}


int bytesToInt (int b4, int b3, int b2, int b1)    
{
  int resultat=0;
  resultat=(b4 << 24) | (b3<<16) | (b2<<8) | b1;   
  return resultat;
}
