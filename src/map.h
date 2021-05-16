typedef struct map map;

struct map{
	int width;
	int height;
	int** data;
};

map* makeMap(int width, int height);
void freeMap(map* m);
