#pragma once
#include "stack.h"
#include "config.h"
#include "map.h"

typedef struct ant ant;

struct ant{
	stack* memoryStack;

	node currentPosition;	// current position
	node memoryPosition; // memory position
	
	int energy; //energy remaining
	
	/*direction itch states*/
	int itchUp;
	int itchDown;
	int itchRight;
	int itchLeft;
	
	int collectedGold;
	int lastCheckDirection; // last direction checked
};

/* Helper functions */
ant* makeAnt(int x, int y, int energy);
void freeAnt(ant* a);
int isAlive(ant* a);
void collectGold(map* m, ant* a);
void collectGoldOnJump(map* m, ant* a, node startPosition, node endPosition);

/* Ant specific functions */

void mark(map* m, ant* a);
void move_f(map* m, ant* a);	//right
void move_b(map* m, ant* a);	//left
void move_l(map* m, ant* a);	//up
void move_r(map* m, ant* a);	//down

int cwf(map* m, ant* a);
int cwb(map* m, ant* a);
int cwl(map* m, ant* a);	
int cwr(map* m, ant* a);

int bjpi(map* m, ant* a);
int cjpi(map* m, ant* a);

void backtrack(ant* a);

/* Stack functions */
node pop(ant* a);
node peek(ant* a);
void push(ant* a);
void clear(ant* a);
int empty(ant* a);
int full(ant* a);
