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
	while(1){
		int nval = getMapData(m, a->currentPosition.x+positions-1, a->currentPosition.y);
		if(nval == TILE_WALL){
			a->itchRight = positions-1;
			return positions-1;
		}
		else if(nval == TILE_PHEROMONE){
			a->itchRight = 0;
			return 0;
		}
		positions++;
	}
}
int cwb(map* m, ant* a){	//left
	int positions = 1;
	while(1){
		int nval = getMapData(m, a->currentPosition.x-positions+1, a->currentPosition.y);
		if(nval == TILE_WALL){
			a->itchLeft = positions-1;
			return positions-1;
		}
		else if(nval == TILE_PHEROMONE){
			a->itchLeft = 0;
			return 0;
		}
		positions++;
	}
}
int cwl(map* m, ant* a){	//up
	int positions = 1;
	while(1){
		int nval = getMapData(m, a->currentPosition.x, a->currentPosition.y+positions-1);
		if(nval == TILE_WALL){
			a->itchUp = positions-1;
			return positions-1;
		}
		else if(nval == TILE_PHEROMONE){
			a->itchUp = 0;
			return 0;
		}
		positions++;
	}
}
int cwr(map* m, ant* a){	//down
	int positions = 1;
	while(1){
		int nval = getMapData(m, a->currentPosition.x, a->currentPosition.y-positions+1);
		if(nval == TILE_WALL){
			a->itchDown = positions-1;
			return positions-1;
		}
		else if(nval == TILE_PHEROMONE){
			a->itchDown = 0;
			return 0;
		}
		positions++;
	}
}

void mark(map* m, ant* a){
	setMapData(m, a->currentPosition.x, a->currentPosition.y, TILE_PHEROMONE);
}
