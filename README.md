# Recursive-Descent-Parser
Recursive descent parser for the following language:

<program> ::=	 program <block> .
<block> ::=	 begin <stmtlist> end
<stmtlist> ::= 	<stmt> <morestmts>
<morestmts> ::=	 ; <stmtlist
<stmt> ::=	<assign>  |  <ifstmt>  |  <whilestmt>  |  <block>
<assign> ::=	<variable> = <expr>
<ifstmt> ::=	if <testexpr> then <stmt> else <stmt>
<whilestmt> ::= 	while <testexpr> do <stmt>
<testexpr> ::=	<variable> <= <expr>
<expr> ::=	+ <expr> <expr>  |  ∗ <expr> <expr>  |  <variable>  |  <digit>
<variable> :: = 	a | b | c
<digit> :: = 	0 | 1 | 2
