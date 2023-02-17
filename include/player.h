#ifndef PLAYER_H
#define PLAYER_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "globals.h"

void movePlayer();
void KeysDown(unsigned char key, int x, int y);
void KeysUp(unsigned char key,int x,int y);
bool checkCollisions();

#endif //PLAYER_H
