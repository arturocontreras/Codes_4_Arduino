
int ref = 66;
long t_ant = 0; //Medicion de tiempo para que ingrese al envio_monitoreo

void setup() {
  Serial1.begin(115200);//Comunicacion con C2
  Serial.begin(115200);
}

void loop() {
  
 // if((millis()-t_ant)>=1400){
    Serial1.print('x');
    Serial1.print((char)12);
    Serial1.print((char)02);
    Serial1.print((char)46);
    Serial1.print((char)ref);
    Serial1.print((char)77);
    Serial1.print((char)04);
    Serial1.print((char)77);
    Serial1.print((char)ref);
    Serial1.print((char)210);
    Serial1.print((char)2);
    Serial1.print((char)66);
    Serial1.print('y');
    t_ant = millis();//Se actualiza el tiempo anterior

  //}
    
    if(Serial.available()>0){
      ref=Serial.read();
      Serial.println(ref);
    }
    
    delay(1500);
    
    
}

//Punto de prueba
//Lat : -12.024647
//Lon : -77.047725
//yaw = 210
//U = 2-> no obstaculo
