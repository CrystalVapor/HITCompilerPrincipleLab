%{
#define NOINCLUDE_CMM_SCANNER_TAB_H
#include "CmmParserTypes.h"
#include "Structure/ParserNodes.h"
#include "ErrorReporter.h"
#undef NOINCLUDE_CMM_SCANNER_TAB_H

%}

%option yylineno

COMMENTSINGLE "//"
COMMENTMULTI "/*"

SEMI ;
COMMA ,
ASSIGNOP =
PLUS \+
MINUS \-
STAR \*
DIV \/
AND &&
OR \|\|
DOT \.
NOT !

EQ ==
NEQ !=
LE <=
LT <
GE >=
GT >

LP \(
RP \)
LB \[
RB \]
LC \{
RC \}

TYPE int|float
STRUCT struct
RETURN return
IF if
ELSE else
WHILE while

INTOCT [-]?0[1-7][0-7]*
INTHEX [-]?0[xX][0-9a-fA-F]+
INTDEC [-]?(0|[1-9][0-9]*)
INT {INTDEC}|{INTOCT}|{INTHEX}
FLOAT ({INTDEC}\.[0-9]+)|(([-]?[0-9]+\.[0-9]*|[0-9]*\.[0-9]*)[Ee][+-]?[0-9]+)
ID [a-zA-Z_][a-zA-Z0-9_]*

SPACE [ \t\n\r]+

ID_ERROR [0-9][a-zA-Z0-9_]*
INTOCT_ERROR [-]?0[0-7]*[89][0-9]*
INTHEX_ERROR [-]?0[xX][0-9a-fA-F]*[g-zG-Z]*[0-9a-zA-Z]*
INTDEC_ERROR [-]?[1-9][0-9]*[a-zA-Z]*
FLOAT_ERROR ({INTDEC}\.[0-9]*[a-zA-Z]+)|(([-]?[0-9]*\.[0-9]*|[0-9]*\.[0-9]*)[Ee][+-]?[0-9]*[a-zA-Z]+)
INT_ERROR {INTDEC_ERROR}|{INTOCT_ERROR}|{INTHEX_ERROR}

ERROR .

%%
{COMMENTSINGLE} { while (input() != '\n'); }
{COMMENTMULTI} {
    int c;
    // note that when input meets EOF, it will return 0, not EOF.(issue #2, CmmScanner.c, line 1751)
    const int lexerEOF = 0;
    int startLine = yylineno;
    while ((c = input()) != lexerEOF) {
        if (c == '*') {
            if ((c = input()) == '/') {
                break;
            }
            else if(c == lexerEOF)
            {
                goto error_UC;
            }
            else {
                unput(c);
            }
        }
    }
error_UC:
    if (c == lexerEOF) {
                 reportError(startLine, UnterminatedComment, "unterminated comment detected.");
                 break;
    }
}

{INT} { yylval.nodeIndex = newParserNode(INT, yylineno, 0, NULL, INVALID_NODE_INDEX); return INT; }
{FLOAT} { yylval.nodeIndex = newParserNode(FLOAT, yylineno, 0, NULL, INVALID_NODE_INDEX); return FLOAT; }

{SEMI} { yylval.nodeIndex = newParserNode(SEMI, yylineno, 0, NULL, INVALID_NODE_INDEX); return SEMI; }
{COMMA} { yylval.nodeIndex = newParserNode(COMMA, yylineno, 0, NULL, INVALID_NODE_INDEX); return COMMA; }
{ASSIGNOP} { yylval.nodeIndex = newParserNode(ASSIGNOP, yylineno, 0, NULL, INVALID_NODE_INDEX); return ASSIGNOP; }
{PLUS} { yylval.nodeIndex = newParserNode(PLUS, yylineno, 0, NULL, INVALID_NODE_INDEX); return PLUS; }
{MINUS} { yylval.nodeIndex = newParserNode(MINUS, yylineno, 0, NULL, INVALID_NODE_INDEX); return MINUS; }
{STAR} { yylval.nodeIndex = newParserNode(STAR, yylineno, 0, NULL, INVALID_NODE_INDEX); return STAR; }
{DIV} { yylval.nodeIndex = newParserNode(DIV, yylineno, 0, NULL, INVALID_NODE_INDEX); return DIV; }
{AND} { yylval.nodeIndex = newParserNode(AND, yylineno, 0, NULL, INVALID_NODE_INDEX); return AND; }
{OR} { yylval.nodeIndex = newParserNode(OR, yylineno, 0, NULL, INVALID_NODE_INDEX); return OR; }
{DOT} { yylval.nodeIndex = newParserNode(DOT, yylineno, 0, NULL, INVALID_NODE_INDEX); return DOT; }
{NOT} { yylval.nodeIndex = newParserNode(NOT, yylineno, 0, NULL, INVALID_NODE_INDEX); return NOT; }
{TYPE} { yylval.nodeIndex = newParserNode(TYPE, yylineno, 0, NULL, INVALID_NODE_INDEX); return TYPE; }

{EQ} { yylval.nodeIndex = newParserNode(EQ, yylineno, 0, NULL, INVALID_NODE_INDEX); return EQ; }
{NEQ} { yylval.nodeIndex = newParserNode(NEQ, yylineno, 0, NULL, INVALID_NODE_INDEX); return NEQ; }
{LE} { yylval.nodeIndex = newParserNode(LE, yylineno, 0, NULL, INVALID_NODE_INDEX); return LE; }
{LT} { yylval.nodeIndex = newParserNode(LT, yylineno, 0, NULL, INVALID_NODE_INDEX); return LT; }
{GE} { yylval.nodeIndex = newParserNode(GE, yylineno, 0, NULL, INVALID_NODE_INDEX); return GE; }
{GT} { yylval.nodeIndex = newParserNode(GT, yylineno, 0, NULL, INVALID_NODE_INDEX); return GT; }

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

{INT_ERROR} { reportErrorFormat(yylineno, InvalidNumber,"Invalid number \"%s\" ", yytext); return YYerror;}
{FLOAT_ERROR} { reportErrorFormat(yylineno, InvalidFloat, "Invalid float \"%s\" ", yytext); return YYerror;}
{ID_ERROR} { reportErrorFormat(yylineno, InvalidIdentifier, "Invalid identifier \"%s\" ", yytext); return YYerror;}


{ERROR} { reportErrorFormat(yylineno, UnrecognizedCharacter, "Unrecognized character \"%s\" ", yytext); return YYerror;}
%%
