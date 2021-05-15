#include "Arduino.h"
#include "Arduboy2.h"
#include "FoodGame.h"

const uint8_t apple[] PROGMEM = {
0x18, 0x3c, 0x7d, 0x3b, 0x74, 0x3c, 0x18, 0x00
};

FoodGame::FoodGame(Arduboy2 arduboy)
{
  _arduboy = arduboy;
  _player = Rect(_arduboy.width()/2, _arduboy.height() - 16, 16, 16);
  _fruitSize = 8;
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

void FoodGame::drawPlayer(uint8_t const animal[])
{
  //_arduboy.fillRect(_player.x, _player.y, _player.width, _player.height, WHITE);
  _arduboy.drawBitmap(_player.x, _player.y, animal, _player.width, _player.height, WHITE);
  if(_player.x >= _arduboy.width()) _player.x -= _arduboy.width();
  if(_player.x + _player.width <= 0) _player.x += _arduboy.width();
}

void FoodGame::spawnFruit(){
  if(millis() - _startTime > _timeInterval){
    int idx = 0;
    for(int i = 0; i < 10; i++){
      if(_fruits[i].x == 0){
        idx = i;
        break;
      }
    }

    _fruits[idx].x = random(_fruitSize/2, _arduboy.width()-_fruitSize/2);
    _fruits[idx].y = -4;
	_timeInterval -= 50;
    _startTime = millis();
  }
}

void FoodGame::drawFruit(){
  for(int i = 0; i < 10; i++){
    if(_fruits[i].x != 0){
      //_arduboy.fillCircle(_fruits[i].x, _fruits[i].y, _fruitSize, WHITE);
	  _arduboy.drawBitmap(_fruits[i].x - 4, _fruits[i].y - 7, apple, 8, 8, WHITE);
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

void FoodGame::gameLoop(uint8_t const animal[]){
  buttonsPressed();
  
  if(!_gameOver){
    drawPlayer(animal);
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
  for(int i = 0; i < 10; i++){
    _fruits[i].x = 0;
  }
}