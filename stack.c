/*
* stack.c
*/

#include "stack.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>


stack *push(stack *top, int value) {
	stack *new_top;


	new_top = malloc(sizeof(*new_top));


	if (new_top == NULL) {
		exit(1);
	}


	new_top->value = value;
	new_top->next = top;

	return new_top;

}


stack *pop(stack *top) {

	stack *new_top;

	if (top == NULL) {
		printf("shouldn't be popping");
		return new_top;
	}

	new_top = top->next;
	top->next = NULL;
	free(top);


	return new_top;
}

void freeAll(stack *top) {

	while(top){
		top = pop(top);
	}

}

/*
//intialize a stack
void init_stack (stack *s)
{
	s->first = NULL;
}

void push (stack *s, int val) {
	stack_elt *elt;
	// allocate a new list element with malloc
	elt = malloc(sizeof(*elt));

	if (elt == NULL) {
		//TODO
		//need to free all memory manually prior
		exit(1);
	}

	elt->value = val; 
	elt->next = s->first;
	s->first = elt;

}



int pop (stack *s) { 
	stack_elt *elt;
	int v; 
	if (s->first) {
		elt = s->first;
		// if pop only element on the stack
		s->first = elt->next;
		v = elt->value;
		free(elt);
		return v;
	}
	else {
		return 0;
	}

		 


}

int peek (stack *s) {
	if (s->first) {
		return (s->first)->value; 
	}

	else {
		return 0; 
	}
}



void print_stack (stack *s) {
	int value;
	stack_elt *elt;
	while (s->first) {
		elt = s->first;
		value = elt->value;
		printf("%d\n", value);
		s->first = elt->next; 
	}

}

void free_all (stack *s) {
	stack_elt *elt;
	while (s->first) {
		elt = s->first;
		s->first = elt->next;
		free(elt);

	}
}
*/

/*
int main() {
	int v;
	int v1;
	stack *stack_ptr;
	stack_ptr = malloc(sizeof(*stack_ptr));
	push(stack_ptr, 3);
	push(stack_ptr, 4);
	v = pop(stack_ptr);
	v1 = peek(stack_ptr);
	printf("%d\n", v1);

}

*/
 
