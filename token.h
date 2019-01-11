/*
 * token.h
 */

#define MAX_TOKEN_LENGTH 250

#include <stdio.h>

typedef struct {
  enum { DEFUN, IDENT, RETURN, 
         PLUS, MINUS, MUL, DIV, MOD, 
         AND, OR, NOT, 
         LT, LE, EQ, GE, GT,
         IF, ELSE, ENDIF, 
         DROP, DUP, SWAP, ROT,
	 ARG,
         LITERAL,
         BROKEN_TOKEN } type;
  int literal_value;    // this field used to store the value of literal tokens
  int arg_no;           // this field used to store the index of argument literals argN
  char str[MAX_TOKEN_LENGTH];
} token;

// line_number : You can use this to keep track of the current line number which can be useful in reporting syntax errors.
extern int line_number;

int read_token (token *theToken, FILE *theFile);

// Extra functions which you may wish to define and use , or not
const char *token_type_to_string (int type);

void print_token (token *theToken);

int parseWhiteSpace(FILE *f);
int parse_comments(FILE *f);

