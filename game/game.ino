#include <Arduboy2.h>
#include <FoodGame.h>
#include <DanceGame.h>
#include "sprites.c"

Arduboy2 arduboy;
FoodGame fg = FoodGame(arduboy);
DanceGame dg = DanceGame(arduboy);
Sprites sprites;
byte frame = 0;
bool fgBool = false;
bool dgBool = false;

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
  
  if(fgBool){
    fg.gameLoop();
    if(arduboy.justPressed(B_BUTTON))fgBool = false;
  }else if(dgBool){
    dg.gameLoop();
    if(arduboy.justPressed(B_BUTTON))dgBool = false;
  }else{
    if(arduboy.justPressed(A_BUTTON)){
      fg.reset();
      fgBool = true;
    }else if(arduboy.justPressed(B_BUTTON)){
      dg.reset();
      dgBool = true;
    }

    drawMenu();
    sprites.drawSelfMasked(3 * arduboy.width()/4 - 8, arduboy.height()/2 - 8, mandrake_idle, frame);
    if (arduboy.everyXFrames(10)) frame++;
    if (frame > 1) frame = 0;
  }
  
  arduboy.display();
  arduboy.idle();
}

void printCentered(int x, int y, String text){
  int totalX = text.length() * 6;
  arduboy.setCursor(x-totalX/2, y);
  arduboy.print(text);
}

void drawMenu(){
  arduboy.setCursor(3, arduboy.height()-12);
  arduboy.print("INTERACT");
  drawArrow(8*6 + 5, arduboy.height()-9);
}
void drawArrow(int x, int y){
  arduboy.drawPixel(x, y, WHITE);
  arduboy.drawPixel(x+1, y+1, WHITE);
  arduboy.drawPixel(x+1, y, WHITE);
  arduboy.drawPixel(x+1, y-1, WHITE);
}
