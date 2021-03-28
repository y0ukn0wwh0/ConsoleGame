#include <Arduboy2.h>

// make an instance of arduboy used for many functions
Arduboy2 arduboy;


// This function runs once in your game.
// use it for anything that needs to be set only once in your game.
void setup() {
  // initiate arduboy instance
  arduboy.begin();

  // here we set the framerate to 15, we do not need to run at
  // default 60 and it saves us battery life
  arduboy.setFrameRate(15);
}


// our main game loop, this runs once every cycle/frame.
// this is where our game logic goes.
void loop() {
  // pause render until it's time for the next frame
  if (!(arduboy.nextFrame()))
    return;

  // first we clear our screen to black
  arduboy.clear();

  drawMenu();
  
  // then we finaly we tell the arduboy to display what we just wrote to the display
  arduboy.display();
}

void drawMenu(){
  arduboy.drawRoundRect(3, 6, 120, 52, 3, WHITE);
  
  printCenteredX(arduboy.width()/2, 3, "BEAT TILTER", 0);
  arduboy.drawPixel(30, 6, BLACK);
  
  printCenteredX(arduboy.width()/2, 20, "START  A", 0);
  
  arduboy.drawCircle(84, 23, 6, WHITE);
}

void printCenteredX(int x, int y, char text[], int extrasize){
  int totalX = strlen(text) * 6 + extrasize;
  arduboy.setCursor(x-totalX/2, y);
  arduboy.print(text);
}