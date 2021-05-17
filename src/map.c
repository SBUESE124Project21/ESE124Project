#include "map.h"
#include "config.h"
#include <stdlib.h>
#include <stdio.h>
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


node getStartPosition(map* m){
	int x = 0;
	int y = 0;
	
	node a;
	a.x = -1;
	a.y = -1;
	for(y = 0; y < m->height; y++){
		for(x = 0; x < m->width; x++){
			if((x == 0 || x == m->width - 1) || (y==0 || y ==m->height-1)){
				if(getMapData(m, x, y) == TILE_SPACE){
					a.x = x;
					a.y = y;
					return a;
				}
			}	
		}
	}
	return a;
}
void printMap(map* m, FILE* outputFile){
	int x = 0;
	int y = 0;
	
	for(y = 0; y < m->height; y++){
		for(x = 0; x < m->width; x++){
			fprintf(outputFile, "%c", (char)getMapData(m, x, y));
		}
		fprintf(outputFile, "\n");
	}
}
void printMapWithAnt(map* m, int x, int y, FILE* outputFile){
	int ix = 0;
	int iy = 0;
	int oldchar = getMapData(m, x,y);
	setMapData(m, x, y, (int)'a');
	for(iy = 0; iy < m->height; iy++){
		for(ix = 0; ix < m->width; ix++){
			fprintf(outputFile, "%c", (char)getMapData(m, ix, iy));
		}
		fprintf(outputFile,"\n");
	}
	setMapData(m, x, y, oldchar);
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
	if(x >= 0 && y >= 0 && x < m->width && y < m->height){
		return m->data[x][y];
	}
	return TILE_OUTSIDE;
}
int setMapData(map* m, int x, int y, int value){
	if(x >= 0 && y >= 0 && x < m->width && y < m->height){
		m->data[x][y] = value;
		return 1;
	}
	return 0;
}
