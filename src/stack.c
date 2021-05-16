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
	s->count--;
	return s->array[s->count];
}

node speek(stack* s){
	return s->array[s->count-1];
}

void spush(stack* s, node n){
	s->array[s->count] = n;
	s->count++;
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
