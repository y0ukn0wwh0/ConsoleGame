#include "Arduino.h"
#include "Arduboy2.h"
#include "Scanner.h"
#include "Font3x5.h"

const uint8_t PROGMEM explore[] = {
0x00, 0x60, 0x78, 0x44, 0x5a, 0x5a, 0x5d, 0x5d, 0x5a, 0x5a, 0x44, 0x78, 0x60, 0x00,
0x20, 0x30, 0x36, 0x36, 0x16, 0x20, 0x30, 0x30, 0x20, 0x16, 0x36, 0x36, 0x30, 0x20,
};

Scanner::Scanner(Arduboy2 arduboy, Font3x5 font){
	_arduboy = arduboy;
	_font = font;
	reset();
}

void Scanner::gameLoop(uint8_t const scanIcon[]) {
	_arduboy.pollButtons();

	if (!_tagFound) {
		_arduboy.drawBitmap(_arduboy.width() / 2 - 6, 8, scanIcon, 12, 15, WHITE);
		printCentered(_arduboy.width() / 2, 38, "GET CLOSE TO A TAG!");

		if (_arduboy.justPressed(A_BUTTON)) {
			_tagFound = true;
		}
	}
	else {
		_arduboy.drawBitmap(_arduboy.width() / 2 - 6, 8, explore, 14, 14, WHITE);
		printCentered(_arduboy.width() / 2, 38, "YOU FOUND A DUNGEON!");
	}
}

void Scanner::printCentered(uint8_t x, uint8_t y, String text) {
	uint8_t newX = x - (text.length() * 4) / 2;
	_font.setCursor(newX, y);
	_font.print(text);
}

void Scanner::reset() {
	_tagFound = false;
}