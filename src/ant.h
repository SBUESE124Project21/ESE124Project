
/* structs */

typedef struct ant ant;
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


struct ant{
	stack* memoryStack;

	int x, y;	// current position
	int mx, my; // memory position
	
	
	int energy; //energy remaining
	
	/*direction itch states*/
	int itchUp;
	int itchDown;
	int itchRight;
	int itchLeft;	
	
	int distance; //distance of last measured itch direction
};

/* Stack related functions */

stack* makeStack(int maxSize);

node* pop(stack* s);
node* peek(stack* s);
void push(node* n);
void clear(stack* s);
int empty(stack* s);
int full(stack* s);

/* Ant specific functions */

void mark(ant* a);
void move_f(ant* a);	//right
void move_b(ant* a);	//left
void move_l(ant* a);	//up
void move_r(ant* a);	//down

int cwf(ant* a);
int cwb(ant* a);
int cwl(ant* a);	
int cwr(ant* a);

int bjpi(ant* a);
int cjpi(ant* a);

void backtrack(ant* a, int x, int y);

