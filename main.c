// CS 2110: HW09
// Erica Rabinovich
// main.c

#include "myLib.h"
#include "drawing.h"
#include "robot.h"
#include "robot_logic.h"
#include "item.h"
#include "stdlib.h"

// State enum definition
enum GBAState {
	TITLE,
	TITLE_NODRAW,
    MAIN,
    GAME_OVER,
    GAME_OVER_NODRAW
};

ROBOT snake[MAX];
unsigned int numRobots;
ROBOT *front;

unsigned int bIndex;
ROBOT *back;

int rd;
int cd;

int collided;
int selfCollide;

ITEM items[MAX];
unsigned int numItems;

unsigned int score;

int main() {
    REG_DISPCNT = MODE_3 | BG2_EN;

    enum GBAState state = TITLE;
    selfCollide = 0;

    int stay = 0;
    int dChange = 0;

    while(1) { //main game loop

        //overall state logic
        switch(state) {
		case TITLE:
			getTitleScreen();

            state = TITLE_NODRAW;
			break;

        case TITLE_NODRAW:
            if (KEY_DOWN_NOW(BUTTON_START)) { //Enter
                state = MAIN;
            }
			break;

        case MAIN:
            fillScreen(BLACK);

            score = 0;

            getMainScreen();

            snake[0].x = 0;
            snake[0].y = 0;
            rd = 0;
            cd = 1;

            numRobots = 1;
            numItems = 0;

            front = snake;
            back = snake;
            bIndex = 0;

            while(1) { //main state loop

                waitForVblank();

                if (KEY_DOWN_NOW(BUTTON_SELECT)) { //Backspace
                    state = TITLE;
                    break;
                }

                if (KEY_DOWN_NOW(BUTTON_RIGHT) && !dChange) { //go right with right arrow, only if not going left
                    if (cd != -1) {
                        rd = 0;
                        cd = 1;
                        dChange = 1; //allow only one direction change per cycle
                    }
                }

                if (KEY_DOWN_NOW(BUTTON_LEFT) && !dChange) { //go left with left arrow, only if not going right
                    if (cd != 1) {
                        rd = 0;
                        cd = -1;
                        dChange = 1;
                    }
                }

                if (KEY_DOWN_NOW(BUTTON_UP) && !dChange) { //go up with up arrow, only if not going down
                    if (rd != 1) {
                        rd = -1;
                        cd = 0;
                        dChange = 1;
                    }
                }

                if (KEY_DOWN_NOW(BUTTON_DOWN) && !dChange) { //go down with down arrow, only if not going up
                    if (rd != -1) {
                        rd = 1;
                        cd = 0;
                        dChange = 1;
                    }
                }

                if (!stay) {

                    collided = 0;
                    dChange = 0;

                    for (unsigned int i = 0; i < numItems; i++) {
                        checkItemCollision(i);
                    }

                    if (!collided) { //only move if snake has not grown
                        eraseRobot(back->x, back->y); //erase back robot

                        back->x = front->x + cd;
                        back->y = front->y + rd;
                        front = back; //new front is old back

                        back++;

                        drawImage3(CALCROW(front->y), CALCCOL(front->x), ROBOT_WIDTH, ROBOT_HEIGHT, robot); //draw new front

                        checkSelfCollision();

                        if (selfCollide) {
                            state = GAME_OVER;
                            break;
                        }
                    }

                    if (back > snake + numRobots - 1) {
                        back = snake;
                    }

                    bIndex = back - snake;

                    if (front->x < 0 || front->x > 13
                        || front->y < 0 || front->y > 7) { //check for collision with borders
                        state = GAME_OVER;
                        break;
                    }

                    if (numItems < 1) {
                        generateItem();
                    }
                } //main state loop

                stay++;

                if (stay > 70) { //only move every 70 Vblanks
                    stay = 0;
                }
            }

            break;

        case GAME_OVER:
            getGameOver();

            state = GAME_OVER_NODRAW;
            break;

        case GAME_OVER_NODRAW:
            if (KEY_DOWN_NOW(BUTTON_START)) { //Enter
                selfCollide = 0;
                state = MAIN;
            }

            if (KEY_DOWN_NOW(BUTTON_SELECT)) { //Backspace
                state = TITLE;
                break;
            }
            break;
        }
    } //main game loop
}
