#include "stack.h"

typedef struct ant ant;


struct ant{
	stack* memoryStack;

	int x, y;	// current position
	int mx, my; // memory position
	
	
	int energy; //energy remaining
	
	/*direction itch states*/
	int itchUp;
	int itchDown;
	int itchRight;
	int itchLeft;	
	
	int distance; //distance of last measured itch direction
};

/* Ant specific functions */

void mark(ant* a);
void move_f(ant* a);	//right
void move_b(ant* a);	//left
void move_l(ant* a);	//up
void move_r(ant* a);	//down

int cwf(ant* a);
int cwb(ant* a);
int cwl(ant* a);	
int cwr(ant* a);

int bjpi(ant* a);
int cjpi(ant* a);

void backtrack(ant* a, int x, int y);

