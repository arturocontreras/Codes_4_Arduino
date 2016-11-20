/*
#include "arduino.h"
#include "parpadeo.h"

parpadeo::parpadeo(int pata , int ton , int toff)
{
  pinMode(pata, OUTPUT);  //ejemplo
  _pata = pata;
  _ton = ton;
  _toff = toff;
}
void parpadeo::parpadear()
{
  digitalWrite(_pata, HIGH);   //enciende
  delay(_ton);                   
  digitalWrite(_pata, LOW);    //apaga
  delay(_toff);   
}*/

#include "arduino.h"
#include "parpadeo.h"

parpadeo::parpadeo()
{

}
void parpadeo::parpadear(int pata , int ton , int toff)
{
  pinMode(pata, OUTPUT);  //ejemplo
  _pata = pata;
  _ton = ton;
  _toff = toff;
  digitalWrite(_pata, HIGH);   //enciende
  delay(_ton);                   
  digitalWrite(_pata, LOW);    //apaga
  delay(_toff);   
}
void parpadeo::state(int pin , int estado)
{
  pinMode(pin, OUTPUT);  //ejemplo 
 _pin = pin;
 _estado = estado;

  if(estado == 1) digitalWrite(_pin, HIGH);   //enciende
  else  analogWrite(_pin, _estado);   //enciende
}