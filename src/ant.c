
/* Stack functions */

node* pop(stack* s){
	if(s->count > 0){
		node* ptr = s->top;
		s->top = ptr->nextNode;
		s->count--;
		return ptr;
	}
	return NULL;
}

node* peek(stack* s){
	return s->top;
}

void push(node* n){
	n->nextNode = s->top;
	s->top = n;
	s->count++;
}

void clear(stack* s){
	while(s->count > 0){
		node* n = pop(s);
		free(n);
	}
}
int empty(stack* s){
	return s->count == 0;
}
int full(stack* s){
	return s->count >= s->maxSize;
}

/* Ant specific functions */
