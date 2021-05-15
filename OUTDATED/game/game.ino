#include <Arduboy2.h>
#include <FoodGame.h>
#include <DanceGame.h>
#include <Scanner.h>
#include <Items.h>
#include <Font3x5.h>
#include "sprites.c"

Arduboy2 arduboy;
Font3x5 font = Font3x5();
FoodGame foodGame = FoodGame(arduboy);
DanceGame danceGame = DanceGame(arduboy, font);
Scanner scanner = Scanner(arduboy, font);
Items items = Items(arduboy, font);
//Sprites sprites;
//byte frame = 0;
char *options[] = {"FOOD", "DANCE", "INTERACT", "ITEMS", "SCANNER"};
byte optionSel = 0;

enum screen {menu, food, dance, item, scan};
screen sc = menu;

void setup() {
  arduboy.begin();
  arduboy.setFrameRate(15);
  Serial.begin(9600);
}

void loop() {
  if (!(arduboy.nextFrame()))
    return;

  arduboy.clear();
  arduboy.pollButtons();

  switch(sc){
    case menu:
      if(arduboy.justReleased(A_BUTTON)){
        switch(optionSel){
          case 0:
            foodGame.reset();
            sc = food;
            break;
          case 1:
            danceGame.reset();
            sc = dance;
            break;
          case 3:
            items.reset();
            sc = item;
            break;
          case 4:
            scanner.reset();
            sc = scan;
            break;  
        }
      }
      
      if (arduboy.justPressed(RIGHT_BUTTON)) {
        optionSel++;
        Serial.println(optionSel);
        Serial.println(options[optionSel]);
        if (optionSel == 5) optionSel = 0;
      } else if (arduboy.justPressed(LEFT_BUTTON)) {
        optionSel--;
        if (optionSel == 255) optionSel = 4;
      }

      drawMenu();
      arduboy.drawBitmap(3 * arduboy.width() / 4 - 8, arduboy.height() / 2 - 8, mandrake, 16, 16, WHITE);
      //sprites.drawSelfMasked(3 * arduboy.width() / 4 - 8, arduboy.height() / 2 - 8, mandrake, frame);
      //if (arduboy.everyXFrames(10)) frame++;
      //if (frame > 1) frame = 0;

      break;
    case food:
      foodGame.gameLoop(mandrake);
      if (arduboy.justPressed(B_BUTTON))sc = menu;
      break;
    case dance:
      danceGame.gameLoop(mandrake);
      if (arduboy.justPressed(B_BUTTON))sc = menu;
      break;
    case item:
      items.gameLoop(scanIcon, mandrake);
      if (arduboy.justPressed(B_BUTTON))sc = menu;
      break;
    case scan:
      scanner.gameLoop(scanIcon);
      if (arduboy.justPressed(B_BUTTON))sc = menu;
      break;
  }
  
  arduboy.display();
  arduboy.idle();
}

/*void printCentered(int x, int y, String text){
  int totalX = text.length() * 6;
  arduboy.setCursor(x-totalX/2, y);
  arduboy.print(text);
  }*/

void drawMenu() {
  font.setCursor(3, arduboy.height() - 12);
  font.print(options[optionSel]);
  drawArrow(strlen(options[optionSel]) * 4 + 5, arduboy.height() - 9);
}

void drawArrow(byte x, byte y) {
  arduboy.drawPixel(x, y, WHITE);
  arduboy.drawPixel(x + 1, y + 1, WHITE);
  arduboy.drawPixel(x + 1, y, WHITE);
  arduboy.drawPixel(x + 1, y - 1, WHITE);
}
