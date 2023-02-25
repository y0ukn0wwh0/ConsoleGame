# Portable Gaming Console

This repository contains the development process of a portable gaming console based on Arduino, as well as 'DUNG!', a game made with the Arduboy library.
The following paragraphs detail the steps to the building of the console, the game installation and a brief description of it.

## Console Assembly

The following components are used:
- Arduino Nano
- 3 PTS636 switches, 2.5mm height
- MSK12C01-07 slide switch
- 601730 battery, 250mAh, 6*17*30mm dimensions
- TP4056 charging module
- 5kΩ SMD resistor
- i2c OLED screen, 0.96 inches, with the ssd1306 chip
- 5V buzzer, 12mm diameter
- 2 headers, 15 pins each (Arduino Nano)
- Our custom PCB (you can download the files [here](/Console/pcb_dev.zip) and upload them to EasyEDA)

Before welding the components to the PCB it is necessary to switch the charging module resisor to the 5kΩ one.

Having acquired all the required components one can procees with their welding to the PCB following the [schematic](/Console/schematic.png). The following welding order is advised:
1. Charging module
2. Bottom header
3. Buzzer
4. Screen
5. Sliding switch
6. Top header
7. 3 switches
8. Battery

<img src="/Showcase/welding_done.png" height="300">

With all the components in place, the board can be set in the box.

<img src="/Showcase/box.jpg" height="300">

## Alternative to the PCB welding
If one wants a simple setup, the assembly can be done on a breadboard. In this case the only components needed are the Arduino, switches, screen and buzzer. These can be connected to the Arduino pins following the image:

<img src="/Console/breadboard.png" height="300">

## Game
To install the game, the libraries available in the ... folder are necessary. These were obtained from the following repositories:
- [Arduboy2](https://github.com/MLXXXp/Arduboy2)
- [ArduboyTones](https://github.com/MLXXXp/ArduboyTones)
- [ArdBitmap](https://github.com/igvina/ArdBitmap)

The versions available in this repository were slightly altered due to some needed changes like the modification of the button pins.

These libraries are then placed in the correct directory so that the Arduino IDE imports them (generally 'C:\Program Files (x86)\Arduino\libraries').
After this you can simply upload the [game.ino](/Game/game/game.ino) file to the Arduino with the [sprites.c](/Game/game/sprites.c) file in the same folder. The installation is now complete.

### Mechanics
The game has various rounds each containing various levels. The number of levels in each round is increased as the player progresses. The objective is simply to complete as most levels as you can.

In each level, enemies launch projectiles in the direction of the player. In turn, the player has to reflect them by pressing the corresponding button in the right rythm.
Beyond the enemies getting stronger as the game moves forward, at the final level of each round a boss enemy shows up, making the progression more difficult.

At the beginning of each attempt, the following characters are offered as a choice to the player:
|            | Warrior | Archer  | Mage      |
| ---------- | ------- | ------- | --------- |
| **Health** | 6       | 4       | 2         |
| **Attack** | 2       | 3       | 4         |

By successfully reflecting enemy projectiles the player wins 'special points'. After accumulating 6 of these points, the player can use the character's special ability:
- **Warrior**: Creates a shield that blocks an enemy projectile.
- **Archer**: Shoots an arrow that drags enemy projectiles in it's direction. In case it hits an enemy directly it inflicts twice the damage.
- **Mage**: Shoots a projectile that heals 1 health point if it hits an enemy. If it doesn't, the mage is unable to attack for 2 seconds. 

There are also various items given to the player randomly after a finished round. These items can be:
- **Weapons**: Add attack damage to the player. Weapons give more damage depending on their level.
- **Gems**: There are several types of gems and they duplicate the damage the player inflicts if they correspond to the type of enemy.
- **Potions**: Heals 1 health point when used.
The player can only hold two items but they can be switched if another one is found. Note that the item that is switched out is lost.

The following image showcases the different bosses correpondent to the enemy/gem types in this order:
- Swamp
- Undead
- Ancient
- Fire
- Forest
- Normal
<img src="/Showcase/screenshots/enemy_bosses.png" width="600">

### Controls
The console's three buttons have the following functions:
|           | A Button               | B Button              | C Button                     |
| --------- | ---------------------- | --------------------- | ---------------------------- |
| **Menus** | Move to the left       | Select/Confirm        | Move to the right/Return     |
| **Game**  | Reflect projectiles    | Use potion            | Use special attack           |

### Interface
<img src="/Showcase/screenshots/interface.png" width="600">

### Screens
<img src="/Showcase/screenshots/title_screen.png" width="300">  <img src="/Showcase/screenshots/choose_hero.png" width="300">  <img src="/Showcase/screenshots/game.png" width="300">
<img src="/Showcase/screenshots/monster_defeated.png" width="300">  <img src="/Showcase/screenshots/round_won.png" width="300">  <img src="/Showcase/screenshots/equip_item.png" width="300">
<img src="/Showcase/screenshots/new_highscore.png" width="300">  <img src="/Showcase/screenshots/game_over.png" width="300">  <img src="/Showcase/screenshots/highscores.png" width="300">
