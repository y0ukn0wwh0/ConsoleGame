#ifndef Button_h
#define Button_h

#include "Arduino.h"
#include "Arduboy2.h"

class Button
{
  public:
    Button();
    void display();
    void move();
  private:
    int _posx;
    int _posy;
    char _button;
    char _possibleButtons[];
};

#endif