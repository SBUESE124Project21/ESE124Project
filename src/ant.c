#include "ant.h"

node pop(ant* a){
	return a->memoryPosition = spop(a->memoryStack);
}
node peek(ant* a){
	return a->currentPosition = speek(a->memoryStack);
}
void push(ant* a){
	spush(a->memoryStack, a->currentPosition);
}
void clear(ant* a){
	sclear(a->memoryStack);
}
int empty(ant* a){
	return sempty(a->memoryStack);
}
int full(ant* a){
	return sfull(a->memoryStack);
}

void move_f(ant* a){
	//right
	a->currentPosition->x++;
	a->energy -= MOVE_ENERGY;
}
void move_b(ant* a){
	//left
	a->currentPosition->x--;
	a->energy -= MOVE_ENERGY;
}
void move_l(ant* a){
	//up
	a->currentPosition->y--;
	a->energy -= MOVE_ENERGY;
}
void move_r(ant* a){
	//down
	a->currentPosition->y++;
	a->energy -= MOVE_ENERGY;
}

