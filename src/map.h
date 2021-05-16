#include "stack.h"
typedef struct map map;

struct map{
	int width;
	int height;
	int** data;
	node antOrigin;
};

map* makeMap(int width, int height);
void freeMap(map* m);
int getMapData(map* m, node antPosition);
int setMapData(map* m, node antPosition, int value);
