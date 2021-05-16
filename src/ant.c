#include "ant.h"
#include <stdlib.h>

ant* makeAnt(int x, int y, int energy){
	ant* a = (ant*)calloc(1, sizeof(ant));
	a->memoryStack = makeStack(MAX_STACKSIZE);
	a->currentPosition.x = x;
	a->currentPosition.y = y;
	a->energy = energy;
	return a;
}
void freeAnt(ant* a){
	freeStack(a->memoryStack);
	free(a);
}

int isAlive(ant* a){
	return a->energy > 0;
}

node pop(ant* a){
	a->memoryPosition = spop(a->memoryStack);
	a->energy -= PUSH_POP_ENERGY;
	return a->memoryPosition;
}
node peek(ant* a){
	a->memoryPosition = speek(a->memoryStack);
	a->energy -= PEEK_CLEAR_ENERGY;
	return a->memoryPosition;
}
void push(ant* a){
	a->energy -= PUSH_POP_ENERGY;
	spush(a->memoryStack, a->currentPosition);
}
void clear(ant* a){
	a->energy -= PEEK_CLEAR_ENERGY;
	sclear(a->memoryStack);
}
int empty(ant* a){
	return sempty(a->memoryStack);
}
int full(ant* a){
	return sfull(a->memoryStack);
}

void move_f(map* m, ant* a){
	//right
	if(a->currentPosition.x < m->width-1){
		a->currentPosition.x++;
		a->energy -= MOVE_ENERGY;
	}
}
void move_b(map* m, ant* a){
	//left
	if(a->currentPosition.x > 1){
		a->currentPosition.x--;
		a->energy -= MOVE_ENERGY;
	}
}
void move_l(map* m, ant* a){
	//up
	
	if(a->currentPosition.y < m->height-1){
		a->currentPosition.y--;
		a->energy -= MOVE_ENERGY;
	}
}
void move_r(map* m, ant* a){
	//down
	if(a->currentPosition.y>1){
		a->currentPosition.y++;
		a->energy -= MOVE_ENERGY;
	}
}

int cwf(map* m, ant* a){	//right
	int positions = 1;
	a->lastCheckDirection = DIR_RIGHT;
	while(1){
		int nval = getMapData(m, a->currentPosition.x+positions, a->currentPosition.y);
		if(nval == TILE_WALL || nval == TILE_PHEROMONE){
			a->itchRight = positions-1;
			return positions-1;
		}
		positions++;
	}
}
int cwb(map* m, ant* a){	//left
	int positions = 1;
	a->lastCheckDirection = DIR_LEFT;
	while(1){
		int nval = getMapData(m, a->currentPosition.x-positions, a->currentPosition.y);
		if(nval == TILE_WALL || nval == TILE_PHEROMONE){
			a->itchRight = positions-1;
			return positions-1;
		}
		positions++;
	}
}
int cwl(map* m, ant* a){	//up
	int positions = 1;
	a->lastCheckDirection = DIR_UP;
	while(1){
		int nval = getMapData(m, a->currentPosition.x, a->currentPosition.y+positions);
		if(nval == TILE_WALL || nval == TILE_PHEROMONE){
			a->itchRight = positions-1;
			return positions-1;
		}
		positions++;
	}
}
int cwr(map* m, ant* a){	//down
	int positions = 1;
	a->lastCheckDirection = DIR_DOWN;
	while(1){
		int nval = getMapData(m, a->currentPosition.x, a->currentPosition.y-positions);
		if(nval == TILE_WALL || nval == TILE_PHEROMONE){
			a->itchRight = positions-1;
			return positions-1;
		}
		positions++;
	}
}

int bjpi(ant* a){
	switch(a->lastCheckDirection){
		case DIR_RIGHT:
			if(a->itchRight > 0){
				a->currentPosition.x += a->itchRight;
				a->itchRight = 0; 
				a->energy -= BJPI_ENERGY;
				return 1;
			}
			return 0;
			break;
		case DIR_LEFT:
			if(a->itchRight > 0){
				a->currentPosition.x -= a->itchLeft;
				a->itchRight = 0; 
				a->energy -= BJPI_ENERGY;
				return 1;
			}
			return 0;
			break;
		case DIR_UP:
			if(a->itchRight > 0){
				a->currentPosition.y -= a->itchUp;
				a->itchRight = 0; 
				a->energy -= BJPI_ENERGY;
				return 1;
			}
			return 0;
			break;
		case DIR_DOWN:
			if(a->itchRight > 0){
				a->currentPosition.y += a->itchDown;
				a->itchRight = 0; 
				a->energy -= BJPI_ENERGY;
				return 1;
			}
			return 0;
			break;
		default:
			break;
	}
}

int cjpi(ant* a){
	switch(a->lastCheckDirection){
		case DIR_RIGHT:
			if(a->itchRight > 0){
				a->currentPosition.x += 1;
				a->itchRight = 0; 
				a->energy -= BJPI_ENERGY;
				return 1;
			}
			return 0;
			break;
		case DIR_LEFT:
			if(a->itchRight > 0){
				a->currentPosition.x -= 1;
				a->itchRight = 0; 
				a->energy -= BJPI_ENERGY;
				return 1;
			}
			return 0;
			break;
		case DIR_UP:
			if(a->itchRight > 0){
				a->currentPosition.y -= 1;
				a->itchRight = 0; 
				a->energy -= BJPI_ENERGY;
				return 1;
			}
			return 0;
			break;
		case DIR_DOWN:
			if(a->itchRight > 0){
				a->currentPosition.y += 1;
				a->itchRight = 0; 
				a->energy -= BJPI_ENERGY;
				return 1;
			}
			return 0;
			break;
		default:
			break;
	}
}


void backtrack(ant* a){
	a->currentPosition = a->memoryPosition;
}

void mark(map* m, ant* a){
	setMapData(m, a->currentPosition.x, a->currentPosition.y, TILE_PHEROMONE);
}
