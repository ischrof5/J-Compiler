//token_test.c


#include <stdio.h>
#include <stdlib.h>
//#include "token.h"

#include "translator.h"



int main (int argc, char *argv[]) {
	int i = 0;
	FILE *theFile;
	FILE *outFile;
	char *filename = malloc(300 * sizeof(char));
	char *label_filename = malloc(300 * sizeof(char));
	char *outFileName = malloc(300 * sizeof(char)); 
	token *theToken;
	token curr_token;
	
	stack *top_stack;
	top_stack = malloc(sizeof(*top_stack));
	theToken = malloc(sizeof(curr_token));

	if (argc < 2) {
		printf("First argument should be a filename\n");
		exit(1);
	}

	theFile = fopen(argv[1], "r");
	if (!theFile) {
		printf("Problem opening the file\n");
		exit (1);
	}
	strcpy(filename, argv[1]);
	strncpy(outFileName, filename, strlen(filename) - 1);
	strncpy(label_filename, filename, strlen(filename) - 2);
	strcat(outFileName, "asm");
	outFile = fopen(outFileName, "w+");
	

	

	while (read_token(theToken, theFile) == 0) {
		translate (outFile, theToken, top_stack, label_filename);
		printf("\n");
		printf("%s", token_type_to_string(theToken->type));
		//print_token(theToken);
		
		printf("\n\n");
		/*
		curr_token = *theToken;
		switch (curr_token.type) {
			case IDENT:
				printf("IDENT %s", curr_token.str);
				break;


			case LITERAL:
				printf("LITERAL %d", curr_token.literal_value);
				break;

			default:
			printf("%s", token_type_to_string(curr_token.type));
			break;
		}
		printf("\n\n");
		*/
	}

	free(theToken);
	free(filename);
	free(outFileName);
	free(label_filename);
	free(top_stack);
	fclose(theFile);
	fclose(outFile);
}
