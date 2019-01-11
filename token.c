//token.c

#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "token.h"



int line_number = 0;

char fileLine[MAX_TOKEN_LENGTH];
//this is the pointer to a character on the line
char *line_char = NULL; 


int parse_comments(FILE *f) {
	
	int curr_char;
	curr_char = fgetc(f);
	while(curr_char != EOF && curr_char != '\n') {
		curr_char = fgetc(f);

	}

	curr_char = fgetc(f);
	line_number++;
	return curr_char;
	//return the 
}

int parseWhiteSpace(FILE *f) {

	int curr_char;
	curr_char = fgetc(f);
	while(curr_char != EOF && isspace(curr_char)) {
		curr_char = fgetc(f);
	}
	return curr_char;
} 

//parse the string and save it to the token that is passed in 
int read_token (token *theToken, FILE *theFile) {
	char *discardA;
	char *discardR;
	char *discardG;
	int curr_char;
	int i = 0;
	
	curr_char = fgetc(theFile);
	//printf("%c", curr_char);
	//get to the first character
	while (isspace(curr_char) || curr_char == ';') {
		if (isspace(curr_char)) {
			curr_char = parseWhiteSpace(theFile);
		}
		else if (curr_char == ';') {
			curr_char = parse_comments(theFile);
		}
	}


	//begin parsing the non white space characters 
	while (!isspace(curr_char) && curr_char != EOF) {
		//printf("%c", curr_char);
		theToken->str[i] = curr_char;
		curr_char = fgetc(theFile);
		if(curr_char == EOF) {
			++i;
			theToken->str[i] = '\0';
			break;
		}
		i++;
	}
	//termine the string
	theToken->str[i] = '\0';

	//printf(the_token.str);
	/*



		if ((line_char == NULL) || (*line_char == '\0')) {
			if (fgets (fileLine, MAX_TOKEN_LENGTH, theFile)) {

				//locate the first ; and put in a terminator to the line

				for (i = 0; i < MAX_TOKEN_LENGTH; ++i) {
					if (fileLine[i] == ';') {
						//put this null character in to indicate terminated string in arrary
						fileLine[i] = 0x00;
						break;

					}
				}

				line_char = fileLine; 
				++line_number;
			}

			else {
				// no more tokens to read from the file
				return -1;

			}

		}
		//advance to the next character in the line

		while ((*line_char != '\0') && (isspace(*line_char))) {
			++line_char;
		}

		if (*line_char == '\0') {
			continue;
		}

		//may need to fix the incrementing line char in the for loop
		for (i = 0; i < MAX_TOKEN_LENGTH; ++i, ++line_char) {
			if (isgraph(*line_char)) {
				the_token.str[i] = *line_char;
			}

			else { 

				break;
			}

		}


		//printf(the_token.str);
*/

	if (strcmp(theToken->str, "defun") == 0) {
		printf("defun success");
		theToken->type = DEFUN;
		printf("%s", token_type_to_string(theToken->type));
		return 0;

	}

	if (strcmp(theToken->str, "return") == 0) {
		printf("return success");
		theToken->type = RETURN;
		printf("%s", token_type_to_string(theToken->type));
		
		return 0;

	}

	if (strcmp(theToken->str, "+") == 0) {
		printf("add success");
		theToken->type = PLUS;
		printf("%s", token_type_to_string(theToken->type));
		return 0;

	}

	if (strcmp(theToken->str, "-") == 0) {
		printf("subtract success");
		theToken->type = MINUS;
		printf("%s", token_type_to_string(theToken->type));
		return 0;

	}

	if (strcmp(theToken->str, "*") == 0) {
		printf("multiply success");
		theToken->type = MUL;
		printf("%s", token_type_to_string(theToken->type));
		return 0;

	}

	if (strcmp(theToken->str, "/") == 0) {
		printf("divide success");

		theToken->type = DIV;
		printf("%s", token_type_to_string(theToken->type));
		
		return 0;

	}

	if (strcmp(theToken->str, "%") == 0) {
		printf("mod success");
		theToken->type = MOD;
		printf("%s", token_type_to_string(theToken->type));

		return 0;

	}

	if (strcmp(theToken->str, "gt") == 0) {
		printf("GT success");
		theToken->type = GT;
		printf("%s", token_type_to_string(theToken->type));
		return 0;

	}

	if (strcmp(theToken->str, "lt") == 0) {
		printf("LT success");
		theToken->type = LT;
		return 0;

	}

	if (strcmp(theToken->str, "ge") == 0) {
		printf("GE success");
		theToken->type = GE;
		return 0;

	}



	if (strcmp(theToken->str, "le") == 0) {
		printf("LE success");
		theToken->type = LE;
		return 0;

	}

	if (strcmp(theToken->str, "eq") == 0) {
		printf("equals success");
		theToken->type = EQ;
		return 0;

	}

	if (strcmp(theToken->str, "and") == 0) {
		printf("and success");
		theToken->type = AND;
		return 0;

	}

	if (strcmp(theToken->str, "or") == 0) {
		printf("or success");
		theToken->type = OR;
		return 0;

	}

	if (strcmp(theToken->str, "not") == 0) {
		printf("not success");
		theToken->type = NOT;
		return 0;
	}


	if (strcmp(theToken->str, "if") == 0) {
		printf("if success");
		theToken->type = IF;
		return 0;
	}


	if (strcmp(theToken->str, "else") == 0) {
		printf("else success");
		theToken->type = ELSE;
		return 0;
	}

	if (strcmp(theToken->str, "endif") == 0) {
		printf("endif success");
		theToken->type = ENDIF;
		return 0;
	}

	if (strcmp(theToken->str, "drop") == 0) {
		printf("drop success");
		theToken->type = DROP;
		return 0;
	}

	if (strcmp(theToken->str, "dup") == 0) {
		printf("dup success");
		theToken->type = DUP;
		return 0;
	}

	if (strcmp(theToken->str, "swap") == 0) {
		printf("swap success");
		theToken->type = SWAP;
		return 0;
	}

	if (strcmp(theToken->str, "rot") == 0) {
		printf("rot success");
		theToken->type = ROT;
		return 0;
	}
	//TODO need to think a bit more about this one
	if (theToken->str[0] == 'a' && theToken->str[1] == 'r' && theToken->str[2] == 'g' && isdigit(theToken->str[3])) {
		printf("argN success");
		theToken->type = ARG;
		if((isdigit(theToken->str[3]) && strlen(theToken->str) == 4)) {
			theToken->arg_no = (int) theToken->str[3] - 48;
			printf("%d", theToken->arg_no);
			return 0;

		}

		else if ((strlen(theToken->str) == 5) && (isdigit(theToken->str[3])) && (isdigit(theToken->str[4]))) {
			char digit_number[2] = {theToken->str[3], theToken->str[4]};
			int converted = atoi(digit_number);
			if (converted > 20) {
				printf("argument number too big \n");
				return -2;
			}

			theToken->arg_no = converted;
			printf("%d", theToken->arg_no);

			return 0;
		}

		
		
	}

	//check for literal preceded by the hex '0x'

	if ((theToken->str[0] == '0') && (theToken->str[1] == 'x')) {
		for (i = 2; i < strlen(theToken->str); ++i) {
			if (!isxdigit(theToken->str[i])) {
				theToken->type = BROKEN_TOKEN;
				return -1;
			}
		}

		theToken->type = LITERAL;
		printf("literal success");
		theToken->literal_value = strtol(theToken->str, NULL, 16);
		printf("%d", theToken->literal_value);
		return 0;
	}
	//if the value is a decimal value
	if (isdigit(theToken->str[0]) || (theToken->str[0] == '-')) {
		for (i = 1; i < strlen(theToken->str); ++i) {
			if (!isxdigit(theToken->str[i])) {
				theToken->type = BROKEN_TOKEN;
				return -1;
			}
		}
		printf("digits success");
		theToken->type = LITERAL;
		sscanf(theToken->str, "%d", &(theToken->literal_value));
		return 0;
	}
	
	if (isalpha(theToken->str[0])) {
		/*
		for (int i = 0; i < strlen(theToken->str); i++) {
			if (isalnum(theToken->str[i]) == 0) {
				theToken->type = BROKEN_TOKEN;
				printf("%s", "BROKEN_TOKEN");
				return -1;
			}

		}
		*/
		
		printf("IDENT success");
		theToken->type = IDENT;
		return 0;
		
	}

	else {
		theToken->type = BROKEN_TOKEN;
		return -1;
	}

	//if it doesnt't fit any of the other strings then it is broken
	
}




void print_token (token *theToken) {
	token the_token = *theToken;
	printf("%s", theToken->str);
}

const char *token_type_to_string(int type) {

	if (type == LITERAL) {
		return "LITERAL";
	}

	if (type == IDENT) {
		return "IDENT";
	}

	if (type == DEFUN) {
		return "DEFUN";
	}

	if (type == RETURN) {
		 return "RETURN";
	}

	if (type == PLUS) {
		return "PLUS";
	}

	if (type == MINUS) {
		return "MINUS";
	}

	if (type == MUL) {
		return "MUL";
	}

	if (type == DIV) {
		return "DIV";
	}

	if (type == MOD) {
		return "MOD";
	}

	if (type == AND) {
		return "AND";
	}

	if (type == OR) {
		return "OR";
	}

	if (type == NOT) {
		return "NOT";
	}

	if (type == LT) {
		return "LT";
	}

	if (type == LE) {
		return "LE";
	}

	if (type == EQ) {
		return "EQ";
	}

	if (type == GE) {
		return "GE";
	}

	if (type == GT){
		return "GT";
	}

	if (type == IF) {
		return "IF";
	}

	if (type == ELSE) {
		return "ELSE";
	}

	if (type == ENDIF) {
		return "ENDIF";
	}

	if (type == DROP) {
		return "DROP";
	}

	if (type == DUP) {
		return "DUP";
	}

	if (type == SWAP) {
		return "SWAP";
	}

	if (type == ROT) {
		return "ROT";
	}

	if (type == ARG) {
		return "ARG";
	}

	if (type == BROKEN_TOKEN) {
		return "BROKEN_TOKEN";
	}

	else {
		return "NAME_ERROR";
	}
}





