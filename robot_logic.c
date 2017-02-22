// CS 2110: HW09
// Erica Rabinovich
// robot_logic.c

#include "robot_logic.h"
#include "myLib.h"
#include "drawing.h"
#include "robot.h"
#include "main_screen2.h"

/* addRobot
* A function that will grow the snake by
* adding another robot.
* @param rd direction of change for row of front
* @param cd direction of change for col of front
*/
void addRobot(int rd, int cd) {
    for (unsigned int i = numRobots++; i > bIndex; i--) { //make room in snake for new robot
        snake[i] = snake[i - 1];
    }

    snake[bIndex].x = front->x + cd;
    snake[bIndex].y = front->y + rd;
    drawImage3(CALCROW(front->y), CALCCOL(front->x), ROBOT_WIDTH, ROBOT_HEIGHT, robot); //redraw robot erased by collision
    front = snake + bIndex;
    drawImage3(CALCROW(front->y), CALCCOL(front->x), ROBOT_WIDTH, ROBOT_HEIGHT, robot); //draw new front

    back++;

    score += 50;
    getScore();
}

/* eraseRobot
* A function that will erase a robot from
* the screen.
* @param x x-coordinate of robot to be erased
* @param y y-coordinate of robot to be erased
*/
void eraseRobot(int x, int y) {
    for (int row = 0; row < ROBOT_HEIGHT; row++) {
        DMA[3].src = (&main_screen2[((row + CALCROW(y) - 10) * MAIN_SCREEN2_WIDTH) + (CALCCOL(x) - 10)]);
		DMA[3].dst = (&videoBuffer[OFFSET(row + CALCROW(y), CALCCOL(x), 240)]);
		DMA[3].cnt = ROBOT_WIDTH | DMA_ON | DMA_SOURCE_INCREMENT;
    }
}

/* checkSelfCollision
* A function that will check to see
* if the snake has collided with itself.
*/
void checkSelfCollision() {
    for (unsigned int i = 0; i < numRobots; i++) {
        if ((snake + i) != front && snake[i].x == front->x && snake[i].y == front->y) {
            selfCollide = i + 1;
        }
    }
}
