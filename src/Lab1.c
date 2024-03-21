#include <stdio.h>
#include "Lab1.h"
#include "CmmParserTypes.h"
#include "Structure/ParserNodes.h"
#include "ErrorReporter.h"

//#define ALWAYS_TRY_PRINT_PARSER_TREE

extern void yyrestart(FILE* input_file);

int main(int argc, char** argv){
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
#ifndef ALWAYS_TRY_PRINT_PARSER_TREE
    if(!ret)
#else
    if(1)
#endif
    {
        printParserTree_PreOrder(getParserTreeRoot(), 0);
    }
#ifndef ALWAYS_TRY_PRINT_PARSER_TREE
    if(ret)
#else
    if(1)
#endif
    {
        printError(stderr);
        resetErrorReporter();
    }

#ifdef DEBUG_PARSER_TREE
    printf("DEBUG_PARSER_NODES:\n");
    printAllNodes();
#endif

    freeParserNodes();
    return ret;
}



