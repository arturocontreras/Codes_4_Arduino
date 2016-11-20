#include <NewPing.h>
int ibyte,val;
int datas[10];
int data[9];
int XT; //Tipo de tarea
int carga;
int nivel_tanque;
float medida_u1;
float medida_u2;
int flag1;
unsigned long tiempo_inicio;

#define PC Serial
#define C1 Serial1
#define SCADA Serial2

#define VA1 2 // Electroválvula 1, tipo salida a relé //IZQUIERDA
#define VA2 3 // Electroválvula 2, tipo salida a relé //DERECHA
#define MB  4 // Relé de la motobomba

//Tareas
#define fumigacion  1
#define adquisicion 2
#define transporte  3
#define MAX_CARGA   100
#define MIN_LEVEL_TANQUE   10
#define REF_U1   100
#define REF_U2   100
#define TIEMPO_PARADA   10000 //En milisegundos

//Sensores de ultrasonido
#define trig1 41
#define echo1 43
#define trig2 45
#define echo2 47
#define trig3 49
#define echo3 51
#define MAX_DISTANCE 200 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.

NewPing tanque(trig1, echo1, MAX_DISTANCE); // NewPing setup of pins and maximum distance.
NewPing arbol_der(trig2, echo2, MAX_DISTANCE); // NewPing setup of pins and maximum distance.
NewPing arbol_izq(trig3, echo3, MAX_DISTANCE); // NewPing setup of pins and maximum distance.

//Sensores Analógicos
#define S1 A1 
#define S2 A2 
#define S3 A3 
#define S4 A4 
#define transmisor_presion A14
#define corriente_total A10
#define votaje_total A9
#define humedad_suelo A12
#define ph_suelo A13
#define radiacion_solar A11
//Sensores I2C y digitales
#define dht11 53

//

//Entradas y salidas extras
#define Out1 23 
#define Out2 25 
#define Out3 27 
#define Out4 29 
#define In1  31 
#define In2  33 
#define In3  35 
#define In4  37 

// variables
int buttonState = 0;        

void setup() {
  // initialize the LED pin as an output:
  pinMode(VA1, OUTPUT);      
  pinMode(VA2, OUTPUT);   
  pinMode(MB, OUTPUT);   
  
  PC.begin(9600);
  C1.begin(9600); //Comunicación con C1
  SCADA.begin(9600); //Comunicación con SCADA
}

void loop(){
  
  medida_u1 = medida1();

  if(medida_u1 <= REF_U1 && medida_u1>10 && medida_u1!=0 ) //detecta el arbol en el lado1?
  digitalWrite(VA1, HIGH);  
  else
  digitalWrite(VA1, LOW);
  
  medida_u2 = medida2();
  
  if(medida_u2 <= REF_U2 && medida_u2>10 && medida_u2!=0 ) //detecta el arbol en el lado1?
  digitalWrite(VA2, HIGH);  
  else
  digitalWrite(VA2, LOW);
    
  delay(50);                      // Wait 50ms between pings (about 20 pings/sec). 29ms should be the shortest delay between pings.

  control_presion();
  
  read_sensors();
}

void enviar_datos(){}
void init_sensors(){}
boolean llego_DP(){} 
void colocar_sensor(){}
void recoger_sensor(){} 
void read_sensors(){
  //Se van a tomar 4 muestras que se van a promediar
  //Trabajaremos con interrupción timer 1
  enviar_datos();
 
}
void control_presion(){
}

float medida1(){
  unsigned int uS = arbol_izq.ping(); // Send ping, get ping time in microseconds (uS).
  Serial.print("Ping: ");
  Serial.print(uS / US_ROUNDTRIP_CM); // Convert ping time to distance in cm and print result (0 = outside set distance range)
  Serial.println("cm");
  return uS / US_ROUNDTRIP_CM;
}

float medida2(){
  unsigned int uS = arbol_der.ping(); // Send ping, get ping time in microseconds (uS).
  Serial.print("Ping: ");
  Serial.print(uS / US_ROUNDTRIP_CM); // Convert ping time to distance in cm and print result (0 = outside set distance range)
  Serial.println("cm");
  return uS / US_ROUNDTRIP_CM;
}
