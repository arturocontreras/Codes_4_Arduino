int ibyte,val;
int datas[10];
int data[9];
int XT; //Tipo de tarea
int carga;
int nivel_tanque;
int medida_u1;
int medida_u2;
int flag1;
unsigned long tiempo_inicio;

#define PC Serial
#define C1 Serial1
#define SCADA Serial2

#define VA1 2 // Electroválvula 1, tipo salida a relé
#define VA2 3 // Electroválvula 2, tipo salida a relé
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

//Sensores Analógicos
#define S1 A1 
#define S2 A2 
#define S3 A3 
#define S4 A4 


//Sensores I2C

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

   if(C1.available()>0){
    val=C1.read();
      if(val=='S'){
      while(C1.available()==0){};
        int i=0;
        for(i=0;i<9;i=i+1){
         data[i]=C1.read();
          while(C1.available()==0 && (char)data[i]!='J'){
         };
         } 
       }
  } 
  
  XT =data[0];
  
  if(XT == 1){ //Transporte
    if(carga < MAX_CARGA)
    C1.print(1); //Envía señal de habilitación de navegación
    else{
    C1.print(2); //Envía señal de deshabilitación de navegación
    }
  }
  
  if(XT == 2){ //Fumigación
    if(nivel_tanque < MIN_LEVEL_TANQUE)
    C1.print(2); //Envía señal de deshabilitación de navegación
    else{
    C1.print(1); //Envía señal de habilitación de navegación
    digitalWrite(MB, HIGH); //Activando motor bomba
    //Acticación de electroválvulas
      if(medida_u1 <= REF_U1) //detecta el arbol en el lado1?
      digitalWrite(VA1, HIGH);  
      else
      digitalWrite(VA1, LOW);
       
      if(medida_u2 <= REF_U2) //detecta el arbol en el lado2?
      digitalWrite(VA2, HIGH);  
      else
      digitalWrite(VA2, LOW); 
    }
  }
  
  if(XT == 3){ //Adquisición de datos
  init_sensors();
 
    if(llego_DP()){ //El robot llego a un data point?
      C1.print(2); //Envía señal de deshabilitación de navegación, esto puede estar contenido directamente en el C2
      if(flag1 == 1){
      tiempo_inicio = millis();
      flag1 = 0;
      }
      
      while((millis() - tiempo_inicio) < TIEMPO_PARADA){
      colocar_sensor(); //Uniendo algunos sensores con suelo del terreno
      read_sensors();
      }

      recoger_sensor();  
      
    }
    
  C1.print(1); //Envía señal de habilitación de navegación
  }
  
  enviar_datos();
}

void enviar_datos(){}
void init_sensors(){}
boolean llego_DP(){} 
void colocar_sensor(){}
void recoger_sensor(){} 
void read_sensors(){
  //Se van a tomar 4 muestras que se van a promediar
  //Trabajaremos con interrupción timer 1
  

}
