//
// Created by Crystal on 2024/3/18.
//
#include "CmmParserTypes.h"
#include "Structure/TokenName.h"

char GrammarSymbolNames[ARGS - PROGRAM + 1][20] = {
        "Program",
        "ExtDefList",
        "ExtDef",
        "ExtDecList",
        "Specifier",
        "StructSpecifier",
        "OptTag",
        "Tag",
        "VarDec",
        "FunDec",
        "VarList",
        "ParamDec",
        "CompSt",
        "StmtList",
        "Stmt",
        "DefList",
        "Def",
        "DecList",
        "Dec",
        "Exp",
        "Args"
};

char TokenNames[WHILE - INT + 1][20] = {
        "INT",
        "FLOAT",
        "ID",
        "SEMI",
        "COMMA",
        "ASSIGNOP",
        "RELOP",
        "PLUS",
        "MINUS",
        "STAR",
        "DIV",
        "AND",
        "OR",
        "DOT",
        "NOT",
        "TYPE",
        "LP",
        "RP",
        "LB",
        "RB",
        "LC",
        "RC",
        "STRUCT",
        "RETURN",
        "IF",
        "ELSE",
        "WHILE"
};

const char *getGrammarSymbolName(int grammarSymbol) {
    return GrammarSymbolNames[grammarSymbol - PROGRAM];
}

const char* getTokenName(int token)
{
    return TokenNames[token - INT];
}
