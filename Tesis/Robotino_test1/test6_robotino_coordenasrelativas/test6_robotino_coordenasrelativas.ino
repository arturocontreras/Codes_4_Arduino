// Reference the I2C Library
#include <Wire.h>
// Reference the HMC5883L Compass Library
#include <HMC5883L.h>
#include <Math.h>
#include "TimerOne.h"

#define GYRO 0x68 //  when AD0 is connected to GND ,gyro address is 0x68.
//#define GYRO 0x69  // when AD0 is connected to VCC ,gyro address is 0x69  
#define G_SMPLRT_DIV 0x15
#define G_DLPF_FS 0x16
#define G_INT_CFG 0x17
#define G_PWR_MGM 0x3E
#define G_TO_READ 8 // 2 bytes for each axis x, y, z

//Motores
#define M1F 8
#define M1B 9
#define M2F 10
#define M2B 11
#define vmax 60

int g_offx = 64; //120
int g_offy = 34; //20
int g_offz = 8; //93
int hx, hy, hz, turetemp;
int prev_hx, prev_hy, prev_hz;
//initializes the gyroscope

HMC5883L compass;
// Declaración de variables para muestras de la velocidad
unsigned long time=0;
int sampleTime=20;
int error = 0;
int set_point = 0;
int val = 0;
long uc = 0;//Señal control
int error_ant = 0; //memoria de error
long tiempo_ant = 0; //memoria de tiempo
long dT = 0; //Variación de tiempo para el controlador
int Ki = 4;
int Kp = 2;
float yaw = 0;
boolean start = true;

byte addr;
int gyro[4];

void initGyro()
{
 writeTo(GYRO, G_PWR_MGM, 0x00);
 writeTo(GYRO, G_SMPLRT_DIV, 0x07); // EB, 50, 80, 7F, DE, 23, 20, FF
 writeTo(GYRO, G_DLPF_FS, 0x1E); // +/- 2000 dgrs/sec, 1KHz, 1E, 19
 writeTo(GYRO, G_INT_CFG, 0x00);
}
void getGyroscopeData(int * result)
{
 int regAddress = 0x1B;
 int temp, x, y, z;
 byte buff[G_TO_READ];
 readFrom(GYRO, regAddress, G_TO_READ, buff); //read the gyro data from the ITG3200
 result[0] = ((buff[2] << 8) | buff[3]) + g_offx;
 result[1] = ((buff[4] << 8) | buff[5]) + g_offy;
 result[2] = ((buff[6] << 8) | buff[7]) + g_offz;
 result[3] = (buff[0] << 8) | buff[1]; // temperature
 }


void setup() {
 
 Wire.begin();
 initGyro();
 
 cli();//stop interrupt
 Timer1.initialize(20000);         // initialize timer1, en microsegundos
 Timer1.attachInterrupt(calculo_yaw);  // attaches callback() as a timer overflow interrupt
 sei();//allow interrupts
 
 Serial.begin(115200);  
 Serial3.begin(9600);  


}

void loop() {
   
 do{
  go_yaw(90);
  getGyroscopeData(gyro); 
  } while(abs(error) > 5);

 delay(4000);

 avanzar();

 delay(4000);
 
 yaw = 0;
 hx = 0;
 hy = 0;
 hz = 0;
 
 do{
  go_yaw(90);
  getGyroscopeData(gyro); 
  } while(abs(error) > 5);
  

 delay(4000);

 avanzar();

 delay(4000);
 
  yaw = 0;
  hx = 0;
  hy = 0;
  hz = 0;
  
 do{
  go_yaw(90);
  getGyroscopeData(gyro); 
  } while(abs(error) > 5);
  
 delay(4000);

 avanzar();

 delay(4000);

  yaw = 0;
  hx = 0;
  hy = 0;
  hz = 0;

 delay(4000);

}


void go_yaw(int yaw_deseado){
  
  error = yaw_deseado - yaw;
  if(start == true) {
    if(error > 0){
      if(abs(error)<=180){
          error = yaw_deseado - yaw;
          uc = Kp*error;
          uc = abs(uc);
          if(uc > vmax) uc = vmax; //Saturación
          
          Serial3.print("derecha  "); 
          Serial3.print(yaw); 
          Serial3.print("    "); 
          Serial3.println(yaw_deseado);  
          analogWrite(M1F,0);
          analogWrite(M1B,uc);
          analogWrite(M2F,uc);
          analogWrite(M2B,0);
      }
  
      else{
          error = 360-(yaw_deseado - yaw);
          uc = Kp*error;
          uc = abs(uc);
          if(uc > vmax) uc = vmax; //Saturación
          
          Serial3.print("izquierda  ");  
          Serial3.print(yaw); 
          Serial3.print("    "); 
          Serial3.println(yaw_deseado);
          analogWrite(M1F,uc);
          analogWrite(M1B,0);
          analogWrite(M2F,0);
          analogWrite(M2B,uc);
      }
    }
    
    else{

      if(abs(error)<=180){
          error = yaw_deseado - yaw;
          uc = Kp*error;
          uc = abs(uc);
          if(uc > vmax) uc = vmax; //Saturación
          
          Serial3.print("izquierda  ");
          Serial3.print(yaw); 
          Serial3.print("    "); 
          Serial3.println(yaw_deseado);
          analogWrite(M1F,uc);
          analogWrite(M1B,0);
          analogWrite(M2F,0);
          analogWrite(M2B,uc);
          
      }
  
      else{
          error = 360-(yaw_deseado - yaw);
          uc = Kp*error;
          uc = abs(uc);
          if(uc > vmax) uc = vmax; //Saturación
          
          Serial3.print("derecha  ");
          Serial3.print(yaw); 
          Serial3.print("    "); 
          Serial3.println(yaw_deseado);  
          analogWrite(M1F,0);
          analogWrite(M1B,uc);
          analogWrite(M2F,uc);
          analogWrite(M2B,0);
      }
      
    }

  
  }

}

void avanzar(){
  analogWrite(M1F,vmax);
  analogWrite(M1B,0);
  analogWrite(M2F,vmax);
  analogWrite(M2B,0);

  delay(800);

  analogWrite(M1F,0);
  analogWrite(M1B,0);
  analogWrite(M2F,0);
  analogWrite(M2B,0);
  
}

void calculo_yaw(){
 
   hx = gyro[0] / 14.375 - 5;
   hy = gyro[1] / 14.375 - 2;
   hz = gyro[2] / 6;
 
    yaw += (((float)(prev_hz + hz) * sampleTime)*1) / 2000; //
//    int inc = (prev_hz + hz)/2;
//    Serial.print("incremento=");
//    Serial.println(inc);
    prev_hz= hz;  // Se debe recordar una muestra previa de velocidad
    // Se coloca el ángulo recorrido en una escala de 0 a 360 grados
    if (yaw < 0){
      yaw += 360;
    }
    else if (yaw >= 360)
    {
      yaw -= 360;
    }     

   Serial.print(" Z=");
   Serial.print((int)hz);
   Serial.print(" yaw=");
   Serial.println(yaw);
   
}

//---------------- Functions
//Writes val to address register on ACC
void writeTo(int DEVICE, byte address, byte val) {
  Wire.beginTransmission(DEVICE); //start transmission to ACC 
  Wire.write(address);        // send register address
  Wire.write(val);        // send value to write
  Wire.endTransmission(); //end transmission
}
//reads num bytes starting from address register on ACC in to buff array
 void readFrom(int DEVICE, byte address, int num, byte buff[]) {
 Wire.beginTransmission(DEVICE); //start transmission to ACC 
 Wire.write(address);        //sends address to read from
 Wire.endTransmission(); //end transmission
 
 Wire.beginTransmission(DEVICE); //start transmission to ACC
 Wire.requestFrom(DEVICE, num);    // request 6 bytes from ACC
 
 int i = 0;
 while(Wire.available())    //ACC may send less than requested (abnormal)
 { 
   buff[i] = Wire.read(); // receive a byte
   i++;
 }
 Wire.endTransmission(); //end transmission
}

