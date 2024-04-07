//
// Created by Crystal on 2024/3/31.
//

#include "CmmParserTypes.h"
#include "Structure/ParserNodes.h"
#include "SemanticAnalyzer.h"
#include "ErrorReporter.h"
#include "InterCodeGenerator.h"

#include "Lab3.h"
#include "Structure/SymbolTable.h"


void registerPredefinedFunctions(SymbolTable_t symbolTable);

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

    SymbolTable_t symbolTable = SymbolTable_create();

    registerPredefinedFunctions(symbolTable);

    semanticAnalyze(getParserTreeRoot(), symbolTable);

    ret = hasError();
    if(ret) {
        printError(stderr);
        fprintf(stderr, "Semantic error detected.\n");
        resetErrorReporter();
        semanticAnalyze_End();
        freeParserNodes();
        return ret;
    }



    InterCodeHandle codeHandle =  generateInterCode(getParserTreeRoot(), stdout, symbolTable);

    generateInterCode_End();


    semanticAnalyze_End();
    SymbolTable_destroy(symbolTable);
    freeParserNodes();

    return ret;
}

void registerPredefinedFunctions(SymbolTable_t symbolTable) {
    SymbolInfo_Function_t readFunc = SymbolInfo_Function_createBaked(SVT_Int,
                                                                     NULL,
                                                                     NULL,
                                                                     NULL,
                                                                     NULL,
                                                                     0);
    Symbol_Value_Type writeFuncParamType[1] = {SVT_Int};
    char* writeFuncParamName[1] = {"value"};
    SymbolInfo_t writeFuncParamInfo[1] = {NULL};
    SymbolInfo_Function_t writeFunc = SymbolInfo_Function_createBaked(SVT_Int,
                                                                      NULL,
                                                                      writeFuncParamType,
                                                                      writeFuncParamName,
                                                                      writeFuncParamInfo,
                                                                      1);
    readFunc->isDefined = 1;
    writeFunc->isDefined = 1;
    SymbolRecord record;
    SymbolTable_createFunctionByInfo(symbolTable, &record, readFunc);
    SymbolTable_insertRecord(symbolTable, "read", &record);
    SymbolTable_createFunctionByInfo(symbolTable, &record, writeFunc);
    SymbolTable_insertRecord(symbolTable, "write", &record);
}
