#ifndef DanceGame_h
#define DanceGame_h

#include "Arduino.h"
#include "Arduboy2.h"
#include "Font3x5.h"

class DanceGame
{
  public:
    DanceGame(Arduboy2 arduboy, Font3x5 font);
    void gameLoop(uint8_t const animal[]);
	void reset();
  private:
    Arduboy2 _arduboy;
	Font3x5 _font;
	bool _showSequence;
	uint8_t _sequence[20];
	uint8_t _idxW;
	uint8_t _idxR;
	uint8_t _seqAmount;
	bool _showButton;
	bool _gameOver;
	uint8_t _btnPressed;
	void generateButtons();
	void changeButton();
	void buttonToImg(uint8_t button, uint8_t const animal[]);
	void checkButtonsPressed();
	void printCentered(uint8_t x, uint8_t y, String text);
	void drawArrow(uint8_t x, uint8_t y, uint8_t arrow);
};

#endif