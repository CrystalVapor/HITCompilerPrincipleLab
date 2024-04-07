//
// Created by Crystal on 2024/3/19.
//

#include "Structure/SymbolTable.h"
#include "ErrorReporter.h"
#include "Structure/ParserNodes.h"
#include "SemanticAnalyzer.h"

#include "Lab2.h"

int main(int argc, char** argv) {
    if(argc<2)
    {
        fprintf(stderr, "Usage: %s <input file>\n", argv[0]);
        return 1;
    }
    FILE* file = fopen(argv[1], "r");
    if(file == NULL)
    {
        fprintf(stderr, "Error: Cannot open file %s\n", argv[1]);
        return 1;
    }

    yyset_debug(0);
    yyrestart(file);
    yyparse();
    int ret = hasError();

#ifdef DEBUG_PARSER_TREE
    printf("DEBUG_PARSER_NODES:\n");
    printAllNodes();
#endif

    if(ret)
    {
        printError(stderr);
        fprintf(stderr, "Lexical or syntax error detected, aborted before semantic analyzing.\n");
        freeParserNodes();
        return ret;
    }

    SymbolTable_t symbolTable = SymbolTable_create();

    semanticAnalyze(getParserTreeRoot(), symbolTable);

    ret = hasError();
    if(ret) {
        printError(stderr);
        resetErrorReporter();
    }

    semanticAnalyze_End();
    SymbolTable_destroy(symbolTable);
    freeParserNodes();

    return ret;
}

