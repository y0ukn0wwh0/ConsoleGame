#include "Arduino.h"
#include "Arduboy2.h"
#include "FoodGame.h"

const uint8_t PROGMEM _apple[] = {B01110000, B11111000, B11111100, B11111010, B01110000};

FoodGame::FoodGame(){}

FoodGame::FoodGame(Arduboy2 arduboy)
{
  _arduboy = arduboy;
  _player = Rect(_arduboy.width()/2, _arduboy.height() - 10, 10, 10);
  _fruitSize = 2;
  reset();
}

void FoodGame::buttonsPressed()
{
  if (_arduboy.pressed(LEFT_BUTTON)){
    _player.x -= 3;
  }else if (_arduboy.pressed(RIGHT_BUTTON)){
    _player.x += 3;
  }else if(_gameOver && _arduboy.pressed(A_BUTTON)){
    reset();
  }
}

void FoodGame::drawPlayer()
{
  _arduboy.fillRect(_player.x, _player.y, _player.width, _player.height, WHITE);
  if(_player.x >= _arduboy.width()) _player.x -= _arduboy.width();
  if(_player.x + _player.width <= 0) _player.x += _arduboy.width();
}

void FoodGame::spawnFruit(){
  if(millis() - _startTime > _timeInterval){
    int idx = 0;
    for(int i = 0; i < 5; i++){
      if(_fruits[i].x == 0){
        idx = i;
        break;
      }
    }

    _fruits[idx].x = random(_fruitSize, _arduboy.width()-_fruitSize);
    _fruits[idx].y = -3;
	_timeInterval -= 50;
    _startTime = millis();
  }
}

void FoodGame::drawFruit(){
  for(int i = 0; i < 5; i++){
    if(_fruits[i].x != 0){
      //_arduboy.fillCircle(_fruits[i].x, _fruits[i].y, _fruitSize, WHITE);
	  _arduboy.drawBitmap(_fruits[i].x - 2, _fruits[i].y - 4, _apple, 5, 8, WHITE);
      _fruits[i].y += 2;

      if(_arduboy.collide(_fruits[i], _player)){
        _score++;
        _fruits[i].x = 0;
      }else if(_fruits[i].y > _arduboy.height()+_fruitSize){
        _missed++;
        _fruits[i].x = 0;
      }
    }
  }
}

void FoodGame::printCentered(int x, int y, String text){
  int totalX = text.length() * 6;
  _arduboy.setCursor(x-totalX/2, y);
  _arduboy.print(text);
}

void FoodGame::gameLoop(){
  buttonsPressed();
  
  if(!_gameOver){
    drawPlayer();
    spawnFruit();
    drawFruit();
  }else{
    printCentered(_arduboy.width()/2, 10, "GAME OVER");
    printCentered(_arduboy.width()/2, 20, "Score: " + String(_score));
	printCentered(_arduboy.width()/2, 35, "Press A to restart");
	printCentered(_arduboy.width()/2, 45, "Press B to go back");
  }
  
  if(_missed >= 3)_gameOver = true;
}

void FoodGame::reset(){
  _score = 0;
  _missed = 0;
  _player.x = _arduboy.width()/2;
  _startTime = 0;
  _gameOver = false;
  _timeInterval = 2000;
  for(int i = 0; i < 5; i++){
    _fruits[i].x = 0;
  }
}