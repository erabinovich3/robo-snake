// CS 2110: HW09
// Erica Rabinovich
// myLib.c

#include "myLib.h"
#include "stdio.h"
#include "drawing.h"

/* waitForVblank
* A function that will wait for Vblank to occur.
*/
void waitForVblank() {
    while (SCANELINECOUNTER > 160);
    while (SCANELINECOUNTER < 160);
}

/* getScore
* A function that will erase the old score
* before formatting and drawing the current one.
*/
void getScore() {
    drawRect(151, 45, 8, 180, BLACK);
    sprintf(buffer, "%d", score);
    drawString(151, 45, buffer, WHITE);
}
