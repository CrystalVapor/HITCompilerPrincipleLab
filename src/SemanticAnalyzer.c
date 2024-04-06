#pragma clang diagnostic push
#pragma ide diagnostic ignored "misc-no-recursion"
//
// Created by Crystal on 2024/3/20.
//

#include <stdarg.h>
#include "Structure/ParserNodes.h"
#include "Structure/SymbolTable.h"
#include "Structure/SemanticInfo.h"
#include "ErrorReporter.h"

#include "SemanticAnalyzer.h"

#define GET_SEMANTIC_INFO(nodeIndex)  ((SemanticInfo_t)GET_NODE(nodeIndex)->semanticInfo)

int semanticErrors = 0;

SemanticInfo intLiteralInfo;
SemanticInfo floatLiteralInfo;

SymbolTable_t symbolTable;
SimpleArray_t semanticInfoList;

SymbolInfo_Function_t currentFunctionInfo = NULL;
SimpleArray_t currentStructInfoStack;
SimpleArray_t currentType;
SimpleArray_t currentTypeMeta;

SimpleArray_t functionForwardDeclarationList;

int currentDimensions[32];
int currentDimensionCount = 0;

char* currentVarName = NULL;

SimpleArray_t anonymousStructList;

////////////////////////////////////////
// Semantic Analyzer
////////////////////////////////////////

int Analyze_Program(ParserNode_I nodeIndex);
int Analyze_ExtDefList(ParserNode_I nodeIndex);
int Analyze_ExtDef(ParserNode_I nodeIndex);
int Analyze_ExtDecList(ParserNode_I nodeIndex);

int Analyze_Specifier(ParserNode_I nodeIndex);
int Analyze_StructSpecifier(ParserNode_I nodeIndex);
int Analyze_OptTag(ParserNode_I nodeIndex);
int Analyze_Tag(ParserNode_I nodeIndex);

int Analyze_VarDec(ParserNode_I nodeIndex);
// will push the function name as current var name and function info as current function info
int Analyze_FunDec(ParserNode_I nodeIndex);
int Analyze_VarList(ParserNode_I nodeIndex);
int Analyze_ParamDec(ParserNode_I nodeIndex);

int Analyze_CompSt(ParserNode_I nodeIndex);
int Analyze_StmtList(ParserNode_I nodeIndex);
int Analyze_Stmt(ParserNode_I nodeIndex);

int Analyze_DefList(ParserNode_I nodeIndex);
int Analyze_DefList_StructMember(ParserNode_I nodeIndex);
int Analyze_DefList_Variable(ParserNode_I nodeIndex);
int Analyze_Def_StructMember(ParserNode_I nodeIndex);
int Analyze_Def_Variable(ParserNode_I nodeIndex);
int Analyze_DecList_Variable(ParserNode_I nodeIndex);
int Analyze_DecList_StructMember(ParserNode_I nodeIndex);
int Analyze_Dec_Variable(ParserNode_I nodeIndex);
int Analyze_Dec_StructMember(ParserNode_I nodeIndex);

int Analyze_Exp(ParserNode_I nodeIndex);
int Analyze_Args(ParserNode_I nodeIndex);

////////////////////////////////////////
// Inheritance Property
////////////////////////////////////////

/**
 * Set the current function info.
 * Will auto try to define the function's parameters as variables.
 * and start return checking.
 * if function Info is NULL, will clear the current function info.
 * @param functionInfo
 */
void Analyze_pushCurrentFunctionInfo(SymbolInfo_Function_t functionInfo){
    currentFunctionInfo = functionInfo;
}

void Analyze_popCurrentFunctionInfo(){
    currentFunctionInfo = NULL;
}

/**
 * Get the current function info.
 * @return the current function info.
 */
SymbolInfo_Function_t Analyze_getCurrentFunctionInfo(){
    return currentFunctionInfo;
}

/**
 * push the current struct info into the stack.
 * will turn DefList's default definition behavior to struct member definition rather than variable definition.
 * if struct Info stack is empty, will turn DefList's default definition behavior to variable definition.
 * @param structInfo
 */
void Analyze_pushCurrentStructInfo(SymbolInfo_Struct_t structInfo){
    SimpleArray_pushBack(currentStructInfoStack, &structInfo);
}

/**
 * pop the current struct info from the stack.
 * will turn DefList's default definition behavior to variable definition.
 * if struct Info stack is empty, will turn DefList's default definition behavior to variable definition.
 */
void Analyze_popCurrentStructInfo(){
    SimpleArray_popBack(currentStructInfoStack, NULL);
}

/**
 * Get the current struct info.
 * @return the current struct info, NULL if stack is empty.
 */
SymbolInfo_Struct_t Analyze_getCurrentStructInfo(){
    if(currentStructInfoStack->num == 0){
        return NULL;
    }
    else
    {
        return *((SymbolInfo_Struct_t*)SimpleArray_back(currentStructInfoStack));
    }
}

/**
 * Set the current type info, affect the VarDec's behavior.
 * @param type the current type.
 * @param typeMeta the current type meta.
 */
void Analyze_pushCurrentTypeInfo(Symbol_Value_Type type, SymbolInfo_t typeMeta){
    SimpleArray_pushBack(currentType, &type);
    SimpleArray_pushBack(currentTypeMeta, &typeMeta);
}

/**
 * Pop the current type info.
 */
void Analyze_popCurrentTypeInfo(){
    SimpleArray_popBack(currentType,NULL);
    SimpleArray_popBack(currentTypeMeta, NULL);
}

/**
 * Get the current type info.
 * @param type the current type.
 * @param typeMeta the current type meta.
 */
void Analyze_getCurrentTypeInfo(Symbol_Value_Type *type, SymbolInfo_t *typeMeta){
    *type = *((Symbol_Value_Type*)SimpleArray_back(currentType));
    *typeMeta = *((SymbolInfo_t*)SimpleArray_back(currentTypeMeta));
}

void Analyze_pushCurrentVarName(char* varName){
    currentVarName = varName;
}

void Analyze_popCurrentVarName(){
    currentVarName = NULL;
}

char* Analyze_getCurrentVarName(){
    return currentVarName;
}

void Analyze_pushCurrentDimension(int dimension){
    currentDimensions[currentDimensionCount++] = dimension;
}

void Analyze_clearCurrentDimension(){
    currentDimensionCount = 0;
}

int Analyze_getCurrentDimensionCount(){
    return currentDimensionCount;
}

int* Analyze_getCurrentDimensions(){
    return currentDimensions;
}

/**
 * Helper function to destroy the anonymous struct.
 * @param structInfoToDestroy
 */
void Analyze_Helper_DestructorForAnonymousStruct(void* structInfoToDestroy)
{
    SymbolInfo_Struct_t structInfo = *((SymbolInfo_Struct_t*)structInfoToDestroy);
    SymbolInfo_Struct_destroy(structInfo);
}

////////////////////////////////////////
// Helper
////////////////////////////////////////

/**
 * Check if the children of a node match a rule.
 * @param nodeIndex The index of the node.
 * @param rule The rule to match, a list of token.
 * @param ruleSize The size of the rule.
 */
int isChildrenMatchRule(ParserNode_I nodeIndex, int ruleSize, ...);

void Analyze_Helper_operatorTwoParameters(ParserNode_I nodeIndex, ParserNode_t node);

void Analyze_Helper_logicTwoParameters(ParserNode_I nodeIndex, ParserNode_t node);

////////////////////////////////////////
// Implementation
////////////////////////////////////////

void Analyze_HandleFunctionDefintion(ParserNode_I nodeIndex);

void Analyze_HandleFunctionDeclaration(ParserNode_I nodeIndex);

int semanticAnalyze(ParserNode_I rootNodeIndex) {
    semanticErrors = 0;
    symbolTable = SymbolTable_create();
    semanticInfoList = SimpleArray_create(sizeof(SemanticInfo_t));
    anonymousStructList = SimpleArray_create(sizeof(SymbolInfo_Struct_t));
    currentStructInfoStack = SimpleArray_create(sizeof(SymbolInfo_Struct_t));
    currentType = SimpleArray_create(sizeof(Symbol_Value_Type));
    currentTypeMeta = SimpleArray_create(sizeof(SymbolInfo_t));
    functionForwardDeclarationList = SimpleArray_create(sizeof(SymbolInfo_Function_t));
    Analyze_Program(rootNodeIndex);
    if(functionForwardDeclarationList->num!=0)
    {
        for(int i = 0; i < functionForwardDeclarationList->num; i++)
        {
            SymbolInfo_Function_t functionInfo = *((SymbolInfo_Function_t*)SimpleArray_at(functionForwardDeclarationList, i));
            reportErrorFormat(functionInfo->firstDeclaredLine, UndefinedExternalFunction, "Function \"%s\" declared but not defined", functionInfo->functionName);
        }
    }
    return semanticErrors;
}

void semanticAnalyze_End(){
    SymbolTable_destroy(symbolTable);
    SimpleArray_destroy(semanticInfoList, SemanticInfo_destroy);
    SimpleArray_destroy(anonymousStructList, Analyze_Helper_DestructorForAnonymousStruct);
    SimpleArray_destroy(currentStructInfoStack, NULL);
    SimpleArray_destroy(currentType, NULL);
    SimpleArray_destroy(currentTypeMeta, NULL);
    SimpleArray_destroy(functionForwardDeclarationList, NULL);
}

SymbolTable_t semanticAnalyze_getSymbolTable() {
    return symbolTable;
}

int Analyze_Program(ParserNode_I nodeIndex){
    if(isChildrenMatchRule(nodeIndex, 1, EXT_DEF_LIST)){
        Analyze_ExtDefList(GET_CHILD(nodeIndex, 0));
    }
    return 0;
}
int Analyze_ExtDefList(ParserNode_I nodeIndex){
    if(isChildrenMatchRule(nodeIndex, 2, EXT_DEF, EXT_DEF_LIST)){
        Analyze_ExtDef(GET_CHILD(nodeIndex, 0));
        Analyze_ExtDefList(GET_CHILD(nodeIndex, 1));
    }
    else if(isChildrenMatchRule(nodeIndex, 0)){

    }
    return 0;
}
int Analyze_ExtDef(ParserNode_I nodeIndex){
    if(isChildrenMatchRule(nodeIndex, 3, SPECIFIER, EXT_DEC_LIST, SEMI)){
        Analyze_Specifier(GET_CHILD(nodeIndex, 0));
        Analyze_ExtDecList(GET_CHILD(nodeIndex, 1));
    }
    else if(isChildrenMatchRule(nodeIndex, 2, SPECIFIER, SEMI)){
        Analyze_Specifier(GET_CHILD(nodeIndex, 0));
    }
    else if(isChildrenMatchRule(nodeIndex, 3, SPECIFIER, FUN_DEC, COMP_STM)){
        Analyze_HandleFunctionDefintion(nodeIndex);

    }
    else if(isChildrenMatchRule(nodeIndex, 3, SPECIFIER, FUN_DEC, SEMI)){

        Analyze_HandleFunctionDeclaration(nodeIndex);
    }
    return 0;
}

void Analyze_HandleFunctionDefintion(ParserNode_I nodeIndex) {
    Analyze_Specifier(GET_CHILD(nodeIndex, 0));
    Symbol_Value_Type returnType = GET_SEMANTIC_INFO(GET_CHILD(nodeIndex, 0))->valueType;
    SymbolInfo_t returnMeta = GET_SEMANTIC_INFO(GET_CHILD(nodeIndex, 0))->valueInfo;

    Analyze_FunDec(GET_CHILD(nodeIndex, 1));
    SymbolInfo_Function_t functionInfo = Analyze_getCurrentFunctionInfo();
    functionInfo->returnType = returnType;
    functionInfo->returnTypeMeta = returnMeta;

    // Set to a valid offset to tell the function is defined
    functionInfo->offset = 1;

    // check if the function is defined & forward declaration check
    // use var name to store the function name

    char* functionName = Analyze_getCurrentVarName();
    SymbolRecord_t record;
    SymbolDefineStatus defineStatus = SymbolTable_lookupRecord(symbolTable, functionName, &record);
    // to tell us if we should destroy the current function info
    int currentFunctionValid = 1;
    if(defineStatus == SDS_Defined)
    {
        reportErrorFormat(GET_NODE(nodeIndex)->lineNum, FunctionRedefinition, "Function \"%s\" redefined", functionName);
        currentFunctionValid = 0;
    }
    else if(defineStatus == SDS_Declared){
        if(!SymbolInfo_Function_isReturnTypeMatched(record->info, functionInfo)){
            reportErrorFormat(GET_NODE(nodeIndex)->lineNum, ImplicitFunctionDeclaration, "Function \"%s\" redefined with different return type", functionName);
            currentFunctionValid = 0;
        }
        else if(!SymbolInfo_Function_isParameterListMatched(record->info, functionInfo)){
            reportErrorFormat(GET_NODE(nodeIndex)->lineNum, ImplicitFunctionDeclaration, "Function \"%s\" redefined with different parameter list", functionName);
            currentFunctionValid = 0;
        }
        else{
            SymbolInfo_Function_t existedFuncInfo = record->info;
            existedFuncInfo->offset = 1;
            // remove the undefined forward declaration
            for(int i = 0; i < functionForwardDeclarationList->num; i++)
            {
                SymbolInfo_Function_t forwardFunction = *((SymbolInfo_Function_t*)SimpleArray_at(functionForwardDeclarationList, i));
                // same memory address, remove the forward declaration
                if(existedFuncInfo == forwardFunction)
                {
                    SimpleArray_removeElement(functionForwardDeclarationList, i, NULL);
                    break;
                }
            }
            // destroy the current function info and replace it with the existed one
            SymbolInfo_Function_destroy(functionInfo);
            functionInfo = existedFuncInfo;
        }
    }
    else{
        functionInfo->firstDeclaredLine = GET_NODE(nodeIndex)->lineNum;
        functionInfo->offset = 1;
        SymbolRecord outRecord;
        SymbolTable_createFunctionByInfo(symbolTable, &outRecord, functionInfo);
        SymbolTable_insertRecord(symbolTable, functionName, &outRecord);
    }

    //before we enter the function, pop the current variable name(function name)
    Analyze_popCurrentVarName();

        Analyze_pushCurrentFunctionInfo(functionInfo);
            SymbolTable_enterScope(symbolTable);

                for(int i = 0; i < functionInfo->parameterCount; i++){
                    SymbolInfo_Parameter_t parameter = functionInfo->parameters[i];

                    SymbolRecord parameterRecord;
                    SymbolInfo_Variable_t info = SymbolInfo_Variable_createBaked(parameter->parameterType,
                                                                                 parameter->parameterMeta);
                    (&parameterRecord)->type = ST_Variable;
                    (&parameterRecord)->info = info;

                    SymbolTable_insertRecord(symbolTable, parameter->parameterName, &parameterRecord);
                }

                // truly analyze CompSt with current function info

                Analyze_CompSt(GET_CHILD(nodeIndex, 2));

                // End of the function

            SymbolTable_leaveScope(symbolTable);
        Analyze_popCurrentFunctionInfo();

    // this will be set to 0 if the function's return type is not matched
    if(!currentFunctionValid)
    {
        SymbolInfo_Function_destroy(functionInfo);
    }
}

void Analyze_HandleFunctionDeclaration(ParserNode_I nodeIndex) {
    Analyze_Specifier(GET_CHILD(nodeIndex, 0));
    Symbol_Value_Type returnType = GET_SEMANTIC_INFO(GET_CHILD(nodeIndex, 0))->valueType;
    SymbolInfo_t returnMeta = GET_SEMANTIC_INFO(GET_CHILD(nodeIndex, 0))->valueInfo;

    Analyze_FunDec(GET_CHILD(nodeIndex, 1));
    SymbolInfo_Function_t functionInfo = Analyze_getCurrentFunctionInfo();
    Analyze_popCurrentFunctionInfo();
    functionInfo->returnType = returnType;
    functionInfo->returnTypeMeta = returnMeta;

    // set to INVALID_OFFSET to tell the function is not defined
    functionInfo->offset = INVALID_OFFSET;

    char* functionName = Analyze_getCurrentVarName();
    SymbolRecord_t record;
    SymbolDefineStatus defineStatus = SymbolTable_lookupRecord(symbolTable, functionName, &record);
    if(defineStatus >= SDS_Declared)
    {
        if(!SymbolInfo_Function_isReturnTypeMatched(record->info, functionInfo)){
            reportErrorFormat(GET_NODE(nodeIndex)->lineNum, ImplicitFunctionDeclaration, "Function \"%s\" redefined with different return type", functionName);
            SymbolInfo_Function_destroy(functionInfo);
        }
        else if(!SymbolInfo_Function_isParameterListMatched(record->info, functionInfo)){
            reportErrorFormat(GET_NODE(nodeIndex)->lineNum, ImplicitFunctionDeclaration, "Function \"%s\" redefined with different parameter list", functionName);
            SymbolInfo_Function_destroy(functionInfo);
        }
        else{
            SymbolRecord outRecord;
            SymbolTable_createFunctionByInfo(symbolTable, &outRecord, functionInfo);
            SymbolTable_insertRecord(symbolTable, functionName, &outRecord);
        }
    }
    else{
        functionInfo->firstDeclaredLine = GET_NODE(nodeIndex)->lineNum;
        SimpleArray_pushBack(functionForwardDeclarationList, &functionInfo);
        SymbolRecord outRecord;
        SymbolTable_createFunctionByInfo(symbolTable, &outRecord, functionInfo);
        SymbolTable_insertRecord(symbolTable, functionName, &outRecord);
    }

}

int Analyze_ExtDecList(ParserNode_I nodeIndex){
    if(isChildrenMatchRule(nodeIndex, 1, VAR_DEC)){
        Analyze_VarDec(GET_CHILD(nodeIndex, 0));
        if(GET_SEMANTIC_INFO(GET_CHILD(nodeIndex, 0))->valueType != SVT_Void) {
            char* varName = Analyze_getCurrentVarName();
            SymbolRecord record;
            SymbolTable_createVariableByInfo(symbolTable, &record, GET_SEMANTIC_INFO(GET_CHILD(nodeIndex, 0))->valueInfo);
            SymbolTable_insertRecord(symbolTable, varName, &record);
        }
        Analyze_popCurrentVarName();
    }
    else if(isChildrenMatchRule(nodeIndex, 3, VAR_DEC, COMMA, EXT_DEC_LIST)){
        Analyze_VarDec(GET_CHILD(nodeIndex, 0));
        if(GET_SEMANTIC_INFO(GET_CHILD(nodeIndex, 0))->valueType != SVT_Void) {
            char* varName = Analyze_getCurrentVarName();
            SymbolRecord record;
            SymbolTable_createVariableByInfo(symbolTable, &record, GET_SEMANTIC_INFO(GET_CHILD(nodeIndex, 0))->valueInfo);
            SymbolTable_insertRecord(symbolTable, varName, &record);
        }
        Analyze_popCurrentVarName();
        Analyze_ExtDecList(GET_CHILD(nodeIndex, 2));

    }
    return 0;
}

int Analyze_Specifier(ParserNode_I nodeIndex){
    if(isChildrenMatchRule(nodeIndex, 1, TYPE)){
        char* typeName = GET_NODE(GET_CHILD(nodeIndex, 0))->ID;
        if(strcmp(typeName, "int") == 0){
            GET_NODE(nodeIndex)->semanticInfo = SemanticInfo_createRvalue(SVT_Int, NULL, semanticInfoList);
        }
        else if(strcmp(typeName, "float") == 0){
            GET_NODE(nodeIndex)->semanticInfo = SemanticInfo_createRvalue(SVT_Float, NULL, semanticInfoList);
        }
    }
    else if(isChildrenMatchRule(nodeIndex, 1, STRUCT_SPECIFIER)){
        Analyze_StructSpecifier(GET_CHILD(nodeIndex, 0));
        GET_NODE(nodeIndex)->semanticInfo = GET_NODE(GET_CHILD(nodeIndex, 0))->semanticInfo;
    }
    return 0;
}
int Analyze_StructSpecifier(ParserNode_I nodeIndex){
    if(isChildrenMatchRule(nodeIndex, 2, STRUCT, TAG)){
        Analyze_Tag(GET_CHILD(nodeIndex, 1));
        SymbolRecord_t record;
        char* structName = GET_CHILD_NODE(nodeIndex, 1)->ID;
        SymbolDefineStatus defineStatus = SymbolTable_lookupRecord(symbolTable, structName, &record);
        if(defineStatus == SDS_Undefined){
            reportErrorFormat(GET_NODE(nodeIndex)->lineNum, UndefinedStruct, "Struct name \"%s\" undefined", structName);
            // to continue the analysis, we will define the struct as an empty struct
            SymbolInfo_Struct_t structInfo = SymbolInfo_Struct_createBaked(NULL, NULL, NULL, 0);
            SimpleArray_pushBack(anonymousStructList, &structInfo);
            GET_NODE(nodeIndex)->semanticInfo = SemanticInfo_createRvalue(SVT_Struct, structInfo, semanticInfoList);
        }
        else if(record->type!=ST_Struct){
            reportErrorFormat(GET_NODE(nodeIndex)->lineNum, ConflictStructDefinition, "Name \"%s\" is defined as Function or Variable", structName);
            // to continue the analysis, we will define the struct as an empty struct
            SymbolInfo_Struct_t structInfo = SymbolInfo_Struct_createBaked(NULL, NULL, NULL, 0);
            SimpleArray_pushBack(anonymousStructList, &structInfo);
            GET_NODE(nodeIndex)->semanticInfo = SemanticInfo_createRvalue(SVT_Struct, structInfo, semanticInfoList);
        }
        else{
            GET_NODE(nodeIndex)->semanticInfo = SemanticInfo_createRvalue(SVT_Struct, record->info, semanticInfoList);
        }
    }
    else if(isChildrenMatchRule(nodeIndex, 5, STRUCT, OPT_TAG, LC, DEF_LIST, RC)){
        Analyze_OptTag(GET_CHILD(nodeIndex, 1));
        // Before we try to define the non-anonymous struct, we check if the struct name is already defined
        char* structName = GET_CHILD_NODE(nodeIndex, 1)->ID;
        int isStructAnonymous = structName == NULL;
        if(!isStructAnonymous) {
            SymbolRecord_t record;
            SymbolDefineStatus defineStatus = SymbolTable_lookupRecord(symbolTable, structName, &record);
            if(defineStatus == SDS_Defined){
                // Conflict Name, create an empty anonymous struct to continue the analysis
                reportErrorFormat(GET_NODE(nodeIndex)->lineNum, ConflictStructDefinition, "Struct name \"%s\" redefined", structName);
                SymbolInfo_Struct_t structInfo = SymbolInfo_Struct_createBaked(NULL, NULL, NULL, 0);
                SimpleArray_pushBack(anonymousStructList, &structInfo);
                GET_NODE(nodeIndex)->semanticInfo = SemanticInfo_createRvalue(SVT_Struct, structInfo, semanticInfoList);
                return 1;
            }
        }
        // Create an anonymous struct
        SymbolInfo_Struct_t structInfo = SymbolInfo_Struct_createBaked(NULL, NULL, NULL, 0);
        Analyze_pushCurrentStructInfo(structInfo);
        // When we are analyzing DefList, this struct info will be filled with members(or not);
        Analyze_DefList(GET_CHILD(nodeIndex, 3));
        Analyze_popCurrentStructInfo();
        // If the struct is not anonymous, we will try to define it in the symbol table
        if(!isStructAnonymous) {
            SymbolRecord outRecord;
            SymbolTable_createStructByInfo(symbolTable, &outRecord, structInfo);
            SymbolTable_insertRecord(symbolTable, structName, &outRecord);
        }
        else{
            // If the struct is anonymous, we will store it in the anonymous struct list so that we can destroy it later
            SimpleArray_pushBack(anonymousStructList, &structInfo);
        }
        GET_NODE(nodeIndex)->semanticInfo = SemanticInfo_createRvalue(SVT_Struct, structInfo, semanticInfoList);
    }
    return 0;
}
int Analyze_OptTag(ParserNode_I nodeIndex){
    if(isChildrenMatchRule(nodeIndex, 1, ID)){
        GET_NODE(nodeIndex)->ID = GET_CHILD_NODE(nodeIndex, 0)->ID;
    }
    else if(isChildrenMatchRule(nodeIndex, 0)){
        GET_NODE(nodeIndex)->ID = NULL;
    }
    return 0;
}
int Analyze_Tag(ParserNode_I nodeIndex){
    if(isChildrenMatchRule(nodeIndex, 1, ID)){
        GET_NODE(nodeIndex)->ID = GET_CHILD_NODE(nodeIndex, 0)->ID;
    }
    return 0;
}

int Analyze_VarDec(ParserNode_I nodeIndex){
    if(isChildrenMatchRule(nodeIndex, 1, ID)){
        Analyze_pushCurrentVarName(GET_NODE(GET_CHILD(nodeIndex, 0))->ID);
    }
    else if(isChildrenMatchRule(nodeIndex, 4, VAR_DEC, LB, INT, RB)){
        Analyze_VarDec(GET_CHILD(nodeIndex, 0));
        Analyze_pushCurrentDimension(GET_NODE(GET_CHILD(nodeIndex, 2))->intVal);
    }
    return 0;
}

int Analyze_FunDec(ParserNode_I nodeIndex){
    if(isChildrenMatchRule(nodeIndex, 3, ID, LP, RP)){
        char* functionName = GET_NODE(GET_CHILD(nodeIndex, 0))->ID;
        SymbolInfo_Function_t functionInfo = SymbolInfo_Function_createBaked(SVT_Void, NULL, NULL, NULL, NULL, 0);
        // transfer the function name to the above level
        Analyze_pushCurrentVarName(functionName);
        Analyze_pushCurrentFunctionInfo(functionInfo);
    }
    else if(isChildrenMatchRule(nodeIndex, 4, ID, LP, VAR_LIST, RP)){
        SymbolInfo_Function_t functionInfo = SymbolInfo_Function_createBaked(SVT_Void, NULL, NULL, NULL, NULL, 0);
        Analyze_pushCurrentFunctionInfo(functionInfo);
        Analyze_VarList(GET_CHILD(nodeIndex, 2));
        char* functionName = GET_NODE(GET_CHILD(nodeIndex, 0))->ID;
        Analyze_pushCurrentVarName(functionName);
    }
    return 0;
}
int Analyze_VarList(ParserNode_I nodeIndex){
    if(isChildrenMatchRule(nodeIndex, 1, PARAM_DEC)){
        Analyze_ParamDec(GET_CHILD(nodeIndex, 0));
        SymbolInfo_Parameter_t parameter = GET_SEMANTIC_INFO(GET_CHILD(nodeIndex, 0))->valueInfo;
        SymbolInfo_Function_t functionInfo = Analyze_getCurrentFunctionInfo();
        if(parameter!=NULL){
            SymbolInfo_Function_addParameter(functionInfo, parameter);
        }
    }
    else if(isChildrenMatchRule(nodeIndex, 3, PARAM_DEC, COMMA, VAR_LIST)){
        Analyze_ParamDec(GET_CHILD(nodeIndex, 0));
        SymbolInfo_Parameter_t parameter = GET_SEMANTIC_INFO(GET_CHILD(nodeIndex, 0))->valueInfo;
        SymbolInfo_Function_t functionInfo = Analyze_getCurrentFunctionInfo();
        if(parameter!=NULL){
            SymbolInfo_Function_addParameter(functionInfo, parameter);
        }
        Analyze_VarList(GET_CHILD(nodeIndex, 2));
    }
    return 0;
}
int Analyze_ParamDec(ParserNode_I nodeIndex){
    if(isChildrenMatchRule(nodeIndex, 2, SPECIFIER, VAR_DEC)){
        Analyze_Specifier(GET_CHILD(nodeIndex, 0));
        Analyze_pushCurrentTypeInfo(GET_SEMANTIC_INFO(GET_CHILD(nodeIndex, 0))->valueType,
                                    GET_SEMANTIC_INFO(GET_CHILD(nodeIndex, 0))->valueInfo);
        Analyze_VarDec(GET_CHILD(nodeIndex, 1));
        Analyze_popCurrentTypeInfo();
        SymbolInfo_Function_t functionInfo = Analyze_getCurrentFunctionInfo();
        Symbol_Value_Type type = GET_SEMANTIC_INFO(GET_CHILD(nodeIndex, 0))->valueType;
        SymbolInfo_t typeMeta = GET_SEMANTIC_INFO(GET_CHILD(nodeIndex, 0))->valueInfo;
        char* varName = Analyze_getCurrentVarName();
        int *dimensions = Analyze_getCurrentDimensions();
        int dimensionCount = Analyze_getCurrentDimensionCount();
        if(SymbolInfo_Function_hasParameterName(functionInfo, varName)){
            reportErrorFormat(GET_NODE(nodeIndex)->lineNum, VariableNameRedefinition, "parameter \"%s\" redefined", varName);
            GET_NODE(nodeIndex)->semanticInfo = SemanticInfo_createRvalue(SVT_Void, NULL, semanticInfoList);
        }
        else{
            if(dimensionCount == 0){
                SymbolInfo_Parameter_t parameter = SymbolInfo_Parameter_createBaked(type, varName, typeMeta);
                GET_NODE(nodeIndex)->semanticInfo = SemanticInfo_createRvalue(SVT_Int, parameter, semanticInfoList);
            }
            else {
                SymbolInfo_Array_t arrayInfo = SymbolInfo_Array_createBaked(type, typeMeta, dimensions, dimensionCount);
                SymbolInfo_Parameter_t parameter = SymbolInfo_Parameter_createBaked(SVT_Array, varName, arrayInfo);
                GET_NODE(nodeIndex)->semanticInfo = SemanticInfo_createRvalue(SVT_Int, parameter, semanticInfoList);
                Analyze_clearCurrentDimension();
            }
        }
        Analyze_popCurrentVarName();
    }
    return 0;
}

int Analyze_CompSt(ParserNode_I nodeIndex){
    // no need to analyze the COMP_STM
    if(isChildrenMatchRule(nodeIndex, 4, LC, DEF_LIST, STMT_LIST, RC)){
        Analyze_DefList_Variable(GET_CHILD(nodeIndex, 1));
        Analyze_StmtList(GET_CHILD(nodeIndex, 2));
        // use intVal to store current scope for intercode generation
        GET_NODE(nodeIndex)->intVal = SymbolTable_getScope(symbolTable);
    }
    return 0;
}
int Analyze_StmtList(ParserNode_I nodeIndex){
    // no need to analyze the STMT_LIST, just analyze the STMT in the list
    if(isChildrenMatchRule(nodeIndex, 2, STMT, STMT_LIST)){
        Analyze_Stmt(GET_CHILD(nodeIndex, 0));
        Analyze_StmtList(GET_CHILD(nodeIndex, 1));
    }
    else if(isChildrenMatchRule(nodeIndex, 0)){

    }
    return 0;
}
int Analyze_Stmt(ParserNode_I nodeIndex){
    if(isChildrenMatchRule(nodeIndex, 2, EXP, SEMI)){
        Analyze_Exp(GET_CHILD(nodeIndex, 0));
        // no need to analyze this type of STMT, just check the type of the EXP
    }
    else if(isChildrenMatchRule(nodeIndex, 1, COMP_STM)){
        SymbolTable_enterScope(symbolTable);
        Analyze_CompSt(GET_CHILD(nodeIndex, 0));
        SymbolTable_leaveScope(symbolTable);
    }
    else if(isChildrenMatchRule(nodeIndex, 3, RETURN, EXP, SEMI)){
        Analyze_Exp(GET_CHILD(nodeIndex, 1));
        SymbolInfo_Function_t funcInfo = Analyze_getCurrentFunctionInfo();
        if(!SemanticInfo_checkReturnType(funcInfo, GET_SEMANTIC_INFO(GET_CHILD(nodeIndex, 1)))){
            reportErrorFormat(GET_NODE(nodeIndex)->lineNum, ReturnTypeMismatch, "Return type mismatch");
        }
    }
    else if(isChildrenMatchRule(nodeIndex, 5, IF, LP, EXP, RP, STMT)){
        Analyze_Exp(GET_CHILD(nodeIndex, 2));
        Analyze_Stmt(GET_CHILD(nodeIndex, 4));
        if(!SemanticInfo_checkValueType(GET_SEMANTIC_INFO(GET_CHILD(nodeIndex, 2)), SVT_Int)){
            reportErrorFormat(GET_NODE(nodeIndex)->lineNum, OperatorTypeMismatch, "Only int can be used in if condition");
        }
    }
    else if(isChildrenMatchRule(nodeIndex, 7, IF, LP, EXP, RP, STMT, ELSE, STMT)){
        Analyze_Exp(GET_CHILD(nodeIndex, 2));
        Analyze_Stmt(GET_CHILD(nodeIndex, 4));
        Analyze_Stmt(GET_CHILD(nodeIndex, 6));
        if(!SemanticInfo_checkValueType(GET_SEMANTIC_INFO(GET_CHILD(nodeIndex, 2)), SVT_Int)){
            reportErrorFormat(GET_NODE(nodeIndex)->lineNum, OperatorTypeMismatch, "Only int can be used in if condition");
        }
    }
    else if(isChildrenMatchRule(nodeIndex, 5, WHILE, LP, EXP, RP, STMT)){
        Analyze_Exp(GET_CHILD(nodeIndex, 2));
        Analyze_Stmt(GET_CHILD(nodeIndex, 4));
        if(!SemanticInfo_checkValueType(GET_SEMANTIC_INFO(GET_CHILD(nodeIndex, 2)), SVT_Int)){
            reportErrorFormat(GET_NODE(nodeIndex)->lineNum, OperatorTypeMismatch, "Only int can be used in while condition");
        }
    }
    return 0;
}

int Analyze_DefList(ParserNode_I nodeIndex){
    if(Analyze_getCurrentStructInfo() != NULL){
        Analyze_DefList_StructMember(nodeIndex);
    }
    else{
        Analyze_DefList_Variable(nodeIndex);
    }
    return 0;
}
int Analyze_DefList_Variable(ParserNode_I nodeIndex){
    if(isChildrenMatchRule(nodeIndex, 2, DEF, DEF_LIST)){
        Analyze_Def_Variable(GET_CHILD(nodeIndex, 0));
        Analyze_DefList_Variable(GET_CHILD(nodeIndex, 1));
    }
    else if(isChildrenMatchRule(nodeIndex, 0)){
    }
    return 0;
}

int Analyze_Def_Variable(ParserNode_I nodeIndex){
    if(isChildrenMatchRule(nodeIndex, 3, SPECIFIER, DEC_LIST, SEMI)){
        Analyze_Specifier(GET_CHILD(nodeIndex, 0));
        Analyze_pushCurrentTypeInfo(GET_SEMANTIC_INFO(GET_CHILD(nodeIndex, 0))->valueType,
                                    GET_SEMANTIC_INFO(GET_CHILD(nodeIndex, 0))->valueInfo);
        Analyze_DecList_Variable(GET_CHILD(nodeIndex, 1));
        Analyze_popCurrentTypeInfo();
    }
    return 0;
}

int Analyze_DecList_Variable(ParserNode_I nodeIndex){
    if(isChildrenMatchRule(nodeIndex, 1, DEC)){
        Analyze_Dec_Variable(GET_CHILD(nodeIndex, 0));
        if(GET_SEMANTIC_INFO(GET_CHILD(nodeIndex, 0))->valueType != SVT_Void) {
            char* varName = Analyze_getCurrentVarName();
            SymbolRecord record;
            SymbolTable_createVariableByInfo(symbolTable, &record, GET_SEMANTIC_INFO(GET_CHILD(nodeIndex, 0))->valueInfo);
            SymbolTable_insertRecord(symbolTable, varName, &record);
        }
        Analyze_popCurrentVarName();
    }
    else if(isChildrenMatchRule(nodeIndex, 3, DEC, COMMA, DEC_LIST)){
        Analyze_Dec_Variable(GET_CHILD(nodeIndex, 0));

        if(GET_SEMANTIC_INFO(GET_CHILD(nodeIndex, 0))->valueType != SVT_Void) {
            char* varName = Analyze_getCurrentVarName();
            SymbolRecord record;
            SymbolTable_createVariableByInfo(symbolTable, &record, GET_SEMANTIC_INFO(GET_CHILD(nodeIndex, 0))->valueInfo);
            SymbolTable_insertRecord(symbolTable, varName, &record);
        }
        Analyze_popCurrentVarName();
        Analyze_DecList_Variable(GET_CHILD(nodeIndex, 2));
    }
    return 0;
}

int Analyze_Dec_Variable(ParserNode_I nodeIndex){
    // get inheritance property
    Symbol_Value_Type type;
    SymbolInfo_t typeMeta;
    Analyze_getCurrentTypeInfo(&type, &typeMeta);

    if(isChildrenMatchRule(nodeIndex, 1, VAR_DEC)){
        Analyze_VarDec(GET_CHILD(nodeIndex, 0));
        char* varName = Analyze_getCurrentVarName();
        int *dimensions = Analyze_getCurrentDimensions();
        int dimensionCount = Analyze_getCurrentDimensionCount();
        SymbolRecord_t record;
        SymbolDefineStatus defineStatus = SymbolTable_lookupRecord(symbolTable, varName, &record);
        if(defineStatus > SDS_ExternalDefined){
            reportErrorFormat(GET_NODE(nodeIndex)->lineNum, VariableNameRedefinition, "Variable \"%s\" redefined", varName);
            GET_NODE(nodeIndex)->semanticInfo = SemanticInfo_createRvalue(SVT_Void, NULL, semanticInfoList);
        }
        else{
            if(dimensionCount == 0){
                SymbolInfo_Variable_t variable = SymbolInfo_Variable_createBaked(type,typeMeta);
                GET_NODE(nodeIndex)->semanticInfo = SemanticInfo_createRvalue(SVT_Int, variable, semanticInfoList);
            }
            else {
                SymbolInfo_Array_t arrayInfo = SymbolInfo_Array_createBaked(type, typeMeta, dimensions, dimensionCount);
                SymbolInfo_Variable_t variable = SymbolInfo_Variable_createBaked(SVT_Array, arrayInfo);
                GET_NODE(nodeIndex)->semanticInfo = SemanticInfo_createRvalue(SVT_Int, variable, semanticInfoList);
                Analyze_clearCurrentDimension();
            }
        }
    }
    else if(isChildrenMatchRule(nodeIndex, 3, VAR_DEC, ASSIGNOP, EXP)){
        Analyze_VarDec(GET_CHILD(nodeIndex, 0));
        char* varName = Analyze_getCurrentVarName();
        int *dimensions = Analyze_getCurrentDimensions();
        int dimensionCount = Analyze_getCurrentDimensionCount();
        Analyze_Exp(GET_CHILD(nodeIndex, 2));

        SymbolRecord_t record;
        SymbolDefineStatus defineStatus = SymbolTable_lookupRecord(symbolTable, varName, &record);
        if(defineStatus > SDS_ExternalDefined){
            reportErrorFormat(GET_NODE(nodeIndex)->lineNum, VariableNameRedefinition, "Variable \"%s\" redefined", varName);
            GET_NODE(nodeIndex)->semanticInfo = SemanticInfo_createRvalue(SVT_Void, NULL, semanticInfoList);
        }
        else{
            SymbolInfo_Variable_t variable;
            if(dimensionCount == 0){
                variable = SymbolInfo_Variable_createBaked(type,typeMeta);
                GET_NODE(nodeIndex)->semanticInfo = SemanticInfo_createRvalue(SVT_Int, variable, semanticInfoList);
            }
            else {
                SymbolInfo_Array_t arrayInfo = SymbolInfo_Array_createBaked(type, typeMeta, dimensions, dimensionCount);
                variable = SymbolInfo_Variable_createBaked(SVT_Array, arrayInfo);
                GET_NODE(nodeIndex)->semanticInfo = SemanticInfo_createRvalue(SVT_Int, variable, semanticInfoList);
                Analyze_clearCurrentDimension();
            }
            if(!SymbolInfo_Helper_isTypeMatched(variable->type, variable->meta,
                                                 GET_SEMANTIC_INFO(GET_CHILD(nodeIndex, 2))->valueType,
                                                 GET_SEMANTIC_INFO(GET_CHILD(nodeIndex, 2))->valueInfo)){
                reportErrorFormat(GET_NODE(nodeIndex)->lineNum, AssignmentTypeMismatch, "Assignment type mismatch");
                if(GET_SEMANTIC_INFO(nodeIndex)->valueType == SVT_Array){
                    SymbolInfo_Array_destroy(variable->meta);
                }
                GET_SEMANTIC_INFO(nodeIndex)->valueType = SVT_Void;
                GET_SEMANTIC_INFO(nodeIndex)->valueInfo = NULL;
            }

        }
    }
    return 0;
}

int Analyze_DecList_StructMember(ParserNode_I nodeIndex){
    if(isChildrenMatchRule(nodeIndex, 1, DEC)){
        Analyze_Dec_StructMember(GET_CHILD(nodeIndex, 0));
        // insert valid member into the struct
        if(GET_SEMANTIC_INFO(GET_CHILD(nodeIndex, 0))->valueInfo != NULL) {
            SymbolInfo_Struct_insertMember(Analyze_getCurrentStructInfo(),
                                           GET_SEMANTIC_INFO(GET_CHILD(nodeIndex, 0))->valueInfo);
        }
    }
    else if(isChildrenMatchRule(nodeIndex, 3, DEC, COMMA, DEC_LIST)){
        Analyze_Dec_StructMember(GET_CHILD(nodeIndex, 0));
        // insert valid member into the struct
        if(GET_SEMANTIC_INFO(GET_CHILD(nodeIndex, 0))->valueInfo != NULL) {
            SymbolInfo_Struct_insertMember(Analyze_getCurrentStructInfo(),
                                           GET_SEMANTIC_INFO(GET_CHILD(nodeIndex, 0))->valueInfo);
        }
        Analyze_DecList_StructMember(GET_CHILD(nodeIndex, 2));
    }
    return 0;
}

int Analyze_DefList_StructMember(ParserNode_I nodeIndex){
    if(isChildrenMatchRule(nodeIndex, 2, DEF, DEF_LIST)){
        Analyze_Def_StructMember(GET_CHILD(nodeIndex, 0));
        Analyze_DefList_StructMember(GET_CHILD(nodeIndex, 1));
    }
    else if(isChildrenMatchRule(nodeIndex, 0)){
    }
    return 0;
}

int Analyze_Def_StructMember(ParserNode_I nodeIndex){
    if(isChildrenMatchRule(nodeIndex, 3, SPECIFIER, DEC_LIST, SEMI)){
        Analyze_Specifier(GET_CHILD(nodeIndex, 0));
        Analyze_pushCurrentTypeInfo(GET_SEMANTIC_INFO(GET_CHILD(nodeIndex, 0))->valueType,
                                    GET_SEMANTIC_INFO(GET_CHILD(nodeIndex, 0))->valueInfo);
        Analyze_DecList_StructMember(GET_CHILD(nodeIndex, 1));
        Analyze_popCurrentTypeInfo();
    }
    return 0;
}


int Analyze_Dec_StructMember(ParserNode_I nodeIndex){
    SymbolInfo_Struct_t ownerStruct = Analyze_getCurrentStructInfo();
    Symbol_Value_Type type;
    SymbolInfo_t typeMeta;
    Analyze_getCurrentTypeInfo(&type, &typeMeta);
    if(isChildrenMatchRule(nodeIndex, 1, VAR_DEC)){
        Analyze_VarDec(GET_CHILD(nodeIndex, 0));
        char* varName = Analyze_getCurrentVarName();
        int *dimensions = Analyze_getCurrentDimensions();
        int dimensionCount = Analyze_getCurrentDimensionCount();
        if(SymbolInfo_Struct_checkMemberName(ownerStruct, varName)){
            reportErrorFormat(GET_NODE(nodeIndex)->lineNum, InvalidMemberDefinition, "Struct member \"%s\" redefined", varName);
            GET_NODE(nodeIndex)->semanticInfo = SemanticInfo_createRvalue(SVT_Void, NULL, semanticInfoList);
        }
        else{
            if(dimensionCount == 0){
                SymbolInfo_Member_t member = SymbolInfo_Member_createBaked(type, varName, typeMeta);
                GET_NODE(nodeIndex)->semanticInfo = SemanticInfo_createRvalue(SVT_Int, member, semanticInfoList);
            }
            else {
                SymbolInfo_Array_t arrayInfo = SymbolInfo_Array_createBaked(type, typeMeta, dimensions, dimensionCount);
                SymbolInfo_Member_t member = SymbolInfo_Member_createBaked(SVT_Int, varName, arrayInfo);
                GET_NODE(nodeIndex)->semanticInfo = SemanticInfo_createRvalue(SVT_Int, member, semanticInfoList);
                Analyze_clearCurrentDimension();
            }
        }
        Analyze_popCurrentVarName();
    }
    else if(isChildrenMatchRule(nodeIndex, 3 , VAR_DEC, ASSIGNOP, EXP)){
        Analyze_VarDec(GET_CHILD(nodeIndex, 0));
        Analyze_Exp(GET_CHILD(nodeIndex, 2));
        char* varName = Analyze_getCurrentVarName();
        int *dimensions = Analyze_getCurrentDimensions();
        int dimensionCount = Analyze_getCurrentDimensionCount();
        SymbolInfo_Member_t member;
        if(SymbolInfo_Struct_checkMemberName(ownerStruct, varName)){
            reportErrorFormat(GET_NODE(nodeIndex)->lineNum, InvalidMemberDefinition, "Struct member \"%s\" redefined", varName);
            GET_NODE(nodeIndex)->semanticInfo = SemanticInfo_createRvalue(SVT_Void, NULL, semanticInfoList);
        }
        else{
            if(dimensionCount == 0){
                member = SymbolInfo_Member_createBaked(type, varName, typeMeta);
                GET_NODE(nodeIndex)->semanticInfo = SemanticInfo_createRvalue(SVT_Int, member, semanticInfoList);
            }
            else {
                SymbolInfo_Array_t arrayInfo = SymbolInfo_Array_createBaked(type, typeMeta, dimensions, dimensionCount);
                member = SymbolInfo_Member_createBaked(SVT_Array, varName, arrayInfo);
                GET_NODE(nodeIndex)->semanticInfo = SemanticInfo_createRvalue(SVT_Int, member, semanticInfoList);
                Analyze_clearCurrentDimension();
            }
            if(!SymbolInfo_Helper_isTypeMatched(member->memberType, member->memberMeta,
                                                 GET_SEMANTIC_INFO(GET_CHILD(nodeIndex, 2))->valueType,
                                                 GET_SEMANTIC_INFO(GET_CHILD(nodeIndex, 2))->valueInfo)){
                reportErrorFormat(GET_NODE(nodeIndex)->lineNum, AssignmentTypeMismatch, "Assignment type mismatch");
                if(GET_SEMANTIC_INFO(nodeIndex)->valueInfo!=NULL)
                {
                    SymbolInfo_Member_destroy(GET_SEMANTIC_INFO(nodeIndex)->valueInfo);
                }
                GET_SEMANTIC_INFO(nodeIndex)->valueType = SVT_Void;
                GET_SEMANTIC_INFO(nodeIndex)->valueInfo = NULL;
            }
        }
        Analyze_popCurrentVarName();
    }
    return 0;
}

#pragma clang diagnostic push
#pragma ide diagnostic ignored "bugprone-branch-clone"
int Analyze_Exp(ParserNode_I nodeIndex){
    ParserNode_t node = GET_NODE(nodeIndex);
    if(isChildrenMatchRule(nodeIndex, 3, EXP, ASSIGNOP, EXP)){
        Analyze_Exp(GET_CHILD(nodeIndex, 0));
        Analyze_Exp(GET_CHILD(nodeIndex, 2));

        if(!GET_SEMANTIC_INFO(GET_CHILD(nodeIndex, 0))->isLValue){
            reportError(node->lineNum, AssignToRvalue, "Assign to rvalue");
            //use the first child's semantic info to let the analysis can continue
            node->semanticInfo = GET_SEMANTIC_INFO(GET_CHILD(nodeIndex, 0));
        }
        else if(!SemanticInfo_isTypeMatched(GET_SEMANTIC_INFO(GET_CHILD(nodeIndex, 0)),
                                       GET_SEMANTIC_INFO(GET_CHILD(nodeIndex, 2)))){
            reportErrorFormat(node->lineNum, AssignmentTypeMismatch, "Assignment type mismatch");
            //use the first child's semantic info to let the analysis can continue
            node->semanticInfo = GET_SEMANTIC_INFO(GET_CHILD(nodeIndex, 0));
        }
        else if(SemanticInfo_checkValueType(GET_SEMANTIC_INFO(GET_CHILD(nodeIndex, 0)),SVT_Array)
                ||SemanticInfo_checkValueType(GET_SEMANTIC_INFO(GET_CHILD(nodeIndex, 0)),SVT_Void)){
            reportErrorFormat(node->lineNum, AssignmentTypeMismatch, "Assignment type mismatch");
            //use the first child's semantic info to let the analysis can continue
            node->semanticInfo = GET_SEMANTIC_INFO(GET_CHILD(nodeIndex, 0));
        }
        else {
            // directly use the first child's semantic info to allow continuous assignment
            node->semanticInfo = GET_SEMANTIC_INFO(GET_CHILD(nodeIndex, 0));
        }
    }
    else if(isChildrenMatchRule(nodeIndex, 3, EXP, AND, EXP)){
        Analyze_Exp(GET_CHILD(nodeIndex, 0));
        Analyze_Exp(GET_CHILD(nodeIndex, 2));

        Analyze_Helper_logicTwoParameters(nodeIndex, node);
    }
    else if(isChildrenMatchRule(nodeIndex, 3, EXP, OR, EXP)){
        Analyze_Exp(GET_CHILD(nodeIndex, 0));
        Analyze_Exp(GET_CHILD(nodeIndex, 2));

        Analyze_Helper_logicTwoParameters(nodeIndex, node);
    }
    else if(isChildrenMatchRule(nodeIndex, 3, EXP, EQ, EXP)){
        Analyze_Exp(GET_CHILD(nodeIndex, 0));
        Analyze_Exp(GET_CHILD(nodeIndex, 2));

        Analyze_Helper_operatorTwoParameters(nodeIndex, node);
    }
    else if(isChildrenMatchRule(nodeIndex, 3, EXP, NEQ, EXP)){
        Analyze_Exp(GET_CHILD(nodeIndex, 0));
        Analyze_Exp(GET_CHILD(nodeIndex, 2));

        Analyze_Helper_operatorTwoParameters(nodeIndex, node);
    }
    else if(isChildrenMatchRule(nodeIndex, 3, EXP, LT, EXP)){
        Analyze_Exp(GET_CHILD(nodeIndex, 0));
        Analyze_Exp(GET_CHILD(nodeIndex, 2));

        Analyze_Helper_operatorTwoParameters(nodeIndex, node);
    }
    else if(isChildrenMatchRule(nodeIndex, 3, EXP, LE, EXP)){
        Analyze_Exp(GET_CHILD(nodeIndex, 0));
        Analyze_Exp(GET_CHILD(nodeIndex, 2));

        Analyze_Helper_operatorTwoParameters(nodeIndex, node);
    }
    else if(isChildrenMatchRule(nodeIndex, 3, EXP, GT, EXP)){
        Analyze_Exp(GET_CHILD(nodeIndex, 0));
        Analyze_Exp(GET_CHILD(nodeIndex, 2));

        Analyze_Helper_operatorTwoParameters(nodeIndex, node);
    }
    else if(isChildrenMatchRule(nodeIndex, 3, EXP, GE, EXP)){
        Analyze_Exp(GET_CHILD(nodeIndex, 0));
        Analyze_Exp(GET_CHILD(nodeIndex, 2));

        Analyze_Helper_operatorTwoParameters(nodeIndex, node);
    }
    else if(isChildrenMatchRule(nodeIndex, 3, EXP, PLUS, EXP)){
        Analyze_Exp(GET_CHILD(nodeIndex, 0));
        Analyze_Exp(GET_CHILD(nodeIndex, 2));

        Analyze_Helper_operatorTwoParameters(nodeIndex, node);
    }
    else if(isChildrenMatchRule(nodeIndex, 3, EXP, MINUS, EXP)){
        Analyze_Exp(GET_CHILD(nodeIndex, 0));
        Analyze_Exp(GET_CHILD(nodeIndex, 2));

        Analyze_Helper_operatorTwoParameters(nodeIndex, node);
    }
    else if(isChildrenMatchRule(nodeIndex, 3, EXP, STAR, EXP)){
        Analyze_Exp(GET_CHILD(nodeIndex, 0));
        Analyze_Exp(GET_CHILD(nodeIndex, 2));

        Analyze_Helper_operatorTwoParameters(nodeIndex, node);
    }
    else if(isChildrenMatchRule(nodeIndex, 3, EXP, DIV, EXP)){
        Analyze_Exp(GET_CHILD(nodeIndex, 0));
        Analyze_Exp(GET_CHILD(nodeIndex, 2));

        Analyze_Helper_operatorTwoParameters(nodeIndex, node);
    }else if(isChildrenMatchRule(nodeIndex, 3, LP, EXP, RP)){
        Analyze_Exp(GET_CHILD(nodeIndex, 1));

        node->semanticInfo = GET_NODE(GET_CHILD(nodeIndex, 1))->semanticInfo;
    }
    else if(isChildrenMatchRule(nodeIndex, 2, MINUS, EXP)){
        Analyze_Exp(GET_CHILD(nodeIndex, 1));

        SemanticInfo_t expInfo = GET_SEMANTIC_INFO(GET_CHILD(nodeIndex, 1));
        node->semanticInfo = SemanticInfo_makeRvalue(expInfo, semanticInfoList);
    }
    else if(isChildrenMatchRule(nodeIndex, 2, NOT, EXP)){
        Analyze_Exp(GET_CHILD(nodeIndex, 1));

        SemanticInfo_t expInfo = GET_SEMANTIC_INFO(GET_CHILD(nodeIndex, 1));
        if(!SemanticInfo_checkValueType(expInfo, SVT_Int)){
            reportErrorFormat(node->lineNum, OperatorTypeMismatch, "Operator type mismatch");

            //use the first child's semantic info to let the analysis can continue
            node->semanticInfo = GET_SEMANTIC_INFO(GET_CHILD(nodeIndex, 0));
        }
        else{
            node->semanticInfo = SemanticInfo_makeRvalue(expInfo, semanticInfoList);
        }
    }else if(isChildrenMatchRule(nodeIndex, 4, ID, LP, ARGS, RP)){
        // Function call with arguments
        Analyze_Args(GET_CHILD(nodeIndex, 2));

        SymbolRecord_t record;
        SymbolDefineStatus defineStatus = SymbolTable_lookupRecord(symbolTable, GET_NODE(GET_CHILD(nodeIndex, 0))->ID, &record);

        SemanticInfo_t argsInfo[32] = {0};
        int argsNum = 0;
        ParserNode_I argsNodeIndex = GET_CHILD(nodeIndex, 2);
        // ARGS->EXP | ARGS->EXP COMMA ARGS
        // if ARGS->EXP, child num will be 1, means ARGS is END
        // otherwise ARGS-> EXP COMMA ARGS, child num will be 3, means ARGS is not END
        do{
            // set argsInfo[argsNum] to the semantic info of the EXP as the current argument
            argsInfo[argsNum++] = GET_SEMANTIC_INFO(GET_CHILD(argsNodeIndex, 0));
            // after setting the current argument, if ARGS is END, break the loop
            if(GET_CHILD_NUM(argsNodeIndex) == 1){
                break;
            }
            // if ARGS is not END, set argsNodeIndex to the next ARGS
            argsNodeIndex = GET_CHILD(argsNodeIndex, 2);
        }while(1);
        if(defineStatus < SDS_ExternalDefined)
        {
            reportErrorFormat(node->lineNum, UndefinedFunctionCalled, "Undefined function \"%s\"", GET_NODE(GET_CHILD(nodeIndex, 0))->ID);
            //make an empty semantic info to let the analysis can continue
            node->semanticInfo = SemanticInfo_createRvalue(SVT_Int, NULL, semanticInfoList);
        }
        else if(record->type != ST_Function)
        {
            reportErrorFormat(node->lineNum, FunctionCalledOnNonFunction, "Function called on non-function \"%s\"", GET_NODE(GET_CHILD(nodeIndex, 0))->ID);
            //make an empty semantic info to let the analysis can continue
            node->semanticInfo = SemanticInfo_createRvalue(SVT_Int, NULL, semanticInfoList);
        }
        else if(!SemanticInfo_checkParameterList(record->info, argsInfo, argsNum))
        {
            reportErrorFormat(node->lineNum, ParameterListMismatch, "Parameter list mismatch in function \"%s\"", GET_NODE(GET_CHILD(nodeIndex, 0))->ID);
            //make an empty semantic info to let the analysis can continue
            node->semanticInfo = SemanticInfo_createRvalue(SVT_Int, NULL, semanticInfoList);
        }
        else
        {
            SymbolInfo_Function_t functionInfo = (SymbolInfo_Function_t)record->info;
            node->semanticInfo = SemanticInfo_createRvalue(functionInfo->returnType, functionInfo->returnTypeMeta, semanticInfoList);
        }
    }
    else if(isChildrenMatchRule(nodeIndex, 3, ID, LP, RP)){
        // Function call without arguments
        SymbolRecord_t record;
        SymbolDefineStatus defineStatus = SymbolTable_lookupRecord(symbolTable, GET_NODE(GET_CHILD(nodeIndex, 0))->ID, &record);
        if(defineStatus < SDS_ExternalDefined)
        {
            reportErrorFormat(node->lineNum, UndefinedFunctionCalled, "Undefined function \"%s\"", GET_NODE(GET_CHILD(nodeIndex, 0))->ID);
            //make an empty semantic info to let the analysis can continue
            node->semanticInfo = SemanticInfo_createRvalue(SVT_Int, NULL, semanticInfoList);
        }
        else if(record->type != ST_Function)
        {
            reportErrorFormat(node->lineNum, FunctionCalledOnNonFunction, "Function called on non-function \"%s\"", GET_NODE(GET_CHILD(nodeIndex, 0))->ID);
            //make an empty semantic info to let the analysis can continue
            node->semanticInfo = SemanticInfo_createRvalue(SVT_Int, NULL, semanticInfoList);
        }
        else if(!SemanticInfo_checkParameterList(record->info, NULL, 0))
        {
            reportErrorFormat(node->lineNum, ParameterListMismatch, "Parameter list mismatch in function \"%s\"", GET_NODE(GET_CHILD(nodeIndex, 0))->ID);
            //make an empty semantic info to let the analysis can continue
            node->semanticInfo = SemanticInfo_createRvalue(SVT_Int, NULL, semanticInfoList);
        }
        else
        {
            SymbolInfo_Function_t functionInfo = (SymbolInfo_Function_t)record->info;
            node->semanticInfo = SemanticInfo_createRvalue(functionInfo->returnType, functionInfo->returnTypeMeta, semanticInfoList);
        }
    }
    else if(isChildrenMatchRule(nodeIndex, 4, EXP, LB, EXP, RB)){
        // Array access
        Analyze_Exp(GET_CHILD(nodeIndex, 0));
        Analyze_Exp(GET_CHILD(nodeIndex, 2));

        if(!SemanticInfo_checkValueType(GET_SEMANTIC_INFO(GET_CHILD(nodeIndex, 0)), SVT_Array)){
            reportErrorFormat(node->lineNum, ArrayAccessOnNonArray, "Array access on non-array");
            //make an empty semantic info to let the analysis can continue
            node->semanticInfo = SemanticInfo_createLvalue(SVT_Int, NULL, INVALID_SCOPE, semanticInfoList);
        }
        else if(!SemanticInfo_checkValueType(GET_SEMANTIC_INFO(GET_CHILD(nodeIndex, 2)), SVT_Int)){
            reportErrorFormat(node->lineNum, ArrayIndexTypeMismatch, "Array index type mismatch");
            //make an empty semantic info to let the analysis can continue
            node->semanticInfo = SemanticInfo_createLvalue(SVT_Int, NULL, INVALID_SCOPE, semanticInfoList);
        }
        else{
            SymbolInfo_Array_t arrayInfo = GET_SEMANTIC_INFO(GET_CHILD(nodeIndex, 0))->valueInfo;
            node->semanticInfo = SemanticInfo_createLvalue(arrayInfo->elementType, arrayInfo->elementStructInfo, GET_SEMANTIC_INFO(GET_CHILD(nodeIndex, 0))->scope, semanticInfoList);
        }
    }
    else if(isChildrenMatchRule(nodeIndex, 3, EXP, DOT, ID)){
        // Member access
        Analyze_Exp(GET_CHILD(nodeIndex, 0));

        if(!SemanticInfo_checkValueType(GET_SEMANTIC_INFO(GET_CHILD(nodeIndex, 0)), SVT_Struct)){
            reportErrorFormat(node->lineNum, MemberAccessOnNonStruct, "Member access on non-struct");
            //make an empty semantic info to let the analysis can continue
            node->semanticInfo = SemanticInfo_createLvalue(SVT_Int, NULL, INVALID_SCOPE, semanticInfoList);
        }
        else{
            SymbolInfo_Member_t member = SemanticInfo_getMemberInfo(GET_SEMANTIC_INFO(GET_CHILD(nodeIndex, 0)),
                                                                    GET_NODE(GET_CHILD(nodeIndex, 2))->ID);
            if(member == NULL) {
                reportErrorFormat(node->lineNum, UndefinedStructMember, "Undefined struct member \"%s\"",
                                  GET_NODE(GET_CHILD(nodeIndex, 2))->ID);
                //make an empty semantic info to let the analysis can continue
                node->semanticInfo = SemanticInfo_createLvalue(SVT_Int, NULL, INVALID_SCOPE, semanticInfoList);
            }
            else{
                node->semanticInfo = SemanticInfo_createLvalue(member->memberType, member->memberMeta, GET_SEMANTIC_INFO(GET_CHILD(nodeIndex, 0))->scope, semanticInfoList);
            }
        }
    }
    else if(isChildrenMatchRule(nodeIndex, 1, ID))
    {
        // Variable
        SymbolRecord_t record;
        SymbolDefineStatus defineStatus = SymbolTable_lookupRecord(symbolTable, GET_CHILD_NODE(nodeIndex, 0)->ID, &record);
        if(defineStatus <= SDS_ExternalDefined){
            // Error: Undefined variable, we assume it as an anonymous int variable
            //        which is defined in scope -1 (impossible to be found)
            reportErrorFormat(node->lineNum, UndefinedVariable, "Undefined variable \"%s\"", GET_CHILD_NODE(nodeIndex, 0)->ID);
            //make an empty semantic info to let the analysis can continue
            node->semanticInfo = SemanticInfo_createLvalue(SVT_Int ,NULL, INVALID_SCOPE, semanticInfoList);
        }
        else if(record->type != ST_Variable){
            reportErrorFormat(node->lineNum, VariableNameRedefinition, "Name  \"%s\" is defined and can not be a Variable", GET_CHILD_NODE(nodeIndex, 0)->ID);
            //make an empty semantic info to let the analysis can continue
            node->semanticInfo = SemanticInfo_createLvalue(SVT_Int ,NULL, INVALID_SCOPE, semanticInfoList);
        }
        else{
            SymbolInfo_Variable_t variableInfo = (SymbolInfo_Variable_t)record->info;
            //make an empty semantic info to let the analysis can continue
            node->semanticInfo = SemanticInfo_createLvalue(variableInfo->type, variableInfo->meta, record->scope, semanticInfoList);
        }

    }
    else if(isChildrenMatchRule(nodeIndex, 1, INT))
    {
        // Constant integer
        node->semanticInfo = SemanticInfo_createRvalue(SVT_Int, NULL, semanticInfoList);
    }
    else if(isChildrenMatchRule(nodeIndex, 1, FLOAT))
    {
        // Constant float
        node->semanticInfo = SemanticInfo_createRvalue(SVT_Float, NULL, semanticInfoList);
    }
    return 0;
}


#pragma clang diagnostic pop

int Analyze_Args(ParserNode_I nodeIndex){
    if(isChildrenMatchRule(nodeIndex, 1, EXP)){
        Analyze_Exp(GET_CHILD(nodeIndex, 0));
        GET_NODE(nodeIndex)->semanticInfo = GET_NODE(GET_CHILD(nodeIndex, 0))->semanticInfo;
    }
    else if(isChildrenMatchRule(nodeIndex, 3, EXP, COMMA, ARGS)){
        Analyze_Exp(GET_CHILD(nodeIndex, 0));
        Analyze_Args(GET_CHILD(nodeIndex, 2));
        GET_NODE(nodeIndex)->semanticInfo = GET_NODE(GET_CHILD(nodeIndex, 0))->semanticInfo;
    }
    return 0;
}

#pragma clang diagnostic push
#pragma ide diagnostic ignored "bugprone-branch-clone"
void Analyze_Helper_logicTwoParameters(ParserNode_I nodeIndex, ParserNode_t node) {
    if(!SemanticInfo_isTypeMatched(GET_SEMANTIC_INFO(GET_CHILD(nodeIndex, 0)),
                                   GET_SEMANTIC_INFO(GET_CHILD(nodeIndex, 2)))){
        reportErrorFormat(node->lineNum, OperatorTypeMismatch, "Operator type mismatch");
        //make an RValue from the first child's semantic info to let the analysis can continue
        node->semanticInfo = SemanticInfo_makeRvalue(GET_SEMANTIC_INFO(GET_CHILD(nodeIndex, 0)), semanticInfoList);
    }
    else if(!SemanticInfo_checkValueType(GET_SEMANTIC_INFO(GET_CHILD(nodeIndex, 0)),SVT_Int)){
        reportErrorFormat(node->lineNum, OperatorTypeMismatch, "Operator type mismatch");
        //make an RValue from the first child's semantic info to let the analysis can continue
        node->semanticInfo = SemanticInfo_makeRvalue(GET_SEMANTIC_INFO(GET_CHILD(nodeIndex, 0)), semanticInfoList);
    }
    else {
        node->semanticInfo = SemanticInfo_makeRvalue(GET_SEMANTIC_INFO(GET_CHILD(nodeIndex, 0)), semanticInfoList);
    }
}

void Analyze_Helper_operatorTwoParameters(ParserNode_I nodeIndex, ParserNode_t node) {
    if(!SemanticInfo_isTypeMatched(GET_SEMANTIC_INFO(GET_CHILD(nodeIndex, 0)),
                                   GET_SEMANTIC_INFO(GET_CHILD(nodeIndex, 2)))){
        reportErrorFormat(node->lineNum, OperatorTypeMismatch, "Operator type mismatch");
        //make an RValue from the first child's semantic info to let the analysis can continue
        node->semanticInfo = SemanticInfo_makeRvalue(GET_SEMANTIC_INFO(GET_CHILD(nodeIndex, 0)), semanticInfoList);
    }else if(!SemanticInfo_checkValueType(GET_SEMANTIC_INFO(GET_CHILD(nodeIndex, 0)),SVT_Int)
             ||!SemanticInfo_checkValueType(GET_SEMANTIC_INFO(GET_CHILD(nodeIndex, 0)),SVT_Float)){
        reportErrorFormat(node->lineNum, OperatorTypeMismatch, "Operator type mismatch");
        //make an RValue from the first child's semantic info to let the analysis can continue
        node->semanticInfo = SemanticInfo_makeRvalue(GET_SEMANTIC_INFO(GET_CHILD(nodeIndex, 0)), semanticInfoList);
    }
    else {
        node->semanticInfo = SemanticInfo_makeRvalue(GET_SEMANTIC_INFO(GET_CHILD(nodeIndex, 0)), semanticInfoList);
    }
}
#pragma clang diagnostic pop

#pragma clang diagnostic pop