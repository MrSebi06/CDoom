#ifndef DISPLAY_H
#define DISPLAY_H

#include <GL/glut.h>
#include <math.h>
#include "globals.h"

typedef struct
{
    int fr1, fr2; // frame 1 frame 2, to create constant frame rate
}Time;

void pixel(int x, int y, int c);
void clearBackground();
void clipBehindPlayer(int *x1, int *y1, int *z1, int x2, int y2, int z2);
void drawWall(int x1, int x2, int b1, int b2, int t1, int t2, int c, int s);
int dist(int x1, int y1, int x2, int y2);
void draw3D();
void display();

extern Time T;

#endif //DISPLAY_H
