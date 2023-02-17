#include "include/display.h"
#include "include/player.h"
#include "include/level.h"


Time T;
Keys K;
Math M;
Player P;
Walls W[30];
Sectors S[30];

int main(int argc, char* argv[]) {
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

    glutInitWindowPosition(GLSW/2, GLSH/2);
    glutInitWindowSize(GLSW, GLSH);

    glutCreateWindow("");

    glPointSize(PIXELSCALE);

    gluOrtho2D(0.0, GLSW, 0.0, GLSH);

    init();

    glutDisplayFunc(display);
    glutKeyboardFunc(KeysDown);
    glutKeyboardUpFunc(KeysUp);

    glutMainLoop();

    return 0;
}
