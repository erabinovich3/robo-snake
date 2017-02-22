// CS 2110: HW09
// Erica Rabinovich
// item.c

#include "drawing.h"
#include "robot_logic.h"
#include "stdlib.h"
#include "battery.h"
#include "bolt.h"
#include "gear.h"
#include "oil.h"
#include "wrench.h"
#include "robot.h"
#include "item.h"
#include "main_screen2.h"
#include "myLib.h"

/* generateItem
* A function that will generate
* a new item for the snake to consume.
*/
void generateItem() {
    int x = rand() % 12 + 1;
    int y = rand() % 6 + 1;

    for (unsigned int i = 0; i < numRobots; i++) {
        if (x == snake[i].x && y == snake[i].y) {
            x = rand() % 12 + 1;
            y = rand() % 6 + 1;
        }
    }

    int choice = rand() % 5;

    if (choice == 0) {
        drawImage3(CALCROW(y), CALCCOL(x), BATTERY_WIDTH, BATTERY_HEIGHT, battery);
    } else if (choice == 1) {
        drawImage3(CALCROW(y), CALCCOL(x), BOLT_WIDTH, BOLT_HEIGHT, bolt);
    } else if (choice == 2) {
        drawImage3(CALCROW(y), CALCCOL(x), GEAR_WIDTH, GEAR_HEIGHT, gear);
    } else if (choice == 3) {
        drawImage3(CALCROW(y), CALCCOL(x), OIL_WIDTH, OIL_HEIGHT, oil);
    } else if (choice == 4) {
        drawImage3(CALCROW(y), CALCCOL(x), WRENCH_WIDTH, WRENCH_HEIGHT, wrench);
    }

    items[numItems].x = x;
    items[numItems].y = y;
    items[numItems++].type = choice;
}

/* drawString
* A function that will check to see if
* the snake has consumed an item.
* @param i index of item in array to
*   check for collision with
*/
void checkItemCollision(unsigned int i) {
    if (items[i].x == front->x && items[i].y == front->y) {
        eraseItem(items[i].x, items[i].y);
        addRobot(rd, cd);
        collided = 1;
    }
}

/* eraseItem
* A function that will erase an item
* from the screen.
* @param x x-coordinate of item
* @param y y-coordinate of item
*/
void eraseItem(int x, int y) {
    for (int row = 0; row < 15; row++) {
        DMA[3].src = (&main_screen2[((row + CALCROW(y) - 10) * MAIN_SCREEN2_WIDTH) + (CALCCOL(x) - 10)]);
		DMA[3].dst = (&videoBuffer[OFFSET(row + CALCROW(y), CALCCOL(x), 240)]);
		DMA[3].cnt = 15 | DMA_ON | DMA_SOURCE_INCREMENT;
    }

    numItems--;
}
