typedef struct ant ant;
typedef struct node node;
typedef struct stack stack;

struct node {
	int x;
	int y;
	node* nextNode;
};

struct stack{
	node* top;
	int count;
	int maxSize;
};


struct ant{
	stack* memoryStack;
	int x;
	int y;
	
};

node* pop(stack* s);
node* peek(stack* s);
void push(node* n);
void clear(stack* s);
int empty(stack* s);
int full(stack* s);


