//translator.h

#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>

#include "token.h"
#include "stack.h"

void translate (FILE *theFile, token *theToken, stack *stack, char *filename);