#define state1 9

#include "Arduino.h"
#if !defined(SERIAL_PORT_MONITOR)
  #error "Arduino version not supported. Please update your IDE to the latest version."
#endif

#if defined(SERIAL_PORT_USBVIRTUAL)
  // Shield Jumper on HW (for Leonardo and Due)
  #define port SERIAL_PORT_HARDWARE
  #define pcSerial SERIAL_PORT_USBVIRTUAL
#else
  // Shield Jumper on SW (using pins 12/13 or 8/9 as RX/TX)
  #include "SoftwareSerial.h"
  SoftwareSerial port(12, 13);
  SoftwareSerial serialx(2, 3);

  #define pcSerial SERIAL_PORT_MONITOR
#endif

#include "EasyVR.h"

EasyVR easyvr(port);

//Groups and Commands
enum Groups
{
  GROUP_0  = 0,
  GROUP_1  = 1,
  GROUP_2  = 2,
  GROUP_3  = 3,
  GROUP_4  = 4,
  GROUP_5  = 5,
  GROUP_6  = 6,
};

enum Group0 
{
  G0_OPEN = 0,
};

enum Group1 
{
  G1_HOLA = 0,
  G1_CHAU = 1,
  G1_PERSIANA = 2,
  G1_CLOSE = 3,
};

enum Group2 
{
  G2_ABRIR_PUERTA = 0,
  G2_CERRAR_PUERTA = 1,
  G2_ABRIR_VENTANA = 2,
  G2_CERRAR_VENTANA = 3,
  G2_PRENDER_LUCES = 4,
  G2_APAGAR_LUCES = 5,
  G2_ABRIR_PERSIANA = 6,
  G2_CERRAR_PERSIANA = 7,
  G2_ENCENDER_CALEFACCION = 8,
  G2_APAGAR_CALEFACCION = 9,
  G2_ALARMA = 10,
};

enum Group3 
{
  G3_LLAMAR_EMERGENCIA = 0,
  G3_ABRIR_VENTANA = 1,
  G3_ABRIR_PUERTA = 2,
  G3_PRENDER_LUZ = 3,
};

enum Group4 
{
  G4_ABRIR_VENTANA = 0,
  G4_ABRIR_PUERTA = 1,
  G4_LLAMAR_EMERGENCIA = 2,
};

enum Group5 
{
  G5_PERUANO = 0,
  G5_HOLA_PERU = 1,
  G5_CHAU_PERU = 2,
};

enum Group6 
{
  G6_CERRAR_PUERTA = 0,
  G6_ABRIR_VENTANA = 1,
  G6_CERRAR_VENTANA = 2,
  G6_XZXZ = 3,
};


int8_t group, idx;

void setup()
{
  // setup PC serial port
  pcSerial.begin(9600);
  serialx.begin(38400);

  // bridge mode?
  int mode = easyvr.bridgeRequested(pcSerial);
  switch (mode)
  {
  case EasyVR::BRIDGE_NONE:
    // setup EasyVR serial port
    port.begin(9600);
    // run normally
    pcSerial.println(F("---"));
    pcSerial.println(F("Bridge not started!"));
    break;
    
  case EasyVR::BRIDGE_NORMAL:
    // setup EasyVR serial port (low speed)
    port.begin(9600);
    // soft-connect the two serial ports (PC and EasyVR)
    easyvr.bridgeLoop(pcSerial);
    // resume normally if aborted
    pcSerial.println(F("---"));
    pcSerial.println(F("Bridge connection aborted!"));
    break;
    
  case EasyVR::BRIDGE_BOOT:
    // setup EasyVR serial port (high speed)
    port.begin(115200);
    // soft-connect the two serial ports (PC and EasyVR)
    easyvr.bridgeLoop(pcSerial);
    // resume normally if aborted
    pcSerial.println(F("---"));
    pcSerial.println(F("Bridge connection aborted!"));
    break;
  }

  while (!easyvr.detect())
  {
    Serial.println("EasyVR not detected!");
    delay(1000);
  }

  easyvr.setPinOutput(EasyVR::IO1, LOW);
  Serial.println("EasyVR detected!");
  easyvr.setTimeout(5);
  easyvr.setLanguage(4);

  group = GROUP_2; //<-- start group (customize)

  serialx.write("AT+LINK=3014,10,91158");
  serialx.write("\n");
  serialx.write("\r");

  delay(3000);
}

void action();

void loop()
{
  easyvr.setPinOutput(EasyVR::IO1, HIGH); // LED on (listening)

  Serial.print("Say a command in Group ");
  Serial.println(group);
  easyvr.recognizeCommand(group);

  do
  {
    // can do some processing while waiting for a spoken command
  }
  while (!easyvr.hasFinished());
  
  easyvr.setPinOutput(EasyVR::IO1, LOW); // LED off

  idx = easyvr.getWord();
  if (idx >= 0)
  {
    // built-in trigger (ROBOT)
    // group = GROUP_X; <-- jump to another group X
    return;
  }
  idx = easyvr.getCommand();
  if (idx >= 0)
  {
    // print debug message
    uint8_t train = 0;
    char name[32];
    Serial.print("Command: ");
    Serial.print(idx);
    if (easyvr.dumpCommand(group, idx, name, train))
    {
      Serial.print(" = ");
      Serial.println(name);
    }
    else
      Serial.println();
    easyvr.playSound(0, EasyVR::VOL_FULL);
    // perform some action
    action();
  }
  else // errors or timeout
  {
    if (easyvr.isTimeout())
      Serial.println("Timed out, try again...");
    int16_t err = easyvr.getError();
    if (err >= 0)
    {
      Serial.print("Error ");
      Serial.println(err, HEX);
    }
  }
}

void action()
{
    switch (group)
    {
    case GROUP_0:
      switch (idx)
      {
      case G0_OPEN:
        // write your action code here
        // group = GROUP_X; <-- or jump to another group X for composite commands
        break;
      }
      break;
    case GROUP_1:
      switch (idx)
      {
      case G1_HOLA:
        // write your action code here
        // group = GROUP_X; <-- or jump to another group X for composite commands
        break;
      case G1_CHAU:
        // write your action code here
        // group = GROUP_X; <-- or jump to another group X for composite commands
        break;
      case G1_PERSIANA:
        // write your action code here
        // group = GROUP_X; <-- or jump to another group X for composite commands
        break;
      case G1_CLOSE:
        // write your action code here
        // group = GROUP_X; <-- or jump to another group X for composite commands
        break;
      }
      break;
    case GROUP_2:
      switch (idx)
      {
      case G2_ABRIR_PUERTA:
        serialx.print('x');
        serialx.print('a');
        // write your action code here
        // group = GROUP_X; <-- or jump to another group X for composite commands
        break;
      case G2_CERRAR_PUERTA:
        serialx.print('x');
        serialx.print('b');
        // write your action code here
        // group = GROUP_X; <-- or jump to another group X for composite commands
        break;
      case G2_ABRIR_VENTANA:
        serialx.print('x');
        serialx.print('c');
        // write your action code here
        // group = GROUP_X; <-- or jump to another group X for composite commands
        break;
      case G2_CERRAR_VENTANA:
        serialx.print('x');
        serialx.print('d');

        // write your action code here
        // group = GROUP_X; <-- or jump to another group X for composite commands
        break;
      case G2_PRENDER_LUCES:
        serialx.print('x');
        serialx.print('e');
        // write your action code here
        // group = GROUP_X; <-- or jump to another group X for composite commands
        break;
      case G2_APAGAR_LUCES:
        serialx.print('x');
        serialx.print('f');
        // write your action code here
        // group = GROUP_X; <-- or jump to another group X for composite commands
        break;
      case G2_ABRIR_PERSIANA:
        serialx.print('x');
        serialx.print('g');
        // write your action code here
        // group = GROUP_X; <-- or jump to another group X for composite commands
        break;
      case G2_CERRAR_PERSIANA:
        serialx.print('x');
        serialx.print('h');
        // write your action code here
        // group = GROUP_X; <-- or jump to another group X for composite commands
        break;
      case G2_ENCENDER_CALEFACCION:
        serialx.print('x');
        serialx.print('i');
        // write your action code here
        // group = GROUP_X; <-- or jump to another group X for composite commands
        break;
      case G2_APAGAR_CALEFACCION:
        serialx.print('x');
        serialx.print('j');
        // write your action code here
        // group = GROUP_X; <-- or jump to another group X for composite commands
        break;
      case G2_ALARMA:
        serialx.print('x');
        serialx.print('k');
        // write your action code here
        // group = GROUP_X; <-- or jump to another group X for composite commands
        break;
      }
      break;
    case GROUP_3:
      switch (idx)
      {
      case G3_LLAMAR_EMERGENCIA:
        // write your action code here
        // group = GROUP_X; <-- or jump to another group X for composite commands
        break;
      case G3_ABRIR_VENTANA:
        // write your action code here
        // group = GROUP_X; <-- or jump to another group X for composite commands
        break;
      case G3_ABRIR_PUERTA:
        // write your action code here
        // group = GROUP_X; <-- or jump to another group X for composite commands
        break;
      case G3_PRENDER_LUZ:
        // write your action code here
        // group = GROUP_X; <-- or jump to another group X for composite commands
        break;
      }
      break;
    case GROUP_4:
      switch (idx)
      {
      case G4_ABRIR_VENTANA:
        // write your action code here
        // group = GROUP_X; <-- or jump to another group X for composite commands
        break;
      case G4_ABRIR_PUERTA:
        // write your action code here
        // group = GROUP_X; <-- or jump to another group X for composite commands
        break;
      case G4_LLAMAR_EMERGENCIA:
        // write your action code here
        // group = GROUP_X; <-- or jump to another group X for composite commands
        break;
      }
      break;
    case GROUP_5:
      switch (idx)
      {
      case G5_PERUANO:
        // write your action code here
        // group = GROUP_X; <-- or jump to another group X for composite commands
        break;
      case G5_HOLA_PERU:
        // write your action code here
        // group = GROUP_X; <-- or jump to another group X for composite commands
        break;
      case G5_CHAU_PERU:
        // write your action code here
        // group = GROUP_X; <-- or jump to another group X for composite commands
        break;
      }
      break;
    case GROUP_6:
      switch (idx)
      {
      case G6_CERRAR_PUERTA:
        // write your action code here
        // group = GROUP_X; <-- or jump to another group X for composite commands
        break;
      case G6_ABRIR_VENTANA:
        // write your action code here
        // group = GROUP_X; <-- or jump to another group X for composite commands
        break;
      case G6_CERRAR_VENTANA:
        // write your action code here
        // group = GROUP_X; <-- or jump to another group X for composite commands
        break;
      case G6_XZXZ:
        // write your action code here
        // group = GROUP_X; <-- or jump to another group X for composite commands
        break;
      }
      break;
    }
}
