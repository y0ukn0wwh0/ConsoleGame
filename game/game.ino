#include <Arduboy2.h>
#include <EEPROM.h>
#include "sprites.c"

Arduboy2 arduboy;
BeepPin1 beep;
unsigned long bulletTime;
byte bulletX = arduboy.width() - 46;
bool goToPlayer = true;
enum screen {choose, start, game, over, won};
screen sc = choose;
byte level = 1;
byte highscore;
byte rectChoiceX = 32;
uint8_t* chosenHero;

#define ENEMY_LEFT arduboy.width()-33
#define BULLET_INTERVAL_RIGHT 32
#define BULLET_INTERVAL_LEFT 24
#define FLOOR_LEVEL 40

void setup() {
  arduboy.begin();
  beep.begin();
  arduboy.initRandomSeed();
  randomSeed(arduboy.generateRandomSeed());
  //EEPROM.write(0, 0);
  highscore = EEPROM.read(0);
  if(highscore == 255)highscore = 0;
}

void loop() {
  if (!(arduboy.nextFrame()))
    return;

  arduboy.clear();
  arduboy.pollButtons();
  beep.timer();

  switch(sc){
    case choose:
      arduboy.drawBitmap(34, arduboy.height()/2-5, hero1, 10, 10, WHITE);
      arduboy.drawBitmap(54, arduboy.height()/2-5, hero2, 10, 10, WHITE);
      arduboy.drawBitmap(74, arduboy.height()/2-5, hero3, 10, 10, WHITE);
      arduboy.drawRect(rectChoiceX, arduboy.height()/2-7, 14, 14);
      if(arduboy.justPressed(B_BUTTON)){
        if(rectChoiceX < 72)rectChoiceX += 20;
        else rectChoiceX = 32;
      }
      if(arduboy.justPressed(A_BUTTON)){
        switch(rectChoiceX){
          case 32:
            chosenHero = hero1;
            break;
          case 52:
            chosenHero = hero2;
            break;
          case 72:
            chosenHero = hero3;
            break;
        }
        sc = start;
      }
      break;
    case start:
      if(highscore != 0)printCentered(20, "HIGHSCORE: " + String(highscore));
      printCentered(30, "PRESS A TO START");
      if(arduboy.justPressed(A_BUTTON)){
        sc = game;
      }
      break;
      
    case game:
      if(bulletX == ENEMY_LEFT){
        if(random(10) < 7 && goToPlayer == false){
          sc = won;
        }else{
          goToPlayer = true;
        }
      }
    
      if(arduboy.justPressed(A_BUTTON) && bulletX+5 < BULLET_INTERVAL_RIGHT  && bulletX+5 > BULLET_INTERVAL_LEFT ){
        beep.tone(beep.freq(5230.251), 5);
        goToPlayer = false;
      }else if(bulletX+5 < BULLET_INTERVAL_LEFT){
        sc = over;
      }

      //arduboy.drawLine(0, FLOOR_LEVEL, arduboy.width(), FLOOR_LEVEL);
    
      arduboy.drawBitmap(16, FLOOR_LEVEL-10, chosenHero, 10, 10, WHITE);
      arduboy.drawBitmap(arduboy.width() - 26, FLOOR_LEVEL-10, getEnemy(level), 10, 10, WHITE);
      
      arduboy.drawBitmap(bulletX, FLOOR_LEVEL - 10, bullet, 10, 10, WHITE);
      //arduboy.drawRect(24, arduboy.height()/2 - 4, 8, 8);

      arduboy.setCursor(arduboy.width() - 10, 3);
      arduboy.print(level);
    
      if(millis() - bulletTime > 15){
        if(goToPlayer)
          bulletX--;
        else
          bulletX++;
        bulletTime = millis();
      }
      break;

    case over:
      printCentered(10, "GAME OVER");
      printCentered(30, "PRESS B TO RESTART");
      if(arduboy.justPressed(B_BUTTON)){
        sc = game;
        bulletX = ENEMY_LEFT;
        goToPlayer = true;
      }
      break;

    case won:
      if(level > highscore){
        highscore = level;
        EEPROM.write(0, level);
      }
      if(level < 4){
        printCentered(10, "MONSTER KILLED");
        printCentered(30, "PRESS A TO NEXT ROUND");
        printCentered(40, "PRESS B TO MENU");
      }
      else{
        printCentered(10, "GAME WON!");
        printCentered(30, "PRESS B TO MENU");
      }
      if(arduboy.justPressed(A_BUTTON) && level < 4){
        level++;
        sc = game;
        bulletX = ENEMY_LEFT;
        goToPlayer = true;
      }
      if(arduboy.justPressed(B_BUTTON)){
        sc = start;
      }
      break;
  }
  
  arduboy.display();
  arduboy.idle();
}

void printCentered(byte y, String text){
  byte totalX = text.length() * 6;
  arduboy.setCursor(arduboy.width()/2 - totalX/2, y);
  arduboy.print(text);
}

uint8_t* getEnemy(byte lvl){
  switch(lvl){
    case 1:
      return tree1;
    case 2:
      return tree2;
    case 3:
      return tree3;
    case 4:
      return tree4;
  }
}
