// CS 2110: HW09
// Erica Rabinovich
// item.h

typedef struct {
    int x;
    int y;
    int type; //???
} ITEM;

//Function Prototypes
void generateItem();
void checkItemCollision(unsigned int i);
void eraseItem(int x, int y);

//Extern variables
extern ROBOT snake[MAX];
extern ROBOT *front;
extern unsigned int numRobots;
extern ITEM items[MAX];
extern unsigned int numItems;
extern int cd;
extern int rd;
extern int collided;
