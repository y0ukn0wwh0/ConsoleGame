#ifndef Items_h
#define Items_h

#include "Arduino.h"
#include "Arduboy2.h"
#include "Font3x5.h"

class Items
{
public:
	Items(Arduboy2 arduboy, Font3x5 font);
	void gameLoop(uint8_t const scanIcon[], uint8_t const animal[]);
	void reset();
private:
	Arduboy2 _arduboy;
	Font3x5 _font;
	char *_items[3];
	byte _itemSel;
	enum screen { menu, scan, confirm};
	screen _sc;
	void drawMenu();
	void drawArrow(uint8_t x, uint8_t y);
	void printCentered(uint8_t x, uint8_t y, String text);
};

#endif