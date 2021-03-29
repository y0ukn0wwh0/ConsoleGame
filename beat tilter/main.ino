#include <Arduboy2.h>
#include <Button.h>
Arduboy2 arduboy;
bool menu = true;
//char buttons[] = {'A', 'B', 'U', 'D', 'L', 'R'};
unsigned long initTime;
//char b = 'J';
Button buttons[100];
int idx = 0;

void setup() {
  arduboy.begin();
  arduboy.setFrameRate(15);
  
  initTime = millis();
}


void loop() {
  if (!(arduboy.nextFrame()))
    return;

  arduboy.clear();
  
  buttonsPressed();

  if(menu)
    drawMenu();
  else{
    drawGame();
    generateButton();
    for(int i = 0; i < sizeof(buttons); i++){
      buttons[i].display();
      buttons[i].move();
    }
  }
  
  arduboy.display();
}

void drawMenu(){
  arduboy.drawRoundRect(3, 6, 120, 52, 3, WHITE);
  
  printCenteredX(arduboy.width()/2, 3, "BEAT TILTER");
  arduboy.drawPixel(30, 6, BLACK);
  
  printCenteredX(arduboy.width()/2, 20, "START  A");
  
  arduboy.drawCircle(84, 23, 6, WHITE);
}

void drawGame(){
  arduboy.drawRect(1, 1, 25, 60, WHITE);
  arduboy.drawRect(101, 1, 25, 60, WHITE);
  
  arduboy.drawCircle(13, 50, 5, WHITE);
  arduboy.drawCircle(113, 50, 5, WHITE);
  
  printCenteredX(arduboy.width()/2, 20, String(b));
}

void generateButton(){
  if(millis() - initTime >= 2000){
    //int i = random(0, 6);
    Button button();
    buttons[idx] = button;
    idx++;
    initTime = millis();
    //b = buttons[i];
  }
}

void printCenteredX(int x, int y, String text){
  int totalX = text.length() * 6;
  arduboy.setCursor(x-totalX/2, y);
  arduboy.print(text);
}

void buttonsPressed(){
  if (menu && arduboy.pressed(A_BUTTON)){
    menu = false;
  }else if (!menu && arduboy.pressed(B_BUTTON)){
    menu = true;
  }
}