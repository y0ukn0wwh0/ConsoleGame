#ifndef FoodGame_h
#define FoodGame_h

#include "Arduino.h"
#include "Arduboy2.h"

class FoodGame
{
  public:
    FoodGame(Arduboy2 arduboy);
    void gameLoop();
	void reset();
  private:
    Arduboy2 _arduboy;
	Rect _player;
	long _startTime;
	Point _fruits[10];
	short _fruitSize;
	short _score;
	short _missed;
	bool _gameOver;
	short _timeInterval;
	void buttonsPressed();
	void drawPlayer();
	void spawnFruit();
	void drawFruit();
	void printCentered(int x, int y, String text);
};

#endif