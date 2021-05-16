typedef struct map map;

struct map{
	int width;
	int height;
	int** data;
};

map* makeMap(int width, int height);
void freeMap(map* m);
int getMapData(map* m, int x, int y);
int setMapData(map* m, int x, int y, int value);
