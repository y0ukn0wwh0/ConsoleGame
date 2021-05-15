#ifndef Scanner_h
#define Scanner_h

#include "Arduino.h"
#include "Arduboy2.h"
#include "Font3x5.h"

class Scanner
{
public:
	Scanner(Arduboy2 arduboy, Font3x5 font);
	void gameLoop(uint8_t const scanIcon[]);
	void reset();
private:
	Arduboy2 _arduboy;
	Font3x5 _font;
	bool _tagFound;
	void printCentered(uint8_t x, uint8_t y, String text);
};

#endif