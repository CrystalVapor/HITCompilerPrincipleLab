//
// Created by Crystal on 2024/3/19.
//

#include "Structure/SymbolTable.h"
#include "ErrorReporter.h"
#include "Structure/ParserNodes.h"
#include "SemanticAnalyzer.h"

#include "Lab2.h"

int testSymbolTable();

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

    semanticAnalyze(getParserTreeRoot());

    ret = hasError();
    if(ret) {
        printError(stderr);
        resetErrorReporter();
    }



    semanticAnalyze_End();
    freeParserNodes();

    //testSymbolTable();

    return ret;
}

int testSymbolTable(){
    SymbolTable_t symbolTable = SymbolTable_create();
    SymbolRecord record;

    SymbolTable_enterScope(symbolTable);

    printf("-----[testBasicVariable]-----\n");

    //basic variable test
    SymbolTable_createVariableByRawMeta(symbolTable, &record, SVT_Int, NULL);
    SymbolTable_insertRecord(symbolTable, "testIntVar", &record);

    SymbolTable_createVariableByRawMeta(symbolTable, &record, SVT_Float, NULL);
    SymbolTable_insertRecord(symbolTable, "testFloatVar", &record);

    int dim1[1] = {10};
    SymbolInfo_Array_Raw arrayInfo = SymbolInfo_Array_create(SVT_Int, dim1, 1, NULL);
    SymbolTable_Error error = SymbolTable_createVariableByRawMeta(symbolTable, &record, SVT_Array, arrayInfo);
    SymbolTable_insertRecord(symbolTable, "testIntArray", &record);

    int dim2[2] = {10, 20};
    SymbolInfo_Array_Raw arrayInfo2 = SymbolInfo_Array_create(SVT_Float, dim2, 2, NULL);

    SymbolTable_createVariableByRawMeta(symbolTable, &record, SVT_Array, arrayInfo2);
    SymbolTable_insertRecord(symbolTable, "testFloatArray", &record);

    //test variable lookup
    SymbolRecord_t lookupRecord;
    SymbolDefineStatus defineStatus = SymbolTable_lookupRecord(symbolTable, "testIntVar", &lookupRecord);
    char debugBuffer[1024];
    SymbolRecord_printDebug(lookupRecord, debugBuffer, 1024);
    printf("Found testIntVar: %s\n", debugBuffer);

    defineStatus = SymbolTable_lookupRecord(symbolTable, "testFloatVar", &lookupRecord);
    SymbolRecord_printDebug(lookupRecord, debugBuffer, 1024);
    printf("Found testFloatVar: %s\n", debugBuffer);

    defineStatus = SymbolTable_lookupRecord(symbolTable, "testIntArray", &lookupRecord);
    SymbolRecord_printDebug(lookupRecord, debugBuffer, 1024);
    printf("Found testIntArray: %s\n", debugBuffer);

    defineStatus = SymbolTable_lookupRecord(symbolTable, "testFloatArray", &lookupRecord);
    SymbolRecord_printDebug(lookupRecord, debugBuffer, 1024);
    printf("Found testFloatArray: %s\n", debugBuffer);

    printf("-----[testFunction]-----\n");

    //function test, expect: void()
    SymbolTable_createFunctionByRawMeta(symbolTable, &record, SVT_Void, NULL, NULL, NULL, NULL, 0);
    SymbolTable_insertRecord(symbolTable, "testVoidFunc", &record);

    defineStatus = SymbolTable_lookupRecord(symbolTable, "testVoidFunc", &lookupRecord);
    SymbolRecord_printDebug(lookupRecord, debugBuffer, 1024);
    printf("Found testVoidFunc: %s\n", debugBuffer);

    //function with parameters and an array return, expect: int[10][10][-1](int paramInt, float paramFloat)
    int dim3[3] = {10, 10, -1};
    SymbolInfo_Array_Raw arrayInfo3 = SymbolInfo_Array_create(SVT_Int, dim3, 3, NULL);
    Symbol_Value_Type paramTypes[2] = {SVT_Int, SVT_Float};
    char* paramNames[2] = {"paramInt", "paramFloat"};
    void* paramMetas[2] = {NULL, NULL};

    SymbolTable_createFunctionByRawMeta(symbolTable, &record,
                                        SVT_Array, arrayInfo3,
                                        paramTypes, paramNames, paramMetas,
                                        2);
    SymbolTable_insertRecord(symbolTable, "testArrayFunc", &record);

    defineStatus = SymbolTable_lookupRecord(symbolTable, "testArrayFunc", &lookupRecord);
    SymbolRecord_printDebug(lookupRecord, debugBuffer, 1024);
    printf("Found testArrayFunc: %s\n", debugBuffer);

    printf("-----[testStruct]-----\n");

    //struct test, expect: struct{int a; float b;}
    Symbol_Value_Type memberTypes[2] = {SVT_Int, SVT_Float};
    char* memberNames[2] = {"a", "b"};
    void* memberMetas[2] = {NULL, NULL};
    SymbolTable_createStructByRawMeta(symbolTable, &record, memberTypes, memberNames, memberMetas, 2);
    SymbolTable_insertRecord(symbolTable, "testStruct", &record);

    defineStatus = SymbolTable_lookupRecord(symbolTable, "testStruct", &lookupRecord);
    SymbolRecord_printDebug(lookupRecord, debugBuffer, 1024);
    printf("Found testStruct: %s\n", debugBuffer);

    //struct Variable test, expect: struct{int a; float b;} testStructVar;
    SymbolTable_createVariableByRawMeta(symbolTable, &record, SVT_Struct, "testStruct");
    SymbolTable_insertRecord(symbolTable, "testStructVar", &record);

    defineStatus = SymbolTable_lookupRecord(symbolTable, "testStructVar", &lookupRecord);
    SymbolRecord_printDebug(lookupRecord, debugBuffer, 1024);
    printf("Found testStructVar: %s\n", debugBuffer);

    //struct Array test, expect: struct{int a; float b;} testStructArray[10];
    int dim4[1] = {10};
    SymbolInfo_Array_Raw arrayInfo4 = SymbolInfo_Array_create(SVT_Struct, dim4, 1, "testStruct");
    SymbolTable_createVariableByRawMeta(symbolTable, &record, SVT_Array, arrayInfo4);
    SymbolTable_insertRecord(symbolTable, "testStructArray", &record);

    defineStatus = SymbolTable_lookupRecord(symbolTable, "testStructArray", &lookupRecord);
    SymbolRecord_printDebug(lookupRecord, debugBuffer, 1024);
    printf("Found testStructArray: %s\n", debugBuffer);

    //struct Function test, expect: struct{int a; float b;} testStructFunc(int paramInt, float paramFloat)
    SymbolTable_createFunctionByRawMeta(symbolTable, &record,
                                        SVT_Struct, "testStruct",
                                        paramTypes, paramNames, paramMetas,
                                        2);
    SymbolTable_insertRecord(symbolTable, "testStructFunc", &record);

    defineStatus = SymbolTable_lookupRecord(symbolTable, "testStructFunc", &lookupRecord);
    SymbolRecord_printDebug(lookupRecord, debugBuffer, 1024);
    printf("Found testStructFunc: %s\n", debugBuffer);

    //struct Array Function test, expect: struct{int a; float b;} testStructArrayFunc(int paramInt, float paramFloat)[10]
    SymbolInfo_Array_Raw arrayInfo5 = SymbolInfo_Array_create(SVT_Struct, dim4, 1, "testStruct");
    SymbolTable_createFunctionByRawMeta(symbolTable, &record,
                                        SVT_Array, arrayInfo5,
                                        paramTypes, paramNames, paramMetas,
                                        2);
    SymbolTable_insertRecord(symbolTable, "testStructArrayFunc", &record);

    defineStatus = SymbolTable_lookupRecord(symbolTable, "testStructArrayFunc", &lookupRecord);
    SymbolRecord_printDebug(lookupRecord, debugBuffer, 1024);
    printf("Found testStructArrayFunc: %s\n", debugBuffer);

    //nested struct test, expect: struct{int a; struct{int a, float b;} b;} testNestedStructVar;
    Symbol_Value_Type memberTypes2[2] = {SVT_Int, SVT_Struct};
    char* memberNames2[2] = {"a", "b"};
    void* memberMetas2[2] = {NULL, "testStruct"};
    SymbolTable_createStructByRawMeta(symbolTable, &record, memberTypes2, memberNames2, memberMetas2, 2);
    SymbolTable_insertRecord(symbolTable, "testNestedStruct", &record);

    defineStatus = SymbolTable_lookupRecord(symbolTable, "testNestedStruct", &lookupRecord);
    SymbolRecord_printDebug(lookupRecord, debugBuffer, 1024);
    printf("Found testNestedStruct: %s\n", debugBuffer);

    //nested struct variable test, expect: struct{int a; struct{int a, float b;} b;} testNestedStructVar;
    SymbolTable_createVariableByRawMeta(symbolTable, &record, SVT_Struct, "testNestedStruct");
    SymbolTable_insertRecord(symbolTable, "testNestedStructVar", &record);

    defineStatus = SymbolTable_lookupRecord(symbolTable, "testNestedStructVar", &lookupRecord);
    SymbolRecord_printDebug(lookupRecord, debugBuffer, 1024);
    printf("Found testNestedStructVar: %s\n", debugBuffer);



    SymbolTable_destroy(symbolTable);
}