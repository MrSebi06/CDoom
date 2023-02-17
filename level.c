#include "include/level.h"

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
