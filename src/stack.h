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

node* pop(stack* s);
node* peek(stack* s);
void push(node* n);
void clear(stack* s);
int empty(stack* s);
int full(stack* s);

