%{
#include "C_Parser_Types.h"
#include "main.h"
%}

%option yylineno

COMMENTSINGLE "//"
COMMENTMULTI "/*"

INTOCT [+-]?0[0-7]+
INTHEX [+-]?0[xX][0-9a-fA-F]+
INTDEC [+-]?(0|[1-9][0-9]*)
INT {INTDEC}|{INTOCT}|{INTHEX}
FLOAT [+-]?([0-9]*\.[0-9]+|[0-9]+\.[0-9]*)([eE][+-]?[0-9]+)?
ID [a-zA-Z_][a-zA-Z0-9_]*
SEMI ;
COMMA ,
ASSIGNOP =
RELOP ==|!=|<=|<|>=|>
PLUS \+
MINUS \-
STAR \*
DIV \/
AND &&
OR \|\|
DOT \.
NOT !
TYPE int|float
LP \(
RP \)
LB \[
RB \]
LC \{
RC \}
STRUCT struct
RETURN return
IF if
ELSE else
WHILE while

SPACE [ \t\n\r]+

ERROR .

%%
{COMMENTSINGLE} { while (input() != '\n'); }
{COMMENTMULTI} {
    int c;
    while ((c = input()) != EOF) {
        if (c == '*') {
            if ((c = input()) == '/') {
                break;
            }
            else {
                unput(c);
            }
        }
    }
}

{INT} { yylval.nodeIndex = newParserNode(INT, yylineno, 0, NULL, INVALID_NODE_INDEX); return INT; }
{FLOAT} { yylval.nodeIndex = newParserNode(FLOAT, yylineno, 0, NULL, INVALID_NODE_INDEX); return FLOAT; }

{SEMI} { yylval.nodeIndex = newParserNode(SEMI, yylineno, 0, NULL, INVALID_NODE_INDEX); return SEMI; }
{COMMA} { yylval.nodeIndex = newParserNode(COMMA, yylineno, 0, NULL, INVALID_NODE_INDEX); return COMMA; }
{ASSIGNOP} { yylval.nodeIndex = newParserNode(ASSIGNOP, yylineno, 0, NULL, INVALID_NODE_INDEX); return ASSIGNOP; }
{RELOP} { yylval.nodeIndex = newParserNode(RELOP, yylineno, 0, NULL, INVALID_NODE_INDEX); return RELOP; }
{PLUS} { yylval.nodeIndex = newParserNode(PLUS, yylineno, 0, NULL, INVALID_NODE_INDEX); return PLUS; }
{MINUS} { yylval.nodeIndex = newParserNode(MINUS, yylineno, 0, NULL, INVALID_NODE_INDEX); return MINUS; }
{STAR} { yylval.nodeIndex = newParserNode(STAR, yylineno, 0, NULL, INVALID_NODE_INDEX); return STAR; }
{DIV} { yylval.nodeIndex = newParserNode(DIV, yylineno, 0, NULL, INVALID_NODE_INDEX); return DIV; }
{AND} { yylval.nodeIndex = newParserNode(AND, yylineno, 0, NULL, INVALID_NODE_INDEX); return AND; }
{OR} { yylval.nodeIndex = newParserNode(OR, yylineno, 0, NULL, INVALID_NODE_INDEX); return OR; }
{DOT} { yylval.nodeIndex = newParserNode(DOT, yylineno, 0, NULL, INVALID_NODE_INDEX); return DOT; }
{NOT} { yylval.nodeIndex = newParserNode(NOT, yylineno, 0, NULL, INVALID_NODE_INDEX); return NOT; }
{TYPE} { yylval.nodeIndex = newParserNode(TYPE, yylineno, 0, NULL, INVALID_NODE_INDEX); return TYPE; }
{LP} { yylval.nodeIndex = newParserNode(LP, yylineno, 0, NULL, INVALID_NODE_INDEX); return LP; }
{RP} { yylval.nodeIndex = newParserNode(RP, yylineno, 0, NULL, INVALID_NODE_INDEX); return RP; }
{LB} { yylval.nodeIndex = newParserNode(LB, yylineno, 0, NULL, INVALID_NODE_INDEX); return LB; }
{RB} { yylval.nodeIndex = newParserNode(RB, yylineno, 0, NULL, INVALID_NODE_INDEX); return RB; }
{LC} { yylval.nodeIndex = newParserNode(LC, yylineno, 0, NULL, INVALID_NODE_INDEX); return LC; }
{RC} { yylval.nodeIndex = newParserNode(RC, yylineno, 0, NULL, INVALID_NODE_INDEX); return RC; }

{STRUCT} { yylval.nodeIndex = newParserNode(STRUCT, yylineno, 0, NULL, INVALID_NODE_INDEX); return STRUCT; }
{RETURN} { yylval.nodeIndex = newParserNode(RETURN, yylineno, 0, NULL, INVALID_NODE_INDEX); return RETURN; }
{IF} { yylval.nodeIndex = newParserNode(IF, yylineno, 0, NULL, INVALID_NODE_INDEX); return IF; }
{ELSE} { yylval.nodeIndex = newParserNode(ELSE, yylineno, 0, NULL, INVALID_NODE_INDEX); return ELSE; }
{WHILE} { yylval.nodeIndex = newParserNode(WHILE, yylineno, 0, NULL, INVALID_NODE_INDEX); return WHILE; }

{ID} { yylval.nodeIndex = newParserNode(ID, yylineno, 0, NULL, INVALID_NODE_INDEX); return ID; }

{SPACE} ;

{ERROR} { fprintf(stderr, "Error type A at Line %d: unknown identifier: \"%s\" \n", yylineno, yytext); }
%%
