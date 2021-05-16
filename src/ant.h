#include "stack.h"
#include "config.h"
#include "map.h"

#define MARK_ENERGY 3
#define MOVE_ENERGY 3
#define CHECK_ENERGY 1
#define PUSH_POP_ENERGY 4
#define PEEK_CLEAR_ENERGY 2
#define BJPI_ENERGY 5
#define CJPI_ENERGY 3

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
	
	int consumedEnergy;
	int lastCheckDirection; // last direction checked
};

/* Helper functions */
ant* makeAnt(int x, int y, int energy);
void freeAnt(ant* a);

/* Ant specific functions */

void mark(map* m, ant* a);
void move_f(ant* a);	//right
void move_b(ant* a);	//left
void move_l(ant* a);	//up
void move_r(ant* a);	//down

int cwf(map* m, ant* a);
int cwb(map* m, ant* a);
int cwl(map* m, ant* a);	
int cwr(map* m, ant* a);

int bjpi(ant* a);
int cjpi(ant* a);

void backtrack(ant* a, int x, int y);

/* Stack functions */
node pop(ant* a);
node peek(ant* a);
void push(ant* a);
void clear(ant* a);
int empty(ant* a);
int full(ant* a);
