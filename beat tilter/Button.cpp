#include "Arduino.h"
#include "Arduboy2.h"
#include "Button.h"

Button::Button()
{
  _possibleButtons[] = {'A', 'B', 'U', 'D', 'L', 'R'};
  _button = _possibleButtons[random(0, 6)];
  if(random(0,2) == 0)
    _posx = 13;
  else
    _posx = 113;  
  _posy = -6;
}

void Button::display()
{
  arduboy.setCursor(_posx, _posy);
  arduboy.print(text);
}

void Button::move()
{
  _posy += 1;
}