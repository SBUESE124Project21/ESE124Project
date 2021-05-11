stack* makeStack(int maxSize){
	stack* s = (stack*)calloc(1, sizeof(stack));
	s->array = (node*)calloc(maxSize, sizeof(node));
	s->maxSize = maxSize;
	s->count = 0;
}

node pop(stack* s){
	if(s->count > 0){
		s->count--;
		return s->array[s->count];
	}
	return NULL;
}

node peek(stack* s){
	if(s->count > 0){
		return s->array[s->count-1];
	}
	return NULL;
}

void push(node n){
	s->array[s->count] = n;
	s->count++;
}

void clear(stack* s){
	while(s->count > 0){
		pop(s);
	}
}
int empty(stack* s){
	return s->count == 0;
}
int full(stack* s){
	return s->count >= s->maxSize;
}

