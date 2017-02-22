// CS 2110: HW09
// Erica Rabinovich
// drawing.h

//Colors
#define COLOR(R,G,B) (((R) & 0x1F) | (((G) & 0x1F) << 5) | (((B) & 0x1F) << 10))
#define BLACK   COLOR(0 , 0 , 0 )
#define WHITE   COLOR(31, 31, 31)
#define RED     COLOR(31, 0 , 0 )
#define GREEN   COLOR(0 , 31, 0 )
#define BLUE    COLOR(0 , 0 , 31)
#define YELLOW  COLOR(31, 31, 0 )
#define MAGENTA COLOR(31, 0 , 31)
#define CYAN    COLOR(0 , 31, 31)
#define ORANGE  COLOR(31, 15, 0 )
#define BROWN   COLOR(18, 9 , 0 )
#define PURPLE  COLOR(15, 0 , 15)
#define TEAL    COLOR(0 , 15, 15)
#define MAROON  COLOR(15, 0 , 0 )
#define GREY    COLOR(15, 15, 15)
#define PINK    COLOR(31, 18, 19)

//Prototypes
void drawImage3(int r, int c, int width, int height, const unsigned short *image);
void getTitleScreen();
void getMainScreen();
void getGameOver();
void fillScreen(volatile unsigned short color);
void drawChar(int row, int col, char ch, unsigned short color);
void drawTitleChar(int row, int col, char ch, unsigned short color);
void drawString(int row, int col, char *str, unsigned short color);
void drawTitle(int row, int col, char *str, unsigned short color);
void setPixel(int row, int col, unsigned short color);
void drawRect(int row, int col, int height, int width, unsigned short color);

//Extern variables
extern const unsigned char fontdata_6x8[12288]; //used for drawChar and drawString
extern const unsigned char fontdata_12x16[17664]; //used for drawTitleChar and drawTitle

extern unsigned int score;
