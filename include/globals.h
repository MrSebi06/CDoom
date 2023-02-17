#ifndef GLOBALS_H
#define GLOBALS_H

#define RES 1 // 0=160x120 1=360x240 4=640x480
#define SW  (360*RES) // screen width
#define SH  (240*RES) // screen height
#define SW2 (SW/2) // half of screen width
#define SH2 (SH/2) // half of screen height
#define PIXELSCALE (4/RES) // OpenGL pixel scale
#define GLSW (SW*PIXELSCALE) // OpenGL window width
#define GLSH (SH*PIXELSCALE) // OpenGL window height
#define NUMSECT 4 // Number of sectors
#define NUMWALL 16 // Number of walls

typedef struct
{
    float cos[360];
    float sin[360];
}Math;

typedef struct
{
    int x, y, z; // Player position, z is up
    int a; // Player angle of rotation L/R
    int l; // Variable to look up and down
}Player;

typedef struct
{
    int x1, y1; // Bottom line point 1
    int x2, y2; // Bottom line point 2
    int c; // Wall color
}Walls;

typedef struct
{
    int ws, we; // Wall number start and end
    int z1, z2; // Height of bottom and top
    int d; // Add y distance to sort drawing order
    int c1, c2; // Bottom and top color;
    int surf[SW]; // To hold points for surfaces
    int surface; // Is there a surface to draw
}Sectors;

typedef struct
{
    int w,s,a,d; // move up, down, left, right
    int sl,sr; // strafe left, right
    int m; // move up, down, look up, down
}Keys;

extern Keys K;
extern Math M;
extern Player P;
extern Walls W[30];
extern Sectors S[30];

#endif //GLOBALS_H
