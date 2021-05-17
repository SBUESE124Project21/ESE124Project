#include "stack.h"
#include <stdlib.h>

stack* makeStack(int maxSize){
	stack* s = (stack*)calloc(1, sizeof(stack));
	s->array = (node*)calloc(maxSize, sizeof(node));
	s->maxSize = maxSize;
	s->count = 0;
	return s;
}

node spop(stack* s){
	if(s->count > 0){
		s->count--;
		return s->array[s->count];
	}
	else{
		node n;
		return n;
	}
}

node speek(stack* s){	
	if(s->count > 0){
		return s->array[s->count-1];
	}
	else{
		node n;
		return n;
	}
}
int scontains(stack* s, node n){
	int i = 0;
	for(i = 0; i < s->count; i++){
		if(s->array[i].x == n.x && s->array[i].y == n.y){
			return 1;
		}
	}
	return 0;
}
int spush(stack* s, node n){
	if(s->count < s->maxSize){
		s->array[s->count] = n;
		s->count++;
		return 1;
	}	
	return 0;
}

void sclear(stack* s){
	while(s->count > 0){
		pop(s);
	}
}
int sempty(stack* s){
	return s->count == 0;
}
int sfull(stack* s){
	return s->count >= s->maxSize;
}

void freeStack(stack* s){
	free(s->array);
	free(s);
}
