typedef struct map map;

struct map{
	int width;
	int height;
	int** data;
};

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

freeMap(map* m){
	int i;
	
	for(i = 0; i < m->width; i++){
		free(m->data[i]);
	}
	free(m->data);
	free(m);
}
