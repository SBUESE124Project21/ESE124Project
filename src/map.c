#include "map.h"
#include "config.h"
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

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


map* loadMap(FILE* mapfile){
	char* buf = (char*)calloc(MAX_BUFFERSIZE, sizeof(char));
	
	fgets(buf, MAX_BUFFERSIZE, mapfile);	//Get the first line
	int width = strlen(buf);				//Find the map's width from the first line.
	int height = 1;
	
	while(fgets(buf, MAX_BUFFERSIZE, mapfile) != NULL){
		height++;								//Count the number of rows
	}
	
	fseek(mapfile, 0, SEEK_SET);			//Go back to beginning of the file
	
	map* m = makeMap(width, height);
	int x = 0;
	int y = 0;
	
	while(fgets(buf, MAX_BUFFERSIZE, mapfile) != NULL){	//read each row
		for(x = 0; x < width; x++){						//loop over characters
			setMapData(m, x, y, buf[x]);	//insert the map character into the map struct
		}
		y++;
	}
	
	free(buf);	// free the buffer
	return m;	//return the map pointer;
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
