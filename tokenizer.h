#include <stdio.h>
#include <string.h>
#include <stdlib.h>


// accept string and pointer to numtokens
// returns string split by whitespace as an array 
// of strings and sets numtokens to the size of 
// the return array
char** gettokens(char *str, size_t *numtokens);