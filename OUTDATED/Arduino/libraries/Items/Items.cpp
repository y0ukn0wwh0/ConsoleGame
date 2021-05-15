#include "Arduino.h"
#include "Arduboy2.h"
#include "Items.h"
#include "Font3x5.h"

const uint8_t PROGMEM orb[] = {
0xf8, 0xfc, 0xfe, 0x1f, 0x0f, 0x67, 0x67, 0x07, 0x07, 0x0f, 0x1f, 0xfe, 0xfc, 0xf8,
0x07, 0x0f, 0x1f, 0x3e, 0x3c, 0x38, 0x38, 0x3a, 0x3a, 0x3d, 0x3e, 0x1f, 0x0f, 0x07,
};

Items::Items(Arduboy2 arduboy, Font3x5 font) {
	_arduboy = arduboy;
	_font = font;
	reset();
	_items[0] = "MAGIC ORB";
	_items[1] = "PORTAL";
	_items[2] = "CANDY";
}

void Items::gameLoop(uint8_t const scanIcon[], uint8_t const animal[]) {
	_arduboy.pollButtons();

	switch (_sc) {
		case menu:
			if (_arduboy.justReleased(A_BUTTON)) {
				switch (_itemSel) {
					case 0:
						_sc = scan;
						break;
				}
			}

			if (_arduboy.justPressed(RIGHT_BUTTON)) {
				_itemSel++;
				if (_itemSel == 3) _itemSel = 0;
			}
			else if (_arduboy.justPressed(LEFT_BUTTON)) {
				_itemSel--;
				if (_itemSel == 255) _itemSel = 2;
			}

			drawMenu();
			_arduboy.drawBitmap(3 * _arduboy.width() / 4 - 8, _arduboy.height() / 2 - 8, animal, 16, 16, WHITE);
			break;

		case scan:
			_arduboy.drawBitmap(_arduboy.width() / 2 - 6, 8, scanIcon, 12, 15, WHITE);
			printCentered(_arduboy.width() / 2, 38, "GET CLOSE TO A TAG!");

			if (_arduboy.justPressed(A_BUTTON)) {
				_sc = confirm;
			}
			break;

		case confirm:
			_arduboy.drawBitmap(_arduboy.width() / 2 - 6, 8, orb, 14, 14, WHITE);
			printCentered(_arduboy.width() / 2, 38, "USE MAGIC ORB?");
			break;
			
	}
}

void Items::drawMenu() {
	_font.setCursor(3, 3);
	_font.print(_items[_itemSel]);
	drawArrow(strlen(_items[_itemSel]) * 4 + 5, 6);

	_font.setCursor(3, _arduboy.height() - 12);
	_font.print("ITEMS");
}

void Items::drawArrow(uint8_t x, uint8_t y) {
	_arduboy.drawPixel(x, y, WHITE);
	_arduboy.drawPixel(x + 1, y + 1, WHITE);
	_arduboy.drawPixel(x + 1, y, WHITE);
	_arduboy.drawPixel(x + 1, y - 1, WHITE);
}

void Items::printCentered(uint8_t x, uint8_t y, String text) {
	uint8_t newX = x - (text.length() * 4) / 2;
	_font.setCursor(newX, y);
	_font.print(text);
}

void Items::reset() {
	_sc = menu;
	_itemSel = 0;
}