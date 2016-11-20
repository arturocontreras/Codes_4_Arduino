#include <SoftwareSerial.h>
#include "TinyGPS.h"
#include <Wire.h>
#include "TimerThree.h"

TinyGPS gps;
//**************************************ADICIONALES PARA RECEPCION DE COORDENADAS
int ibyte,val;
int sizes;
char datas[10];
char data[400];
boolean flag1 = false;
float latitud,longitud;

//*********************************
#define HW__VERSION_CODE 10736 // SparkFun "9DOF Razor IMU" version "SEN-10736" (HMC5883L magnetometer)
#define pi 3.14159265
#define r_t 6378000
// OUTPUT OPTIONS
/*****************************************************************/
// Set your serial port baud rate used to send out data here!
#define OUTPUT__BAUD_RATE 115200

// Sensor data output interval in milliseconds
// This may not work, if faster than 20ms (=50Hz)
// Code is tuned for 20ms, so better leave it like that
#define OUTPUT__DATA_INTERVAL 20  // in milliseconds

// Output mode definitions (do not change)
#define OUTPUT__MODE_CALIBRATE_SENSORS 0 // Outputs sensor min/max values as text for manual calibration
#define OUTPUT__MODE_ANGLES 1 // Outputs yaw/pitch/roll in degrees
#define OUTPUT__MODE_SENSORS_CALIB 2 // Outputs calibrated sensor values for all 9 axes
#define OUTPUT__MODE_SENSORS_RAW 3 // Outputs raw (uncalibrated) sensor values for all 9 axesw
#define OUTPUT__MODE_SENSORS_BOTH 4 // Outputs calibrated AND raw sensor values for all 9 axes
// Output format definitions (do not change)
#define OUTPUT__FORMAT_TEXT 0 // Outputs data as text
#define OUTPUT__FORMAT_BINARY 1 // Outputs data as binary float

// Select your startup output mode and format here!
int output_mode = OUTPUT__MODE_ANGLES;
int output_format = OUTPUT__FORMAT_TEXT;

// Select if serial continuous streaming output is enabled per default on startup.
#define OUTPUT__STARTUP_STREAM_ON true  // true or false

// If set true, an error message will be output if we fail to read sensor data.
// Message format: "!ERR: reading <sensor>", followed by "\r\n".
boolean output_errors = false;  // true or false

#define OUTPUT__HAS_RN_BLUETOOTH false  // true or false


// "accel x,y,z (min/max) = X_MIN/X_MAX  Y_MIN/Y_MAX  Z_MIN/Z_MAX"
#define ACCEL_X_MIN ((float) -318)
#define ACCEL_X_MAX ((float) 295)
#define ACCEL_Y_MIN ((float) -301)
#define ACCEL_Y_MAX ((float) 305)
#define ACCEL_Z_MIN ((float) -278)
#define ACCEL_Z_MAX ((float) 334)

// Magnetometer (standard calibration mode)
// "magn x,y,z (min/max) = X_MIN/X_MAX  Y_MIN/Y_MAX  Z_MIN/Z_MAX"
#define MAGN_X_MIN ((float) -121)
#define MAGN_X_MAX ((float) 476)
#define MAGN_Y_MIN ((float) -198)
#define MAGN_Y_MAX ((float) 426)
#define MAGN_Z_MIN ((float) -307)
#define MAGN_Z_MAX ((float) 255)

// Gyroscope
// "gyro x,y,z (current/average) = .../OFFSET_X  .../OFFSET_Y  .../OFFSET_Z
#define GYRO_AVERAGE_OFFSET_X ((float) 64.0)
#define GYRO_AVERAGE_OFFSET_Y ((float) 34.0)
#define GYRO_AVERAGE_OFFSET_Z ((float) 8.0)


// DEBUG OPTIONS
/*****************************************************************/
// When set to true, gyro drift correction will not be applied
#define DEBUG__NO_DRIFT_CORRECTION false
// Print elapsed time after each I/O loop
#define DEBUG__PRINT_LOOP_TIME false

// Check if hardware version code is defined
#ifndef HW__VERSION_CODE
  // Generate compile error
  #error YOU HAVE TO SELECT THE HARDWARE YOU ARE USING! See "HARDWARE OPTIONS" in "USER SETUP AREA" at top of Razor_AHRS.ino!
#endif

//Envio a C3
SoftwareSerial mySerial(53, 52); // RX, TX
int V1F,V1B,V2F,V2B; //valores de velocidad a enviar al receptor
#define maximo_rpm 10

// Sensor calibration scale and offset values
#define ACCEL_X_OFFSET ((ACCEL_X_MIN + ACCEL_X_MAX) / 2.0f)
#define ACCEL_Y_OFFSET ((ACCEL_Y_MIN + ACCEL_Y_MAX) / 2.0f)
#define ACCEL_Z_OFFSET ((ACCEL_Z_MIN + ACCEL_Z_MAX) / 2.0f)
#define ACCEL_X_SCALE (GRAVITY / (ACCEL_X_MAX - ACCEL_X_OFFSET))
#define ACCEL_Y_SCALE (GRAVITY / (ACCEL_Y_MAX - ACCEL_Y_OFFSET))
#define ACCEL_Z_SCALE (GRAVITY / (ACCEL_Z_MAX - ACCEL_Z_OFFSET))

#define MAGN_X_OFFSET ((MAGN_X_MIN + MAGN_X_MAX) / 2.0f)
#define MAGN_Y_OFFSET ((MAGN_Y_MIN + MAGN_Y_MAX) / 2.0f)
#define MAGN_Z_OFFSET ((MAGN_Z_MIN + MAGN_Z_MAX) / 2.0f)
#define MAGN_X_SCALE (100.0f / (MAGN_X_MAX - MAGN_X_OFFSET))
#define MAGN_Y_SCALE (100.0f / (MAGN_Y_MAX - MAGN_Y_OFFSET))
#define MAGN_Z_SCALE (100.0f / (MAGN_Z_MAX - MAGN_Z_OFFSET))


// Gain for gyroscope (ITG-3200)
#define GYRO_GAIN 0.06957 // Same gain on all axes
#define GYRO_SCALED_RAD(x) (x * TO_RAD(GYRO_GAIN)) // Calculate the scaled gyro readings in radians per second

// DCM parameters
#define Kp_ROLLPITCH 0.02f
#define Ki_ROLLPITCH 0.00002f
#define Kp_YAW 1.2f
#define Ki_YAW 0.00002f

// Stuff
#define STATUS_LED_PIN 13  // Pin number of status LED
#define GRAVITY 256.0f // "1G reference" used for DCM filter and accelerometer calibration
#define TO_RAD(x) (x * 0.01745329252)  // *pi/180
#define TO_DEG(x) (x * 57.2957795131)  // *180/pi

// Sensor variables
float accel[3];  // Actually stores the NEGATED acceleration (equals gravity, if board not moving).
float accel_min[3];
float accel_max[3];

float magnetom[3];
float magnetom_min[3];
float magnetom_max[3];
float magnetom_tmp[3];

float gyro[3];
float gyro_average[3];
int gyro_num_samples = 0;

// DCM variables
float MAG_Heading;
float Accel_Vector[3]= {0, 0, 0}; // Store the acceleration in a vector
float Gyro_Vector[3]= {0, 0, 0}; // Store the gyros turn rate in a vector
float Omega_Vector[3]= {0, 0, 0}; // Corrected Gyro_Vector data
float Omega_P[3]= {0, 0, 0}; // Omega Proportional correction
float Omega_I[3]= {0, 0, 0}; // Omega Integrator
float Omega[3]= {0, 0, 0};
float errorRollPitch[3] = {0, 0, 0};
float errorYaw[3] = {0, 0, 0};
float DCM_Matrix[3][3] = {{1, 0, 0}, {0, 1, 0}, {0, 0, 1}};
float Update_Matrix[3][3] = {{0, 1, 2}, {3, 4, 5}, {6, 7, 8}};
float Temporary_Matrix[3][3] = {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}};

// Euler angles
float yaw;
float pitch;
float roll;

// DCM timing in the main loop
unsigned long timestamp;
unsigned long timestamp_old;
float G_Dt; // Integration time for DCM algorithm

// More output-state variables
boolean output_stream_on;
boolean output_single_on;
int curr_calibration_sensor = 0;
boolean reset_calibration_session_flag = true;
int num_accel_errors = 0;
int num_magn_errors = 0;
int num_gyro_errors = 0;

boolean flag2=true;


//********Variables para el GPS*************
long startMillis;
long secondsToFirstLocation = 0;
unsigned long chars = 0;

#define DEBUG

float latitude = 0.0;
float longitude = 0.0;
bool newData = false;
int sensorValue=0;
//***********************************

void read_sensors() {
  Read_Gyro(); // Read gyroscope
  Read_Accel(); // Read accelerometer
  Read_Magn(); // Read magnetometer
}

// Read every sensor and record a time stamp
// Init DCM with unfiltered orientation
// TODO re-init global vars?
void reset_sensor_fusion() {
  float temp1[3];
  float temp2[3];
  float xAxis[] = {1.0f, 0.0f, 0.0f};

  read_sensors();
  timestamp = millis();
  
  // GET PITCH
  // Using y-z-plane-component/x-component of gravity vector
  pitch = -atan2(accel[0], sqrt(accel[1] * accel[1] + accel[2] * accel[2]));
	
  // GET ROLL
  // Compensate pitch of gravity vector 
  Vector_Cross_Product(temp1, accel, xAxis);
  Vector_Cross_Product(temp2, xAxis, temp1);
  // Normally using x-z-plane-component/y-component of compensated gravity vector
  // roll = atan2(temp2[1], sqrt(temp2[0] * temp2[0] + temp2[2] * temp2[2]));
  // Since we compensated for pitch, x-z-plane-component equals z-component:
  roll = atan2(temp2[1], temp2[2]);
  
  // GET YAW
  Compass_Heading();
  yaw = MAG_Heading;
  
  // Init rotation matrix
  init_rotation_matrix(DCM_Matrix, yaw, pitch, roll);
}

// Apply calibration to raw sensor readings
void compensate_sensor_errors() {
    // Compensate accelerometer error
    accel[0] = (accel[0] - ACCEL_X_OFFSET) * ACCEL_X_SCALE;
    accel[1] = (accel[1] - ACCEL_Y_OFFSET) * ACCEL_Y_SCALE;
    accel[2] = (accel[2] - ACCEL_Z_OFFSET) * ACCEL_Z_SCALE;

    // Compensate magnetometer error
#if CALIBRATION__MAGN_USE_EXTENDED == true
    for (int i = 0; i < 3; i++)
      magnetom_tmp[i] = magnetom[i] - magn_ellipsoid_center[i];
    Matrix_Vector_Multiply(magn_ellipsoid_transform, magnetom_tmp, magnetom);
#else
    magnetom[0] = (magnetom[0] - MAGN_X_OFFSET) * MAGN_X_SCALE;
    magnetom[1] = (magnetom[1] - MAGN_Y_OFFSET) * MAGN_Y_SCALE;
    magnetom[2] = (magnetom[2] - MAGN_Z_OFFSET) * MAGN_Z_SCALE;
#endif

    // Compensate gyroscope error
    gyro[0] -= GYRO_AVERAGE_OFFSET_X;
    gyro[1] -= GYRO_AVERAGE_OFFSET_Y;
    gyro[2] -= GYRO_AVERAGE_OFFSET_Z;
}

// Reset calibration session if reset_calibration_session_flag is set
void check_reset_calibration_session()
{
  // Raw sensor values have to be read already, but no error compensation applied

  // Reset this calibration session?
  if (!reset_calibration_session_flag) return;
  
  // Reset acc and mag calibration variables
  for (int i = 0; i < 3; i++) {
    accel_min[i] = accel_max[i] = accel[i];
    magnetom_min[i] = magnetom_max[i] = magnetom[i];
  }

  // Reset gyro calibration variables
  gyro_num_samples = 0;  // Reset gyro calibration averaging
  gyro_average[0] = gyro_average[1] = gyro_average[2] = 0.0f;
  
  reset_calibration_session_flag = false;
}

void turn_output_stream_on()
{
  output_stream_on = true;
  digitalWrite(STATUS_LED_PIN, HIGH);
}

void turn_output_stream_off()
{
  output_stream_on = false;
  digitalWrite(STATUS_LED_PIN, LOW);
}

// Blocks until another byte is available on serial port
char readChar()
{
  while (Serial.available() < 1) { } // Block
  return Serial.read();
}

//***************************Variables para el CONTROL---------------------

float yaw_v ;
unsigned long t;
unsigned long Tor;
float epsi = 0.5;
float x_a;
float y_a;
float x_o;
float y_o;
float vl;
float wang;
float W = 1.5;
int T = 20;
///Constantes de control
float kp = 5;
float ki = 0.1;
float int_e = 0;
float R = 0.175;
float u1 = 0;
float u2 = 0;
float u1_ant = 0;
float u2_ant = 0;
float u1_send = 0;
float u2_send = 0;
float v1 = 0; //Right
float v2 = 0; //Left
float phid;
float phi;
float e;
float umax = 5.2; //Configurar maxima velocidad y aceleración.
float amax = 5.2;
// Main loop
float Y[3] = {-12.025104, -12.024982, -12.024725};
float X[3] = {-77.047326, -77.047207, -77.047583};

//**********************************************************************************

void setup()
{
  //-----------------------Comunicacion con C1 --------------------------------------------------
  
  Serial1.begin(115200); 

  //-------------------------------IMU--------------------------------------
  cli();//stop interrupts

  Timer3.initialize(20000);         // initialize timer1, en microsegundos
 // Timer1.pwm(9, 512);                // setup pwm on pin 9, 50% duty cycle
  Timer3.attachInterrupt(callback);  // attaches callback() as a timer overflow interrupt
  
  sei();//allow interrupts
  
  // Init serial output
  Serial.begin(OUTPUT__BAUD_RATE);

  //XBEE_recepcion
  Serial2.begin(115200);
  for (int j=0;j<400;j=j+1){
    data[j] = 0.0000000000000000f;  
  }
  //GPS ************************************************
  Serial3.begin(115200); 
  //C3
  mySerial.begin(115200); //XBEE

  startMillis = millis();
  Serial.println("Starting");
  //********************************************

  // Init status LED
  pinMode (STATUS_LED_PIN, OUTPUT);
  digitalWrite(STATUS_LED_PIN, LOW);

  // Init sensors
  delay(50);  // Give sensors enough time to start
  I2C_Init();
  Accel_Init();
  Magn_Init();
  Gyro_Init();
  
  // Read sensors, init DCM algorithm
  delay(20);  // Give sensors enough time to collect data
  reset_sensor_fusion();
  
    // Init output
  #if (OUTPUT__HAS_RN_BLUETOOTH == true) || (OUTPUT__STARTUP_STREAM_ON == false)
    turn_output_stream_off();
  #else
    turn_output_stream_on();
  #endif
  
   G_Dt=0.020;

}

void loop(){
  for(int i=0; i < 3; i++){
    t = millis();
    Tor = millis();
    x_o = X[i]*pi*r_t/180;
    y_o = Y[i]*pi*r_t/180;
    serial3_recepcion();
    gps_recepcion();
    x_a = longitude*pi*r_t/180; //Ajustar a metros y verificar nuevas coordenadas
    y_a = latitude*pi*r_t/180;
    
    while(abs((x_o-x_a)*(x_o-x_a)+(y_o-y_a)*(y_o-y_a)) > epsi){
     serial3_recepcion();
     gps_recepcion();
     //Serial.println(yaw_v);
     coordenadas_recepcion(); //RECEPCION COORDENADAS XBEE
      ///IMU
      chars = 0;
      read_sensors();
      
      T = (millis()-t);
      if((millis()-t) > 200){
        yaw_v = TO_DEG(yaw);
    
        phi = (-90-yaw_v)*pi/180; /// Ajustar orientacion

        if(phi < -3.141592653)
          phi += 6.283185307;
        if(phi > 3.141592653)
          phi -=6.283185307;
        ///GPS
        gps_recepcion();
        x_a = pi*longitude*r_t/180; //Ajustar a metros y verificar nuevas coordenadas
        y_a = pi*latitude*r_t/180;
        Control();
        t=millis();
      }
    }
  }
}

void callback()
{  
      compensate_sensor_errors();
      // Run DCM algorithm
      Compass_Heading(); // Calculate magnetic heading
      Matrix_update();
      Normalize();
      Drift_correction();
      Euler_angles();
      
      //output_angles();
}

//************************GPS***************************************************************

void gps_recepcion(){
  if (newData)
    {     
    unsigned long age;
    gps.f_get_position(&latitude, &longitude, &age);
    
    latitude == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : latitude;
    longitude == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : longitude;
//    
//    Serial.print("Location: ");
//    Serial.print(latitude, 6);
//    Serial.print(" , ");
//    Serial.print(longitude, 6);
//    Serial.println("");
    
    newData = false;
   } 
}

void serial3_recepcion() {
 while (Serial3.available())
    {
      int c = Serial3.read();
//      Serial.print((char)c); // if you uncomment this you will see the raw data from the GPS
      ++chars;
      if (gps.encode(c)) // Did a new valid sentence come in?
        newData = true;
    }
  
}

///////-----------CONTROL--------------------------------

void Control(){
  phid = atan2(y_o-y_a, x_o-x_a);
  e = phid-phi;
  e = atan2(sin(e),cos(e));
  int_e = int_e + e*T/1000;
  if ((millis()- Tor) < 3000){
    vl = 0;
  }
 else{
    if(max((abs(e)>0.35),(abs((x_o-x_a)*(x_o-x_a)+(y_o-y_a)*(y_o-y_a)) < 1))){
      vl = 0.40;
     }
    else{
      vl = 0.9;
     }
 }
  wang = kp*e + ki*int_e;
  u1_ant = u1;
  u2_ant = u2;
  u1 = (vl/R)+(wang*W/2);
  u2 = (vl/R)-(wang*W/2); 
  Saturadores();
  u1_send = map(u1,-5.2,5.2,0,200);
  u2_send = map(u2,-5.2,5.2,0,200);
  
  Serial1.print(yaw_v);
  Serial1.print(" ");
  Serial1.print(latitude, 6);
  Serial1.print(" ");
  Serial1.print(longitude, 6);
  Serial1.print(" ");
  Serial1.print(u1);
  Serial1.print(" ");
  Serial1.print(u2);
  Serial1.print(" ");
  Serial1.print(phi);
  Serial1.print(" ");
  Serial1.print(phid);
  Serial1.print(" ");
  Serial1.println(e);
  ///Recalcular
  v1 = R*u1;
  v2 = R*u2;
  vl = (v1+v2)/2;
  wang = (v1-v2)/W;

  enviar_c3(u1,u2);
  ///Enviar datos arduino -> Control de velocidades
  ///Estimando nueva posición:  EstdePosicion()  
}

void Saturadores(){
  if (abs(u1) > umax){
    u1 = sign(u1)*umax;
  }   
  if (abs(u2) > umax){
    u2 = sign(u2)*umax;
  }
}
void EstdePosicion(){
  x_a = x_a + T*vl*cos(phi);///phi del IMU, T periodo de muestreo
  y_a = y_a + T*vl*sin(phi);
}

int sign(float x){
  if(x>=0){
    return 1;
    }
  else{
    return -1;
    }
}

//********************************************************************************************

void enviar_c3(float u1,float u2){

  float ww1,ww2;

  ww1 = 30*u1/pi;//(rad/s->rpm(rev/minuto--2*pi rad/60s))
  ww2 = 30*u2/pi;
  
  if(ww1 >= 0){
    V1F = map(ww1,0,50,0,maximo_rpm);
    V1B = 0;
  }
  else{
    V1F = 0;
    V1B = map(-ww1,0,50,0,maximo_rpm);
  }

  if(ww2 >= 0){
    V2F = map(ww2,0,50,0,maximo_rpm);
    V2B = 0;
  }
  else{
    V2F = 0;
    V2B = map(-ww2,0,50,0,maximo_rpm);
  }
  
  mySerial.print("x");
  mySerial.print((char)V1F);
  mySerial.print((char)V1B);
  mySerial.print((char)V2F);
  mySerial.print((char)V2B);
}

//***************RECEPCION COORDENADAS XBEE**************************************
void coordenadas_recepcion(){
  if(Serial2.available()>0)
    {
    
    Timer3.stop(); 
    Timer3.detachInterrupt(); 
    //  cli();
      val=Serial2.read();
        if(val=='x'){

        while(Serial2.available()==0){};
        sizes=(int)Serial2.read();
        while(Serial2.available()==0){};
          int i=0;
          for(i=0;i<sizes;i=i+1){
           data[i]=Serial2.read();
            while(Serial2.available()==0 && (char)data[i]!='y'){
           };
           }
          
           flag1 = true;
         }
  //sei(); 
   }
   
   
    if(flag1){
     for (int j=0;j<sizes;j=j+8){
       
     latitud  = integracion_gps((int)data[j],(int)data[j+1],(int)data[j+2],(int)data[j+3]);
     longitud = integracion_gps((int)data[j+4],(int)data[j+5],(int)data[j+6],(int)data[j+7]);
     Serial.print("     ");
     Serial.print((int)data[j]);
     Serial.print(" ");
     Serial.print((int)data[j+1]);
     Serial.print(" ");
     Serial.print((int)data[j+2]);
     Serial.print(" ");
     Serial.print((int)data[j+3]);
     Serial.print(" ");
     Serial.print((int)data[j+4]);
     Serial.print(" ");
     Serial.print((int)data[j+5]);
     Serial.print(" ");
     Serial.print((int)data[j+6]);
     Serial.print(" ");
     Serial.println((int)data[j+7]);
     
     Serial.print("P");
     Serial.print(j/8 +1);
     Serial.print(":  Latitud =  ");
     Serial.print(latitud , 6);
     Serial.print("   Longitud =  ");
     Serial.println(longitud , 6 );
     
     }
     
     flag1 = false; 
   } 
   
    Timer3.attachInterrupt(callback);
   
   
}

float integracion_gps(int a , int b , int c , int d){

return -((float)a+(float)b/100.0000000000+(float)c/10000.0000000000+(float)d/1000000.0000000000);  
  
}

