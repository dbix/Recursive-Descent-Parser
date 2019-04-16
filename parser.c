#include "parser.h"


/*
 * global variables
 */

static size_t numtokens;
static int currtoken;
static char **tokens;
static int assignments;
static int varrefs;

/*
 * utility functions
 */

// checks if we are out of tokens
// returns 1 if we are out, 0 if we have more
int eof()
{
    int e = 1;

    if (currtoken < numtokens) {
        e = 0;
    }

    return e;
}

// called to check terminals
// returns 1 if they match, or 0 if they don't
int match(char *terminal)
{
    int m = 0;

    if (eof()) {
        eoferror();
    } else if (strcmp(tokens[currtoken], terminal) == 0) {
        m = 1;
        printf("%s\n", terminal);
    } else {
        return 0;
    }
    
    return m;
}


/*
 * rules
 */

// entry point
// <program> ::= program <block>
void program(char **token_list, size_t num_tokens)
{
    printf("<program>\n");

    tokens = token_list;
    numtokens = num_tokens;
    currtoken = 0;
    assignments = 0;
    varrefs = 0;

    if (match("program")) {
        currtoken++;
        block(); // parse <block>
    } else {
        terminalerror("program", tokens[currtoken]);
    }

    if (match(".")) {
        currtoken++;
        if (currtoken < numtokens) {
            printf("ERROR: encountered \".\" before end of file\n");
            exit(1);
        }
    } else {
        terminalerror(".", tokens[currtoken]);
    }

    printf("\n\nCode is correct\n");
    printf("\n\nassignments: %d\nvariable references: %d\n", assignments, varrefs);
}

// <block> ::= begin <stmtlist> end
void block()
{
    printf("<block>\n");

    // parse begin
    if (match("begin")) {
        currtoken++;
    } else {
        terminalerror("begin", tokens[currtoken]);
    }

    // parse <stmtlist>
    stmtlist();

    // parse end
    if (match("end")) {
        currtoken++;
        printf("end\n");
    } else if (match("end.")) {
        printf("end\n");
        tokens[currtoken][0] = '.';
        tokens[currtoken][1] = '\0';
    }  else if (match("end;")) {
        printf("end\n");
        tokens[currtoken][0] = ';';
        tokens[currtoken][1] = '\0';
    } else {
        terminalerror("end", tokens[currtoken]);
    }
        
    // reached end of <block>
    return;
}

// <stmtlist> ::= <stmt> <morestmts>
void stmtlist()
{
    printf("<stmtlist>\n");

    // parse <stmt>
    stmt();

    // parse <morestmts>
    morestmts();
    
    // reached end of <stmtlist>
    return;
}

// <morestmts> ::= ; <stmtlist> | epsilon
void morestmts()
{
    printf("<morestmts>\n");

    // parse ';'
    if (match(";")) {
        currtoken++;
        // parse <stmtlist>
        stmtlist();
    } else {
        // epsilon
    }
}

// <stmt> ::= <assign> | <ifstmt> | <whilestmt> | <block>
void stmt()
{
    printf("<stmt>\n");

    if (match("begin")) {
        // parse <block>
        block();
    } else if (match("if")) {
        // parse <ifstmt>
        ifstmt();
    } else if (match("while")) {
        // parse <whilestmt>
        whilestmt();
    } else {
        // parse <assign>
        assign();
    }
}

// <assign> ::= <variable> = <expr>
void assign()
{
    printf("<assign>\n");

    // parse <variable>
    variable();

    // parse '='
    if (match("=")) {
        currtoken++;
    } else {
        terminalerror("=", tokens[currtoken]);
    }

    // parse <expr>
    expr();

    assignments++;
}

// <ifstmt> ::= if <testexpr> then <stmt> else <stmt>
void ifstmt()
{
    printf("<ifstmt>\n");

    // parse 'if'
    if (match("if")) {
        currtoken++;
    } else {
        terminalerror("if", tokens[currtoken]);
    }

    // parse <testexpr>
    testexpr();

    // parse "then"
    if (match("then")) {
        currtoken++;
    } else {
        terminalerror("then", tokens[currtoken]);
    }

    // parse <stmt>
    stmt();

    // parse "else"
    if (match("else")) {
        currtoken++;
    } else {
        terminalerror("else", tokens[currtoken]);
    }

    // parse <stmt>
    stmt();
}

// <whilestmt> ::= while <testexpr> do <stmt>
void whilestmt()
{
    printf("<whilestmt>\n");

    // parse "while"
    if (match("while")) {
        currtoken++;
    } else {
        terminalerror("while", tokens[currtoken]);
    }

    // parse <testexpr>
    testexpr();

    // parse "do"
    if (match("do")) {
        currtoken++;
    } else {
        terminalerror("do", tokens[currtoken]);
    }

    // parse <stmt>
    stmt();
}

// <testexpr> ::= <variable> <= <expr>
void testexpr()
{
    printf("<testexpr>\n");

    // parse <variable>
    variable();

    // parse "<="
    if (match("<=")) {
        currtoken++;
    } else {
        terminalerror("<=", tokens[currtoken]);
    }

    // parse <expr>
    expr();
}

// <expr> ::= + <expr> <expr> | * <expr> <expr> | <variable> | <digit>
void expr()
{
    printf("<expr>\n");

    if (match("+") || match("*")) {
        printf("%s\n", tokens[currtoken]);
        currtoken++;
        expr();
        expr();
    } else if (match("a")  || match("b")  || match("c") || 
               match("a;") || match("b;") || match("c;")) {
        variable();
    } else if (match("0")  || match("1")  || match("2") ||
               match("0;") || match("1;") || match("2;")) {
        digit();
    }
}

// <variable> ::= a | b | c
void variable()
{
    printf("<variable> ");

    // parse terminals 'a' | 'b' | 'c'
    if (match("a") || match("b") || match("c")) {
        printf("%s\n", tokens[currtoken]);
        currtoken++;
    } else if (match("a;") || match("b;") || match("c;")) {
        printf("%c\n", tokens[currtoken][0]);
        tokens[currtoken][0] = ';';
        tokens[currtoken][1] = '\0';
    } else {
        terminalerror("a | b | c", tokens[currtoken]);
    }

    varrefs++;
}

// <digit> ::= 0 | 1 | 2
void digit()
{
    printf("<digit> ");

    // parse terminals '0' | '1' | '2'
    if (match("0") || match("1") || match("2")) {
        printf("%s\n", tokens[currtoken]);
        currtoken++;
    } else if (match("0;") || match("1;") || match("2;")) {
        printf("%c\n", tokens[currtoken][0]);
        tokens[currtoken][0] = ';';
        tokens[currtoken][1] = '\0';
    } else {
        terminalerror("0 | 1 | 2", tokens[currtoken]);
    }
}

/*
 * error functions
 */

// called when eof is reached unexpectedly
// prints error message and terminates parsing
void eoferror()
{
    printf("\n\nOwO\n\tERROR: reached end of file unexpectedly\nUwU");
}

// called when there is a syntax error
// prints error message and terminates parsing
void syntaxerror(char *msg)
{
    printf("\n\nOwO\n\tSYNTAX ERROR: %s\n\nUwU", msg);
    exit(1);
}

// called when an expected terminal is not found
// prints error message and terminates parsing
void programerror()
{
    printf("\n\nUwU\n\tERROR: file must start with \"program\"\nOwO\n");
}

// called when there is not even a resemblence of a runnable program
// prints error message and terminates parsing
void terminalerror(char *expected, char *actual)
{
    printf("\n\nUwU\n\tERROR: expected \"%s\" and got \"%s\" instead\nOwO\n", expected, actual);
    exit(1);
}