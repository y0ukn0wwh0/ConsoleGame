#include <avr/pgmspace.h>

#ifndef SPRITES
#define SPRITES

//Game logo (73, 17)
const uint8_t PROGMEM logo[] = {
0x00, 0x00, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0x1c, 0x1c, 0x1c, 0xfc, 0xfc, 0xfc, 0xfc, 0xf8, 0x00, 0x00, 0x00, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0x00, 0x00, 0x00, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0x00, 0x00, 0x00, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0x1c, 0x1c, 0x1c, 0xfc, 0xfc, 0xfc, 0xfc, 0xf8, 0x00, 0x00, 0x00, 0xf8, 0xfc, 0xfc, 0xfc, 0xfc, 0x1c, 0x1c, 0x9c, 0x9c, 0x9c, 0x9c, 0x9c, 0x9c, 0x00, 0x00, 0x00, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0x00, 0x00, 
0x00, 0x00, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x70, 0x70, 0x70, 0x7f, 0x7f, 0x7f, 0x7f, 0x3f, 0x00, 0x00, 0x00, 0x3f, 0x7f, 0x7f, 0x7f, 0x7f, 0x70, 0x70, 0x70, 0x7f, 0x7f, 0x7f, 0x7f, 0x3f, 0x00, 0x00, 0x00, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x00, 0x00, 0x00, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x00, 0x00, 0x00, 0x3f, 0x7f, 0x7f, 0x7f, 0x7f, 0x70, 0x70, 0x73, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x00, 0x00, 0x00, 0x73, 0x73, 0x73, 0x73, 0x73, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
};


//Enemy projectile
const uint8_t PROGMEM projectile[] = {
0x00, 0x20, 0x94, 0x78, 0xca, 0x4c, 0x78, 0xa4, 0x10, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00,
};

//Archer's arrow
const uint8_t PROGMEM arrow[] = {
0x05, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x07, 0x02,
};

//Mage's spell
const uint8_t PROGMEM spell[] = {
0x82, 0x82, 0x82, 0xc6, 0x44, 0x6c, 0x7c, 0x38, 0x38, 0x10, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
};

//HEROES
const uint8_t PROGMEM swordsman[] = {
0x08, 0xc4, 0xf8, 0xe8, 0xc8, 0xe8, 0x40, 0xfc, 0x40, 0x00,
0x00, 0x00, 0x03, 0x01, 0x01, 0x03, 0x00, 0x01, 0x00, 0x00,
};
const uint8_t PROGMEM archer[] = {
0xc8, 0xfc, 0xec, 0xec, 0xe8, 0x80, 0x90, 0xe0, 0x40, 0x00,
0x00, 0x03, 0x01, 0x01, 0x03, 0x00, 0x01, 0x00, 0x00, 0x00,
};
const uint8_t PROGMEM mage[] = {
0x60, 0xfc, 0xfc, 0xe4, 0xfc, 0x20, 0x27, 0xfd, 0x07, 0x00, 
0x02, 0x03, 0x03, 0x03, 0x03, 0x02, 0x00, 0x03, 0x00, 0x00, 
};

//MONSTERS
//Normal
const uint8_t PROGMEM normal1[] = {
0x00, 0x00, 0xc4, 0xe8, 0xf8, 0xe8, 0xf8, 0xc4, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x03, 0x01, 0x01, 0x03, 0x00, 0x00, 0x00, 
};
const uint8_t PROGMEM normal2[] = {
0x00, 0xe4, 0xf8, 0xec, 0xfc, 0xec, 0xfc, 0xf8, 0xe4, 0x00, 
0x00, 0x00, 0x03, 0x01, 0x01, 0x01, 0x01, 0x03, 0x00, 0x00, 
};
const uint8_t PROGMEM normal3[] = {
0x40, 0xfc, 0x40, 0xc4, 0xe8, 0xf8, 0xe8, 0xf8, 0xc4, 0x00, 
0x00, 0x01, 0x00, 0x00, 0x03, 0x01, 0x01, 0x03, 0x00, 0x00, 
};
const uint8_t PROGMEM normal4[] = {
0x00, 0x08, 0xfc, 0x48, 0x44, 0xe8, 0xf8, 0xe8, 0xf8, 0xc4, 
0x00, 0x00, 0x03, 0x00, 0x00, 0x03, 0x01, 0x01, 0x03, 0x00, 
};
const uint8_t PROGMEM normal5[] = {
0x00, 0x40, 0xe0, 0x90, 0x84, 0xe8, 0xf8, 0xe8, 0xf8, 0xc4, 
0x00, 0x00, 0x00, 0x01, 0x00, 0x03, 0x01, 0x01, 0x03, 0x00, 
};
const uint8_t PROGMEM normalBoss[] = {
0x60, 0xc0, 0x30, 0xc0, 0x00, 0x00, 0x00, 0x70, 0x80, 0x40, 0xe0, 0xf0, 0xf0, 0xf0, 0x70, 0xe0, 0xc0, 0x80, 0x70, 0x00, 
0x00, 0x01, 0x07, 0x1e, 0x7f, 0xf8, 0xb0, 0x7c, 0xff, 0xfc, 0xfc, 0xff, 0xff, 0xfc, 0xfc, 0xff, 0xff, 0x8f, 0xfc, 0x30, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x0f, 0x07, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x07, 0x0f, 0x00, 0x00, 
};
const uint8_t PROGMEM pNormal[] = {
0x00, 0x20, 0x94, 0x78, 0xca, 0x4c, 0x78, 0xa4, 0x10, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 
};

//Forest
const uint8_t PROGMEM forest1[] = {
0x00, 0x00, 0x20, 0xb0, 0xf0, 0xb0, 0xf0, 0x20, 0x00, 0x00,
0x00, 0x00, 0x00, 0x03, 0x01, 0x01, 0x03, 0x00, 0x00, 0x00,
};
const uint8_t PROGMEM forest2[] = {
0x00, 0x00, 0x21, 0xbd, 0xef, 0xad, 0xff, 0x21, 0x00, 0x00,
0x00, 0x00, 0x00, 0x03, 0x01, 0x01, 0x03, 0x00, 0x00, 0x00,
};
const uint8_t PROGMEM forest3[] = {
0x0c, 0x06, 0xe7, 0xff, 0xff, 0xe7, 0xff, 0xff, 0x06, 0x0c,
0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00,
};
const uint8_t PROGMEM forest4[] = {
0x00, 0x02, 0xff, 0x02, 0x20, 0xb0, 0xf0, 0xb0, 0xf0, 0x20,
0x00, 0x00, 0x03, 0x01, 0x01, 0x03, 0x01, 0x01, 0x03, 0x00,
};
const uint8_t PROGMEM forest5[] = {
0x00, 0x00, 0x2c, 0xb2, 0xf2, 0xb2, 0xf2, 0x2c, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x03, 0x01, 0x01, 0x03, 0x00, 0x00, 0x00, 
};
const uint8_t PROGMEM forestBoss[] = {
0xc0, 0xf0, 0xf8, 0xcc, 0xcc, 0x7e, 0xbe, 0xbb, 0xbf, 0xbf, 0xbf, 0xaf, 0xbf, 0xbe, 0x7e, 0xf4, 0xfc, 0x38, 0x30, 0xc0, 
0x03, 0x03, 0x01, 0x01, 0x00, 0x83, 0xb8, 0xd1, 0xbf, 0x7f, 0xb1, 0xd8, 0xbf, 0xff, 0x83, 0x00, 0x01, 0x01, 0x03, 0x03, 
0x00, 0x00, 0x08, 0x04, 0x0e, 0x0f, 0x07, 0x03, 0x07, 0x0f, 0x0f, 0x0f, 0x07, 0x07, 0x0f, 0x0e, 0x04, 0x08, 0x00, 0x00, 
};
const uint8_t PROGMEM pForest[] = {
0x00, 0xb4, 0x6a, 0xcc, 0x82, 0x06, 0xcc, 0x5a, 0xb4, 0x00, 
0x00, 0x00, 0x01, 0x00, 0x01, 0x01, 0x00, 0x01, 0x00, 0x00, 
};

//Imp
const uint8_t PROGMEM fire1[] = {
0x00, 0x00, 0xc0, 0xec, 0xf8, 0xe8, 0xfc, 0xc0, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x03, 0x01, 0x01, 0x03, 0x00, 0x00, 0x00, 
};
const uint8_t PROGMEM fire2[] = {
0x0c, 0x12, 0xe1, 0x42, 0x40, 0xec, 0xf8, 0xe8, 0xfc, 0xc0, 
0x00, 0x00, 0x03, 0x00, 0x00, 0x03, 0x01, 0x01, 0x03, 0x00, 
};
const uint8_t PROGMEM fire3[] = {
0x10, 0x30, 0x70, 0xf6, 0xfc, 0xf4, 0xfe, 0x70, 0x30, 0x10, 
0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 
};
const uint8_t PROGMEM fire4[] = {
0x00, 0x07, 0xfc, 0x47, 0x40, 0xec, 0xf8, 0xe8, 0xfc, 0xc0, 
0x00, 0x00, 0x03, 0x00, 0x00, 0x03, 0x01, 0x01, 0x03, 0x00, 
};
const uint8_t PROGMEM fire5[] = {
0x00, 0x00, 0xb0, 0xdb, 0xbe, 0xda, 0xbf, 0xd0, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x03, 0x01, 0x01, 0x03, 0x00, 0x00, 0x00, 
};
const uint8_t PROGMEM fireBoss[] = {
0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xc7, 0xcf, 0xfe, 0xfc, 0xcc, 0xc6, 0xff, 0xff, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x83, 0xc7, 0xc3, 0xc3, 0x87, 0x8f, 0x07, 0x83, 0xc1, 0xc3, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0x0f, 0x07, 0x03, 0x03, 0x07, 0x0f, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
};
const uint8_t PROGMEM pFire[] = {
0x00, 0x00, 0xfc, 0x30, 0x18, 0x10, 0x3e, 0xe0, 0x00, 0x00, 
0x00, 0x00, 0x01, 0x03, 0x02, 0x02, 0x03, 0x01, 0x00, 0x00, 
};

//Swamp
const uint8_t PROGMEM swamp1[] = {
0x00, 0x00, 0x80, 0xc0, 0xc0, 0xc0, 0xc0, 0x80, 0x00, 0x00, 
0x00, 0x00, 0x03, 0x02, 0x03, 0x02, 0x03, 0x03, 0x00, 0x00, 
};
const uint8_t PROGMEM swamp2[] = {
0x00, 0xe0, 0xb0, 0xf0, 0xf0, 0xb0, 0xf0, 0xf0, 0xe0, 0x00, 
0x00, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x00, 
};
const uint8_t PROGMEM swamp3[] = {
0x00, 0x00, 0x14, 0x7e, 0xfe, 0xf6, 0x7e, 0x1c, 0x00, 0x00, 
0x00, 0x00, 0x02, 0x03, 0x03, 0x03, 0x03, 0x02, 0x00, 0x00, 
};
const uint8_t PROGMEM swamp4[] = {
0x00, 0x00, 0x00, 0x80, 0x80, 0x80, 0x80, 0x00, 0x00, 0x00, 
0x02, 0x03, 0x03, 0x02, 0x03, 0x02, 0x03, 0x03, 0x03, 0x02, 
};
const uint8_t PROGMEM swamp5[] = {
0x00, 0xe0, 0xf0, 0x68, 0x38, 0x28, 0x78, 0xf0, 0xe0, 0x00, 
0x00, 0x03, 0x03, 0x02, 0x00, 0x00, 0x02, 0x03, 0x03, 0x00, 
};
const uint8_t PROGMEM swampBoss[] = {
0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0xf0, 0xf0, 0xf8, 0xf8, 0xf8, 0x78, 0xf0, 0xf0, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x20, 0x30, 0x30, 0x30, 0x30, 0x23, 0x8c, 0xff, 0xff, 0xff, 0xff, 0xfe, 0xff, 0x8f, 0x23, 0x30, 0xfc, 0x30, 0x30, 0x30, 
0x00, 0x00, 0x08, 0x0c, 0x0e, 0x0e, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0e, 0x0e, 0x0c, 0x08, 0x00, 0x00, 
};
const uint8_t PROGMEM pSwamp[] = {
0x00, 0x00, 0x80, 0xf0, 0xf8, 0xf8, 0xf0, 0x80, 0x00, 0x00, 
0x00, 0x02, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x02, 0x00, 
};

//Ancient
const uint8_t PROGMEM ancient1[] = {
0x00, 0x00, 0xc0, 0xf8, 0xc8, 0xf8, 0xf8, 0xc0, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x03, 0x01, 0x01, 0x03, 0x00, 0x00, 0x00, 
};
const uint8_t PROGMEM ancient2[] = {
0x3e, 0x88, 0x98, 0xff, 0xb9, 0xbf, 0xff, 0x98, 0x80, 0x00, 
0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 
};
const uint8_t PROGMEM ancient3[] = {
0x00, 0x3e, 0xe2, 0xbe, 0x80, 0xf8, 0xc8, 0xf8, 0xf8, 0xc0, 
0x00, 0x00, 0x01, 0x00, 0x00, 0x03, 0x01, 0x01, 0x03, 0x00, 
};
const uint8_t PROGMEM ancient4[] = {
0x00, 0xfe, 0x10, 0x10, 0xfe, 0xe2, 0xfe, 0xfe, 0x30, 0x00, 
0x00, 0x03, 0x00, 0x00, 0x03, 0x03, 0x03, 0x03, 0x03, 0x02, 
};
const uint8_t PROGMEM ancient5[] = {
0x1e, 0x12, 0xf2, 0xf2, 0xf2, 0xf2, 0xf2, 0xfe, 0x1e, 0x1e, 
0x00, 0x00, 0x00, 0x03, 0x01, 0x01, 0x03, 0x00, 0x00, 0x00, 
};
const uint8_t PROGMEM ancientBoss[] = {
0x00, 0x14, 0xfe, 0x14, 0x00, 0xfe, 0x02, 0x02, 0x02, 0x02, 0xfe, 0xfe, 0xfe, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x80, 0x5f, 0x42, 0x02, 0xe3, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf8, 0xc0, 0x00, 0x40, 0x80, 0x00, 
0x00, 0x00, 0x01, 0x01, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x01, 0x00, 0x00, 
};
const uint8_t PROGMEM pAncient[] = {
0x00, 0x20, 0x10, 0x30, 0xfa, 0x7c, 0x30, 0x20, 0x10, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 
};

//Undead
const uint8_t PROGMEM undead1[] = {
0x00, 0x20, 0xfe, 0x60, 0x40, 0x68, 0xd8, 0xe8, 0x78, 0xc0, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x01, 0x01, 0x03, 0x00, 
};
const uint8_t PROGMEM undead2[] = {
0x00, 0xf0, 0x48, 0x40, 0x40, 0x68, 0xd8, 0xe8, 0x78, 0xc0, 
0x00, 0x00, 0x01, 0x00, 0x00, 0x03, 0x01, 0x01, 0x03, 0x00, 
};
const uint8_t PROGMEM undead3[] = {
0x20, 0xfe, 0x40, 0x68, 0xd8, 0xe8, 0x78, 0x40, 0xfe, 0x20, 
0x00, 0x00, 0x00, 0x03, 0x01, 0x01, 0x03, 0x00, 0x00, 0x00, 
};
const uint8_t PROGMEM undead4[] = {
0x00, 0x00, 0x00, 0xaa, 0x76, 0xba, 0xee, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x02, 0x01, 0x01, 0x02, 0x00, 0x00, 0x00, 
};
const uint8_t PROGMEM undead5[] = {
0x00, 0x00, 0xc0, 0x68, 0xd8, 0xe8, 0x78, 0xc0, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x03, 0x01, 0x01, 0x03, 0x00, 0x00, 0x00, 
};
const uint8_t PROGMEM undeadBoss[] = {
0x00, 0xc0, 0x38, 0x0c, 0x06, 0xfb, 0x00, 0xc0, 0xe6, 0xfe, 0xfe, 0xe6, 0xe6, 0xfe, 0xe0, 0x00, 0x00, 0x88, 0x78, 0x1c, 
0x00, 0x1f, 0x7c, 0xc4, 0x86, 0x7a, 0x03, 0x01, 0x81, 0xf3, 0x1f, 0x1f, 0xf3, 0x81, 0x07, 0x7f, 0xf0, 0x0f, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x01, 0x03, 0x00, 0x04, 0x07, 0x01, 0x00, 0x00, 0x01, 0x07, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 
};
const uint8_t PROGMEM pUndead[] = {
0x00, 0x80, 0x80, 0x40, 0x20, 0x10, 0x08, 0x06, 0x04, 0x00, 
0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
};

//ITEMS
//Health potion
const uint8_t PROGMEM healthPotion[] = {
0x00, 0x00, 0xe0, 0x90, 0xd6, 0xd6, 0x90, 0xe0, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 
};


//Gems (grant bonuses against the listed type)
const uint8_t PROGMEM normalGem[] = {
0x00, 0x28, 0x6c, 0x84, 0x68, 0xec, 0x68, 0x84, 0x6c, 0x28, 
0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0x01, 0x00, 0x00, 0x00, 
};
const uint8_t PROGMEM forestGem[] = {
0xc0, 0x60, 0x50, 0x48, 0xc4, 0xa2, 0x52, 0x2a, 0x16, 0x0e, 
0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 
};
const uint8_t PROGMEM fireGem[] = {
0x00, 0x58, 0xdc, 0x86, 0xb0, 0x36, 0x86, 0xec, 0x68, 0x00, 
0x00, 0x00, 0x00, 0x01, 0x01, 0x00, 0x01, 0x00, 0x00, 0x00, 
};
const uint8_t PROGMEM swampGem[] = {
0x00, 0x00, 0x18, 0x24, 0x5a, 0x5a, 0x64, 0x98, 0x00, 0x00, 
0x00, 0x00, 0x01, 0x02, 0x02, 0x02, 0x02, 0x01, 0x00, 0x00, 
};
const uint8_t PROGMEM ancientGem[] = {
0x00, 0x18, 0x24, 0xc2, 0x42, 0x82, 0x42, 0xc2, 0x24, 0x18, 
0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0x01, 0x00, 0x00, 0x00, 
};
const uint8_t PROGMEM undeadGem[] = {
0x00, 0x0a, 0x06, 0x0a, 0x0e, 0x80, 0x40, 0x20, 0x18, 0x10, 
0x00, 0x00, 0x00, 0x01, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 
};

//Weapons (Depend on the chosen class)
//Swordsman
const uint8_t PROGMEM sword1[] = {
0x00, 0x00, 0x80, 0x70, 0x60, 0x50, 0x08, 0x04, 0x02, 0x00, 
0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
};
const uint8_t PROGMEM sword2[] = {
0x00, 0x00, 0xc8, 0xf0, 0x50, 0x78, 0x9c, 0x0e, 0x06, 0x00, 
0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
};
const uint8_t PROGMEM sword3[] = {
0x00, 0x80, 0xf0, 0xa0, 0xf0, 0xb8, 0x1c, 0x0e, 0x07, 0x03, 
0x03, 0x03, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
};
const uint8_t PROGMEM sword4[] = {
0x00, 0x20, 0xc0, 0xe0, 0x70, 0x38, 0x1c, 0x0e, 0x07, 0x00, 
0x02, 0x01, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 
};
const uint8_t PROGMEM sword5[] = {
0x00, 0x1c, 0xf0, 0x98, 0x90, 0xf8, 0x5c, 0x0e, 0x07, 0x03, 
0x03, 0x03, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x00, 0x00, 
};

//Archer
const uint8_t PROGMEM bow1[] = {
0x00, 0x00, 0x02, 0x06, 0xca, 0x32, 0x0a, 0x06, 0x02, 0x00, 
0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
};
const uint8_t PROGMEM bow2[] = {
0x00, 0x10, 0x10, 0xfd, 0x12, 0x12, 0x94, 0x78, 0x10, 0x10, 
0x00, 0x00, 0x00, 0x02, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 
};
const uint8_t PROGMEM bow3[] = {
0x00, 0x20, 0xfd, 0x22, 0x22, 0x22, 0xa4, 0x78, 0x20, 0x20, 
0x00, 0x00, 0x02, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 
};
const uint8_t PROGMEM bow4[] = {
0x00, 0xf0, 0x48, 0xc8, 0x10, 0x13, 0x0c, 0x40, 0xa0, 0x18, 
0x02, 0x01, 0x01, 0x01, 0x01, 0x02, 0x02, 0x01, 0x00, 0x00, 
};
const uint8_t PROGMEM bow5[] = {
0x00, 0x80, 0x80, 0x40, 0x40, 0x88, 0x94, 0x95, 0x63, 0x07, 
0x02, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
};

//Mage
const uint8_t PROGMEM staff1[] = {
0x00, 0x00, 0x80, 0x70, 0x20, 0x10, 0x18, 0x17, 0x05, 0x07, 
0x02, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
};
const uint8_t PROGMEM staff2[] = {
0x00, 0x00, 0x80, 0x40, 0x3d, 0x30, 0x2e, 0x2a, 0x0e, 0x20, 
0x02, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
};
const uint8_t PROGMEM staff3[] = {
0x00, 0x00, 0xa0, 0x48, 0x94, 0x32, 0x4c, 0x29, 0x12, 0x04, 
0x02, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
};
const uint8_t PROGMEM staff4[] = {
0x00, 0x00, 0xe0, 0xc0, 0xa0, 0x10, 0x2d, 0x1e, 0x1e, 0x2d, 
0x02, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
};
const uint8_t PROGMEM staff5[] = {
0x00, 0x40, 0xe0, 0xf0, 0xe0, 0x56, 0x0a, 0x11, 0x19, 0x07, 
0x02, 0x01, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
};

//Probability of the tier weapon being chosen (1-32)
//Example: if the random between 1-32 is bigger or equal to 16 the tier chosen is 1
//         if it is between 8 and 15 the chosen one is tier 2
const uint8_t PROGMEM tierProbs[] = {
  16, 8, 4, 2, 1
};
#endif
