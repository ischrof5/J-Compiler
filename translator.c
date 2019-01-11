//parser.c

#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include "stack.h"
#include "token.h"



//parser is going to be the file that print to the output file

//rename
//whatever the input j file is named, the output should be jfile.asm




int cmp_label_nums = 0;
char subroutine[250];


int if_number;
int top_if_num;
int afterDefunLabel;
stack *top_stack;



void translate (FILE *output_file, token *theToken, stack *a_stack, char *fileName) {

	
	//somehow need to fetch this using read token and and some struct in memory
	//need to malloc two tokens, one for tehe operator and one of the for the next value in cases of IF and DEFUN statements
	/*
	token curr_token;
	token *curr_token_ptr;
	curr_token_ptr = malloc(sizeof(curr_token));
	token next_token;
	token *next_token_ptr;
	next_token_ptr = malloc(sizeof(next_token));
	*/
	char *if_num_string[50];
	//read_token(curr_token_ptr, theFile);
	int lower_value;
	int upper_value;
	
	int arg_shift;
	int value;

	//token curr_token = *theToken;

	//TODO remember to free all of these
	switch (theToken->type) {

		//this takes the top two elements and stores them into R0 and R1 respectively
		
		//arg n fetches an argument N spots below the return value
		//DEFUN should be reading tokens until the end of the function

		case IF:
			if_number++;
			top_stack = push(top_stack, if_number);
			printf("%d", top_stack->value);
			//sprintf(if_num_string, "%d", top_stack->if_count);
			fprintf(output_file, "\tLDR R0 R6 #0\n");
			fprintf(output_file, "\tADD R6 R6 #1\n");
			fprintf(output_file, "\tCMPI R0 #0\n");
			fprintf(output_file, "\tBRnz LABEL_%d%s\n\n", top_stack->value, fileName);
			break;


		case ELSE:
			//get the top most number off of the stack to match with precding IF statement
			value = top_stack->value;
			top_stack = pop(top_stack);
			if_number++;
			top_stack = push(top_stack, if_number);
			fprintf(output_file, "\tBRnzp LABEL_%d%s\n", if_number, fileName);
			fprintf(output_file, "LABEL_%d%s\n\n", value, fileName);
			break;

		case ENDIF:
			value = top_stack->value;
			top_stack = pop(top_stack);
			//drop the stack by one

			fprintf(output_file, "LABEL_%d%s\n", value, fileName);
			break;


		/* :

			printf("Handling an if statement");
			read_token(next_token);
			while (next_token.type != )
			switch (next_token.type) {

				case LITERAL:
					printf("Literal value %d\n", next_token.value);


					if (next_token.value <= 0x00FF) {
						fprintf(output_file, "\tCONST R0 #%d\n", next_token.value);

					}

					else {
						(lower_value = next_token.value & 0x00FF)
						fprintf(output_file, "\tCONST R0 #%d\n", lower_value);
						fprintf(output_file, "\tHICONST R0 #%d\n", next_token.value >> 8);
						
					}

					fprintf(output_file, "\tADD R6 R6 #-1\n\n");
					fprintf(output_file, "\tSTR RO R6 #0\n");

				}

				case IDENT: 

					printf()





				}
				*/
		case ARG :
			arg_shift = (theToken->arg_no) + 2;
			//printf("%d", arg_shift);
			fprintf(output_file, "\tLDR R3 R5 #%d\n", arg_shift);
			fprintf(output_file, "\tSTR R3 R6 #-1\n");
			fprintf(output_file, "\tADD R6 R6 #-1\n");
			break;


		case DEFUN:
			//printf("defun translated");
			//defun
			afterDefunLabel = 1;
			break;
			

		//calling a function
		case IDENT:
			//function definition
			if (afterDefunLabel == 1) {
				fprintf(output_file, "\t.CODE\n");
				fprintf(output_file, "\t.FALIGN\n");
				fprintf(output_file, "%s", theToken->str);
				fprintf(output_file, "\n");
				fprintf(output_file, "\tADD R6 R6 #-3\n");
				fprintf(output_file, "\tSTR R7 R6 #1\n");
				fprintf(output_file, "\tSTR R5 R6 #0\n");
				fprintf(output_file, "\tADD R5 R6 #0\n");
				//TODO understand the purpose of this
				//TODO nned to allocate a spot
				strcpy(subroutine, theToken->str);
				afterDefunLabel = 0;

			}

			else {
				//if the function is called just JSR to the function's label, leave space betweeen the JSR and the label
				fprintf(output_file, "\t JSR " );
				fprintf(output_file, "%s", theToken->str);
				fprintf(output_file, "\n");
				//add antoher spot on the stack
				//fprintf(output_file, "\tADD R6 R6 #-1\n");
			}
			break;

		case RETURN:
			//set the return value to the value at the top of the stack
			fprintf(output_file, "\tLDR R7 R6 #0\n");
			//set the return value address to 2 spots below the the Frame Pointer
			fprintf(output_file, "\tSTR R7 R5 #2\n");
			fprintf(output_file, "\tADD R6 R5 #0\n");
			fprintf(output_file, "\tADD R3 R5 #2\n");
			fprintf(output_file, "\tLDR R5 R6 #0\n");
			fprintf(output_file, "\tLDR R7 R6 #1\n");
			fprintf(output_file, "\tADD R6 R3 #0\n");
			//fpritnf(output_file, "\tADD R6 R6 #3");

			//jump back to where you originally 
			fprintf(output_file, "\tJMPR R7\n");
			break;
		

		case LITERAL:

			if ((-255 <= theToken->literal_value) && (theToken->literal_value  <= 0x00FF)) {
					fprintf(output_file, "\tCONST R0 #%d\n", theToken->literal_value);

			}

			else {
				lower_value = (theToken->literal_value & 0x00FF);
				fprintf(output_file, "\tCONST R0 #%d\n", lower_value);
				upper_value = (theToken->literal_value >> 8) & 0x00FF; 
				fprintf(output_file, "\tHICONST R0 #%d\n", upper_value);
						
			}

			fprintf(output_file, "\tADD R6 R6 #-1\n");
			fprintf(output_file, "\tSTR R0 R6 #0\n");
			break;

		case DROP:
			//move down the stack by one
			fprintf(output_file, "\tADD R6 R6 #1\n");
			break;

		case DUP:
			fprintf(output_file, "\tLDR R0 R6 #0\n");
			//STACK GROWS BY 1
			fprintf(output_file, "\tADD R6 R6 #-1\n");
			fprintf(output_file, "\tSTR R0 R6 #0\n");
			break;

		case SWAP:
			fprintf(output_file, "\tLDR R0 R6 #0\n");
			//move odwn the stack
			fprintf(output_file, "\tADD R6 R6 #1\n");
			fprintf(output_file, "\tLDR R1 R6 #0\n");
			fprintf(output_file, "\tSTR R0 R6 #0\n");
			fprintf(output_file, "\tADD R6 R6 #-1\n");
			fprintf(output_file, "\tSTR R1 R6 #0\n");
			//fprintf(output_file, "\tADD R6 R6 #-1\n");
			break;


		case ROT:
			fprintf(output_file, "\tLDR R0 R6 #0\n");
			//move odwn the stack
			fprintf(output_file, "\tADD R6 R6 #1\n");
			fprintf(output_file, "\tLDR R1 R6 #0\n");
			fprintf(output_file, "\tADD R6 R6 #1\n");
			fprintf(output_file, "\tLDR R2 R6 #0\n");
			fprintf(output_file, "\tSTR R1 R6 #0\n");
			fprintf(output_file, "\tADD R6 R6 #-1\n");
			fprintf(output_file, "\tSTR R0 R6 #0\n");
			fprintf(output_file, "\tADD R6 R6 #-1\n");
			fprintf(output_file, "\tSTR R2 R6 #0\n");
			//fprintf(output_file, "\tADD R6 R6 #-1\n");
			break;

	

		case AND:
			fprintf(output_file, "\tLDR R0 R6 #0\n");
			//move odwn the stack
			fprintf(output_file, "\tADD R6 R6 #1\n");
			fprintf(output_file, "\tLDR R1 R6 #0\n");
			fprintf(output_file, "\tAND R1 R0 R1\n");
			fprintf(output_file, "\tSTR R1 R6 #0\n");
		//	fprintf(output_file, "\tADD R6 R6 #-1\n");
			break;
		
		case OR:
			fprintf(output_file, "\tLDR R0 R6 #0\n");
			//move odwn the stack
			fprintf(output_file, "\tADD R6 R6 #1\n");
			fprintf(output_file, "\tLDR R1 R6 #0\n");
			fprintf(output_file, "\tOR R1 R0 R1\n");
			fprintf(output_file, "\tSTR R1 R6 #0\n");
			//fprintf(output_file, "\tADD R6 R6 #-1\n");
			break;

		case NOT:
			fprintf(output_file, "\tLDR R0 R6 #0\n");
			//move odwn the stack
			fprintf(output_file, "\tADD R6 R6 #1\n");
			//fprintf(output_file, "\tLDR R1 R6 #0\n");
			//fprintf(output_file, "\tADD R6 R6 #1\n");
			fprintf(output_file, "\tNOT R1 R0\n");
			fprintf(output_file, "\tSTR R1 R6 #0\n");
			//fprintf(output_file, "\tADD R6 R6 #-1\n");
			break;

		case PLUS:
			fprintf(output_file, "\tLDR R0 R6 #0\n");
			//move odwn the stack
			fprintf(output_file, "\tADD R6 R6 #1\n");
			fprintf(output_file, "\tLDR R1 R6, #0\n");
			fprintf(output_file, "\tADD R1 R0 R1\n");
			//store the value at the top of the stack
			fprintf(output_file, "\tSTR R1 R6 #0\n");
			//fprintf(output_file, "\tADD R6 R6 #-1\n");

			break;

		case MINUS:
			fprintf(output_file, "\tLDR R0 R6 #0\n");
			//move odwn the stack
			fprintf(output_file, "\tADD R6 R6 #1\n");
			fprintf(output_file, "\tLDR R1 R6 #0\n");
			fprintf(output_file, "\tSUB R1 R0 R1\n");
			fprintf(output_file, "\tSTR R1 R6 #0\n");
			//fprintf(output_file, "\tADD R6 R6 #-1\n");

			break;

		case MUL:
			fprintf(output_file, "\tLDR R0 R6 #0\n");
			//move odwn the stack
			fprintf(output_file, "\tADD R6 R6 #1\n");
			fprintf(output_file, "\tLDR R1 R6 #0\n");
			fprintf(output_file, "\tMUL R1 R0 R1\n");
			fprintf(output_file, "\tSTR R1 R6 #0\n");
			//fprintf(output_file, "\tADD R6 R6 #-1\n");

			break;


		case DIV:
			fprintf(output_file, "\tLDR R0 R6 #0\n");
			//move odwn the stack
			fprintf(output_file, "\tADD R6 R6 #1\n");
			fprintf(output_file, "\tLDR R1 R6 #0\n");
			fprintf(output_file, "\tDIV R1 R0 R1\n");
			fprintf(output_file, "\tSTR R1 R6 #0\n");
			//fprintf(output_file, "\tADD R6 R6 #-1\n");

			break;


		case MOD:
			fprintf(output_file, "\tLDR R0 R6 #0\n");
			//move odwn the stack
			fprintf(output_file, "\tADD R6 R6 #1\n");
			fprintf(output_file, "\tLDR R1 R6 #0\n");
			fprintf(output_file, "\tMOD R1 R0 R1\n");
			fprintf(output_file, "\tSTR R1 R6 #0\n");
			//fprintf(output_file, "\tADD R6 R6 #-1\n");

			break;


		case EQ:
			fprintf(output_file, "\tLDR R0 R6 #0\n");
			//move odwn the stack
			fprintf(output_file, "\tADD R6 R6 #1\n");
			fprintf(output_file, "\tLDR R1 R6 #0\n");
			fprintf(output_file, "\tCMP R0 R1\n");
			//label the true and false branch by number 
			fprintf(output_file , "\tBRz TRUE%d%s\n", cmp_label_nums, fileName);
			fprintf(output_file, "\tCONST R4 #0\n");
			//if it does not execute the true branch that means value to be stored on stack is 0
			fprintf(output_file, "\tBRnzp FALSE%d%s\n", cmp_label_nums, fileName);
			fprintf(output_file, ".FALIGN\n");
			fprintf(output_file, "TRUE%d%s\n", cmp_label_nums, fileName);
			//if true then stack stores non-zero number 1
			fprintf(output_file, "\tCONST R4 #1\n");

			//TODO check if we acutally have to .FALIGN
			fprintf(output_file, ".FALIGN\n");
			fprintf(output_file, "FALSE%d%s\n", cmp_label_nums, fileName);
			//store the resultant branch value on the top of the stack
			fprintf(output_file, "\tSTR R4 R6 #-1\n");
			fprintf(output_file, "\tADD R6 R6 #-1\n");
			++cmp_label_nums;
			break;


		case LT:
			fprintf(output_file, "\tLDR R0 R6 #0\n");
			//move odwn the stack
			fprintf(output_file, "\tADD R6 R6 #1\n");
			fprintf(output_file, "\tLDR R1 R6 #0\n");
			fprintf(output_file, "\tCMP R0 R1\n");
			//label the true and false branch by number 
			fprintf(output_file , "\tBRn TRUE%d%s\n", cmp_label_nums, fileName);
			fprintf(output_file, "\tCONST R4 #0\n");
			//if it does not execute the true branch that means value to be stored on stack is 0
			fprintf(output_file, "\tBRnzp FALSE%d%s\n", cmp_label_nums, fileName);
			fprintf(output_file, ".FALIGN\n");
			fprintf(output_file, "TRUE%d%s\n", cmp_label_nums, fileName);
			//if true then stack stores non-zero number 1
			fprintf(output_file, "\tCONST R4 #1\n");

			//TODO check if we acutally have to .FALIGN
			fprintf(output_file, ".FALIGN\n");
			fprintf(output_file, "FALSE%d%s\n", cmp_label_nums, fileName);
			//store the resultant branch value on the top of the stack
			fprintf(output_file, "\tSTR R4 R6 #-1\n");
			fprintf(output_file, "\tADD R6 R6 #-1\n");
			++cmp_label_nums;
			break;

		case GT:
			fprintf(output_file, "\tLDR R0 R6 #0\n");
			//move odwn the stack
			fprintf(output_file, "\tADD R6 R6 #1\n");
			fprintf(output_file, "\tLDR R1 R6 #0\n");
			fprintf(output_file, "\tCMP R0 R1\n");
			//label the true and false branch by number 
			fprintf(output_file , "\tBRp TRUE%d%s\n", cmp_label_nums, fileName);
			fprintf(output_file, "\tCONST R4 #0\n");
			//if it does not execute the true branch that means value to be stored on stack is 0
			fprintf(output_file, "\tBRnzp FALSE%d%s\n", cmp_label_nums, fileName);
			fprintf(output_file, ".FALIGN\n");
			fprintf(output_file, "TRUE%d%s\n", cmp_label_nums, fileName);
			//if true then stack stores non-zero number 1
			fprintf(output_file, "\tCONST R4 #1\n");

			//TODO check if we acutally have to .FALIGN
			fprintf(output_file, ".FALIGN\n");
			fprintf(output_file, "FALSE%d%s\n", cmp_label_nums, fileName);
			//store the resultant branch value on the top of the stack
			fprintf(output_file, "\tSTR R4 R6 #-1\n");
			fprintf(output_file, "\tADD R6 R6 #-1\n");
			++cmp_label_nums;
			break;


		case LE:
			fprintf(output_file, "\tLDR R0 R6 #0\n");
			//move odwn the stack
			fprintf(output_file, "\tADD R6 R6 #1\n");
			fprintf(output_file, "\tLDR R1 R6 #0\n");
			fprintf(output_file, "\tCMP R0 R1\n");
			//label the true and false branch by number 
			fprintf(output_file , "\tBRnz TRUE%d%s\n", cmp_label_nums, fileName);
			fprintf(output_file, "\tCONST R4 #0\n");
			//if it does not execute the true branch that means value to be stored on stack is 0
			fprintf(output_file, "\tBRnzp FALSE%d%s\n", cmp_label_nums, fileName);
			fprintf(output_file, ".FALIGN\n");
			fprintf(output_file, "TRUE%d%s\n", cmp_label_nums, fileName);
			//if true then stack stores non-zero number 1
			fprintf(output_file, "\tCONST R4 #1\n");

			//TODO check if we acutally have to .FALIGN
			fprintf(output_file, ".FALIGN\n");
			fprintf(output_file, "FALSE%d%s\n", cmp_label_nums, fileName);
			//store the resultant branch value on the top of the stack
			fprintf(output_file, "\tSTR R4 R6 #-1\n");
			fprintf(output_file, "\tADD R6 R6 #-1\n");
			++cmp_label_nums;
			break;

		case GE:
			fprintf(output_file, "\tLDR R0 R6 #0\n");
			//move odwn the stack
			fprintf(output_file, "\tADD R6 R6 #1\n");
			fprintf(output_file, "\tLDR R1 R6 #0\n");
			fprintf(output_file, "\tCMP R0 R1\n");
			//label the true and false branch by number 
			fprintf(output_file , "\tBRzp TRUE%d%s\n", cmp_label_nums, fileName);
			fprintf(output_file, "\tCONST R4 #0\n");
			//if it does not execute the true branch that means value to be stored on stack is 0
			fprintf(output_file, "\tBRnzp FALSE%d%s\n", cmp_label_nums, fileName);
			fprintf(output_file, ".FALIGN\n");
			fprintf(output_file, "TRUE%d%s\n", cmp_label_nums, fileName);
			//if true then stack stores non-zero number 1
			fprintf(output_file, "\tCONST R4 #1\n");

			//TODO check if we acutally have to .FALIGN
			fprintf(output_file, ".FALIGN\n");
			fprintf(output_file, "FALSE%d%s\n", cmp_label_nums, fileName);
			//store the resultant branch value on the top of the stack
			fprintf(output_file, "\tSTR R4 R6 #-1\n");
			fprintf(output_file, "\tADD R6 R6 #-1\n");
			++cmp_label_nums;
			break;

		case BROKEN_TOKEN:
			break;


	}


}