/*
Dimel Arturo
Libreria parpadeo
*/
/*#ifndef parpadeo_h
#define parpadeo_h
#include "arduino.h"
class parpadeo {
  public:
   parpadeo(int pata , int ton , int toff);
	
   void parpadear();
   
  private:  
   int _pata;
   int _ton; //en ms
   int _toff;
};
#endif*/

/*
Dimel Arturo
Libreria parpadeo
*/
#ifndef parpadeo_h
#define parpadeo_h
#include "arduino.h"
class parpadeo {
  public:
   parpadeo();
	
   void parpadear(int pata , int ton , int toff);
   void state(int pin, int estado);

  private:  
   int _pata;
   int _ton; //en ms
   int _toff;
   int _pin;
   int _estado;	
};
#endif
