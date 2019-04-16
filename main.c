#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "parser.h"

int main(int argc, char *argv[])
{
    // Load that hoe into memory
    long lSize;
    char *in;
    FILE *fp = stdin;
    fseek(fp, 0L, SEEK_END);
    lSize = ftell(fp);
    rewind(fp);
    // allocate memory for entire content
    in = calloc(1, lSize + 1);
    if (!in) fclose(fp), fputs("memory alloc fails\n", stderr), exit(1);
    // copy the file into the in
    if (1 != fread(in, lSize, 1, fp)) fclose(fp), free(in), fputs("entire read fails\n", stderr), exit(1);
    fclose(fp);

    size_t num_tokens;

    char **token_list = gettokens(in, &num_tokens);
    program(token_list, num_tokens);

    free(token_list);

    return EXIT_SUCCESS;
}


