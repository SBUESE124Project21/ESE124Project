#pragma once
#include "stack.h"
#include <stdio.h>
typedef struct map map;

struct map{
	int width;
	int height;
	int** data;
	node antOrigin;
};


map* makeMap(int width, int height);
void freeMap(map* m);
map* loadMap(FILE* mapfile);
void printMapWithAnt(map* m, int x, int y, FILE* outputFile);

node getStartPosition(map* m);
void printMap(map* m, FILE* outputFile);

int getMapData(map* m, int x, int y);
int setMapData(map* m, int x, int y, int value);
