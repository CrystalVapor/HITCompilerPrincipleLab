//
// Created by Crystal on 2024/3/31.
//

#include "CmmParserTypes.h"
#include "Structure/ParserNodes.h"
#include "SemanticAnalyzer.h"
#include "ErrorReporter.h"
#include "InterCodeGenerator.h"

#include "Lab3.h"


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

#ifdef DEBUG_PARSER_TREE
    printf("DEBUG_PARSER_NODES:\n");
    printAllNodes();
#endif

    if(ret)
    {
        printError(stderr);
        fprintf(stderr, "Lexical or syntax error detected, aborted before semantic analyzing.\n");
        resetErrorReporter();
        freeParserNodes();
        return ret;
    }

    semanticAnalyze(getParserTreeRoot());

    ret = hasError();
    if(ret) {
        printError(stderr);
        fprintf(stderr, "Semantic error detected.\n");
        resetErrorReporter();
        semanticAnalyze_End();
        freeParserNodes();
        return ret;
    }

   /* generateInterCode(getParserTreeRoot(), stdout);

    generateInterCode_End();*/
    semanticAnalyze_End();
    freeParserNodes();

    return ret;
}
