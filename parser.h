#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "tokenizer.h"


/*
 * utility functions
 */

// called to check that a terminal matches the current token
// returns 1 if they match, or 0 if they don't
int match(char *terminal);

// checks if we are out of tokens
// returns 1 if we are out, 0 if we have more
int eof();


/*
 * rules
 */

// entry point
// <program> ::= program <block>
void program(char **tokens, size_t numtokens);

// <block> ::= begin <stmtlist> end
void block();

// <stmtlist> ::= <stmt> <morestmts>
void stmtlist();

// <morestmts> ::= ; <stmtlist> | epsilon
void morestmts();

// <stmt> ::= <assign> | <ifstmt> | <whilestmt> | <block>
void stmt();

// <assign> ::= <variable> = <expr>
void assign();

// <ifstmt> ::= if <testexpr> then <stmt> else <stmt>
void ifstmt();

// <whilestmt> ::= while <testexpr> do <stmt>
void whilestmt();

// <testexpr> ::= <variable> <= <expr>
void testexpr();

// <expr> ::= + <expr> <expr> | * <expr> <expr> | <variable> | <digit>
void expr();

// <variable> ::= a | b | c
void variable();

// <digit> ::= 0 | 1 | 2
void digit();


/*
 * error functions
 */

// called when eof is reached unexpectedly
// prints error message and terminates parsing
void eoferror();

// called when there is a syntax error
// prints error message and terminates parsing
void syntaxerror(char *msg);

// called when there is not even a resemblence of a runnable program
// prints error message and terminates parsing
void programerror();

// called when an expected terminal is not found
// prints error message and terminates parsing
void terminalerror(char *expected, char *actual);