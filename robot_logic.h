// CS 2110: HW09
// Erica Rabinovich
// robot_logic.h

typedef struct {
    int x; //corresponds to col
    int y; //corresponds to row
} ROBOT;

#define MAX 300

//Function Prototypes
void eraseRobot(int x, int y);
void addRobot(int rd, int cd);
void checkSelfCollision();

//Extern variables
extern int selfCollide;

extern ROBOT snake[MAX];
extern unsigned int numRobots;

extern ROBOT *front;

extern ROBOT *back;
extern unsigned int bIndex;

extern unsigned int score;
