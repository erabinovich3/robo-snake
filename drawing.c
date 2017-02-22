// CS 2110: HW09
// Erica Rabinovich
// drawing.c

#include "drawing.h"
#include "myLib.h"
#include "title_screen.h"
#include "main_screen2.h"
#include "robot.h"
#include "game_over.h"
#include "stdio.h"

unsigned short *videoBuffer = (u16 *)0x6000000;
char buffer[41];

/* getTitleScreen
* A function that will draw the title screen image
* as well as the title screen text.
*/
void getTitleScreen() {
    drawImage3(0, 0, TITLE_SCREEN_WIDTH, TITLE_SCREEN_HEIGHT, title_screen);
    drawTitle(35, 40, "ROBO SNAKE", BLACK);
    drawString(100, 115, "Press SELECT", BLACK);
    drawString(110, 130, "to play", BLACK);
}

/* getMainScreen
* A function that will draw the initial state
* of the main screen of the game: the background
* and start score.
*/
void getMainScreen() {
    drawImage3(10, 10, MAIN_SCREEN2_WIDTH, MAIN_SCREEN2_HEIGHT, main_screen2);
    sprintf(buffer, "Score: %d", score);
    drawString(151, 3, buffer, WHITE);
}

/* getGameOver
* A function that will draw the game over
* screen of the game as well as the final score
* and other game over text.
*/
void getGameOver() {
    drawImage3(0, 0, GAME_OVER_WIDTH, GAME_OVER_HEIGHT, game_over);
    drawTitle(20, 65, "GAME OVER", BLACK);
    sprintf(buffer, "Score: %d", score);
    drawString(120, 85, buffer, GREY);
    drawString(133, 85, "Press START", BLACK);
    drawString(141, 85, "to play again", BLACK);
}

/* drawChar
* A function that will draw a specified character
* at the specified coordinates in a specified color.
* @param row row to draw the character
* @param col col to draw the character
* @param ch character to draw
* @param color color to draw character in
*/
void drawChar(int row, int col, char ch, u16 color) {
	for(int r=0; r<8; r++) {
		for(int c=0; c<6; c++) {
			if(fontdata_6x8[OFFSET(r, c, 6) + ch*48]) {
				setPixel(row+r, col+c, color);
			}
		}
	}
}

/* drawString
* A function that will draw a string at the
* specified location in a specified color.
* @param row row to draw string
* @param col col to draw string
* @param *str string to draw
* @param color color to draw string in
*/
void drawString(int row, int col, char *str, u16 color) {
	while(*str) {
		drawChar(row, col, *str++, color);
		col += 6;
	}
}

/* drawTitleChar
* A function that will draw a specified title-size
* character at the specified coordinates in a specified color.
* ! ONLY WORKS WITH CAPITAL LETTERS AND SPACE !
* @param row row to draw the character
* @param col col to draw the character
* @param ch title-size character to draw
* @param color color to draw character in
*/
void drawTitleChar(int row, int col, char ch, u16 color) {
	for(int r = 0; r < 16; r++) {
		for(int c = 0; c < 12; c++) {
			if(fontdata_12x16[OFFSET(r, c, 12) + ch * 192]) {
				setPixel(row + r, col + c, color);
			}
		}
	}
}

/* drawTitle
* A function that will draw a title-size string at the
* specified location in a specified color.
* ! ONLY WORKS WITH CAPITAL LETTERS AND SPACE !
* @param row row to draw string
* @param col col to draw string
* @param *str title-size string to draw
* @param color color to draw string in
*/
void drawTitle(int row, int col, char *str, u16 color) {
	while(*str) {
		drawTitleChar(row, col, *str++, color);
		col += 12;
	}
}

/* fillScreen
* A function that will fill the screen
* with one color.
* @param color color to fill screen with
*/
void fillScreen(volatile u16 color) {
    DMA[3].src = (&color);
    DMA[3].dst = videoBuffer;
    DMA[3].cnt = 38400 | DMA_ON | DMA_SOURCE_FIXED;
}

/* drawimage3
* A function that will draw an arbitrary sized image
* onto the screen (with DMA).
* @param r row to draw the image
* @param c column to draw the image
* @param width width of the image
* @param height height of the image
* @param image Pointer to the first element of the image.
*/
void drawImage3(int r, int c, int width, int height, const u16 *image) {
    for (int row = 0; row < height; row++) {
        DMA[3].src = (&image[row * width]);
		DMA[3].dst = (&videoBuffer[OFFSET(r + row, c, 240)]);
		DMA[3].cnt = width | DMA_ON | DMA_SOURCE_INCREMENT;
    }
}

/* setPixel
* A function that will set a single pixel
* to a certain color.
* @param row row of pixel to set
* @param col col of pixel to set
* @param color color to set pixel
*/
void setPixel(int row, int col, u16 color) {
	videoBuffer[OFFSET(row, col, 240)] = color;
}

/* drawString
* A function that will draw a rectangle
* of a specified size in a certain color.
* @param r row coordinate to draw rectangle
* @param c col coordinate to draw rectangle
* @param height height of rectangle
* @param width width of rectangle
* @param color color of rectangle
*/
void drawRect(int r, int c, int height, int width, unsigned short color) {
    for (int row = 0; row < height; row++) {
        DMA[3].src = (&color);
		DMA[3].dst = (&videoBuffer[OFFSET(r + row, c, 240)]);
		DMA[3].cnt = width | DMA_ON | DMA_SOURCE_FIXED;
    }
}
