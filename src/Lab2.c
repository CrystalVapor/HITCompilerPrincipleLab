//
// Created by Crystal on 2024/3/19.
//
#include "Structure/SemanticNodes.h"
#include "Structure/SymbolTable.h"

#include "Lab2.h"

int testSymbolTable();

int main(int argc, char** argv) {
    testSymbolTable();
    return 0;
}

int testSymbolTable(){
    SymbolTable_t symbolTable = SymbolTable_create();
    SymbolRecord record;

    printf("-----[testBasicVariable]-----\n");

    //basic variable test
    SymbolTable_createVariable(symbolTable, &record, SVT_Int, NULL);
    SymbolTable_insertRecord(symbolTable, "testIntVar", &record);
    
    SymbolTable_createVariable(symbolTable, &record, SVT_Float, NULL);
    SymbolTable_insertRecord(symbolTable, "testFloatVar", &record);

    int dim1[1] = {10};
    SymbolInfo_Array_Raw arrayInfo = SymbolInfo_Array_create(SVT_Int, dim1, 1, NULL);
    SymbolTable_Error error = SymbolTable_createVariable(symbolTable, &record, SVT_Array, arrayInfo);
    SymbolTable_insertRecord(symbolTable, "testIntArray", &record);

    int dim2[2] = {10, 20};
    SymbolInfo_Array_Raw arrayInfo2 = SymbolInfo_Array_create(SVT_Float, dim2, 2, NULL);

    SymbolTable_createVariable(symbolTable, &record, SVT_Array, arrayInfo2);
    SymbolTable_insertRecord(symbolTable, "testFloatArray", &record);

    //test variable lookup
    SymbolRecord_t lookupRecord;
    SymbolDefineStatus defineStatus = SymbolTable_lookupRecord(symbolTable, "testIntVar", &lookupRecord);
    char debugBuffer[1024];
    SymbolRecord_printDebug(lookupRecord, debugBuffer, 1024);
    printf("lookup testIntVar: %s\n", debugBuffer);

    defineStatus = SymbolTable_lookupRecord(symbolTable, "testFloatVar", &lookupRecord);
    SymbolRecord_printDebug(lookupRecord, debugBuffer, 1024);
    printf("lookup testFloatVar: %s\n", debugBuffer);

    defineStatus = SymbolTable_lookupRecord(symbolTable, "testIntArray", &lookupRecord);
    SymbolRecord_printDebug(lookupRecord, debugBuffer, 1024);
    printf("lookup testIntArray: %s\n", debugBuffer);

    defineStatus = SymbolTable_lookupRecord(symbolTable, "testFloatArray", &lookupRecord);
    SymbolRecord_printDebug(lookupRecord, debugBuffer, 1024);
    printf("lookup testFloatArray: %s\n", debugBuffer);

    printf("-----[testFunction]-----\n");

    //function test
    SymbolTable_createFunction(symbolTable, &record, SVT_Void, NULL, NULL, NULL, NULL, 0);
    SymbolTable_insertRecord(symbolTable, "testVoidFunc", &record);

    defineStatus = SymbolTable_lookupRecord(symbolTable, "testVoidFunc", &lookupRecord);
    SymbolRecord_printDebug(lookupRecord, debugBuffer, 1024);
    printf("lookup testVoidFunc: %s\n", debugBuffer);
}