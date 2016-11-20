#include <Wire.h> // I2C library, gyroscope
// Accelerometer ADXL345
#define ACC (0xA7>>1)    //ADXL345 ACC address
#define A_TO_READ (6)        //num of bytes we are going to read each time (two bytes for each axis)
void initAcc() {
//Turning on the ADXL345
writeTo(ACC, 0x2D, 1<<3);      
writeTo(ACC, 0x31, 0x0B);
writeTo(ACC, 0x2C, 0x09);
//by default the device is in +-2g range reading
}
void getAccelerometerData(int * result) {
int regAddress = 0x32;    //first axis-acceleration-data register on the ADXL345
byte buff[A_TO_READ];
readFrom(ACC, regAddress, A_TO_READ, buff); //read the acceleration data from the ADXL345
//each axis reading comes in 10 bit resolution, ie 2 bytes.  Least Significat Byte first!!
//thus we are converting both bytes in to one int
result[0] = (((int)buff[1]) << 8) | buff[0];   
result[1] = (((int)buff[3])<< 8) | buff[2];
result[2] = (((int)buff[5]) << 8) | buff[4];
}
void setup()
{
Serial.begin(9600);
Wire.begin();
initAcc();
}
void loop()
{
int hx,hy,hz;
int acc[3];
int ang_x; //roll
int ang_y; //pitch

getAccelerometerData(acc);
hx = acc[0];
hy = acc[1];
hz = acc[2];
Serial.print(" X=");
Serial.print(hx);
Serial.print(" Y=");
Serial.print(hy);
Serial.print(" Z=");
Serial.println(hz);
delay(50); 
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

