#include "Arduino.h"
#include "Arduboy2.h"
#include "DanceGame.h"
#include "dance_sprites.c"

uint8_t _possibleButtons[] = {LEFT_BUTTON, RIGHT_BUTTON, UP_BUTTON, DOWN_BUTTON};

DanceGame::DanceGame(Arduboy2 arduboy)
{
  _arduboy = arduboy;
  reset();
}

void DanceGame::generateButtons(){
  for(short i = _idxW; i < _idxW + (_seqAmount-_idxW); i++){
    _sequence[i] = _possibleButtons[random(4)];
  }
}

void DanceGame::changeButton(){
  if(!_showButton){
    delay(800);
    _showButton = true;
    if(_idxR == _seqAmount){
      _showSequence = false;
      _idxR = 0;
    }
  }else{
    delay(200);
    _idxR++;
    _showButton = false;
  }
}

void DanceGame::buttonToImg(uint8_t button){
  switch(button){
    case LEFT_BUTTON:
        _arduboy.drawBitmap(_arduboy.width()/2 - 8, _arduboy.height()/2, mandrake_left, 16, 16, WHITE);
        drawArrow(_arduboy.width()/2 - 12, _arduboy.height()/2 + 8, 0);
        break;
    case RIGHT_BUTTON:
        _arduboy.drawBitmap(_arduboy.width() / 2 - 8, _arduboy.height() / 2, mandrake_right, 16, 16, WHITE);
        drawArrow(_arduboy.width() / 2 + 12, _arduboy.height() / 2 + 8, 1);
        break;
    case UP_BUTTON:
        _arduboy.drawBitmap(_arduboy.width() / 2 - 8, _arduboy.height() / 2, mandrake_up, 16, 16, WHITE);
        drawArrow(_arduboy.width() / 2, _arduboy.height() / 2 - 4, 2);
        break;
    case DOWN_BUTTON:
        _arduboy.drawBitmap(_arduboy.width() / 2 - 8, _arduboy.height() / 2, mandrake_down, 16, 16, WHITE);
        drawArrow(_arduboy.width() / 2, _arduboy.height() / 2 + 20, 3);
        break;
    default:
        _arduboy.drawBitmap(_arduboy.width() / 2 - 8, _arduboy.height() / 2, mandrake_standing, 16, 16, WHITE);
        break;
  }
}

void DanceGame::checkButtonsPressed(){
  uint8_t button = 0;
  if(_arduboy.justReleased(LEFT_BUTTON)){
    _btnPressed = LEFT_BUTTON;
    button = LEFT_BUTTON;
  }else if(_arduboy.justReleased(RIGHT_BUTTON)){
    _btnPressed = RIGHT_BUTTON;
    button = RIGHT_BUTTON;
  }else if(_arduboy.justReleased(UP_BUTTON)){
    _btnPressed = UP_BUTTON;
    button = UP_BUTTON;
  }else if(_arduboy.justReleased(DOWN_BUTTON)){
    _btnPressed = DOWN_BUTTON;
    button = DOWN_BUTTON;
  }
  
  if(button != _sequence[_idxR] && button != 0){
    _gameOver = true;
  }else if(button == _sequence[_idxR]){
    _idxR++;
  }

  if(_idxR >= _seqAmount){
    _seqAmount++;
    _idxR = 0;
    _idxW = _seqAmount-1;
    _showSequence = true;
    _btnPressed = 0;
    randomSeed(_arduboy.generateRandomSeed());
    generateButtons();
  }
}

void DanceGame::printCentered(uint8_t x, uint8_t y, String text){
  uint8_t newX = x - (text.length() * 6)/2;
  _arduboy.setCursor(newX, y);
  _arduboy.print(text);
}

void DanceGame::gameLoop(){
  _arduboy.pollButtons();
  
  if(!_gameOver){
    if(_showSequence){
      printCentered(_arduboy.width()/2, 10, "WATCH CLOSELY");
      if (_showButton)
          buttonToImg(_sequence[_idxR]);
      changeButton();
    }else{
      checkButtonsPressed();
      printCentered(_arduboy.width()/2, 10, "REPEAT THE DANCE");
      buttonToImg(_btnPressed);
    }
  }else{
    printCentered(_arduboy.width()/2, 10, "GAMEOVER");
    printCentered(_arduboy.width() / 2, 30, "SCORE: " + String(_seqAmount));
  }
}

void DanceGame::drawArrow(uint8_t x, uint8_t y, uint8_t arrow) {
    switch (arrow) {
        case 0:
            _arduboy.drawPixel(x, y, WHITE);
            _arduboy.drawPixel(x, y + 1, WHITE);
            _arduboy.drawPixel(x, y - 1, WHITE);
            _arduboy.drawPixel(x - 1, y, WHITE);
            break;
        case 1:
            _arduboy.drawPixel(x, y, WHITE);
            _arduboy.drawPixel(x, y + 1, WHITE);
            _arduboy.drawPixel(x, y - 1, WHITE);
            _arduboy.drawPixel(x + 1, y, WHITE);
            break;
        case 2:
            _arduboy.drawPixel(x, y, WHITE);
            _arduboy.drawPixel(x - 1, y, WHITE);
            _arduboy.drawPixel(x + 1, y, WHITE);
            _arduboy.drawPixel(x, y - 1, WHITE);
            break;
        case 3:
            _arduboy.drawPixel(x, y, WHITE);
            _arduboy.drawPixel(x - 1, y, WHITE);
            _arduboy.drawPixel(x + 1, y, WHITE);
            _arduboy.drawPixel(x, y + 1, WHITE);
            break;
    }
}

void DanceGame::reset(){
  _gameOver = false;
  _idxR = 0;
  _idxW = 0;
  _seqAmount = 3;
  _btnPressed = 0;
  _showSequence = true;
  _showButton = true;
  randomSeed(_arduboy.generateRandomSeed());
  generateButtons();
}