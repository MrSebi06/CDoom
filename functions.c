#include "header.h"

bool checkCollisions(int *x, int *y) {
    int ptx = *x + (M.cos[P.a] * 15);
    int pty = *y + (M.sin[P.a] * 15);

    for (int i = 0; i < NUMWALL; i++) {
        int x1 = W[i].x1;
        int y1 = W[i].y1;
        int x2 = W[i].x2;
        int y2 = W[i].y2;
        int c = W[i].c;

        int d = ((x2 - x1) * (pty - y1)) - ((y2 - y1) * (ptx - x1));
        if (d < 0) {
            continue;
        }

        int distToWall = abs((M.sin[P.a] * (x1 - ptx)) - (M.cos[P.a] * (y1 - pty)));
        if (distToWall > 15) {
            continue;
        }

        printf("Collision detected with wall %d\n", i);
        return true;
    }

    return false;
}



void pixel(int x, int y, int c)
{
    int rgb[3];

    switch (c) {
        case 0: rgb[0] = 255;   rgb[1] = 255;   rgb[2] = 0;     break;  // Yellow
        case 1: rgb[0] = 160;   rgb[1] = 160;   rgb[2] = 0;     break;  // Yellow dark
        case 2: rgb[0] = 0;     rgb[1] = 255;   rgb[2] = 0;     break;  // Green
        case 3: rgb[0] = 0;     rgb[1] = 160;   rgb[2] = 0;     break;  // Green dark
        case 4: rgb[0] = 0;     rgb[1] = 255;   rgb[2] = 255;   break;  // Cyan
        case 5: rgb[0] = 0;     rgb[1] = 160;   rgb[2] = 160;   break;  // Cyan dark
        case 6: rgb[0] = 160;   rgb[1] = 100;   rgb[2] = 0;     break;  // Brown
        case 7: rgb[0] = 110;   rgb[1] = 50;    rgb[2] = 0;     break;  // Brown dark
        case 8: rgb[0] = 0;     rgb[1] = 60;    rgb[2] = 130;   break;  // Background
        default: rgb[0] = 255;  rgb[1] = 255;   rgb[2] = 255;
    }
    glColor3ub(rgb[0], rgb[1], rgb[2]);
    glBegin(GL_POINTS);
    glVertex2i(x*PIXELSCALE+2, y*PIXELSCALE+2);
    glEnd();
}

void movePlayer()
{
    int dx = M.sin[P.a] * 10;
    int dy = M.cos[P.a] * 10;

    if (K.w == 1) {
        int new_x = P.x + dx;
        int new_y = P.y + dy;

        if (!checkCollisions(&new_x, &new_y)) {
            P.x = new_x;
            P.y = new_y;
        }
    }

    if (K.s == 1) {
        int new_x = P.x - dx;
        int new_y = P.y - dy;

        if (!checkCollisions(&new_x, &new_y)) {
            P.x = new_x;
            P.y = new_y;
        }
    }

    if (K.a == 1) {
        P.a -= 4;
        if (P.a < 0) {
            P.a += 360;
        }
    }

    if (K.d == 1) {
        P.a += 4;
        if (P.a >= 360) {
            P.a -= 360;
        }
    }
}



void clearBackground()
{
    int x, y;

    for(y = 0; y < SH; y++)
    {
        for(x = 0; x < SW; x++)
        {
            pixel(x, y, 8);         // Clear background color
        }
    }
}

void clipBehindPlayer(int *x1, int *y1, int *z1, int x2, int y2, int z2)
{
    float da = *y1;     // Distance plane -> point a
    float db = y2;      // Distance plane -> point b
    float d = da-db; if(d == 0) { d = 1; }
    float s = da / (da-db);     // Intersection factor (0 < s < 1)

    *x1 = *x1 + s * (x2 - (*x1));
    *y1 = *y1 + s * (y2 - (*y1));   if(*y1 == 0) { *y1 = 1; }
    *z1 = *z1 + s * (z2 - (*z1));
}

void drawWall(int x1, int x2, int b1, int b2, int t1, int t2, int c, int s)
{
    int x, y;

    // Hold difference in distance
    int dyb = b2 - b1;                          // Y distance of bottom line
    int dyt = t2 - t1;                          // Y distance of top line
    int dx  = x2 - x1; if(dx == 0){ dx = 1; }   // X distance
    int xs = x1;                                // Hold initial x1 starting point

    // Clip X
    if(x1 < 1) { x1 = 1; }  // Clip left
    if(x2 < 1) { x2 = 1; }  // Clip left
    if(x1 > SW-1) { x1 = SW-1; }    // Clip right
    if(x2 > SW-1) { x2 = SW-1; }    // Clip right

    // Draw x vertical line
    for(x = x1; x < x2; x++)
    {
        // The y start and end point
        int y1 = dyb * (x-xs+0.5) / dx+b1;      // Y bottom point
        int y2 = dyt * (x-xs+0.5) / dx+t1;      // Y top point

        // Clip Y
        if (y1 < 1){ y1 = 1; }
        if (y2 < 1){ y2 = 1; }
        if (y1 > SH-1){ y1 = SH-1; }
        if (y2 > SH-1){ y2 = SH-1; }

        // Surface
        if(S[s].surface == 1)   // Save bottom points
        {
            S[s].surf[x] = y1;
            continue;
        }
        if(S[s].surface == 2)   // Save top points
        {
            S[s].surf[x] = y2;
            continue;
        }
        if(S[s].surface == -1)   // Bottom
        {
            for(y = S[s].surf[x]; y < y1; y++)
            {
                pixel(x, y, S[s].c1);
            }
        }
        if(S[s].surface == -2)   // Bottom
        {
            for(y = y2; y < S[s].surf[x]; y++)
            {
                pixel(x, y, S[s].c2);
            }
        }

        for(y = y1; y < y2; y++)    // Normal wall
        {
            pixel(x, y, c);
        }
    }
}

int dist(int x1, int y1, int x2, int y2)
{
    int distance = sqrt((x2-x1) * (x2-x1) + (y2-y1) * (y2-y1));
    return distance;
}

void draw3D()
{
    int  s, w, loop;
    int wx[4], wy[4], wz[4];
    float  CS = M.cos[P.a], SN = M.sin[P.a];

    // Order sectors by distance
    for(s = 0; s < NUMSECT; s++)
    {
        for(w = 0; w < NUMSECT-s-1; w++)
        {
            if(S[w].d < S[w+1].d)
            {
                Sectors st = S[w];
                S[w] = S[w+1];
                S[w+1] = st;
            }
        }
    }

    // Draw sector
    for(s = 0; s < NUMSECT; s++) {
        S[s].d = 0;     // Clear distance

        if(P.z < S[s].z1){ S[s].surface = 1; }      // Bottom surface
        else if(P.z > S[s].z2){ S[s].surface = 2; } // Top surface
        else{ S[s].surface = 0; }                   // No surface

        for(loop = 0; loop < 2; loop++) {
            for (w = S[s].ws; w < S[s].we; w++) {
                // Offset bottom two points by player
                int x1 = W[w].x1 - P.x, y1 = W[w].y1 - P.y;
                int x2 = W[w].x2 - P.x, y2 = W[w].y2 - P.y;

                // Swap for surface
                if(loop == 0) {
                    int swp = x1;
                    x1 = x2;
                    x2 = swp;
                    swp = y1;
                    y1 = y2;
                    y2 = swp;
                }

                // World x position
                wx[0] = x1 * CS - y1 * SN;
                wx[1] = x2 * CS - y2 * SN;
                wx[2] = wx[0];
                wx[3] = wx[1];

                // World y position (depth)
                wy[0] = y1 * CS + x1 * SN;
                wy[1] = y2 * CS + x2 * SN;
                wy[2] = wy[0];
                wy[3] = wy[1];
                S[s].d += dist(0, 0, (wx[0] + wx[1]) / 2, (wy[0] + wy[1]) / 2);

                // World z height
                wz[0] = S[s].z1 - P.z + ((P.l * wy[0]) / 32.0);
                wz[1] = S[s].z1 - P.z + ((P.l * wy[1]) / 32.0);
                wz[2] = wz[0] + S[s].z2;
                wz[3] = wz[1] + S[s].z2;

                // Don't draw if behind player
                if (wy[0] < 1 && wy[1] < 1) { continue; }
                // Point 1 behind player, clip
                if (wy[0] < 1) {
                    clipBehindPlayer(&wx[0], &wy[0], &wz[0], wx[1], wy[1], wz[1]);  // Bottom line
                    clipBehindPlayer(&wx[2], &wy[2], &wz[2], wx[3], wy[3], wz[3]);  // Top line
                }
                // Point 2 behind player, clip
                if (wy[1] < 1) {
                    clipBehindPlayer(&wx[1], &wy[1], &wz[1], wx[0], wy[0], wz[0]);  // Bottom line
                    clipBehindPlayer(&wx[3], &wy[3], &wz[3], wx[2], wy[2], wz[2]);  // Top line
                }

                // Screen x, screen y position
                for (int i = 0; i < 4; i++) {
                    wx[i] = wx[i] * 200 / wy[i] + SW2;
                    wy[i] = wz[i] * 200 / wy[i] + SH2;
                }

                // Draw points
                drawWall(wx[0], wx[1], wy[0], wy[1], wy[2], wy[3], W[w].c, s);
            }
            S[s].d /= (S[s].we - S[s].ws);  // Find  average sector distance
            S[s].surface *= -1;             // Flip to  negative to draw surface
        }
    }
}

void display()
{
    int x, y;
    if(T.fr1 - T.fr2 >= 50)                                 // Only draw 20 frames/s
    {
        clearBackground();
        movePlayer();
        draw3D();

        T.fr2 = T.fr1;
        glutSwapBuffers();
        glutReshapeWindow(GLSW, GLSH);          // Prevent window scaling
    }

    T.fr1 = glutGet(GLUT_ELAPSED_TIME);                 // 1000 ms/s
    glutPostRedisplay();
}

void KeysDown(unsigned char key, int x, int y)
{
    if(key=='z'==1){ K.w =1;}
    if(key=='s'==1){ K.s =1;}
    if(key=='q'==1){ K.a =1;}
    if(key=='d'==1){ K.d =1;}
    if(key=='m'==1){ K.m =1;}
    if(key=='a'==1){ K.sr=1;}
    if(key=='e'==1){ K.sl=1;}
}

void KeysUp(unsigned char key,int x,int y)
{
    if(key=='z'==1){ K.w =0;}
    if(key=='s'==1){ K.s =0;}
    if(key=='q'==1){ K.a =0;}
    if(key=='d'==1){ K.d =0;}
    if(key=='m'==1){ K.m =0;}
    if(key=='a'==1){ K.sr=0;}
    if(key=='e'==1){ K.sl=0;}
}

int loadSectors[] =
        {   // Wall start, wall end, z1 height, z2 height, bottom color, top color
                0, 4, 0, 40, 2, 3,     // Sector 1
                4, 8, 0, 40, 4,  5,      // Sector 2
                8, 12, 0, 40, 6,  7,   // Sector 3
                12, 16, 0, 40, 0, 1   // Sector  4
        };

int loadWalls[]=
        {   // x1, y1, x2, y2, color
                0, 0, 32, 0, 0,
                32, 0, 32, 32, 1,
                32, 32, 0, 32, 0,
                0, 32, 0, 0, 1,

                64, 0, 96, 0, 2,
                96, 0, 96, 32, 3,
                96, 32, 64, 32, 2,
                64, 32, 64, 0, 3,

                64, 64, 96, 64, 4,
                96, 64, 96, 96, 5,
                96, 96, 64, 96, 4,
                64, 96, 64, 64, 5,

                0, 64, 32, 64, 6,
                32, 64, 32, 96, 7,
                32,  96, 0, 96, 6,
                0, 96, 0, 64, 7

        };

void init()
{
    int x;

    // Store sin & cos in degrees
    for(x = 0; x < 360; x++)
    {
        M.cos[x] = cos(x/180.0*M_PI);
        M.sin[x] = sin(x/180.0*M_PI);
    }

    // Init player
    P.x = 70;
    P.y = -110;
    P.z = 20;
    P.a = 0;
    P.l = 0;

    // Load sectors
    int s, w;
    int v1 = 0, v2 = 0;
    for(s = 0; s < NUMSECT; s++) {
        S[s].ws = loadSectors[v1 + 0];                        // Wall start number
        S[s].we = loadSectors[v1 + 1];                        // Wall end number
        S[s].z1 = loadSectors[v1 + 2];                        // Sector bottom height
        S[s].z2 = loadSectors[v1 + 3] - loadSectors[v1 + 2];  // Sector top height
        S[s].c1 = loadSectors[v1 + 4];                        // Sector top color
        S[s].c2 = loadSectors[v1 + 5];                        // Sector bottom color
        v1 += 6;
        for (w = S[s].ws; w < S[s].we; w++) {
            W[w].x1 = loadWalls[v2 + 0];  // Bottom x1
            W[w].y1 = loadWalls[v2 + 1];  // Bottom y1
            W[w].x2 = loadWalls[v2 + 2];  // Top x2
            W[w].y2 = loadWalls[v2 + 3];  // Top y2
            W[w].c = loadWalls[v2 + 4];  // Top y2
            v2 += 5;
        }
    }
}
