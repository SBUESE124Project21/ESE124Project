#include "map.h"
#include "config.h"
#include <stdlib.h>

map* makeMap(int width, int height){
	map* m = (map*)calloc(1, sizeof(map));
	
	m->width = width;
	m->height = height;
	
	m->data = (int**)calloc(width, sizeof(int*));
	
	int i;
	for(i = 0; i < width; i++){
		m->data[i] = (int*)calloc(height, sizeof(int));
	}
	
	return m;
}

void freeMap(map* m){
	int i;
	
	for(i = 0; i < m->width; i++){
		free(m->data[i]);
	}
	free(m->data);
	free(m);
}

int getMapData(map* m, int x, int y){
	if(x > 0 && y > 0 && x < m->width && y < m->height){
		return m->data[x][y];
	}
	return TILE_OUTSIDE;
}
int setMapData(map* m, int x, int y, int value){
	if(x > 0 && y > 0 && x < m->width && y < m->height){
		m->data[x][y] = value;
		return 1;
	}
	return 0;
}
