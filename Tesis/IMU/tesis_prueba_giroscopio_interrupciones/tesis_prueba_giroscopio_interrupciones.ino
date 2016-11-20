#include "TimerOne.h"

//From http://www.varesano.net//
#include <Wire.h> // I2C library, gyroscope
// Gyroscope ITG3200 
#define GYRO 0x68 //  when AD0 is connected to GND ,gyro address is 0x68.
//#define GYRO 0x69  // when AD0 is connected to VCC ,gyro address is 0x69  
#define G_SMPLRT_DIV 0x15
#define G_DLPF_FS 0x16
#define G_INT_CFG 0x17
#define G_PWR_MGM 0x3E
#define G_TO_READ 8 // 2 bytes for each axis x, y, z
// offsets are chip specific. 
int g_offx = 64; //120
int g_offy = 34; //20
int g_offz = 8; //93
int hx, hy, hz, turetemp;
int prev_hx, prev_hy, prev_hz;
float roll,pitch, yaw; //x,y,z
int roll2,pitch2, yaw2; //x,y,z
//initializes the gyroscope

// Declaración de variables para muestras de la velocidad
unsigned long time=0;
int sampleTime=20;

void initGyro()
{
 /*****************************************
 * ITG 3200
 * power management set to:
 * clock select = internal oscillator
 * no reset, no sleep mode
 * no standby mode
 * sample rate to = 125Hz
 * parameter to +/- 2000 degrees/sec
 * low pass filter = 5Hz
 * no interrupt
 ******************************************/
 writeTo(GYRO, G_PWR_MGM, 0x00);
 writeTo(GYRO, G_SMPLRT_DIV, 0x07); // EB, 50, 80, 7F, DE, 23, 20, FF
 writeTo(GYRO, G_DLPF_FS, 0x1E); // +/- 2000 dgrs/sec, 1KHz, 1E, 19
 writeTo(GYRO, G_INT_CFG, 0x00);
}
void getGyroscopeData(int * result)
{
 /**************************************
 Gyro ITG-3200 I2C
 registers:
 temp MSB = 1B, temp LSB = 1C
 x axis MSB = 1D, x axis LSB = 1E
 y axis MSB = 1F, y axis LSB = 20
 z axis MSB = 21, z axis LSB = 22
 *************************************/
 int regAddress = 0x1B;
 int temp, x, y, z;
 byte buff[G_TO_READ];
 readFrom(GYRO, regAddress, G_TO_READ, buff); //read the gyro data from the ITG3200
 result[0] = ((buff[2] << 8) | buff[3]) + g_offx;
 result[1] = ((buff[4] << 8) | buff[5]) + g_offy;
 result[2] = ((buff[6] << 8) | buff[7]) + g_offz;
 result[3] = (buff[0] << 8) | buff[1]; // temperature
 }
 //
void setup()
{
 Wire.begin();
 initGyro();
 
 cli();//stop interrupt
 Timer1.initialize(20000);         // initialize timer1, en microsegundos
 Timer1.attachInterrupt(calculo_angulos);  // attaches callback() as a timer overflow interrupt
 sei();//allow interrupts

 Serial.begin(115200);
 Serial3.begin(9600);
}
//
void loop()
{
 byte addr;
 int gyro[4];
 getGyroscopeData(gyro);
// hx = gyro[0] / 5.59 ;
// hy = gyro[1] / 5.59;
// hz = gyro[2] / 5.59;
 
 hx = gyro[0] / 14.375 - 5;
 hy = gyro[1] / 14.375 - 2;
 hz = gyro[2] / 14.375;
 
 turetemp = 35+ ((double) (gyro[3] + 13200)) / 280; // temperature
 
    //Envio por bluetooth
   Serial3.print(" roll=");
   Serial3.print(roll);
   Serial3.print(" pitch=");
   Serial3.print(pitch);
   Serial3.print(" yaw=");
   Serial3.println(yaw);
   
 delay(10); 
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

void calculo_angulos(){

    roll += (((float)(prev_hx + hx) * sampleTime)*1) / 2000; //
    prev_hx= hx;  // Se debe recordar una muestra previa de velocidad
    // Se coloca el ángulo recorrido en una escala de 0 a 360 grados
    if (roll < 0){
      roll += 360;
    }
    else if (roll >= 360)
    {
      roll -= 360;
    }
    
    roll2=(roll*255)/360;
    
    //***********************************************************************
    
    pitch += (((float)(prev_hy + hy) * sampleTime)*1) / 2000; //
    prev_hy= hy;  // Se debe recordar una muestra previa de velocidad
    // Se coloca el ángulo recorrido en una escala de 0 a 360 grados
    if (pitch < 0){
      pitch += 360;
    }
    else if (pitch >= 360)
    {
      pitch -= 360;
    }
    
    pitch2= (pitch*255)/360;
    
    //***********************************************************************
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
    
     yaw2= (yaw*255)/360;
     
   Serial.print(" X=");
   Serial.print((int)hx );
   Serial.print(" Y=");
   Serial.print((int)hy );
   Serial.print(" Z=");
   Serial.print((int)hz);
   Serial.print(" roll=");
   Serial.print(roll);
   Serial.print(" pitch=");
   Serial.print(pitch);
   Serial.print(" yaw=");
   Serial.println(yaw);
   
//   Serial3.print(" X=");
//   Serial3.print((int)hx );
//   Serial3.print(" Y=");
//   Serial3.print((int)hy );
//   Serial3.print(" Z=");
//   Serial3.print((int)hz);
//   Serial3.print(" roll=");
//   Serial3.print(roll);
//   Serial3.print(" pitch=");
//   Serial3.print(pitch);
//   Serial3.print(" yaw=");
//   Serial3.println(yaw);
  
}
