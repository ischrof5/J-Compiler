
// define the stack element data structure
typedef struct stack_elt_tag { 
	int value;
	struct stack_elt_tag *next;
} stack;

stack *push(stack *top, int value);
stack *pop(stack *top);
void freeAll(stack *top);