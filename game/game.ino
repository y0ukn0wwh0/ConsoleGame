#include <Arduboy2.h>
#include <FoodGame.h>
#include <MatchGame.h>

Arduboy2 arduboy;
FoodGame fg;
bool fgBool = false;

void setup() {
  arduboy.begin();
  arduboy.setFrameRate(15);
  Serial.begin(9600);

  fg = FoodGame(arduboy);
}

void loop() {
  if (!(arduboy.nextFrame()))
    return;

  arduboy.clear();
  arduboy.pollButtons();
  
  if(fgBool){
    fg.gameLoop();
    if(arduboy.justReleased(B_BUTTON))fgBool = false;
  }
  else{
    printCentered(arduboy.width()/2, arduboy.height()/2 - 9, "A - FOOD GAME");
    printCentered(arduboy.width()/2, arduboy.height()/2, "B - MATCH GAME");
    if(arduboy.justReleased(A_BUTTON)){
      fg.reset();
      fgBool = true;
    }
  }
  arduboy.display();
}

void printCentered(int x, int y, String text){
  int totalX = text.length() * 6;
  arduboy.setCursor(x-totalX/2, y);
  arduboy.print(text);
}
