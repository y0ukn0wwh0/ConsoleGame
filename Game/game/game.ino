#include <Arduboy2.h>
#include <ArduboyTones.h>
#include <EEPROM.h>
#include "sprites.c"

const uint16_t score[] PROGMEM = {
 NOTE_C5,205, NOTE_REST,205, NOTE_C5,205, NOTE_G5,205, NOTE_F5,205, NOTE_REST,205, NOTE_E5,205, NOTE_REST,205,
 NOTE_C5,205, NOTE_REST,205, NOTE_C5,205, NOTE_G5,205, NOTE_F5,205, NOTE_REST,205, NOTE_E5,205, NOTE_REST,205,
 NOTE_C5,205, NOTE_REST,1027, NOTE_E5,205, NOTE_REST,205, NOTE_C5,205, NOTE_REST,1027, NOTE_E5,205, NOTE_REST,205,
 TONES_REPEAT
};

#define HEROX 16                                                    //Hero position
#define FLOOR_LEVEL 40                                              //The bottom edge of where the heroes and monsters are drawn
#define BASIC_ENEMY_LEFT arduboy.width()-26                         //Left side of the basic enemies aka where the projectiles are spawned
#define BOSS_LEFT arduboy.width()-36                                //Left side of the bosses
#define REQUIRED_STAMINA 30                                         //The stamina the hero requires to attack       
#define REQUIRED_SPECIAL_POINTS 6                                   //Required special points to use hero's special 
#define REQUIRED_RECOVER_TIME 2000                                  //Time for the mage to recover from a failed spell
#define FIRST_ITEM_X arduboy.width()/2 - 9                          //X position of the first slot in the equip menu
#define SECOND_ITEM_X arduboy.width()/2 + 7                         //X position of the second slot in the equip menu
const String alphabet = "ABCDEFGHIJKLMNOPQRSTUVXYZ";                //Alphabet to insert the player's name when he has a new highscore

Arduboy2 arduboy;
ArduboyTones sound(arduboy.audio.enabled);
enum screen {start, choose, game, over, won, roundOver, equipItem, highscore}; //All the different screens in the game
screen sc = start;                                                  //Current screen
enum heroType {s, a, m};                                            //Types of heroes - Swordsman, Archer, Mage
byte heroChoiceX = 41;                                              //Used to determine where the selection rectangle in the choice menu is drawn
byte level, gameRound;                                              //Game level and round
uint8_t *enemy;                                                     //Enemy to draw
float projectileX, projectileSpeed;                                 //Enemy projectile's position and it's speed
bool goToPlayer;                                                    //Used to know whether the projectile goes towards the player
unsigned long projectileRecharge;                                   //Used to know when to spawn another projectile if needed
unsigned long recoverTime;                                          //Used to know if the recover time for the mage has passed after missing a spell
byte currentStamina;                                                //Current amount of stamina that the player has
byte maxEnemyHealth, enemyHealth;                                   //Enemies max and current health
byte enemyType;                                                     //Enemy type (1-Normal, 2-Forest, 3-Fire, 4-Swamp, 5-Ancient, 6-Undead)
byte enemyLeft;                                                     //Left side of the enemy, whter it be basic or boss
bool bossLevel, bossDefeated;                                       //Used to know if the level is a boss one and if it was defeated
uint8_t* rewardedItem;                                              //Rewarded item after a boss
String rewardName;                                                  //Rewarded item's name
bool itemFound;                                                     //Used to know if an item was found after the boss round
byte itemChoiceX = FIRST_ITEM_X;                                    //Used in the equip item screen to cyle through the item slots
byte letter1=0, letter2=0, letter3=0;                               //Letters of the name to register after a highscore. These are indexes of the alphabet string
byte letterChoiceX = arduboy.width()/2 - 7;                         //Used to cycle through the letters in the highscore screen
byte highscoreAddr;                                                 //EEPROM address to right a new highscore
bool showHighscore;                                                 //Tells the start screen to show the highscores or not
bool playAudio = true;                                              //Should the console play audio or not

//Animation stuff
#define ARDBITMAP_SBUF arduboy.getBuffer()                          //Screen buffer pointer expression (used in the ArdBitmap library)
#include <ArdBitmap.h>                                              //ArdBitmap - Library to edit sprites
ArdBitmap<WIDTH, HEIGHT> ardbitmap;
byte frame;                                                         //Used to draw the projectiles in the drawRotatedProjectile function
long changeFrameTime;                                               //Know when to change the frame
float logoSize;                                                     //Used in the resize animation for the logo in the start screen

//Used to know when is time to write the screen buffer to serial.
//unsigned long timeSerial;

//Hero classes
class Hero{
  public:
    byte maxHealth, health, basicAttack, attack, arrowX, spellX, specialPoints;
    uint8_t* weapon1; uint8_t* weapon2; uint8_t* weapon3; uint8_t* weapon4; uint8_t* weapon5;
    uint8_t* item1; uint8_t* item2;
    boolean usedSpecial = false, item1Def = false, item2Def = false;
    virtual void draw();
    virtual void useSpecial();
    virtual heroType getType();
};

//The Swordsman has a large amount of health, but does less damage 
//His special is a shield that protects him from the enemy one time
class Swordsman : public Hero{
  public:
    Swordsman(){
      maxHealth = 6; health = maxHealth; basicAttack = 2; attack = basicAttack;
      weapon1 = sword1; weapon2 = sword2; weapon3 = sword3; weapon4 = sword4; weapon5 = sword5;
    }
    virtual void draw(){
      arduboy.drawBitmap(HEROX,FLOOR_LEVEL-10, swordsman, 10, 10);
      if(usedSpecial)
        arduboy.drawCircle(HEROX+4, FLOOR_LEVEL-5, 7);
    }

    virtual void useSpecial(){
       if(!usedSpecial && specialPoints == REQUIRED_SPECIAL_POINTS){
        usedSpecial = true;
        specialPoints = 0;
      }
    }

    virtual heroType getType(){
      return s;
    }
};

//The Archer is has a decent amount of health and does a bit more damage than the Swordsman
//His special is an arrow that drags the enemy projectiles towards them but deals more damage if it doesn't
class Archer : public Hero{
  public:
    Archer(){
      maxHealth = 4; health = maxHealth; basicAttack = 3; attack = basicAttack;
      weapon1 = bow1; weapon2 = bow2; weapon3 = bow3; weapon4 = bow4; weapon5 = bow5;
    }
    virtual void draw(){
      arduboy.drawBitmap(HEROX,FLOOR_LEVEL-10, archer, 10, 10);
      if(usedSpecial){
        arduboy.drawBitmap(arrowX,FLOOR_LEVEL-5, arrow, 10, 3);
        arrowX+=2;

        //If arrow directly hits the enemy it does double the damage
        if(arrowX+10 >= enemyLeft){
          usedSpecial = false;
          arrowX = 0;
          (attack*2 > enemyHealth) ? enemyHealth = 0 : enemyHealth -= attack*2;
          if(playAudio)sound.tone(600,200);
        }
      }
    }
    virtual void useSpecial(){
      if(!usedSpecial && specialPoints == REQUIRED_SPECIAL_POINTS){
        arrowX = HEROX;
        usedSpecial = true;
        specialPoints = 0;
      }
    }
    virtual heroType getType(){
      return a;
    }
};

//The Mage is very fragile but does more damage than the other classes
//His special fires a spell that recovers 1 health point if it hits the enemy
//If it hits a projectile, it prevents the mage from doing anything for 2 seconds
class Mage : public Hero{
  public:
    Mage(){
      maxHealth = 2; health = maxHealth; basicAttack = 4; attack = basicAttack;
      weapon1 = staff1; weapon2 = staff2; weapon3 = staff3; weapon4 = staff4; weapon5 = staff5;
    }
    virtual void draw(){
      arduboy.drawBitmap(HEROX,FLOOR_LEVEL-10, mage, 10, 10);
      if(usedSpecial){
        arduboy.drawBitmap(spellX,FLOOR_LEVEL-9, spell, 10, 3);
        spellX+=2;

        //Spell recovers health if it hits the enemy
        if(spellX+10 >= enemyLeft){
          usedSpecial = false;
          spellX = 0;
          (attack > enemyHealth) ? enemyHealth = 0 : enemyHealth -= attack;
          if(playAudio)sound.tone(600,200);
          if(health < maxHealth)
            health++;
        }
      }
    }
    virtual void useSpecial(){
     if(!usedSpecial && specialPoints == REQUIRED_SPECIAL_POINTS){
        spellX = HEROX;
        usedSpecial = true;
        specialPoints = 0;
      }
    }
    virtual heroType getType(){
      return m;
    }
};

Hero *hero;

void setup(){
  //Serial.begin(250000);
  arduboy.beginDoFirst();
  arduboy.initRandomSeed();
  sound.tones(score);
}

void loop(){
  if (!(arduboy.nextFrame()))
    return;

  arduboy.clear();
  arduboy.pollButtons();

  switch(sc){
    case start:
      if(arduboy.justPressed(A_BUTTON)){
        playAudio = !playAudio;
        if(playAudio)sound.tones(score);
        else sound.noTone();
          
      }
      if(arduboy.justPressed(B_BUTTON)){
        showHighscore = !showHighscore;
      }

      //If the player wants to see the highscores, read the corresponding addresses in the EEPROM
      //In order: round, level, first letter of the name to register, second letter, third letter
      if(showHighscore){
        printCentered(10, F("HIGHSCORES"));
        byte firstAddr = EEPROM_STORAGE_SPACE_START;
        byte hsX = 25;
        for(byte i = firstAddr; i <= firstAddr + 10; i += 5){
          byte eepromRound = EEPROM.read(i);
          if(eepromRound != 255){
            byte eepromLevel = EEPROM.read(i+1);
            byte firstLetter = EEPROM.read(i+2);
            byte secondLetter = EEPROM.read(i+3);
            byte thirdLetter = EEPROM.read(i+4);
            String hsName = String(char(firstLetter))+String(char(secondLetter))+String(char(thirdLetter))+" "+String(eepromRound)+"-"+String(eepromLevel);
            printCentered(hsX, hsName);
            hsX += 10;
          }
        }
      }else{
        //Increase logo size to full, to make a little animation
        if(logoSize < 1)
          logoSize += 0.01;
        ardbitmap.drawBitmapResized(arduboy.width()/2 - (73*logoSize)/2, arduboy.height()/2 - (17*logoSize)/2, logo, 73, 17, WHITE, ALIGN_NONE, MIRROR_NONE, logoSize);

        if(playAudio)
          arduboy.drawBitmap(arduboy.width()-15, 5, audio, 10, 10);
        
        if(arduboy.justPressed(DOWN_BUTTON)){
          sc = choose;
          sound.noTone();
        }
      }
      
      break;
      
    case choose:
      //Draw possible selections
      printCentered(10, F("CHOOSE YOUR HERO!"));
      arduboy.drawBitmap(43, arduboy.height()/2-5, swordsman, 10, 10);
      arduboy.drawBitmap(59, arduboy.height()/2-5, archer, 10, 10);
      arduboy.drawBitmap(75, arduboy.height()/2-5, mage, 10, 10);
      arduboy.drawRect(heroChoiceX, arduboy.height()/2 - 7, 14, 14);

      //Cycle the selection through the different heroes
      //Right
      if(arduboy.justPressed(B_BUTTON)){
        if(playAudio)sound.tone(4000,100);
        if(heroChoiceX < 73)heroChoiceX += 16;
        else heroChoiceX = 41;
      }
      //Left
      if(arduboy.justPressed(A_BUTTON)){
        if(playAudio)sound.tone(4000,100);
        if(heroChoiceX > 41)heroChoiceX -= 16;
        else heroChoiceX = 73;
      }
      //Confirm
      if(arduboy.justPressed(DOWN_BUTTON)){
        if(playAudio)sound.tone(4000,100,4500,100,5000,100);
        switch(heroChoiceX){
          case 41:
            hero = new Swordsman;
            break;
          case 57:
            hero = new Archer;
            break;
          case 73:
            hero = new Mage;
            break;
        }
        reset();
        sc = game;
      }
      break;

    case game:
      //Check if the enemy in this level is a boss
      if(bossLevel){
        enemyLeft = BOSS_LEFT;
        arduboy.drawBitmap(BOSS_LEFT, FLOOR_LEVEL-20, enemy, 20, 20);
      }else{
        enemyLeft = BASIC_ENEMY_LEFT;
        arduboy.drawBitmap(enemyLeft, FLOOR_LEVEL-10, enemy, 10, 10);
      }
    
      //Draw in order: hero, current stamina, health points, special points and items
      hero->draw();
      //arduboy.setCursor(arduboy.width() - 22, 3);
      //arduboy.print(enemyHealth);
      arduboy.fillRect(HEROX, FLOOR_LEVEL + 11, currentStamina, 6);
      arduboy.setCursor(HEROX, 10);
      arduboy.print(F("HP:"));
      arduboy.print(hero->health);
      arduboy.print(F(" SP:"));
      arduboy.print(hero->specialPoints);
      //arduboy.drawRect(arduboy.width() - 42, FLOOR_LEVEL + 6, 12, 12);
      //arduboy.drawRect(arduboy.width() - 28, FLOOR_LEVEL + 6, 12, 12);
      if(hero->item1Def)
        arduboy.drawBitmap(arduboy.width() - 41, 8, hero->item1, 10, 10);
      if(hero->item2Def)
        arduboy.drawBitmap(arduboy.width() - 27, 8, hero->item2, 10, 10);

      //If projectile is not destroyed, move it
      if(projectileX > 0){
        drawProjectile();
        
        //Move the projectile every frame
        if(goToPlayer)
          projectileX-=projectileSpeed;
        else
          projectileX+=projectileSpeed;

        //In case the hero is an archer and he shot his special arrow, the projectile is dragged by the arrow fired
        if(hero->getType() == a && hero->usedSpecial){
          if(projectileX <= hero->arrowX + 10){
            projectileX = hero->arrowX + 10;
            goToPlayer = false;
            if(projectileX+5 >= enemyLeft){
              hero->usedSpecial = false;
              hero->arrowX = 0;
            }
          }
        }

        //If the hero is a mage the spell fired by him destroys the projectile aswell as the spell itself
        //also start the timer for the mage's recovery and for the enemy's projectile
        if(hero->getType() == m && hero->usedSpecial){
          if(projectileX <= hero->spellX + 10 && goToPlayer == true){
            hero->usedSpecial = false;
            hero->spellX = 0;
            projectileX = 0;
            recoverTime = millis();
            projectileRecharge = millis();
            currentStamina = 0;
          }
        }

        //Enemy health depleted if the projectile is going towards the enemy and touches them
        if(projectileX+5 >= enemyLeft && !goToPlayer){
          if(playAudio)sound.tone(600,200);
          (hero->attack > enemyHealth) ? enemyHealth = 0 : enemyHealth -= hero->attack;
          goToPlayer = true;
          projectileX = 0;
          projectileRecharge = millis();
        }
        
      //Spawn another projectile after 0.8 seconds if the first was destroyed
      }else if(millis() - projectileRecharge > 800){
        if(playAudio)sound.tone(500,100);
        projectileX = enemyLeft;
      }

      //If the projectile touches the player it is reflected in case the hero is a swordsman and used the shield
      //else reduce health, and destroy the projectile (by setting its position to 0)
      if(projectileX+5 < HEROX + 8 && projectileX > 0){
        if(hero->getType() == s && hero->usedSpecial){
          goToPlayer = false;
          hero->usedSpecial = false;
          if(playAudio)sound.tone(800,200);
        }else{
          if(bossLevel){
            if(2 > hero->health)hero->health = 0;
            else hero->health-=2;
          }
          else hero->health--;
          projectileX = 0;
          projectileRecharge = millis();
          if(playAudio)sound.tone(100,100);
        }
      }

      //Level won if the enemy has no health left
      if(enemyHealth == 0){
        sc = won;
        if(bossLevel)
          bossDefeated = true;
      }

      //Game over if the player has no health left. Also check for a new highscore
      if(hero->health == 0){
        if(playAudio)sound.tone(300,200,200,200,100,200);
        highscoreAddr = checkForHighscore();
        if(highscoreAddr > 0)
          sc = highscore;
        else
          sc = over;
      }

      //Recharge stamina after it's depleted
      //If the hero is a mage and is still recovering, the stamina does not recharge
      if(currentStamina < REQUIRED_STAMINA){
        if(hero->getType() != m || millis() - recoverTime > REQUIRED_RECOVER_TIME)
          currentStamina++;
      }

      //If the player timed the button press correctly and he has enough stamina, the projectile is reflected
      //also reward the player with a special point
      if(arduboy.justPressed(A_BUTTON) && currentStamina == REQUIRED_STAMINA){
        if(projectileX+5 < HEROX + 16  && projectileX+5 > HEROX + 8 ){
          if(hero->specialPoints < REQUIRED_SPECIAL_POINTS)
            hero->specialPoints++;
          goToPlayer = false;
          if(playAudio)sound.tone(800,200);
        }
        currentStamina = 0;
      }

      //Use hero's special
      if(arduboy.justPressed(B_BUTTON)){
        if(currentStamina == REQUIRED_STAMINA)
          hero->useSpecial();
          if(playAudio)sound.tone(4000,50,2000,50,1000,50);
      }

      //Use health potion if the player has one. Always check slot 1 first
      if(arduboy.justPressed(DOWN_BUTTON)){
        if(hero->health < hero-> maxHealth){
          if(hero->item1Def && hero->item1 == healthPotion){
            hero->health++;
            hero->item1Def = false;
            if(playAudio)sound.tone(1000,200);
          }else if(hero->item2Def && hero->item2 == healthPotion){
            hero->health++;
            hero->item2Def = false;
            if(playAudio)sound.tone(1000,200);
          }
        }
      }
      break;

    case over:
      printCentered(10, F("GAME OVER"));
      printCentered(30, F("PRESS B TO RESTART"));
      printCentered(40, F("PRESS C TO GO BACK"));
      if(arduboy.justPressed(DOWN_BUTTON)){
        reset();
        sc = game;
        if(playAudio)sound.tone(4000,100,4500,100,5000,100);
      }else if(arduboy.justPressed(B_BUTTON)){
        sc = start;
        if(playAudio)sound.tones(score);
      }
      break;
      
    case won:

      //Check if it is a boss level
      bossLevel = (level == gameRound+2);

      if(bossDefeated){
        nextLevel(bossLevel);
      }else{
        printCentered(10, F("MONSTER DEFEATED"));
        printCentered(30, F("PRESS B TO PROCEED"));
  
        if(arduboy.justPressed(DOWN_BUTTON)){
          nextLevel(bossLevel);
          if(playAudio)sound.tone(500,100);
        }
      }
      break;
      
    case roundOver:
    
      //If an item is found go to the equip screen
      printCentered(5, F("ROUND WON!"));
      if(itemFound){
        printCentered(20, rewardName);
        printCentered(30, F("FOUND"));
        arduboy.drawBitmap(arduboy.width()/2 - 5, arduboy.height()/2 + 10, rewardedItem, 10, 10);
        if(arduboy.justPressed(DOWN_BUTTON)){
          sc = equipItem;
          if(playAudio)sound.tone(4000,100);
        }
      }else{
        printCentered(20, F("NOTHING FOUND"));
        printCentered(30, F("THIS TIME"));
        if(arduboy.justPressed(DOWN_BUTTON)){
          sc = game;
          if(playAudio)sound.tone(500,100);
        }
      }
      break;

    case equipItem:

      //Show item slots and equiped items
      printCentered(5, F("EQUIP ITEM"));
      arduboy.drawRect(arduboy.width()/2 - 14, arduboy.height()/2 - 6, 12, 12);
      arduboy.drawRect(arduboy.width()/2 + 2, arduboy.height()/2 - 6, 12, 12);
      if(hero->item1Def)
        arduboy.drawBitmap(arduboy.width()/2 - 13, arduboy.height()/2 - 5, hero->item1, 10, 10);
      if(hero->item2Def)
        arduboy.drawBitmap(arduboy.width()/2 + 3, arduboy.height()/2 - 5, hero->item2, 10, 10);

      printCentered(45, "CANCEL");

      //Draw circle that indicates what is selected. Change y position if the selection is the cancel button.
      if(itemChoiceX == 40)
        arduboy.fillCircle(itemChoiceX, 48, 2);
      else
        arduboy.fillCircle(itemChoiceX, arduboy.height()/2 - 11, 2);

      //Cycle through the options.
      //Left
      if(arduboy.justPressed(A_BUTTON)){
        if(playAudio)sound.tone(4000,100);
        if(itemChoiceX == FIRST_ITEM_X) itemChoiceX = 40;
        else if(itemChoiceX == 40) itemChoiceX = SECOND_ITEM_X;
        else itemChoiceX = FIRST_ITEM_X;
      }
      //Right
      if(arduboy.justPressed(B_BUTTON)){
        if(playAudio)sound.tone(4000,100);
        if(itemChoiceX == FIRST_ITEM_X) itemChoiceX = SECOND_ITEM_X;
        else if(itemChoiceX == 40) itemChoiceX = FIRST_ITEM_X;
        else itemChoiceX = 40;
      }
      //Confirm. Replace the item in the selected slot.
      if(arduboy.justPressed(DOWN_BUTTON)){
        if(playAudio)sound.tone(4000,100);
        if(itemChoiceX == FIRST_ITEM_X){
          hero->item1 = rewardedItem;
          hero->item1Def = true;
        }else if(itemChoiceX == SECOND_ITEM_X){
          hero->item2 = rewardedItem;
          hero->item2Def = true;
        }
        updateAttack();
        sc = game;
      }
      break;

    case highscore:

      //Show the new highscore menu, it is basically a name selector with 3 characters
      printCentered(5, F("NEW HIGHSCORE!"));
      String highscore = String(gameRound) + "-" + String(level);
      printCentered(20, highscore);
      String letters = String(alphabet[letter1]) + String(alphabet[letter2]) + String(alphabet[letter3]);
      printCentered(35, letters);

      //Draw the indicator of the selections. Change the y position if the option is to confirm
      if(letterChoiceX == 37)
        arduboy.fillCircle(letterChoiceX, 53, 1);
      else
        arduboy.fillCircle(letterChoiceX, 32, 1);

      printCentered(50, "CONFIRM");

      //Cycle through the options.
      //Left
      if(arduboy.justPressed(A_BUTTON)){
        if(playAudio)sound.tone(4000,100);
        if(letterChoiceX == arduboy.width()/2 - 7) letterChoiceX = 37;
        else if(letterChoiceX == 37) letterChoiceX = arduboy.width()/2 + 5;
        else letterChoiceX -= 6;
      }
      //Right
      if(arduboy.justPressed(B_BUTTON)){
        if(playAudio)sound.tone(4000,100);
        if(letterChoiceX == arduboy.width()/2 + 5) letterChoiceX = 37;
        else if(letterChoiceX == 37) letterChoiceX = arduboy.width()/2 - 7;
        else letterChoiceX += 6;
      }
      //Cycle through the alphabet if the letters are selected 
      //or if the player wants to confirm, write to the address in the EEPROM the round and level of the highscore aswell as the desired name
      if(arduboy.justPressed(DOWN_BUTTON)){
        if(playAudio)sound.tone(4000,100);
        if(letterChoiceX == arduboy.width()/2 - 7){
          if(letter1 == 24)letter1 = 0;
          else letter1++;
        }else if(letterChoiceX == arduboy.width()/2 - 1){
          if(letter2 == 24)letter2 = 0;
          else letter2++;
        }else if(letterChoiceX == arduboy.width()/2 + 5){
          if(letter3 == 24)letter3 = 0;
          else letter3++;
        }else{
          EEPROM.write(highscoreAddr, gameRound);
          EEPROM.write(highscoreAddr+1, level);
          EEPROM.write(highscoreAddr+2, alphabet[letter1]);
          EEPROM.write(highscoreAddr+3, alphabet[letter2]);
          EEPROM.write(highscoreAddr+4, alphabet[letter3]);
          letterChoiceX = arduboy.width()/2 - 7;
          sc = over;
        }
      }
      break;
  }

  //Write screen buffer to serial. Used in a python program to mirror the console screen to the pc.
  /*if(millis() - timeSerial > 100){
    Serial.write(arduboy.getBuffer(), 128 * 64 / 8);
    timeSerial = millis();
  }*/
  
  arduboy.display();
  arduboy.idle();
}

//Print a string on the center of the screen
void printCentered(byte y, String text){
  byte totalX = text.length() * 6;
  arduboy.setCursor(arduboy.width()/2 - totalX/2, y);
  arduboy.print(text);
}

//Get a random enemy, also a random type if it is wanted. If it is a boss level the enemy is the boss of the desired type
void getRandomEnemy(bool newType, bool boss){
  arduboy.initRandomSeed();
  if(newType){
    enemyType = random(1, 7);
  }
  long monster;
  boss ? monster = 5 : monster = random(0, 5);
  switch(enemyType){
    case 1:
      switch(monster){
        case 0: enemy = normal1; break;
        case 1: enemy = normal2; break;
        case 2: enemy = normal3; break;
        case 3: enemy = normal4; break;
        case 4: enemy = normal5; break;
        case 5: enemy = normalBoss; break;
      }
      break;
    case 2:
      switch(monster){
        case 0: enemy = forest1; break;
        case 1: enemy = forest2; break;
        case 2: enemy = forest3; break;
        case 3: enemy = forest4; break;
        case 4: enemy = forest5; break;
        case 5: enemy = forestBoss; break;
      }
      break;
    case 3:
      switch(monster){
        case 0: enemy = fire1; break;
        case 1: enemy = fire2; break;
        case 2: enemy = fire3; break;
        case 3: enemy = fire4; break;
        case 4: enemy = fire5; break;
        case 5: enemy = fireBoss; break;
      }
      break;
    case 4:
      switch(monster){
        case 0: enemy = swamp1; break;
        case 1: enemy = swamp2; break;
        case 2: enemy = swamp3; break;
        case 3: enemy = swamp4; break;
        case 4: enemy = swamp5; break;
        case 5: enemy = swampBoss; break;
      }
      break;
    case 5:
      switch(monster){
        case 0: enemy = ancient1; break;
        case 1: enemy = ancient2; break;
        case 2: enemy = ancient3; break;
        case 3: enemy = ancient4; break;
        case 4: enemy = ancient5; break;
        case 5: enemy = ancientBoss; break;
      }
      break;
    case 6:
      switch(monster){
        case 0: enemy = undead1; break;
        case 1: enemy = undead2; break;
        case 2: enemy = undead3; break;
        case 3: enemy = undead4; break;
        case 4: enemy = undead5; break;
        case 5: enemy = undeadBoss; break;
      }
      break;
  }
}

//Get a random gem
bool getRandomGem(){
  arduboy.initRandomSeed();
  long gem = random(1, 7);
  switch(gem){
    case 1:
      rewardName = F("NORMAL GEM");
      rewardedItem = normalGem;
      return true;
    case 2:
      rewardName = F("FOREST GEM");
      rewardedItem = forestGem;
      return true;
    case 3:
      rewardName = F("FIRE GEM");
      rewardedItem = fireGem;
      return true;
    case 4:
      rewardName = F("SWAMP GEM");
      rewardedItem = swampGem;
      return true;
    case 5:
      rewardName = F("ANCIENT GEM");
      rewardedItem = ancientGem;
      return true;
    case 6:
      rewardName = F("UNDEAD GEM");
      rewardedItem = undeadGem;
      return true;
  }
}

//Get random weapon. It is chosen by checking the tier probabilities array in the sprites.c file.
bool getRandomWeapon(){
  arduboy.initRandomSeed();
  long randomTier = random(1, 33);
  byte chosenTier = 0;
  for(int i = 0; i < 5; i++){
    if(randomTier >= tierProbs[i]){
      chosenTier = i+1;
      break;
    }
  }
  switch(chosenTier){
    case 0:
      return false;
    case 1:
      rewardName = F("TIER 1 WEAPON");
      rewardedItem = hero->weapon1;
      return true;
    case 2:
      rewardName = F("TIER 2 WEAPON");
      rewardedItem = hero->weapon2;
      return true;
    case 3:
      rewardName = F("TIER 3 WEAPON");
      rewardedItem = hero->weapon3;
      return true;
    case 4:
      rewardName = F("TIER 4 WEAPON");
      rewardedItem = hero->weapon4;
      return true;
    case 5:
      rewardName = F("TIER 5 WEAPON");
      rewardedItem = hero->weapon5;
      return true; 
  }
}

//Get random item by choosing first its type (weapon, gem or health potion).
//This can also return no item.
bool getRandomItem(){
  arduboy.initRandomSeed();
  long itemType = random(1, 6);
  uint8_t* item;
  switch(itemType){
    case 1:
    case 2:
      return getRandomWeapon();
    case 3:
      return getRandomGem();
    case 4:
      rewardName = F("HEALTH POTION");
      rewardedItem = healthPotion;
      return true;
    case 5:
      return false;
  }
}

//Return the type of the gem. The gem types are the same as the enemy types.
byte getGemType(uint8_t* gem){
  if(gem == normalGem) return 1;
  else if(gem == forestGem) return 2;
  else if(gem == fireGem) return 3;
  else if(gem == swampGem) return 4;
  else if(gem == ancientGem) return 5;
  else if(gem == undeadGem) return 6;
  else return 0;
}

//Increase attack depending on the weapon tier.
void addWeaponTierStats(uint8_t* item){
  if(item == hero->weapon1){
    hero->attack = hero->basicAttack +1;
  }else if(item == hero->weapon2){
    hero->attack = hero->basicAttack +2;
  }else if(item == hero->weapon3){
    hero->attack = hero->basicAttack +3;
  }else if(item == hero->weapon4){
    hero->attack = hero->basicAttack +4;
  }else if(item == hero->weapon5){
    hero->attack = hero->basicAttack +5;
  }
}

//Update attack depending on the items equiped.
//First look for gems which double the basic attack.
//Then add the corresponding attack bonus from the weapon.
void updateAttack(){
  hero->attack = hero->basicAttack;

  if(hero->item1Def && getGemType(hero->item1) == enemyType)
    hero->attack *= 2;

  if(hero->item2Def && getGemType(hero->item2) == enemyType)
    hero->attack *= 2;

  if(hero->item1Def){
    addWeaponTierStats(hero->item1);
  }

  if(hero->item2Def){
    addWeaponTierStats(hero->item2);
  }
}

//Each frame mirror image on an axis (which gives the effect of rotation)
//Only mirror horizontally on the swamp and fire types because of their projectile appearence
void drawRotatedProjectile(uint8_t* image){
  switch(frame){
    case 0: ardbitmap.drawBitmap(projectileX, FLOOR_LEVEL-10, image, 10, 10, WHITE, ALIGN_NONE, MIRROR_NONE);break;
    case 1: ardbitmap.drawBitmap(projectileX, FLOOR_LEVEL-10, image, 10, 10, WHITE, ALIGN_NONE, MIRROR_HORIZONTAL);break;
    case 2: ardbitmap.drawBitmap(projectileX, FLOOR_LEVEL-10, image, 10, 10, WHITE, ALIGN_V_CENTER, MIRROR_HOR_VER);break;
    case 3: ardbitmap.drawBitmap(projectileX, FLOOR_LEVEL-10, image, 10, 10, WHITE, ALIGN_V_CENTER, MIRROR_VERTICAL);break;
  }
  byte endValue = 3;
  if(image == pFire || image == pSwamp){
    endValue = 1;
  }
  if(millis() - changeFrameTime > 200){
    if(!goToPlayer){
      if(frame == endValue)frame = 0;
      else frame++;
    }else{
      if(frame == 0)frame = endValue;
      else frame--;
    }
    changeFrameTime = millis();
  }
}

//Draw the enemy's projectile. Get the corresponding one if the enemy is a boss
void drawProjectile(){
  if(!bossLevel)
    drawRotatedProjectile(projectile);
  else{
    switch(enemyType){
      case 1: drawRotatedProjectile(pNormal); break;
      case 2: drawRotatedProjectile(pForest); break;
      case 3: drawRotatedProjectile(pFire); break;
      case 4: drawRotatedProjectile(pSwamp); break;
      case 5: drawRotatedProjectile(pAncient); break;
      case 6: drawRotatedProjectile(pUndead); break;
    }
  }
}

//Reset the level and all the stats
//Enemies' max health increases for each level and round
void reset(){
  level = 1;
  gameRound = 1;
  getRandomEnemy(true, false);
  maxEnemyHealth = 2*gameRound + level;
  enemyHealth = maxEnemyHealth;
  hero->health = hero->maxHealth;
  projectileX = enemyLeft;
  projectileRecharge = millis();
  goToPlayer = true;
  currentStamina = REQUIRED_STAMINA;
  hero->arrowX = 0;
  hero->usedSpecial = false;
  hero->specialPoints = 0;
  hero->item1Def = false;
  hero->item2Def = false;
  bossDefeated = false;
  bossLevel = false;
  projectileSpeed = 1;
  highscoreAddr = 0;
  letter1 = letter2 = letter3 = 0;
  logoSize = 0;
  frame = 0;
}

//Load next level. Set new round, increase projectile speed and reward an item if a boss was defeated.
//Bosses have +6 health.
void nextLevel(bool bossLvl){
  sc = game;
  level++;
  getRandomEnemy(bossDefeated, bossLvl);
  if(bossDefeated){
    level = 1;
    gameRound++;
    if(projectileSpeed < 3)projectileSpeed += 0.2;
    sc = roundOver;
    bossDefeated = false;
    itemFound = getRandomItem();
    if(playAudio)sound.tone(3000,200,3500,200,4000,200);
  }
  projectileX = enemyLeft;
  goToPlayer = true;
  currentStamina = REQUIRED_STAMINA;
  hero->arrowX = 0;
  hero->usedSpecial = false;
  maxEnemyHealth = 2*gameRound + level;
  if(bossLvl)
    maxEnemyHealth += 6;
  enemyHealth = maxEnemyHealth;
  frame = 0;
}

//Read the round and level in the corresponding addresses to check for a new highscore
//If a new highscore is due, alter the position of the other highscores if applicable
byte checkForHighscore(){
  byte firstAddr = EEPROM_STORAGE_SPACE_START;
  for(byte i = firstAddr; i <= firstAddr + 10; i += 5){
    byte eepromRound = EEPROM.read(i);
    byte eepromLevel = EEPROM.read(i+1);
    if(eepromRound == 255 || gameRound > eepromRound ||
       (gameRound == eepromRound && level > eepromLevel)){
        if(i == firstAddr){
          //If highscore is first place
          //Copy second highscore to third place
          EEPROM.write(firstAddr + 10, EEPROM.read(firstAddr + 5));
          EEPROM.write(firstAddr + 11, EEPROM.read(firstAddr + 6));
          EEPROM.write(firstAddr + 12, EEPROM.read(firstAddr + 7));
          EEPROM.write(firstAddr + 13, EEPROM.read(firstAddr + 8));
          EEPROM.write(firstAddr + 14, EEPROM.read(firstAddr + 9));
          //Copy first highscore to second place
          EEPROM.write(firstAddr + 5, EEPROM.read(firstAddr));
          EEPROM.write(firstAddr + 6, EEPROM.read(firstAddr + 1));
          EEPROM.write(firstAddr + 7, EEPROM.read(firstAddr + 2));
          EEPROM.write(firstAddr + 8, EEPROM.read(firstAddr + 3));
          EEPROM.write(firstAddr + 9, EEPROM.read(firstAddr + 4));
        }else if(i == firstAddr + 5){
          //If the highscore is second place
          //Copy second highscore to third place
          EEPROM.write(firstAddr + 10, EEPROM.read(firstAddr + 5));
          EEPROM.write(firstAddr + 11, EEPROM.read(firstAddr + 6));
          EEPROM.write(firstAddr + 12, EEPROM.read(firstAddr + 7));
          EEPROM.write(firstAddr + 13, EEPROM.read(firstAddr + 8));
          EEPROM.write(firstAddr + 14, EEPROM.read(firstAddr + 9));
        }
      return i;
    }
  }
  return 0;
}
