%{
#define NOINCLUDE_CMM_SCANNER_TAB_H
#include <stddef.h>
#include "CmmParserTypes.h"
#include "Structure/ParserNodes.h"
#include "ErrorReporter.h"
#undef NOINCLUDE_CMM_SCANNER_TAB_H
%}

%union {
    ParserNode_I nodeIndex;
}

%token <nodeIndex> INT // A sequence of digits without spaces
%token <nodeIndex> FLOAT // A real number consisting of digits and a decimal point, point must be surrounded by digits
%token <nodeIndex> ID // A sequence of letters, digits, and underscores, starting with a letter or underscore, at most 52 characters
%token <nodeIndex> SEMI // ;
%token <nodeIndex> COMMA // ,
%token <nodeIndex> ASSIGNOP // =
%token <nodeIndex> EQ NEQ LE LT GE GT // ==, !=, <=, <, >=, >
%token <nodeIndex> PLUS // +
%token <nodeIndex> MINUS // -
%token <nodeIndex> STAR // *
%token <nodeIndex> DIV // /
%token <nodeIndex> AND // &&
%token <nodeIndex> OR // ||
%token <nodeIndex> DOT // .
%token <nodeIndex> NOT // !
%token <nodeIndex> TYPE // int, float
%token <nodeIndex> LP // (
%token <nodeIndex> RP // )
%token <nodeIndex> LB // [
%token <nodeIndex> RB // ]
%token <nodeIndex> LC // {
%token <nodeIndex> RC // }
%token <nodeIndex> STRUCT // struct
%token <nodeIndex> RETURN // return
%token <nodeIndex> IF // if
%token <nodeIndex> ELSE // else
%token <nodeIndex> WHILE // while

%type <nodeIndex> Program ExtDefList ExtDef ExtDecList
%type <nodeIndex> Specifier StructSpecifier OptTag Tag
%type <nodeIndex> VarDec FunDec VarList ParamDec
%type <nodeIndex> CompStm StmtList Stmt
%type <nodeIndex> DefList Def DecList Dec
%type <nodeIndex> Exp Args

// Define the precedence and associativity of the operators
%right ASSIGNOP
%left OR
%left AND
%left EQ NEQ LE LT GE GT
%left PLUS MINUS
%left STAR DIV
%right NOT
%left DOT LP RP LB RB LC RC

%%
// HIGH LEVEL GRAMMAR
Program:
    ExtDefList                      {ParserNode_I children[1] = {$1}; $$ = newParserNode(PROGRAM, NO_LINE_NUMBER, 1, children, INVALID_NODE_INDEX); setParserTreeRoot($$);}
    ;

ExtDefList:
    ExtDef ExtDefList               {ParserNode_I children[2] = {$1, $2}; $$ = newParserNode(EXT_DEF_LIST, NO_LINE_NUMBER, 2, children, INVALID_NODE_INDEX);}
    | /* empty */                   {$$ = newParserNode(EXT_DEF_LIST, NO_LINE_NUMBER, 0, NULL, INVALID_NODE_INDEX);}
    ;

ExtDef:
    Specifier ExtDecList SEMI       {ParserNode_I children[3] = {$1, $2, $3}; $$ = newParserNode(EXT_DEF, NO_LINE_NUMBER, 3, children, INVALID_NODE_INDEX);}
    |Specifier SEMI                 {ParserNode_I children[2] = {$1, $2}; $$ = newParserNode(EXT_DEF, NO_LINE_NUMBER, 2, children, INVALID_NODE_INDEX);}
    |Specifier FunDec CompStm       {ParserNode_I children[3] = {$1, $2, $3}; $$ = newParserNode(EXT_DEF, NO_LINE_NUMBER, 3, children, INVALID_NODE_INDEX);}
    |error SEMI                     {reportError(getParserNode($2)->lineNum, UnexpectedExternalDefinition, "Unexpected External Definition");}
    ;

ExtDecList:
    VarDec                          {ParserNode_I children[1] = {$1}; $$ = newParserNode(EXT_DEC_LIST, NO_LINE_NUMBER, 1, children, INVALID_NODE_INDEX);}
    |VarDec COMMA ExtDecList        {ParserNode_I children[3] = {$1, $2, $3}; $$ = newParserNode(EXT_DEC_LIST, NO_LINE_NUMBER, 3, children, INVALID_NODE_INDEX);}
    ;

//SPECIFIER
Specifier:
    TYPE                            {ParserNode_I children[1] = {$1}; $$ = newParserNode(SPECIFIER, NO_LINE_NUMBER, 1, children, INVALID_NODE_INDEX);}
    |StructSpecifier                {ParserNode_I children[1] = {$1}; $$ = newParserNode(SPECIFIER, NO_LINE_NUMBER, 1, children, INVALID_NODE_INDEX);}
    ;

StructSpecifier:
    STRUCT OptTag LC DefList RC     {ParserNode_I children[5] = {$1, $2, $3, $4, $5}; $$ = newParserNode(STRUCT_SPECIFIER, NO_LINE_NUMBER, 5, children, INVALID_NODE_INDEX);}
    |STRUCT Tag                     {ParserNode_I children[2] = {$1, $2}; $$ = newParserNode(STRUCT_SPECIFIER, NO_LINE_NUMBER, 2, children, INVALID_NODE_INDEX);}
    ;

OptTag:
    ID                              {ParserNode_I children[1] = {$1}; $$ = newParserNode(OPT_TAG, NO_LINE_NUMBER, 1, children, INVALID_NODE_INDEX);}
    |/* empty */                    {$$ = newParserNode(OPT_TAG, NO_LINE_NUMBER, 0, NULL, INVALID_NODE_INDEX);}
    ;

Tag:
    ID                              {ParserNode_I children[1] = {$1}; $$ = newParserNode(TAG, NO_LINE_NUMBER, 1, children, INVALID_NODE_INDEX);}
    ;

//DECLARATION
VarDec:
    ID                              {ParserNode_I children[1] = {$1}; $$ = newParserNode(VAR_DEC, NO_LINE_NUMBER, 1, children, INVALID_NODE_INDEX);}
    |VarDec LB INT RB               {ParserNode_I children[4] = {$1, $2, $3, $4}; $$ = newParserNode(VAR_DEC, NO_LINE_NUMBER, 4, children, INVALID_NODE_INDEX);}
    ;

FunDec:
    ID LP VarList RP                {ParserNode_I children[4] = {$1, $2, $3, $4}; $$ = newParserNode(FUN_DEC, NO_LINE_NUMBER, 4, children, INVALID_NODE_INDEX);}
    |ID LP RP                       {ParserNode_I children[3] = {$1, $2, $3}; $$ = newParserNode(FUN_DEC, NO_LINE_NUMBER, 3, children, INVALID_NODE_INDEX);}
    ;

VarList:
    ParamDec COMMA VarList          {ParserNode_I children[3] = {$1, $2, $3}; $$ = newParserNode(VAR_LIST, NO_LINE_NUMBER, 3, children, INVALID_NODE_INDEX);}
    |ParamDec                       {ParserNode_I children[1] = {$1}; $$ = newParserNode(VAR_LIST, NO_LINE_NUMBER, 1, children, INVALID_NODE_INDEX);}
    ;

ParamDec:
    Specifier VarDec                {ParserNode_I children[2] = {$1, $2}; $$ = newParserNode(PARAM_DEC, NO_LINE_NUMBER, 2, children, INVALID_NODE_INDEX);}
    ;

//STATEMENT
CompStm:
    LC DefList StmtList RC          {ParserNode_I children[4] = {$1, $2, $3, $4}; $$ = newParserNode(COMP_STM, NO_LINE_NUMBER, 4, children, INVALID_NODE_INDEX);}
    ;

StmtList:
    Stmt StmtList                   {ParserNode_I children[2] = {$1, $2}; $$ = newParserNode(STMT_LIST, NO_LINE_NUMBER, 2, children, INVALID_NODE_INDEX);}
    |/* empty */                    {$$ = newParserNode(STMT_LIST, NO_LINE_NUMBER, 0, NULL, INVALID_NODE_INDEX);}
    ;

Stmt:
    Exp SEMI                        {ParserNode_I children[2] = {$1, $2}; $$ = newParserNode(STMT, NO_LINE_NUMBER, 2, children, INVALID_NODE_INDEX);}
    |CompStm                        {ParserNode_I children[1] = {$1}; $$ = newParserNode(STMT, NO_LINE_NUMBER, 1, children, INVALID_NODE_INDEX);}
    |RETURN Exp SEMI                {ParserNode_I children[3] = {$1, $2, $3}; $$ = newParserNode(STMT, NO_LINE_NUMBER, 3, children, INVALID_NODE_INDEX);}
    |IF LP Exp RP Stmt              {ParserNode_I children[4] = {$1, $2, $3, $4}; $$ = newParserNode(STMT, NO_LINE_NUMBER, 4, children, INVALID_NODE_INDEX);}
    |IF LP Exp RP Stmt ELSE Stmt    {ParserNode_I children[6] = {$1, $2, $3, $4, $5, $6}; $$ = newParserNode(STMT, NO_LINE_NUMBER, 6, children, INVALID_NODE_INDEX);}
    |WHILE LP Exp RP Stmt           {ParserNode_I children[4] = {$1, $2, $3, $4}; $$ = newParserNode(STMT, NO_LINE_NUMBER, 4, children, INVALID_NODE_INDEX);}
    |error SEMI                     {reportError(getParserNode($2)->lineNum, UnexpectedStatement, "Unexpected Statement");}
    ;

//LOCAL DEFINITION
DefList:
    Def DefList                     {ParserNode_I children[2] = {$1, $2}; $$ = newParserNode(DEF_LIST, NO_LINE_NUMBER, 2, children, INVALID_NODE_INDEX);}
    |/* empty */                    {$$ = newParserNode(DEF_LIST, NO_LINE_NUMBER, 0, NULL, INVALID_NODE_INDEX);}
    ;

Def:
    Specifier DecList SEMI          {ParserNode_I children[3] = {$1, $2, $3}; $$ = newParserNode(DEF, NO_LINE_NUMBER, 3, children, INVALID_NODE_INDEX);}
    ;

DecList:
    Dec                             {ParserNode_I children[1] = {$1}; $$ = newParserNode(DEC_LIST, NO_LINE_NUMBER, 1, children, INVALID_NODE_INDEX);}
    |Dec COMMA DecList              {ParserNode_I children[3] = {$1, $2, $3}; $$ = newParserNode(DEC_LIST, NO_LINE_NUMBER, 3, children, INVALID_NODE_INDEX);}
    ;

Dec:
    VarDec                          {ParserNode_I children[1] = {$1}; $$ = newParserNode(DEC, NO_LINE_NUMBER, 1, children, INVALID_NODE_INDEX);}
    |VarDec ASSIGNOP Exp            {ParserNode_I children[3] = {$1, $2, $3}; $$ = newParserNode(DEC, NO_LINE_NUMBER, 3, children, INVALID_NODE_INDEX);}
    ;

//EXPRESSION

Exp:
    Exp ASSIGNOP Exp                {ParserNode_I children[3] = {$1, $2, $3}; $$ = newParserNode(EXP, NO_LINE_NUMBER, 3, children, INVALID_NODE_INDEX);}
    |Exp AND Exp                    {ParserNode_I children[3] = {$1, $2, $3}; $$ = newParserNode(EXP, NO_LINE_NUMBER, 3, children, INVALID_NODE_INDEX);}
    |Exp OR Exp                     {ParserNode_I children[3] = {$1, $2, $3}; $$ = newParserNode(EXP, NO_LINE_NUMBER, 3, children, INVALID_NODE_INDEX);}
    |Exp EQ Exp                     {ParserNode_I children[3] = {$1, $2, $3}; $$ = newParserNode(EXP, NO_LINE_NUMBER, 3, children, INVALID_NODE_INDEX);}
    |Exp NEQ Exp                    {ParserNode_I children[3] = {$1, $2, $3}; $$ = newParserNode(EXP, NO_LINE_NUMBER, 3, children, INVALID_NODE_INDEX);}
    |Exp LT Exp                     {ParserNode_I children[3] = {$1, $2, $3}; $$ = newParserNode(EXP, NO_LINE_NUMBER, 3, children, INVALID_NODE_INDEX);}
    |Exp LE Exp                     {ParserNode_I children[3] = {$1, $2, $3}; $$ = newParserNode(EXP, NO_LINE_NUMBER, 3, children, INVALID_NODE_INDEX);}
    |Exp GT Exp                     {ParserNode_I children[3] = {$1, $2, $3}; $$ = newParserNode(EXP, NO_LINE_NUMBER, 3, children, INVALID_NODE_INDEX);}
    |Exp GE Exp                     {ParserNode_I children[3] = {$1, $2, $3}; $$ = newParserNode(EXP, NO_LINE_NUMBER, 3, children, INVALID_NODE_INDEX);}
    |Exp PLUS Exp                   {ParserNode_I children[3] = {$1, $2, $3}; $$ = newParserNode(EXP, NO_LINE_NUMBER, 3, children, INVALID_NODE_INDEX);}
    |Exp MINUS Exp                  {ParserNode_I children[3] = {$1, $2, $3}; $$ = newParserNode(EXP, NO_LINE_NUMBER, 3, children, INVALID_NODE_INDEX);}
    |Exp STAR Exp                   {ParserNode_I children[3] = {$1, $2, $3}; $$ = newParserNode(EXP, NO_LINE_NUMBER, 3, children, INVALID_NODE_INDEX);}
    |Exp DIV Exp                    {ParserNode_I children[3] = {$1, $2, $3}; $$ = newParserNode(EXP, NO_LINE_NUMBER, 3, children, INVALID_NODE_INDEX);}
    |LP Exp RP                      {ParserNode_I children[3] = {$1, $2, $3}; $$ = newParserNode(EXP, NO_LINE_NUMBER, 3, children, INVALID_NODE_INDEX);}
    |MINUS Exp                      {ParserNode_I children[2] = {$1, $2}; $$ = newParserNode(EXP, NO_LINE_NUMBER, 2, children, INVALID_NODE_INDEX);}
    |NOT Exp                        {ParserNode_I children[2] = {$1, $2}; $$ = newParserNode(EXP, NO_LINE_NUMBER, 2, children, INVALID_NODE_INDEX);}
    |ID LP Args RP                  {ParserNode_I children[4] = {$1, $2, $3, $4}; $$ = newParserNode(EXP, NO_LINE_NUMBER, 4, children, INVALID_NODE_INDEX);}
    |ID LP RP                       {ParserNode_I children[3] = {$1, $2, $3}; $$ = newParserNode(EXP, NO_LINE_NUMBER, 3, children, INVALID_NODE_INDEX);}
    |Exp LB Exp RB                  {ParserNode_I children[4] = {$1, $2, $3, $4}; $$ = newParserNode(EXP, NO_LINE_NUMBER, 4, children, INVALID_NODE_INDEX);}
    |Exp DOT ID                     {ParserNode_I children[3] = {$1, $2, $3}; $$ = newParserNode(EXP, NO_LINE_NUMBER, 3, children, INVALID_NODE_INDEX);}
    |ID                             {ParserNode_I children[1] = {$1}; $$ = newParserNode(EXP, NO_LINE_NUMBER, 1, children, INVALID_NODE_INDEX);}
    |INT                            {ParserNode_I children[1] = {$1}; $$ = newParserNode(EXP, NO_LINE_NUMBER, 1, children, INVALID_NODE_INDEX);}
    |FLOAT                          {ParserNode_I children[1] = {$1}; $$ = newParserNode(EXP, NO_LINE_NUMBER, 1, children, INVALID_NODE_INDEX);}
    ;

Args:
    Exp COMMA Args                  {ParserNode_I children[3] = {$1, $2, $3}; $$ = newParserNode(ARGS, NO_LINE_NUMBER, 3, children, INVALID_NODE_INDEX);}
    |Exp                            {ParserNode_I children[1] = {$1}; $$ = newParserNode(ARGS, NO_LINE_NUMBER, 1, children, INVALID_NODE_INDEX);}
    ;

%%