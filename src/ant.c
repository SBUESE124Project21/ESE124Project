#include "ant.h"
#include <stdlib.h>

ant* makeAnt(int x, int y, int energy){
	ant* a = (ant*)calloc(1, sizeof(ant));
	a->memoryStack = makeStack(MAX_STACKSIZE);
	a->currentPosition.x = x;
	a->currentPosition.y = y;
	a->energy = energy;
	a->collectedGold = 0;
	return a;
}
void freeAnt(ant* a){
	freeStack(a->memoryStack);
	free(a);
}

int isAlive(ant* a){
	return a->energy > 0;
}

void collectGold(map* m, ant* a){
	int t = getMapData(m, a->currentPosition.x, a->currentPosition.y);
	if(t == TILE_GOLD){
		a->collectedGold++;
		setMapData(m, a->currentPosition.x, a->currentPosition.y, TILE_SPACE);
	}
}
void collectGoldOnJump(map* m, ant* a, node startPosition, node endPosition){
	int x = startPosition.x;
	int y = startPosition.y;
	if(startPosition.x == endPosition.x){
		int direction = (endPosition.y - startPosition.y) > 0 ? 1 : -1;
		for(y = startPosition.y; y <= endPosition.y; y += direction){
			int t = getMapData(m, x, y);
			if(t == TILE_GOLD){
				a->collectedGold++;
				setMapData(m, a->currentPosition.x, a->currentPosition.y, TILE_SPACE);
			}	
		}
	}
	else if (startPosition.y == endPosition.y){
		int direction = (endPosition.x - startPosition.x) > 0 ? 1 : -1;
		for(x = startPosition.x; x <= endPosition.x; x += direction){
			int t = getMapData(m, x, y);
			if(t == TILE_GOLD){
				a->collectedGold++;
				setMapData(m, x, y, TILE_SPACE);
			}	
		}
	}
}

node pop(ant* a){
	if(empty(a)){
		node n;
		n.x = -1;
		n.y = -1;
		return n;
	}
	a->memoryPosition = spop(a->memoryStack);
	a->energy -= PUSH_POP_ENERGY;
	return a->memoryPosition;
}
node peek(ant* a){
	if(empty(a)){
		node n;
		n.x = -1;
		n.y = -1;
		return n;
	}
	a->memoryPosition = speek(a->memoryStack);
	a->energy -= PEEK_CLEAR_ENERGY;
	return a->memoryPosition;
}
void push(ant* a){
	if(!scontains(a->memoryStack, a->currentPosition)){
		a->energy -= PUSH_POP_ENERGY;
		spush(a->memoryStack, a->currentPosition);
	}
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
	a->energy -= MOVE_ENERGY;
	if(a->currentPosition.x < m->width-1){
		a->currentPosition.x++;
		collectGold(m, a);
	}
}
void move_b(map* m, ant* a){
	//left
	a->energy -= MOVE_ENERGY;
	if(a->currentPosition.x > 1){
		a->currentPosition.x--;
		collectGold(m, a);
	}
}
void move_l(map* m, ant* a){
	//up
	a->energy -= MOVE_ENERGY;
	if(a->currentPosition.y > 1){
		a->currentPosition.y--;
		collectGold(m, a);
	}
}
void move_r(map* m, ant* a){
	//down
	a->energy -= MOVE_ENERGY;
	if(a->currentPosition.y < m->height - 1){
		a->currentPosition.y++;
		collectGold(m, a);
	}
}

int cwf(map* m, ant* a){	//right
	int positions = 1;
	a->energy -= CHECK_ENERGY;
	a->lastCheckDirection = DIR_RIGHT;
	while(1){
		int nval = getMapData(m, a->currentPosition.x+positions, a->currentPosition.y);
		if(nval == TILE_OUTSIDE){
			return 0;
		}
		if(nval == TILE_WALL || nval == TILE_PHEROMONE){
			a->itchRight = positions-1;
			return positions-1;
		}
		positions++;
	}
}
int cwb(map* m, ant* a){	//left
	int positions = 1;
	a->energy -= CHECK_ENERGY;
	a->lastCheckDirection = DIR_LEFT;
	while(1){
		int nval = getMapData(m, a->currentPosition.x-positions, a->currentPosition.y);
		if(nval == TILE_OUTSIDE){
			return 0;
		}
		if(nval == TILE_WALL || nval == TILE_PHEROMONE){
			a->itchRight = positions-1;
			return positions-1;
		}
		positions++;
	}
}
int cwl(map* m, ant* a){	//up
	int positions = 1;
	a->energy -= CHECK_ENERGY;
	a->lastCheckDirection = DIR_UP;
	while(1){
		int nval = getMapData(m, a->currentPosition.x, a->currentPosition.y-positions);
		if(nval == TILE_OUTSIDE){
			return 0;
		}
		if(nval == TILE_WALL || nval == TILE_PHEROMONE){
			a->itchRight = positions-1;
			return positions-1;
		}
		positions++;
	}
}
int cwr(map* m, ant* a){	//down
	int positions = 1;
	a->energy -= CHECK_ENERGY;
	a->lastCheckDirection = DIR_DOWN;
	while(1){
		int nval = getMapData(m, a->currentPosition.x, a->currentPosition.y+positions);
		if(nval == TILE_OUTSIDE){
			return 0;
		}
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
				node start = a->currentPosition;
				a->currentPosition.x += a->itchRight;
				node end = a->currentPosition;
				a->itchRight = 0; 
				a->itchDown = 0;  
				a->itchLeft = 0;  
				a->itchUp = 0; 
				a->energy -= BJPI_ENERGY;
				return 1;
			}
			return 0;
			break;
		case DIR_LEFT:
			if(a->itchRight > 0){
				node start = a->currentPosition;
				a->currentPosition.x -= a->itchLeft;
				node end = a->currentPosition;
				collectGoldOnJump(m, a, start, end);
				a->itchRight = 0; 
				a->itchDown = 0;  
				a->itchLeft = 0;  
				a->itchUp = 0; 
				a->energy -= BJPI_ENERGY;
				return 1;
			}
			return 0;
			break;
		case DIR_UP:
			if(a->itchRight > 0){
				node start = a->currentPosition;
				a->currentPosition.y -= a->itchUp;
				node end = a->currentPosition;
				collectGoldOnJump(m, a, start, end);
				a->itchRight = 0; 
				a->itchDown = 0;  
				a->itchLeft = 0;  
				a->itchUp = 0; 
				a->energy -= BJPI_ENERGY;
				return 1;
			}
			return 0;
			break;
		case DIR_DOWN:
			if(a->itchRight > 0){
				node start = a->currentPosition;
				a->currentPosition.y += a->itchDown;
				node end = a->currentPosition;
				collectGoldOnJump(m, a, start, end);
				a->itchRight = 0; 
				a->itchDown = 0;  
				a->itchLeft = 0;  
				a->itchUp = 0; 
				a->energy -= BJPI_ENERGY;
				return 1;
			}
			return 0;
			break;
		default:
			break;
	}
}

int cjpi(map* m, ant* a){
	switch(a->lastCheckDirection){
		case DIR_RIGHT:
			if(a->itchRight > 0){
				a->currentPosition.x += 1;
				a->itchRight = 0; 
				a->energy -= BJPI_ENERGY;
				collectGold(m,a);
				return 1;
			}
			return 0;
			break;
		case DIR_LEFT:
			if(a->itchRight > 0){
				a->currentPosition.x -= 1;
				a->itchRight = 0; 
				a->energy -= BJPI_ENERGY;
				collectGold(m,a);
				return 1;
			}
			return 0;
			break;
		case DIR_UP:
			if(a->itchRight > 0){
				a->currentPosition.y -= 1;
				a->itchRight = 0; 
				a->energy -= BJPI_ENERGY;
				collectGold(m,a);
				return 1;
			}
			return 0;
			break;
		case DIR_DOWN:
			if(a->itchRight > 0){
				a->currentPosition.y += 1;
				a->itchRight = 0; 
				a->energy -= BJPI_ENERGY;
				collectGold(m,a);
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
