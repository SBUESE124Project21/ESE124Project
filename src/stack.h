#pragma once
typedef struct node node;
typedef struct stack stack;

struct node {
	int x;
	int y;
};

struct stack{
	node* array;
	int count;
	int maxSize;
};

stack* makeStack(int maxSize);

node spop(stack* s);
node speek(stack* s);
int spush(stack* s, node n);
void sclear(stack* s);
int sempty(stack* s);
int sfull(stack* s);
void freeStack(stack* s);
