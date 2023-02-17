#include "include/player.h"

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