#include "ant.h"

node pop(ant* a){
	return spop(a->memoryStack);
}
node peek(ant* a){
	return speek(a->memoryStack);
}
void push(ant* a, node n){
	spush(a->memoryStack, n);
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
	a->x++;
	a->energy -= MOVE_ENERGY;
}
void move_b(ant* a){
	//left
	
}
void move_l(ant* a){
	//up
	
}
void move_r(ant* a){
	//down
	
}
