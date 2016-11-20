//From http://www.varesano.net//
#include <Wire.h> // I2C library, gyroscope
#include <Kalman.h> // Kalman filter library see: http://blog.tkjelectronics.dk/2012/09/a-practical-approach-to-kalman-filter-and-how-to-implement-it/
#include <HMC5883L.h>
// Store our compass as a variable.
HMC5883L compass;

Kalman kalman1; // See https://github.com/TKJElectronics/KalmanFilter for source code

// Gyroscope ITG3200 
#define GYRO 0x68 //  when AD0 is connected to GND ,gyro address is 0x68.
//#define GYRO 0x69  // when AD0 is connected to VCC ,gyro address is 0x69  
#define G_SMPLRT_DIV 0x15
#define G_DLPF_FS 0x16
#define G_INT_CFG 0x17
#define G_PWR_MGM 0x3E
#define G_TO_READ 8 // 2 bytes for each axis x, y, z
// offsets are chip specific. 
//**************Acelerometro
#define ACC (0xA7>>1)    //ADXL345 ACC address
#define A_TO_READ (6)        //num of bytes we are going to read each time (two bytes for each axis)

float den_x,den_y,den_z;
int hx,hy,hz;
int acc[3];
float ang_x; //rho
float ang_y; //phi
float ang_z; //tetha
int error;

//**************

int g_offx = 64; //120
int g_offy = 34; //20
int g_offz = 8; //93
int hxx, hyy, hzz, turetemp;
int prev_hx, prev_hy, prev_hz;
float roll,pitch, yaw; //x,y,z
int roll2,pitch2, yaw2; //x,y,z
float head;
//initializes the gyroscope


//**************Acelerometro

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

//**************
// Declaración de variables para muestras de la velocidad
unsigned long time=0;
int sampleTime=100;
float Angle[2];
double timer1;
double timer2;

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
 Serial.begin(9600);
 Wire.begin();
 initAcc();
 initGyro();
 
 double loopStartTime = micros();
 timer1 = loopStartTime;
 timer2 = loopStartTime;
 
  compass = HMC5883L(); // Construct a new HMC5883 compass.
 error = compass.SetScale(1.3); // Set the scale of the compass.
  
 error = compass.SetMeasurementMode(Measurement_Continuous); // Set the measurement mode to Continuous
}
//
void loop()
{
 byte addr;
 int gyro[4];
 
 //**********Lectura del acelerometro
 head = get_yaw();
 //**********
 
 getGyroscopeData(gyro);
 hxx = gyro[0] / 5.59;
 hyy = gyro[1] / 5.59;
 hzz = gyro[2] / 5.59;
 
// //Aplicar el Filtro Kalman

 yaw = kalman1.getAngle(head, hzz, (double)(micros() - timer1)/1000000); // Calculate the angle using a Kalman filter
 timer1 = micros();
 
 Serial.print("Gy Z : ");
 Serial.print(hzz);
 Serial.print("  magnetometro : ");
 Serial.print(head);
 Serial.print("  yaw : ");
 Serial.println(yaw);
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

float get_yaw(){
  MagnetometerRaw raw = compass.ReadRawAxis();
  // Retrived the scaled values from the compass (scaled to the configured scale).
  MagnetometerScaled scaled = compass.ReadScaledAxis();
  
  // Values are accessed like so:
  int MilliGauss_OnThe_XAxis = scaled.XAxis;// (or YAxis, or ZAxis)

  // Calculate heading when the magnetometer is level, then correct for signs of axis.
  float heading = atan2(scaled.YAxis, scaled.XAxis);

  float declinationAngle = 0.0457;
  heading += declinationAngle;
  
  // Correct for when signs are reversed.
  if(heading < 0)
    heading += 2*PI;
    
  // Check for wrap due to addition of declination.
  if(heading > 2*PI)
    heading -= 2*PI;
   
  // Convert radians to degrees for readability.
  float headingDegrees = heading * 180/M_PI; 

  return headingDegrees;
}
