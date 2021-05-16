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
	a->currentPosition.x++;
	a->energy -= MOVE_ENERGY;
}
void move_b(ant* a){
	//left
	a->currentPosition.x--;
	a->energy -= MOVE_ENERGY;
}
void move_l(ant* a){
	//up
	a->currentPosition.y--;
	a->energy -= MOVE_ENERGY;
}
void move_r(ant* a){
	//down
	a->currentPosition.y++;
	a->energy -= MOVE_ENERGY;
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

int bjpi(map* m, ant* a){
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
				a->currentPosition.x -= a->itchRight;
				a->itchRight = 0; 
				a->energy -= BJPI_ENERGY;
				return 1;
			}
			return 0;
			break;
		case DIR_UP:
			if(a->itchRight > 0){
				a->currentPosition.y -= a->itchRight;
				a->itchRight = 0; 
				a->energy -= BJPI_ENERGY;
				return 1;
			}
			return 0;
			break;
		case DIR_DOWN:
			if(a->itchRight > 0){
				a->currentPosition.y += a->itchRight;
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

void mark(map* m, ant* a){
	setMapData(m, a->currentPosition.x, a->currentPosition.y, TILE_PHEROMONE);
}
