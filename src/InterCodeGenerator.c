//
// Created by Crystal on 2024/3/31.
//

#include <stdarg.h>
#include "Structure/ParserNodes.h"
#include "Structure/SymbolTable.h"
#include "Structure/SimpleList.h"
#include "ErrorReporter.h"
#include "Structure/SemanticInfo.h"

#include "InterCodeGenerator.h"

#define MAX_FUNC_PARAM 100

char tempBuffer[100];

char isParamAddressReferenced[MAX_FUNC_PARAM] = {0};

int currentScope = 0;

SymbolTable_t symbolTable_IC = NULL;

/**
 * Helper functions
 */

int SymbolTable_generateTempName(SymbolTable_t table , InterCodeTempType type, char* buffer, int bufferSize, char* externalSuffix){
    static int TempVarCounter = 0;
    static int TempLabelCounter = 0;
    static int TempFuncCounter = 0;
    switch(type){
        case ICT_TEMP_VAR:
            if(externalSuffix != NULL){
                snprintf(buffer, bufferSize, "t%d_%s", TempVarCounter++, externalSuffix);
            }
            else{
                snprintf(buffer, bufferSize, "t%d", TempVarCounter++);
            }
            break;
        case ICT_TEMP_LABEL:
            if(externalSuffix != NULL){
                snprintf(buffer, bufferSize, "label%d_%s", TempLabelCounter++, externalSuffix);
            }
            else{
                snprintf(buffer, bufferSize, "label%d", TempLabelCounter++);
            }
            break;
        case ICT_TEMP_PARAM:
            if(externalSuffix != NULL){
                snprintf(buffer, bufferSize, "param%d_%s", TempFuncCounter++, externalSuffix);
            }
            else{
                snprintf(buffer, bufferSize, "param%d", TempFuncCounter++);
            }
            break;
    }
}

/**
 * InterCodeGenerator
 */

InterCodeHandle InterCodeGenerate_Program(ParserNode_I nodeIndex);

InterCodeHandle InterCodeGenerate_ExtDefList(ParserNode_I nodeIndex);

InterCodeHandle InterCodeGenerate_ExtDef(ParserNode_I nodeIndex);

InterCodeHandle InterCodeGenerate_ExtDecList(ParserNode_I nodeIndex, InterCodeInstruction *superInstruction);

InterCodeHandle InterCodeGenerate_VarDec(ParserNode_I nodeIndex);

InterCodeHandle InterCodeGenerate_CompSt(ParserNode_I nodeIndex);

InterCodeHandle InterCodeGenerate_StmtList(ParserNode_I nodeIndex);

InterCodeHandle InterCodeGenerate_Stmt(ParserNode_I nodeIndex);

InterCodeHandle InterCodeGenerate_DefList(ParserNode_I nodeIndex);

InterCodeHandle InterCodeGenerate_Def(ParserNode_I nodeIndex);

InterCodeHandle InterCodeGenerate_DecList(ParserNode_I nodeIndex, InterCodeInstruction *superInstruction);

InterCodeHandle InterCodeGenerate_Dec(ParserNode_I nodeIndex);

InterCodeHandle InterCodeGenerate_Exp(ParserNode_I nodeIndex, InterCodeInstruction *superInstruction);

InterCodeHandle InterCodeGenerate_Args(ParserNode_I nodeIndex);

/**
 * Virtual function for generating intermediate code.
 * No need to copy this to your project, just for fun.
 */

void InterCodeInfo_generate_Label(struct InterCodeInfo_s* interCodeInfo, FILE* file){
    
    InterCodeParam_printToBuffer(&interCodeInfo->params[0], tempBuffer, 100);
    fprintf(file, "LABEL %s :\n", tempBuffer);
}

void InterCodeInfo_generate_Func(struct InterCodeInfo_s*  interCodeInfo, FILE* file){
    
    InterCodeParam_printToBuffer(&interCodeInfo->params[0], tempBuffer, 100);
    fprintf(file, "FUNCTION %s :\n", tempBuffer);
}

void InterCodeInfo_generate_Assign(struct InterCodeInfo_s*  interCodeInfo, FILE* file){
    
    InterCodeParam_printToBuffer(&interCodeInfo->params[0], tempBuffer, 100);
    fprintf(file, "%s := ", tempBuffer);
    InterCodeParam_printToBuffer(&interCodeInfo->params[1], tempBuffer, 100);
    fprintf(file, "%s\n", tempBuffer);
}

void InterCodeInfo_generate_Add(struct InterCodeInfo_s*  interCodeInfo, FILE* file){
    
    InterCodeParam_printToBuffer(&interCodeInfo->params[0], tempBuffer, 100);
    fprintf(file, "%s := ", tempBuffer);
    InterCodeParam_printToBuffer(&interCodeInfo->params[1], tempBuffer, 100);
    fprintf(file, "%s + ", tempBuffer);
    InterCodeParam_printToBuffer(&interCodeInfo->params[2], tempBuffer, 100);
    fprintf(file, "%s\n", tempBuffer);
}

void InterCodeInfo_generate_Sub(struct InterCodeInfo_s*  interCodeInfo, FILE* file){
    
    InterCodeParam_printToBuffer(&interCodeInfo->params[0], tempBuffer, 100);
    fprintf(file, "%s := ", tempBuffer);
    InterCodeParam_printToBuffer(&interCodeInfo->params[1], tempBuffer, 100);
    fprintf(file, "%s - ", tempBuffer);
    InterCodeParam_printToBuffer(&interCodeInfo->params[2], tempBuffer, 100);
    fprintf(file, "%s\n", tempBuffer);
}

void InterCodeInfo_generate_Mul(struct InterCodeInfo_s*  interCodeInfo, FILE* file){
    
    InterCodeParam_printToBuffer(&interCodeInfo->params[0], tempBuffer, 100);
    fprintf(file, "%s := ", tempBuffer);
    InterCodeParam_printToBuffer(&interCodeInfo->params[1], tempBuffer, 100);
    fprintf(file, "%s * ", tempBuffer);
    InterCodeParam_printToBuffer(&interCodeInfo->params[2], tempBuffer, 100);
    fprintf(file, "%s\n", tempBuffer);
}

void InterCodeInfo_generate_Div(struct InterCodeInfo_s*  interCodeInfo, FILE* file){
    
    InterCodeParam_printToBuffer(&interCodeInfo->params[0], tempBuffer, 100);
    fprintf(file, "%s := ", tempBuffer);
    InterCodeParam_printToBuffer(&interCodeInfo->params[1], tempBuffer, 100);
    fprintf(file, "%s / ", tempBuffer);
    InterCodeParam_printToBuffer(&interCodeInfo->params[2], tempBuffer, 100);
    fprintf(file, "%s\n", tempBuffer);
}

void InterCodeInfo_generate_Addr(struct InterCodeInfo_s*  interCodeInfo, FILE* file){
    
    InterCodeParam_printToBuffer(&interCodeInfo->params[0], tempBuffer, 100);
    fprintf(file, "%s := &", tempBuffer);
    InterCodeParam_printToBuffer(&interCodeInfo->params[1], tempBuffer, 100);
    fprintf(file, "%s\n", tempBuffer);
}

void InterCodeInfo_generate_Deref_Get(struct InterCodeInfo_s*  interCodeInfo, FILE* file){
    
    InterCodeParam_printToBuffer(&interCodeInfo->params[0], tempBuffer, 100);
    fprintf(file, "%s := *", tempBuffer);
    InterCodeParam_printToBuffer(&interCodeInfo->params[1], tempBuffer, 100);
    fprintf(file, "%s\n", tempBuffer);
}

void InterCodeInfo_generate_Deref_Set(struct InterCodeInfo_s*  interCodeInfo, FILE* file){
    
    fprintf(file, "*");
    InterCodeParam_printToBuffer(&interCodeInfo->params[0], tempBuffer, 100);
    fprintf(file, "%s := ", tempBuffer);
    InterCodeParam_printToBuffer(&interCodeInfo->params[1], tempBuffer, 100);
    fprintf(file, "%s\n", tempBuffer);
}

void InterCodeInfo_generate_Goto(struct InterCodeInfo_s*  interCodeInfo, FILE* file){
    
    InterCodeParam_printToBuffer(&interCodeInfo->params[0], tempBuffer, 100);
    fprintf(file, "GOTO %s\n", tempBuffer);
}

void InterCodeInfo_generate_EQ_Goto(struct InterCodeInfo_s*  interCodeInfo, FILE* file){
    
    InterCodeParam_printToBuffer(&interCodeInfo->params[0], tempBuffer, 100);
    fprintf(file, "IF %s == ", tempBuffer);
    InterCodeParam_printToBuffer(&interCodeInfo->params[1], tempBuffer, 100);
    fprintf(file, "%s GOTO ", tempBuffer);
    InterCodeParam_printToBuffer(&interCodeInfo->params[2], tempBuffer, 100);
    fprintf(file, "%s\n", tempBuffer);
}

void InterCodeInfo_generate_NE_Goto(struct InterCodeInfo_s*  interCodeInfo, FILE* file){
    
    InterCodeParam_printToBuffer(&interCodeInfo->params[0], tempBuffer, 100);
    fprintf(file, "IF %s != ", tempBuffer);
    InterCodeParam_printToBuffer(&interCodeInfo->params[1], tempBuffer, 100);
    fprintf(file, "%s GOTO ", tempBuffer);
    InterCodeParam_printToBuffer(&interCodeInfo->params[2], tempBuffer, 100);
    fprintf(file, "%s\n", tempBuffer);
}

void InterCodeInfo_generate_GE_Goto(struct InterCodeInfo_s*  interCodeInfo, FILE* file){
    
    InterCodeParam_printToBuffer(&interCodeInfo->params[0], tempBuffer, 100);
    fprintf(file, "IF %s >= ", tempBuffer);
    InterCodeParam_printToBuffer(&interCodeInfo->params[1], tempBuffer, 100);
    fprintf(file, "%s GOTO ", tempBuffer);
    InterCodeParam_printToBuffer(&interCodeInfo->params[2], tempBuffer, 100);
    fprintf(file, "%s\n", tempBuffer);
}

void InterCodeInfo_generate_GT_Goto(struct InterCodeInfo_s*  interCodeInfo, FILE* file){
    
    InterCodeParam_printToBuffer(&interCodeInfo->params[0], tempBuffer, 100);
    fprintf(file, "IF %s > ", tempBuffer);
    InterCodeParam_printToBuffer(&interCodeInfo->params[1], tempBuffer, 100);
    fprintf(file, "%s GOTO ", tempBuffer);
    InterCodeParam_printToBuffer(&interCodeInfo->params[2], tempBuffer, 100);
    fprintf(file, "%s\n", tempBuffer);
}

void InterCodeInfo_generate_LE_Goto(struct InterCodeInfo_s*  interCodeInfo, FILE* file){
    
    InterCodeParam_printToBuffer(&interCodeInfo->params[0], tempBuffer, 100);
    fprintf(file, "IF %s <= ", tempBuffer);
    InterCodeParam_printToBuffer(&interCodeInfo->params[1], tempBuffer, 100);
    fprintf(file, "%s GOTO ", tempBuffer);
    InterCodeParam_printToBuffer(&interCodeInfo->params[2], tempBuffer, 100);
    fprintf(file, "%s\n", tempBuffer);
}

void InterCodeInfo_generate_LT_Goto(struct InterCodeInfo_s*  interCodeInfo, FILE* file){
    
    InterCodeParam_printToBuffer(&interCodeInfo->params[0], tempBuffer, 100);
    fprintf(file, "IF %s < ", tempBuffer);
    InterCodeParam_printToBuffer(&interCodeInfo->params[1], tempBuffer, 100);
    fprintf(file, "%s GOTO ", tempBuffer);
    InterCodeParam_printToBuffer(&interCodeInfo->params[2], tempBuffer, 100);
    fprintf(file, "%s\n", tempBuffer);
}

void InterCodeInfo_generate_Return(struct InterCodeInfo_s*  interCodeInfo, FILE* file){
    
    fprintf(file, "RETURN ");
    InterCodeParam_printToBuffer(&interCodeInfo->params[0], tempBuffer, 100);
    fprintf(file, "%s\n", tempBuffer);
}

void InterCodeInfo_generate_Dec(struct InterCodeInfo_s*  interCodeInfo, FILE* file){
    
    fprintf(file, "DEC ");
    InterCodeParam_printToBuffer(&interCodeInfo->params[0], tempBuffer, 100);
    fprintf(file, "%s \n", tempBuffer);
    snprintf(tempBuffer, 100, "%d", INTERCODEPARAM_GETINT(&interCodeInfo->params[1]));
    fprintf(file, "%s\n", tempBuffer);
}

void InterCodeInfo_generate_Arg(struct InterCodeInfo_s*  interCodeInfo, FILE* file){
    
    fprintf(file, "ARG ");
    InterCodeParam_printToBuffer(&interCodeInfo->params[0], tempBuffer, 100);
    fprintf(file, "%s\n", tempBuffer);
}

void InterCodeInfo_generate_Call(struct InterCodeInfo_s*  interCodeInfo, FILE* file){
    
    InterCodeParam_printToBuffer(&interCodeInfo->params[0], tempBuffer, 100);
    fprintf(file, "%s := CALL ", tempBuffer);
    InterCodeParam_printToBuffer(&interCodeInfo->params[1], tempBuffer, 100);
    fprintf(file, "%s\n", tempBuffer);
}

void InterCodeInfo_generate_Param(struct InterCodeInfo_s*  interCodeInfo, FILE* file){
    
    fprintf(file, "PARAM ");
    InterCodeParam_printToBuffer(&interCodeInfo->params[0], tempBuffer, 100);
    fprintf(file, "%s\n", tempBuffer);
}

void InterCodeInfo_generate_Read(struct InterCodeInfo_s*  interCodeInfo, FILE* file){
    
    fprintf(file, "READ ");
    InterCodeParam_printToBuffer(&interCodeInfo->params[0], tempBuffer, 100);
    fprintf(file, "%s\n", tempBuffer);
}

void InterCodeInfo_generate_Write(struct InterCodeInfo_s*  interCodeInfo, FILE* file){
    
    fprintf(file, "WRITE ");
    InterCodeParam_printToBuffer(&interCodeInfo->params[0], tempBuffer, 100);
    fprintf(file, "%s\n", tempBuffer);
}

/**
 * Virtual Table for generating intermediate code.
 * No need to copy this to your project, just for fun.
 */
InterCodeInfo_VT InterCodeInfo_VT_INSTANCE[IC_WRITE+ 1] = {
        {InterCodeInfo_generate_Label},
        {InterCodeInfo_generate_Func},
        {InterCodeInfo_generate_Assign},
        {InterCodeInfo_generate_Add},
        {InterCodeInfo_generate_Sub},
        {InterCodeInfo_generate_Mul},
        {InterCodeInfo_generate_Div},

        {InterCodeInfo_generate_Addr},
        {InterCodeInfo_generate_Deref_Get},
        {InterCodeInfo_generate_Deref_Set},

        {InterCodeInfo_generate_Goto},
        {InterCodeInfo_generate_EQ_Goto},
        {InterCodeInfo_generate_NE_Goto},
        {InterCodeInfo_generate_GE_Goto},
        {InterCodeInfo_generate_GT_Goto},
        {InterCodeInfo_generate_LE_Goto},
        {InterCodeInfo_generate_LT_Goto},

        {InterCodeInfo_generate_Return},

        {InterCodeInfo_generate_Dec},
        {InterCodeInfo_generate_Arg},
        {InterCodeInfo_generate_Call},
        {InterCodeInfo_generate_Param},
        {InterCodeInfo_generate_Read},
        {InterCodeInfo_generate_Write}
};

/*
 * Implementations for InterCodeInfo
 */

InterCodeInfo_t InterCodeInfo_create(InterCodeType type, int paramNum, ...){
    InterCodeInfo_t interCodeInfo = (InterCodeInfo_t)malloc(sizeof(InterCodeInfo));
    interCodeInfo->vptr = &InterCodeInfo_VT_INSTANCE[type];
    interCodeInfo->type = type;
    va_list args;
    va_start(args, paramNum);
    for(int i = 0; i < paramNum; i++) {
        interCodeInfo->params[i].type = va_arg(args, InterCodeParam_Type);
        switch (interCodeInfo->params[i].type) {
            case ICP_INT:
                interCodeInfo->params[i].intVal = va_arg(args, int);
                break;
            case ICP_VAR:
                interCodeInfo->params[i].varID = va_arg(args, int);
                break;
            case ICP_LABEL:
                interCodeInfo->params[i].labelName = strdup(va_arg(args, char*));
                break;
            case ICP_PARAM:
                interCodeInfo->params[i].paramID = va_arg(args, int);
                break;
        }
    }
    va_end(args);
    return interCodeInfo;
}

int InterCodeParam_printToBuffer(InterCodeParam *param, char *buffer, int bufferSize) {
    switch(param->type){
        case ICP_INT:
            return snprintf(buffer, bufferSize, "#%d", INTERCODEPARAM_GETINT(param));
        case ICP_VAR:
            return snprintf(buffer, bufferSize, "t%d", INTERCODEPARAM_GETVAR(param));
        case ICP_LABEL:
            return snprintf(buffer, bufferSize, "%s", INTERCODEPARAM_GETLABEL(param));
        case ICP_PARAM:
            return snprintf(buffer, bufferSize, "p%d", INTERCODEPARAM_GETPARAM(param));
    }
    return 0;
}

/**
 * Implementations for InterCodeHandle
 */

InterCodeHandle InterCodeHandle_create() {
    InterCodeHandle handle = (InterCodeHandle)malloc(sizeof(InterCodeContainer));
    handle->codes = SimpleList_create();
    handle->returnID = INVALID_VAR_ID;
    handle->returnType = ICP_INT;
    return handle;
}

void InterCodeHandle_destroy(InterCodeHandle handle) {
    SimpleList_destroy(handle->codes, free);
    free(handle);
}

void InterCodeHandle_newCode(InterCodeHandle handle, InterCodeType codeType, int paramNum, ...) {
    SimpleList_t codes = handle->codes;
    va_list args;
    va_start(args, paramNum);
    InterCodeInfo_t codeInfo = InterCodeInfo_create(codeType, paramNum, args);
    SimpleList_push_back(codes, codeInfo);
    va_end(args);
}

InterCodeHandle InterCodeHandle_merge(InterCodeHandle handle1, InterCodeHandle handle2) {
    if(handle1 == INVALID_INTERCODE_HANDLE){
        return handle2;
    }
    if(handle2 == INVALID_INTERCODE_HANDLE){
        return handle1;
    }
    handle1->codes = SimpleList_append(handle1->codes, handle2->codes);
    free(handle2);
    return handle1;
}

InterCodeHandle generateInterCode(ParserNode_I rootNodeIndex, FILE *file, SymbolTable_t inSymbolTable) {

    symbolTable_IC = inSymbolTable;
    InterCodeHandle handle = InterCodeGenerate_Program(rootNodeIndex);

    SimpleList_t codes = handle->codes;
    SimpleListNode_t node = codes->head;
    while(node != NULL){
        InterCodeInfo_t interCodeInfo = (InterCodeInfo_t)node->data;
        interCodeInfo->vptr->generateInterCode(interCodeInfo, file);
        node = node->next;
    }

    return handle;
}

void generateInterCode_End(){

}

InterCodeHandle InterCodeGenerate_Program(ParserNode_I nodeIndex) {
    if(isChildrenMatchRule(nodeIndex, 1, EXT_DEF_LIST))
    {
        return InterCodeGenerate_ExtDefList(GET_CHILD(nodeIndex, 0));
    }
    return INVALID_INTERCODE_HANDLE;
}

InterCodeHandle InterCodeGenerate_ExtDefList(ParserNode_I nodeIndex){
    if(isChildrenMatchRule(nodeIndex, 2, EXT_DEF, EXT_DEF_LIST))
    {
        InterCodeHandle handle = InterCodeGenerate_ExtDef(GET_CHILD(nodeIndex, 0));
        InterCodeHandle handle2 = InterCodeGenerate_ExtDefList(GET_CHILD(nodeIndex, 1));
        return InterCodeHandle_merge(handle, handle2);
    }
    else if(isChildrenMatchRule(nodeIndex, 0))
    {
        return INVALID_INTERCODE_HANDLE;
    }
    return INVALID_INTERCODE_HANDLE;
}

InterCodeHandle InterCodeGenerate_ExtDef(ParserNode_I nodeIndex){
    if(isChildrenMatchRule(nodeIndex, 3, SPECIFIER, EXT_DEC_LIST, SEMI)){
        // a global variable declaration
        // make no sense in intermediate code
        SemanticInfo_t specifierSemanticInfo = GET_CHILD_NODE(nodeIndex, 1)->semanticInfo;
        InterCodeInstruction instruction = {NULL, NULL, REQ_NO};
        if(specifierSemanticInfo->valueType == SVT_Struct || specifierSemanticInfo->valueType == SVT_Array){
            // we need to allocate space for the struct or array
            // code:
            // DEC [VarDec's ID] [VarDec's size]
            instruction.specialRequest = REQ_ALLOC;
            instruction.typeSize = SymbolValue_getSize(specifierSemanticInfo->valueType, specifierSemanticInfo->valueInfo);
        }
        InterCodeHandle childExtDecListHandle = InterCodeGenerate_ExtDecList(GET_CHILD(nodeIndex, 1), &instruction);
        return childExtDecListHandle;
    }
    else if(isChildrenMatchRule(nodeIndex, 2, SPECIFIER, SEMI)){
        // a global variable declaration
        // make no sense in intermediate code
        return INVALID_INTERCODE_HANDLE;
    }
    else if(isChildrenMatchRule(nodeIndex, 3, SPECIFIER, FUN_DEC, COMP_STM)){
        // a real function definition
        // need to generate a label for the function
        // code:
        // FUNCTION [FunDec's ID]:
        // PARAM v1
        // PARAM v2
        // ...
        // [CompSt's code]

        // firstly, extract the function's name from FunDec->ID
        ParserNode_t funcID = GET_CHILD_NODE(GET_CHILD(nodeIndex, 1), 0);
        char* funcName = funcID->ID;
        SymbolRecord_t record;
        SymbolTable_lookupRecord(symbolTable_IC, funcName, &record);
        SymbolInfo_Function_t functionInfo = record->info;
        InterCodeHandle handle = InterCodeHandle_create();
        InterCodeHandle_newCode(handle, IC_FUNC, 1,
                                ICP_LABEL, funcName);
        // secondly, generate PARAM for each parameter
        // before we start to exmine the parameters, we need to set the isParamAddressReferenced to 0
        memset(isParamAddressReferenced, 0, MAX_FUNC_PARAM);

        for(int i = 0; i < functionInfo->parameterCount; i++){
            SymbolInfo_Parameter_t paramInfo = functionInfo->parameters[i];
            InterCodeHandle_newCode(handle, IC_PARAM, 1,
                                    ICP_PARAM, i+1);
            // we should instruct the ID that where the param is an address
            // but ID's too far from here, we cant use instruction parameter to do that
            // we use a global array to store the information
            if(paramInfo->parameterType == SVT_Struct || paramInfo->parameterType == SVT_Array){
                isParamAddressReferenced[i] = 1;
            }
        }
        // thirdly, generate the CompSt's code
        InterCodeHandle childCompStHandle = InterCodeGenerate_CompSt(GET_CHILD(nodeIndex, 2));
        handle = InterCodeHandle_merge(handle, childCompStHandle);
        return handle;
    }
    else if(isChildrenMatchRule(nodeIndex, 3, SPECIFIER, FUN_DEC, SEMI)){
        // a forward declaration
        // make no sense in intermediate code
        return INVALID_INTERCODE_HANDLE;
    }
    return INVALID_INTERCODE_HANDLE;
}

InterCodeHandle InterCodeGenerate_ExtDecList(ParserNode_I nodeIndex, InterCodeInstruction* superInstruction){
    if(isChildrenMatchRule(nodeIndex, 1, VAR_DEC))
    {
        InterCodeHandle handle = InterCodeHandle_create();
        InterCodeHandle childVarDecHandle = InterCodeGenerate_VarDec(GET_CHILD(nodeIndex, 0));
        if(superInstruction->specialRequest == REQ_ALLOC)
        {
            InterCodeHandle_newCode(handle, IC_DEC, 2,
                                    ICP_VAR, childVarDecHandle->returnID,
                                    ICP_INT, superInstruction->typeSize);
        }
        handle = InterCodeHandle_merge(handle, childVarDecHandle);
        return handle;
    }
    else if(isChildrenMatchRule(nodeIndex, 3, VAR_DEC, COMMA, EXT_DEC_LIST))
    {
        InterCodeHandle handle = InterCodeHandle_create();
        InterCodeHandle childVarDecHandle = InterCodeGenerate_VarDec(GET_CHILD(nodeIndex, 0));
        if(superInstruction->specialRequest == REQ_ALLOC)
        {
            InterCodeHandle_newCode(handle, IC_DEC, 2,
                                    ICP_VAR, childVarDecHandle->returnID,
                                    ICP_INT, superInstruction->typeSize);
        }
        handle = InterCodeHandle_merge(handle, childVarDecHandle);
        InterCodeHandle childExtDecListHandle = InterCodeGenerate_ExtDecList(GET_CHILD(nodeIndex, 2), superInstruction);
        return InterCodeHandle_merge(handle, childExtDecListHandle);
    }
    return INVALID_INTERCODE_HANDLE;
}

InterCodeHandle InterCodeGenerate_VarDec(ParserNode_I nodeIndex) {
    if(isChildrenMatchRule(nodeIndex, 1, ID))
    {
        InterCodeHandle handle = InterCodeHandle_create();
        SymbolInfo_Variable_t variableInfo = GET_CHILD_NODE(nodeIndex, 0)->semanticInfo->variableInfo;
        handle->returnID = variableInfo->varID;
        handle->returnType = ICP_VAR;
        return handle;
    }
    else if(isChildrenMatchRule(nodeIndex, 4, VAR_DEC, LB, INT, RB))
    {
        // allocate new array
        // we need to return the array's base address
        // but in fact this is not used in this very intermediate code generator
        // we just do something like the ID's case
        InterCodeHandle handle = InterCodeHandle_create();
        SymbolInfo_Variable_t variableInfo = GET_CHILD_NODE(nodeIndex, 0)->semanticInfo->variableInfo;
        handle->returnID = variableInfo->varID;
        handle->returnType = ICP_VAR;
        return handle;
    }
    return INVALID_INTERCODE_HANDLE;
}

InterCodeHandle InterCodeGenerate_CompSt(ParserNode_I nodeIndex){
    if(isChildrenMatchRule(nodeIndex, 4, LC, DEF_LIST, STMT_LIST, RC))
    {
        int prevScope = currentScope;
        int scope = GET_NODE(nodeIndex)->intVal;
        currentScope = scope;

        InterCodeHandle childDefListHandle = InterCodeGenerate_DefList(GET_CHILD(nodeIndex, 1));
        InterCodeHandle childStmtListHandle = InterCodeGenerate_StmtList(GET_CHILD(nodeIndex, 2));
        InterCodeHandle result = InterCodeHandle_merge(childDefListHandle, childStmtListHandle);

        currentScope = prevScope;
        return result;
    }
    return INVALID_INTERCODE_HANDLE;
}

InterCodeHandle InterCodeGenerate_StmtList(ParserNode_I nodeIndex){
    if(isChildrenMatchRule(nodeIndex, 2, STMT, STMT_LIST))
    {
        InterCodeHandle childStmtHandle = InterCodeGenerate_Stmt(GET_CHILD(nodeIndex, 0));
        InterCodeHandle childStmtListHandle = InterCodeGenerate_StmtList(GET_CHILD(nodeIndex, 1));
        return InterCodeHandle_merge(childStmtHandle, childStmtListHandle);
    }
    else if(isChildrenMatchRule(nodeIndex, 0))
    {
        return INVALID_INTERCODE_HANDLE;
    }
    return INVALID_INTERCODE_HANDLE;
}

InterCodeHandle InterCodeGenerate_Stmt(ParserNode_I nodeIndex){
    if(isChildrenMatchRule(nodeIndex, 2, EXP, SEMI))
    {
        // instruct Exp with no return value
        InterCodeInstruction instruction = {NULL, NULL, REQ_NORETURN};
        return InterCodeGenerate_Exp(GET_CHILD(nodeIndex, 0), &instruction);
    }
    else if(isChildrenMatchRule(nodeIndex, 1, COMP_STM))
    {
        // directly return the result of COMP_STM
        return InterCodeGenerate_CompSt(GET_CHILD(nodeIndex, 0));
    }
    else if(isChildrenMatchRule(nodeIndex, 3, RETURN, EXP, SEMI))
    {
        // instruct Exp with retval
        // code:
        // [Exp's code]
        // RETURN [Exp's retval]
        InterCodeInstruction instruction = {NULL, NULL, REQ_NO};
        InterCodeHandle childExpHandle = InterCodeGenerate_Exp(GET_CHILD(nodeIndex, 1), &instruction);
        InterCodeHandle_newCode(childExpHandle, IC_RETURN, 1,
                                childExpHandle->returnType, childExpHandle->returnID);
    }
    else if(isChildrenMatchRule(nodeIndex, 5, IF, LP, EXP, RP, STMT))
    {
        // instruct Exp with InterCodeInstruction:
        //                      no return value,
        //                      trueLabel = BodyLabel,
        //                      falseLabel = AfterLabel
        // code:
        // [Exp's code]
        // LABEL BodyLabel:
        // [stmt's code]
        // LABEL AfterLabel:
        char bodyLabel[100];
        char afterLabel[100];
        SymbolTable_generateNextLabelNameWithSuffix(symbolTable_IC, bodyLabel, 100, "_body");
        SymbolTable_generateNextLabelNameWithSuffix(symbolTable_IC, afterLabel, 100, "_after");
        InterCodeHandle handle = InterCodeHandle_create();
        InterCodeInstruction instruction = {bodyLabel, afterLabel, REQ_NORETURN};
        InterCodeHandle childExpHandle = InterCodeGenerate_Exp(GET_CHILD(nodeIndex, 2), &instruction);
        handle = InterCodeHandle_merge(handle, childExpHandle);

        InterCodeHandle_newCode(handle, IC_LABEL, 1,
                                ICP_LABEL, bodyLabel);

        InterCodeHandle childStmtHandle = InterCodeGenerate_Stmt(GET_CHILD(nodeIndex, 4));
        handle = InterCodeHandle_merge(handle, childStmtHandle);

        InterCodeHandle_newCode(handle, IC_LABEL, 1,
                                ICP_LABEL, afterLabel);

        return handle;
    }
    else if(isChildrenMatchRule(nodeIndex, 7, IF, LP, EXP, RP, STMT, ELSE, STMT))
    {
        // instruct Exp with InterCodeInstruction:
        //                      no return value,
        //                      trueLabel = BodyLabel,
        //                      falseLabel = ElseLabel
        // except that, we need to generate a new label for AfterLabel
        // code:
        // [Exp's code]
        // LABEL BodyLabel:
        // [stmt's code]
        // GOTO AfterLabel
        // LABEL ElseLabel:
        // [stmt's code]
        // LABEL AfterLabel:
        char bodyLabel[100];
        char elseLabel[100];
        char afterLabel[100];
        SymbolTable_generateNextLabelNameWithSuffix(symbolTable_IC, bodyLabel, 100, "_body");
        SymbolTable_generateNextLabelNameWithSuffix(symbolTable_IC, elseLabel, 100, "_else");
        SymbolTable_generateNextLabelNameWithSuffix(symbolTable_IC, afterLabel, 100, "_after");
        InterCodeHandle handle = InterCodeHandle_create();
        InterCodeInstruction instruction = {bodyLabel, elseLabel, REQ_NORETURN};
        InterCodeHandle childExpHandle = InterCodeGenerate_Exp(GET_CHILD(nodeIndex, 2), &instruction);
        handle = InterCodeHandle_merge(handle, childExpHandle);

        InterCodeHandle_newCode(handle, IC_LABEL, 1,
                                ICP_LABEL, bodyLabel);

        InterCodeHandle childStmt1Handle = InterCodeGenerate_Stmt(GET_CHILD(nodeIndex, 4));
        handle = InterCodeHandle_merge(handle, childStmt1Handle);

        InterCodeHandle_newCode(handle, IC_GOTO, 1,
                                ICP_LABEL, afterLabel);
        InterCodeHandle_newCode(handle, IC_LABEL, 1,
                                ICP_LABEL, elseLabel);

        InterCodeHandle childStmt2Handle = InterCodeGenerate_Stmt(GET_CHILD(nodeIndex, 6));
        handle = InterCodeHandle_merge(handle, childStmt2Handle);

        InterCodeHandle_newCode(handle, IC_LABEL, 1,
                                ICP_LABEL, afterLabel);
        return handle;
    }
    else if(isChildrenMatchRule(nodeIndex, 5, WHILE, LP, EXP, RP, STMT))
    {
        // while will repeat stmt's code
        // instruct Exp with InterCodeInstruction:
        //                      no return value,
        //                      trueLabel = BodyLabel,
        //                      falseLabel = AfterLabel
        // code:
        // GOTO ConditionLabel
        // LABEL BodyLabel:
        // [stmt's code]
        // LABEL ConditionLabel:
        // [Exp's code]
        // LABEL AfterLabel:
        char bodyLabel[100];
        char conditionLabel[100];
        char afterLabel[100];
        SymbolTable_generateNextLabelNameWithSuffix(symbolTable_IC, conditionLabel, 100, "_cond");
        SymbolTable_generateNextLabelNameWithSuffix(symbolTable_IC, bodyLabel, 100, "_body");
        SymbolTable_generateNextLabelNameWithSuffix(symbolTable_IC, afterLabel, 100, "_after");
        InterCodeHandle handle = InterCodeHandle_create();

        InterCodeHandle_newCode(handle,IC_GOTO, 1,
                                ICP_LABEL, conditionLabel);

        InterCodeHandle_newCode(handle,IC_LABEL, 1,
                                ICP_LABEL, bodyLabel);

        InterCodeHandle childStmtHandle = InterCodeGenerate_Stmt(GET_CHILD(nodeIndex, 4));
        handle = InterCodeHandle_merge(handle, childStmtHandle);

        InterCodeHandle_newCode(handle,IC_LABEL, 1,
                                ICP_LABEL, conditionLabel);

        InterCodeInstruction instruction = {bodyLabel, afterLabel, REQ_NORETURN};
        InterCodeHandle childExpHandle = InterCodeGenerate_Exp(GET_CHILD(nodeIndex, 2), &instruction);
        handle = InterCodeHandle_merge(handle, childExpHandle);

        InterCodeHandle_newCode(handle, IC_LABEL, 1,
                                ICP_LABEL, afterLabel);
        return handle;
    }
    return INVALID_INTERCODE_HANDLE;
}

InterCodeHandle InterCodeGenerate_DefList(ParserNode_I nodeIndex){
    if(isChildrenMatchRule(nodeIndex, 2, DEF, DEF_LIST))
    {
        InterCodeHandle childDefHandle = InterCodeGenerate_Def(GET_CHILD(nodeIndex, 0));
        InterCodeHandle childDefListHandle = InterCodeGenerate_DefList(GET_CHILD(nodeIndex, 1));
        return InterCodeHandle_merge(childDefHandle, childDefListHandle);
    }
    else if(isChildrenMatchRule(nodeIndex, 0))
    {
        return INVALID_INTERCODE_HANDLE;
    }
    return INVALID_INTERCODE_HANDLE;
}

InterCodeHandle InterCodeGenerate_Def(ParserNode_I nodeIndex){
    if(isChildrenMatchRule(nodeIndex, 3, SPECIFIER, DEC_LIST, SEMI))
    {
        SemanticInfo_t specifierInfo = GET_CHILD_NODE(nodeIndex, 0)->semanticInfo;
        InterCodeInstruction instruction = {NULL, NULL, REQ_NO};
        if(specifierInfo->valueType == SVT_Struct|| specifierInfo->valueType == SVT_Array)
        {
            instruction.specialRequest = REQ_ALLOC;
            instruction.typeSize = SymbolValue_getSize(specifierInfo->valueType, specifierInfo->valueInfo);
        }

        InterCodeHandle childDecListHandle = InterCodeGenerate_DecList(GET_CHILD(nodeIndex, 1), &instruction);
        return childDecListHandle;
    }
    return INVALID_INTERCODE_HANDLE;
}

InterCodeHandle InterCodeGenerate_DecList(ParserNode_I nodeIndex, InterCodeInstruction *superInstruction) {
    if(isChildrenMatchRule(nodeIndex, 1, DEC))
    {
        // allocate size if we need before analyze the DEC
        InterCodeHandle handle = InterCodeHandle_create();
        InterCodeHandle childDecHandle = InterCodeGenerate_Dec(GET_CHILD(nodeIndex, 0));
        if(superInstruction->specialRequest == REQ_ALLOC)
        {
            InterCodeHandle_newCode(handle, IC_DEC, 2,
                                    ICP_VAR, childDecHandle->returnID,
                                    ICP_INT, superInstruction->typeSize);
        }
        return InterCodeHandle_merge(handle, childDecHandle);
    }
    else if(isChildrenMatchRule(nodeIndex, 3, DEC, COMMA, DEC_LIST))
    {
        InterCodeHandle handle = InterCodeHandle_create();
        InterCodeHandle childDecHandle = InterCodeGenerate_Dec(GET_CHILD(nodeIndex, 0));
        if(superInstruction->specialRequest == REQ_ALLOC)
        {
            InterCodeHandle_newCode(handle, IC_DEC, 2,
                                    ICP_VAR, childDecHandle->returnID,
                                    ICP_INT, superInstruction->typeSize);
        }
        handle = InterCodeHandle_merge(handle, childDecHandle);
        InterCodeHandle childDecListHandle = InterCodeGenerate_DecList(GET_CHILD(nodeIndex, 2), superInstruction);
        return InterCodeHandle_merge(handle, childDecListHandle);
    }
    return INVALID_INTERCODE_HANDLE;
}

InterCodeHandle InterCodeGenerate_Dec(ParserNode_I nodeIndex){
    if(isChildrenMatchRule(nodeIndex, 1, VAR_DEC))
    {
        // allocate new variable
        // make no sense in intermediate code
        // but above needs the return value to allocate space.
        return InterCodeGenerate_VarDec(GET_CHILD(nodeIndex, 0));
    }
    else if(isChildrenMatchRule(nodeIndex, 3, VAR_DEC, ASSIGNOP, EXP))
    {
        // allocate new variable and assign value
        // just like the case in EXP
        // the only possible case is to assign to plain variable
        // so....
        // [Exp's code]
        // [VarDec's code]
        // [VarDec's retval] := [Exp's retval]
        InterCodeInstruction instruction = {NULL, NULL, REQ_NO};
        InterCodeHandle childExpHandle = InterCodeGenerate_Exp(GET_CHILD(nodeIndex, 2), &instruction);
        InterCodeHandle childVarDecHandle = InterCodeGenerate_VarDec(GET_CHILD(nodeIndex, 0));
        InterCodeHandle_newCode(childVarDecHandle, IC_ASSIGN, 2,
                                childVarDecHandle->returnType, childVarDecHandle->returnID,
                                childExpHandle->returnType, childExpHandle->returnID);
        int retValID = childVarDecHandle->returnID;
        InterCodeHandle returnHandle = InterCodeHandle_merge(childExpHandle, childVarDecHandle);
        returnHandle->returnID = retValID;
        returnHandle->returnType = ICP_VAR;
        return returnHandle;
    }
    return INVALID_INTERCODE_HANDLE;
}

InterCodeHandle InterCodeGenerate_Exp(ParserNode_I nodeIndex, InterCodeInstruction *superInstruction) {
    if(isChildrenMatchRule(nodeIndex, 3, EXP, ASSIGNOP, EXP)){
        // there's two cases
        // case1: assign to a normal variable(include param)
        // we just have the retval of exp1 and assign exp2 to it

        // case2: assign to a struct member or array element
        // we need to assign to address

        // similar to Args
        InterCodeInstruction leftExpInstruction = {NULL, NULL, REQ_ADDRESS};
        InterCodeHandle childExp1Handle = InterCodeGenerate_Exp(GET_CHILD(nodeIndex, 0), &leftExpInstruction);
        InterCodeInstruction rightExpInstruction = {NULL, NULL, REQ_NO};
        InterCodeHandle childExp2Handle = InterCodeGenerate_Exp(GET_CHILD(nodeIndex, 2), &rightExpInstruction);
        
        if(childExp1Handle->specialReply != REP_IS_ADDRESS)
        {
            // Left is neither a struct member nor an array element
            // (access to these 2 case will return address)
            // the only possible case is that it's a normal variable (ID)
            // then, the only case we need its address is that it's a struct variable or an array variable
            // but the assign between struct variable is not supported in this compiler
            // neither the array's assignment
            // the only case is that it's a normal variable
            
            // we need to generate the code:
            // [Exp2's code]
            // [Exp1's code]
            // [Exp1's retval] := [Exp2's retval]
            InterCodeHandle_newCode(childExp1Handle, IC_ASSIGN, 2,
                                    childExp1Handle->returnType, childExp1Handle->returnID,
                                    childExp2Handle->returnType, childExp2Handle->returnID);
        } else{
            // assign to address
            // we need to generate the code:
            // [Exp2's code]
            // [Exp1's code]
            // *([Exp1's retval]) := [Exp2's retval]
            InterCodeHandle_newCode(childExp1Handle, IC_ASSIGN_LDEREF, 2,
                                    childExp1Handle->returnType, childExp1Handle->returnID,
                                    childExp2Handle->returnType, childExp2Handle->returnID);
        }
        int retValID = childExp1Handle->returnID;
        InterCodeHandle retHandle = InterCodeHandle_merge(childExp1Handle, childExp2Handle);
        retHandle->returnID = retValID;
        retHandle->returnType = ICP_VAR;
        return retHandle;
    }
    else if(isChildrenMatchRule(nodeIndex, 2, EXP, AND, EXP)){
        // we need to implement the short-circuit evaluation
        // code is like:
        // # need ret, label defined
        // [Exp1's code]
        // retVal := 0
        // if Exp1 == 0 GOTO falseLabel
        // [Exp2's code]
        // if Exp2 == 0 GOTO falseLabel
        // retVal := 1
        // GOTO trueLabel
        //
        // # no need ret, label defined
        // [Exp1's code]
        // if Exp1 == 0 GOTO falseLabel
        // [Exp2's code]
        // if Exp2 == 0 GOTO falseLabel
        // GOTO trueLabel
        //
        // # need ret, label not defined
        // [Exp1's code]
        // retVal := 0
        // if Exp1 == 0 GOTO newLabel
        // [Exp2's code]
        // if Exp2 == 0 GOTO newLabel
        // retVal := 1
        // LABEL newLabel:

        char* trueLabel = superInstruction->trueLabel;
        char* falseLabel = superInstruction->falseLabel;
        char newLabel[100];
        int bNeedDefineLabel = 0;
        InterCodeInstruction instruction = {NULL, NULL, REQ_NO};
        InterCodeHandle childExp1Handle = InterCodeGenerate_Exp(GET_CHILD(nodeIndex, 0), &instruction);
        InterCodeHandle childExp2Handle = InterCodeGenerate_Exp(GET_CHILD(nodeIndex, 2), &instruction);
        if(trueLabel == NULL)
        {
            SymbolTable_generateNextLabelName(symbolTable_IC, newLabel, 100);
            trueLabel = newLabel;
            falseLabel = newLabel;
            bNeedDefineLabel = 1;
        }
        int retVarID = INVALID_VAR_ID;
        if(superInstruction->specialRequest != REQ_NORETURN)
        {
            retVarID = SymbolTable_getNextVarID(symbolTable_IC);
            InterCodeHandle_newCode(childExp1Handle, IC_ASSIGN, 2,
                                    ICP_VAR, retVarID,
                                    ICP_INT, 0);
        }
        InterCodeHandle_newCode(childExp1Handle, IC_EQ_GOTO, 3,
                                childExp1Handle->returnType, childExp1Handle->returnID,
                                ICP_INT, 0,
                                ICP_LABEL, falseLabel);
        InterCodeHandle_newCode(childExp2Handle, IC_EQ_GOTO, 3,
                                childExp2Handle->returnType, childExp2Handle->returnID,
                                ICP_INT, 0,
                                ICP_LABEL, falseLabel);
        if(superInstruction->specialRequest != REQ_NORETURN)
        {
            InterCodeHandle_newCode(childExp2Handle, IC_ASSIGN, 2,
                                    ICP_VAR, retVarID,
                                    ICP_INT, 1);
        }
        if(bNeedDefineLabel) {
            InterCodeHandle_newCode(childExp2Handle, IC_LABEL, 1,
                                    ICP_LABEL, trueLabel);
        }else{
            InterCodeHandle_newCode(childExp2Handle, IC_GOTO, 1,
                                    ICP_LABEL, trueLabel);
        }
        childExp2Handle->returnID = retVarID;
        childExp2Handle->returnType = ICP_VAR;
        return InterCodeHandle_merge(childExp1Handle, childExp2Handle);
    }
    else if(isChildrenMatchRule(nodeIndex, 2, EXP, OR, EXP)){
        // we need to implement the short-circuit evaluation
        // code is like:
        // # need ret, label defined
        // [Exp1's code]
        // retVal := 1
        // if Exp1 != 0 GOTO trueLabel
        // [Exp2's code]
        // if Exp2 != 0 GOTO trueLabel
        // retVal := 0
        // GOTO falseLabel
        //
        // # no need ret, label defined
        // [Exp1's code]
        // if Exp1 != 0 GOTO trueLabel
        // [Exp2's code]
        // if Exp2 != 0 GOTO trueLabel
        // GOTO falseLabel
        //
        // # need ret, label not defined
        // [Exp1's code]
        // retVal := 1
        // if Exp1 != 0 GOTO newLabel
        // [Exp2's code]
        // if Exp2 != 0 GOTO newLabel
        // retVal := 0
        // LABEL newLabel:

        char* trueLabel = superInstruction->trueLabel;
        char* falseLabel = superInstruction->falseLabel;
        char newLabel[100];
        int bNeedDefineLabel = 0;
        InterCodeInstruction instruction = {NULL, NULL, REQ_NO};
        InterCodeHandle childExp1Handle = InterCodeGenerate_Exp(GET_CHILD(nodeIndex, 0), &instruction);
        InterCodeHandle childExp2Handle = InterCodeGenerate_Exp(GET_CHILD(nodeIndex, 2), &instruction);
        if(trueLabel == NULL)
        {
            SymbolTable_generateNextLabelName(symbolTable_IC, newLabel, 100);
            trueLabel = newLabel;
            falseLabel = newLabel;
            bNeedDefineLabel = 1;
        }
        int retVarID = INVALID_VAR_ID;
        if(superInstruction->specialRequest != REQ_NORETURN)
        {
            retVarID = SymbolTable_getNextVarID(symbolTable_IC);
            InterCodeHandle_newCode(childExp1Handle, IC_ASSIGN, 2,
                                    ICP_VAR, retVarID,
                                    ICP_INT, 1);
        }
        InterCodeHandle_newCode(childExp1Handle, IC_NE_GOTO, 3,
                                childExp1Handle->returnType, childExp1Handle->returnID,
                                ICP_INT, 0,
                                ICP_LABEL, trueLabel);
        InterCodeHandle_newCode(childExp2Handle, IC_NE_GOTO, 3,
                                childExp2Handle->returnType, childExp2Handle->returnID,
                                ICP_INT, 0,
                                ICP_LABEL, trueLabel);
        if(superInstruction->specialRequest != REQ_NORETURN)
        {
            InterCodeHandle_newCode(childExp2Handle, IC_ASSIGN, 2,
                                    ICP_VAR, retVarID,
                                    ICP_INT, 0);
        }
        if(bNeedDefineLabel) {
            InterCodeHandle_newCode(childExp2Handle, IC_LABEL, 1,
                                    ICP_LABEL, trueLabel);
        }else{
            InterCodeHandle_newCode(childExp2Handle, IC_GOTO, 1,
                                    ICP_LABEL, falseLabel);
        }
        childExp2Handle->returnID = retVarID;
        childExp2Handle->returnType = ICP_VAR;
        return InterCodeHandle_merge(childExp1Handle, childExp2Handle);
    }
    else if(isChildrenMatchRule(nodeIndex, 3, EXP, EQ, EXP)){
        // code:
        // # need ret, label defined
        // [Exp1's code]
        // [Exp2's code]
        // retVal := 1
        // if Exp1 == Exp2 GOTO trueLabel
        // retVal := 0
        // GOTO falseLabel
        //
        // # no need ret, label defined
        // [Exp1's code]
        // [Exp2's code]
        // if Exp1 == Exp2 GOTO trueLabel
        // GOTO falseLabel
        //
        // # need ret, label not defined
        // [Exp1's code]
        // [Exp2's code]
        // retVal := 1
        // if Exp1 == Exp2 GOTO newLabel
        // retVal := 0
        // LABEL newLabel:

        char* trueLabel = superInstruction->trueLabel;
        char* falseLabel = superInstruction->falseLabel;
        char newLabel[100];
        int bNeedDefineLabel = 0;
        InterCodeInstruction instruction = {NULL, NULL, REQ_NO};
        InterCodeHandle childExp1Handle = InterCodeGenerate_Exp(GET_CHILD(nodeIndex, 0), &instruction);
        InterCodeHandle childExp2Handle = InterCodeGenerate_Exp(GET_CHILD(nodeIndex, 2), &instruction);
        if(trueLabel == NULL)
        {
            SymbolTable_generateNextLabelName(symbolTable_IC, newLabel, 100);
            trueLabel = newLabel;
            falseLabel = newLabel;
            bNeedDefineLabel = 1;
        }
        int retVarID = INVALID_VAR_ID;
        if(superInstruction->specialRequest != REQ_NORETURN)
        {
            retVarID = SymbolTable_getNextVarID(symbolTable_IC);
            InterCodeHandle_newCode(childExp2Handle, IC_ASSIGN, 2,
                                    ICP_VAR, retVarID,
                                    ICP_INT, 1);
        }
        InterCodeHandle_newCode(childExp2Handle, IC_EQ_GOTO, 3,
                                childExp1Handle->returnType, childExp1Handle->returnID,
                                childExp2Handle->returnType, childExp2Handle->returnID,
                                ICP_LABEL, trueLabel);
        if(superInstruction->specialRequest != REQ_NORETURN)
        {
            InterCodeHandle_newCode(childExp2Handle, IC_ASSIGN, 2,
                                    ICP_VAR, retVarID,
                                    ICP_INT, 0);
        }
        if(bNeedDefineLabel)
        {
            InterCodeHandle_newCode(childExp2Handle, IC_LABEL, 1,
                                    ICP_LABEL, trueLabel);
        }else{
            InterCodeHandle_newCode(childExp2Handle, IC_GOTO, 1,
                                    ICP_LABEL, falseLabel);
        }
        childExp2Handle->returnID = retVarID;
        childExp2Handle->returnType = ICP_VAR;
        return InterCodeHandle_merge(childExp1Handle, childExp2Handle);
    }
    else if(isChildrenMatchRule(nodeIndex, 3, EXP, NEQ, EXP)){
        // code:
        // # need ret, label defined
        // [Exp1's code]
        // [Exp2's code]
        // retVal := 1
        // if Exp1 != Exp2 GOTO trueLabel
        // retVal := 0
        // GOTO falseLabel
        //
        // # no need ret, label defined
        // [Exp1's code]
        // [Exp2's code]
        // if Exp1 != Exp2 GOTO trueLabel
        // GOTO falseLabel
        //
        // # need ret, label not defined
        // [Exp1's code]
        // [Exp2's code]
        // retVal := 1
        // if Exp1 != Exp2 GOTO newLabel
        // retVal := 0
        // LABEL newLabel:

        char* trueLabel = superInstruction->trueLabel;
        char* falseLabel = superInstruction->falseLabel;
        char newLabel[100];
        int bNeedDefineLabel = 0;
        InterCodeInstruction instruction = {NULL, NULL, REQ_NO};
        InterCodeHandle childExp1Handle = InterCodeGenerate_Exp(GET_CHILD(nodeIndex, 0), &instruction);
        InterCodeHandle childExp2Handle = InterCodeGenerate_Exp(GET_CHILD(nodeIndex, 2), &instruction);
        if(trueLabel == NULL)
        {
            SymbolTable_generateNextLabelName(symbolTable_IC, newLabel, 100);
            trueLabel = newLabel;
            falseLabel = newLabel;
            bNeedDefineLabel = 1;
        }
        int retVarID = INVALID_VAR_ID;
        if(superInstruction->specialRequest != REQ_NORETURN)
        {
            retVarID = SymbolTable_getNextVarID(symbolTable_IC);
            InterCodeHandle_newCode(childExp2Handle, IC_ASSIGN, 2,
                                    ICP_VAR, retVarID,
                                    ICP_INT, 1);
        }
        InterCodeHandle_newCode(childExp2Handle, IC_NE_GOTO, 3,
                                childExp1Handle->returnType, childExp1Handle->returnID,
                                childExp2Handle->returnType, childExp2Handle->returnID,
                                ICP_LABEL, trueLabel);
        if(superInstruction->specialRequest != REQ_NORETURN)
        {
            InterCodeHandle_newCode(childExp2Handle, IC_ASSIGN, 2,
                                    ICP_VAR, retVarID,
                                    ICP_INT, 0);
        }
        if(bNeedDefineLabel)
        {
            InterCodeHandle_newCode(childExp2Handle, IC_LABEL, 1,
                                    ICP_LABEL, trueLabel);
        }else{
            InterCodeHandle_newCode(childExp2Handle, IC_GOTO, 1,
                                    ICP_LABEL, falseLabel);
        }
        childExp2Handle->returnID = retVarID;
        childExp2Handle->returnType = ICP_VAR;
        return InterCodeHandle_merge(childExp1Handle, childExp2Handle);
    }
    else if(isChildrenMatchRule(nodeIndex, 3, EXP, GE, EXP)){
        // code:
        // # need ret, label defined
        // [Exp1's code]
        // [Exp2's code]
        // retVal := 1
        // if Exp1 >= Exp2 GOTO trueLabel
        // retVal := 0
        // GOTO falseLabel
        //
        // # no need ret, label defined
        // [Exp1's code]
        // [Exp2's code]
        // if Exp1 >= Exp2 GOTO trueLabel
        // GOTO falseLabel
        //
        // # need ret, label not defined
        // [Exp1's code]
        // [Exp2's code]
        // retVal := 1
        // if Exp1 >= Exp2 GOTO newLabel
        // retVal := 0
        // LABEL newLabel:

        char* trueLabel = superInstruction->trueLabel;
        char* falseLabel = superInstruction->falseLabel;
        char newLabel[100];
        int bNeedDefineLabel = 0;
        InterCodeInstruction instruction = {NULL, NULL, REQ_NO};
        InterCodeHandle childExp1Handle = InterCodeGenerate_Exp(GET_CHILD(nodeIndex, 0), &instruction);
        InterCodeHandle childExp2Handle = InterCodeGenerate_Exp(GET_CHILD(nodeIndex, 2), &instruction);
        if(trueLabel == NULL)
        {
            SymbolTable_generateNextLabelName(symbolTable_IC, newLabel, 100);
            trueLabel = newLabel;
            falseLabel = newLabel;
            bNeedDefineLabel = 1;
        }
        int retVarID = INVALID_VAR_ID;
        if(superInstruction->specialRequest != REQ_NORETURN)
        {
            retVarID = SymbolTable_getNextVarID(symbolTable_IC);
            InterCodeHandle_newCode(childExp2Handle, IC_ASSIGN, 2,
                                    ICP_VAR, retVarID,
                                    ICP_INT, 1);
        }
        InterCodeHandle_newCode(childExp2Handle, IC_GE_GOTO, 3,
                                childExp1Handle->returnType, childExp1Handle->returnID,
                                childExp2Handle->returnType, childExp2Handle->returnID,
                                ICP_LABEL, trueLabel);
        if(superInstruction->specialRequest != REQ_NORETURN)
        {
            InterCodeHandle_newCode(childExp2Handle, IC_ASSIGN, 2,
                                    ICP_VAR, retVarID,
                                    ICP_INT, 0);
        }
        if(bNeedDefineLabel)
        {
            InterCodeHandle_newCode(childExp2Handle, IC_LABEL, 1,
                                    ICP_LABEL, trueLabel);
        }else{
            InterCodeHandle_newCode(childExp2Handle, IC_GOTO, 1,
                                    ICP_LABEL, falseLabel);
        }
        childExp2Handle->returnID = retVarID;
        childExp2Handle->returnType = ICP_VAR;
        return InterCodeHandle_merge(childExp1Handle, childExp2Handle);
    }
    else if(isChildrenMatchRule(nodeIndex, 3, EXP, GT, EXP)){
// code:
        // # need ret, label defined
        // [Exp1's code]
        // [Exp2's code]
        // retVal := 1
        // if Exp1 > Exp2 GOTO trueLabel
        // retVal := 0
        // GOTO falseLabel
        //
        // # no need ret, label defined
        // [Exp1's code]
        // [Exp2's code]
        // if Exp1 > Exp2 GOTO trueLabel
        // GOTO falseLabel
        //
        // # need ret, label not defined
        // [Exp1's code]
        // [Exp2's code]
        // retVal := 1
        // if Exp1 > Exp2 GOTO newLabel
        // retVal := 0
        // LABEL newLabel:

        char* trueLabel = superInstruction->trueLabel;
        char* falseLabel = superInstruction->falseLabel;
        char newLabel[100];
        int bNeedDefineLabel = 0;
        InterCodeInstruction instruction = {NULL, NULL, REQ_NO};
        InterCodeHandle childExp1Handle = InterCodeGenerate_Exp(GET_CHILD(nodeIndex, 0), &instruction);
        InterCodeHandle childExp2Handle = InterCodeGenerate_Exp(GET_CHILD(nodeIndex, 2), &instruction);
        if(trueLabel == NULL)
        {
            SymbolTable_generateNextLabelName(symbolTable_IC, newLabel, 100);
            trueLabel = newLabel;
            falseLabel = newLabel;
            bNeedDefineLabel = 1;
        }
        int retVarID = INVALID_VAR_ID;
        if(superInstruction->specialRequest != REQ_NORETURN)
        {
            retVarID = SymbolTable_getNextVarID(symbolTable_IC);
            InterCodeHandle_newCode(childExp2Handle, IC_ASSIGN, 2,
                                    ICP_VAR, retVarID,
                                    ICP_INT, 1);
        }
        InterCodeHandle_newCode(childExp2Handle, IC_GT_GOTO, 3,
                                childExp1Handle->returnType, childExp1Handle->returnID,
                                childExp2Handle->returnType, childExp2Handle->returnID,
                                ICP_LABEL, trueLabel);
        if(superInstruction->specialRequest != REQ_NORETURN)
        {
            InterCodeHandle_newCode(childExp2Handle, IC_ASSIGN, 2,
                                    ICP_VAR, retVarID,
                                    ICP_INT, 0);
        }
        if(bNeedDefineLabel)
        {
            InterCodeHandle_newCode(childExp2Handle, IC_LABEL, 1,
                                    ICP_LABEL, trueLabel);
        }else{
            InterCodeHandle_newCode(childExp2Handle, IC_GOTO, 1,
                                    ICP_LABEL, falseLabel);
        }
        childExp2Handle->returnID = retVarID;
        childExp2Handle->returnType = ICP_VAR;
        return InterCodeHandle_merge(childExp1Handle, childExp2Handle);
    }
    else if(isChildrenMatchRule(nodeIndex, 3, EXP, LE, EXP)){
// code:
        // # need ret, label defined
        // [Exp1's code]
        // [Exp2's code]
        // retVal := 1
        // if Exp1 <= Exp2 GOTO trueLabel
        // retVal := 0
        // GOTO falseLabel
        //
        // # no need ret, label defined
        // [Exp1's code]
        // [Exp2's code]
        // if Exp1 <= Exp2 GOTO trueLabel
        // GOTO falseLabel
        //
        // # need ret, label not defined
        // [Exp1's code]
        // [Exp2's code]
        // retVal := 1
        // if Exp1 <= Exp2 GOTO newLabel
        // retVal := 0
        // LABEL newLabel:

        char* trueLabel = superInstruction->trueLabel;
        char* falseLabel = superInstruction->falseLabel;
        char newLabel[100];
        int bNeedDefineLabel = 0;
        InterCodeInstruction instruction = {NULL, NULL, REQ_NO};
        InterCodeHandle childExp1Handle = InterCodeGenerate_Exp(GET_CHILD(nodeIndex, 0), &instruction);
        InterCodeHandle childExp2Handle = InterCodeGenerate_Exp(GET_CHILD(nodeIndex, 2), &instruction);
        if(trueLabel == NULL)
        {
            SymbolTable_generateNextLabelName(symbolTable_IC, newLabel, 100);
            trueLabel = newLabel;
            falseLabel = newLabel;
            bNeedDefineLabel = 1;
        }
        int retVarID = INVALID_VAR_ID;
        if(superInstruction->specialRequest != REQ_NORETURN)
        {
            retVarID = SymbolTable_getNextVarID(symbolTable_IC);
            InterCodeHandle_newCode(childExp2Handle, IC_ASSIGN, 2,
                                    ICP_VAR, retVarID,
                                    ICP_INT, 1);
        }
        InterCodeHandle_newCode(childExp2Handle, IC_LE_GOTO, 3,
                                childExp1Handle->returnType, childExp1Handle->returnID,
                                childExp2Handle->returnType, childExp2Handle->returnID,
                                ICP_LABEL, trueLabel);
        if(superInstruction->specialRequest != REQ_NORETURN)
        {
            InterCodeHandle_newCode(childExp2Handle, IC_ASSIGN, 2,
                                    ICP_VAR, retVarID,
                                    ICP_INT, 0);
        }
        if(bNeedDefineLabel)
        {
            InterCodeHandle_newCode(childExp2Handle, IC_LABEL, 1,
                                    ICP_LABEL, trueLabel);
        }else{
            InterCodeHandle_newCode(childExp2Handle, IC_GOTO, 1,
                                    ICP_LABEL, falseLabel);
        }
        childExp2Handle->returnID = retVarID;
        childExp2Handle->returnType = ICP_VAR;
        return InterCodeHandle_merge(childExp1Handle, childExp2Handle);
    }
    else if(isChildrenMatchRule(nodeIndex, 3, EXP, LT, EXP)){
        // code:
        // # need ret, label defined
        // [Exp1's code]
        // [Exp2's code]
        // retVal := 1
        // if Exp1 < Exp2 GOTO trueLabel
        // retVal := 0
        // GOTO falseLabel
        //
        // # no need ret, label defined
        // [Exp1's code]
        // [Exp2's code]
        // if Exp1 < Exp2 GOTO trueLabel
        // GOTO falseLabel
        //
        // # need ret, label not defined
        // [Exp1's code]
        // [Exp2's code]
        // retVal := 1
        // if Exp1 < Exp2 GOTO newLabel
        // retVal := 0
        // LABEL newLabel:

        char* trueLabel = superInstruction->trueLabel;
        char* falseLabel = superInstruction->falseLabel;
        char newLabel[100];
        int bNeedDefineLabel = 0;
        InterCodeInstruction instruction = {NULL, NULL, REQ_NO};
        InterCodeHandle childExp1Handle = InterCodeGenerate_Exp(GET_CHILD(nodeIndex, 0), &instruction);
        InterCodeHandle childExp2Handle = InterCodeGenerate_Exp(GET_CHILD(nodeIndex, 2), &instruction);
        if(trueLabel == NULL)
        {
            SymbolTable_generateNextLabelName(symbolTable_IC, newLabel, 100);
            trueLabel = newLabel;
            falseLabel = newLabel;
            bNeedDefineLabel = 1;
        }
        int retVarID = INVALID_VAR_ID;
        if(superInstruction->specialRequest != REQ_NORETURN)
        {
            retVarID = SymbolTable_getNextVarID(symbolTable_IC);
            InterCodeHandle_newCode(childExp2Handle, IC_ASSIGN, 2,
                                    ICP_VAR, retVarID,
                                    ICP_INT, 1);
        }
        InterCodeHandle_newCode(childExp2Handle, IC_LT_GOTO, 3,
                                childExp1Handle->returnType, childExp1Handle->returnID,
                                childExp2Handle->returnType, childExp2Handle->returnID,
                                ICP_LABEL, trueLabel);
        if(superInstruction->specialRequest != REQ_NORETURN)
        {
            InterCodeHandle_newCode(childExp2Handle, IC_ASSIGN, 2,
                                    ICP_VAR, retVarID,
                                    ICP_INT, 0);
        }
        if(bNeedDefineLabel)
        {
            InterCodeHandle_newCode(childExp2Handle, IC_LABEL, 1,
                                    ICP_LABEL, trueLabel);
        }else{
            InterCodeHandle_newCode(childExp2Handle, IC_GOTO, 1,
                                    ICP_LABEL, falseLabel);
        }
        childExp2Handle->returnID = retVarID;
        childExp2Handle->returnType = ICP_VAR;
        return InterCodeHandle_merge(childExp1Handle, childExp2Handle);
    }
    else if(isChildrenMatchRule(nodeIndex, 3, EXP, PLUS, EXP)){
        // easy
        // code:
        // [Exp1's code]
        // [Exp2's code]
        // retVal := Exp1 + Exp2
        InterCodeInstruction instruction = {NULL, NULL, REQ_NO};
        InterCodeHandle childExp1Handle = InterCodeGenerate_Exp(GET_CHILD(nodeIndex, 0), &instruction);
        InterCodeHandle childExp2Handle = InterCodeGenerate_Exp(GET_CHILD(nodeIndex, 2), &instruction);
        int retVarID = SymbolTable_getNextVarID(symbolTable_IC);
        InterCodeHandle_newCode(childExp2Handle, IC_ADD, 3,
                                ICP_VAR, retVarID,
                                childExp1Handle->returnType, childExp1Handle->returnID,
                                childExp2Handle->returnType, childExp2Handle->returnID);
        childExp2Handle->returnID = retVarID;
        childExp2Handle->returnType = ICP_VAR;
        return InterCodeHandle_merge(childExp1Handle, childExp2Handle);
    }
    else if(isChildrenMatchRule(nodeIndex, 3, EXP, MINUS, EXP)){
        // easy
        // code:
        // [Exp1's code]
        // [Exp2's code]
        // retVal := Exp1 - Exp2
        InterCodeInstruction instruction = {NULL, NULL, REQ_NO};
        InterCodeHandle childExp1Handle = InterCodeGenerate_Exp(GET_CHILD(nodeIndex, 0), &instruction);
        InterCodeHandle childExp2Handle = InterCodeGenerate_Exp(GET_CHILD(nodeIndex, 2), &instruction);
        int retVarID = SymbolTable_getNextVarID(symbolTable_IC);
        InterCodeHandle_newCode(childExp2Handle, IC_SUB, 3,
                                ICP_VAR, retVarID,
                                childExp1Handle->returnType, childExp1Handle->returnID,
                                childExp2Handle->returnType, childExp2Handle->returnID);
        childExp2Handle->returnID = retVarID;
        childExp2Handle->returnType = ICP_VAR;
        return InterCodeHandle_merge(childExp1Handle, childExp2Handle);
    }
    else if(isChildrenMatchRule(nodeIndex, 3, EXP, STAR, EXP)){
        // easy
        // code:
        // [Exp1's code]
        // [Exp2's code]
        // retVal := Exp1 * Exp2
        InterCodeInstruction instruction = {NULL, NULL, REQ_NO};
        InterCodeHandle childExp1Handle = InterCodeGenerate_Exp(GET_CHILD(nodeIndex, 0), &instruction);
        InterCodeHandle childExp2Handle = InterCodeGenerate_Exp(GET_CHILD(nodeIndex, 2), &instruction);
        int retVarID = SymbolTable_getNextVarID(symbolTable_IC);
        InterCodeHandle_newCode(childExp2Handle, IC_MUL, 3,
                                ICP_VAR, retVarID,
                                childExp1Handle->returnType, childExp1Handle->returnID,
                                childExp2Handle->returnType, childExp2Handle->returnID);
        childExp2Handle->returnID = retVarID;
        childExp2Handle->returnType = ICP_VAR;
        return InterCodeHandle_merge(childExp1Handle, childExp2Handle);
    }
    else if(isChildrenMatchRule(nodeIndex, 3, EXP, DIV, EXP)){
        // easy
        // code:
        // [Exp1's code]
        // [Exp2's code]
        // retVal := Exp1 / Exp2
        InterCodeInstruction instruction = {NULL, NULL, REQ_NO};
        InterCodeHandle childExp1Handle = InterCodeGenerate_Exp(GET_CHILD(nodeIndex, 0), &instruction);
        InterCodeHandle childExp2Handle = InterCodeGenerate_Exp(GET_CHILD(nodeIndex, 2), &instruction);
        int retVarID = SymbolTable_getNextVarID(symbolTable_IC);
        InterCodeHandle_newCode(childExp2Handle, IC_DIV, 3,
                                ICP_VAR, retVarID,
                                childExp1Handle->returnType, childExp1Handle->returnID,
                                childExp2Handle->returnType, childExp2Handle->returnID);
        childExp2Handle->returnID = retVarID;
        childExp2Handle->returnType = ICP_VAR;
        return InterCodeHandle_merge(childExp1Handle, childExp2Handle);
    }
    else if(isChildrenMatchRule(nodeIndex, 3, LP, EXP, RP)){
        // easy
        // this only make sense when we are doing syntax analyze
        // just return the result of EXP
        InterCodeInstruction instruction = {NULL, NULL, REQ_NO};
        return InterCodeGenerate_Exp(GET_CHILD(nodeIndex, 1), &instruction);
    }
    else if(isChildrenMatchRule(nodeIndex, 2, MINUS, EXP)){
        // easy
        // code:
        // [Exp's code]
        // retVal := 0 - expRet
        InterCodeInstruction instruction = {NULL, NULL, REQ_NO};
        InterCodeHandle childExpHandle = InterCodeGenerate_Exp(GET_CHILD(nodeIndex, 1), &instruction);
        int retVarID = SymbolTable_getNextVarID(symbolTable_IC);
        InterCodeHandle_newCode(childExpHandle, IC_SUB, 3,
                                ICP_VAR, retVarID,
                                ICP_INT, 0,
                                childExpHandle->returnType, childExpHandle->returnID);
        childExpHandle->returnID = retVarID;
        childExpHandle->returnType = ICP_VAR;
        return childExpHandle;
    }
    else if(isChildrenMatchRule(nodeIndex, 2, NOT, EXP)){
        // seems a relop-like sentence
        // codes:

        // # need ret, label defined
        // [Exp's code]
        // retVal := 1
        // if expRet == 0 GOTO trueLabel
        // retVal := 0
        // GOTO falseLabel
        //
        // # no need ret, label defined
        // [Exp's code]
        // if expRet == 0 GOTO trueLabel
        // GOTO falseLabel
        //
        // # need ret, label not defined
        // [Exp's code]
        // retVal := 1
        // if expRet == 0 GOTO [newLabel]
        // retVal := 0
        // LABEL [newLabel]:
        char* trueLabel = superInstruction->trueLabel;
        char* falseLabel = superInstruction->falseLabel;
        char newLabel[100];
        int bNeedDefineLabel = 0;
        if(trueLabel == NULL && falseLabel == NULL){
            // label not defined
            SymbolTable_generateNextLabelName(symbolTable_IC, newLabel, 100);
            trueLabel = newLabel;
            falseLabel = newLabel;
            bNeedDefineLabel = 1;
        }
        InterCodeInstruction instruction = {NULL, NULL, REQ_NO};
        InterCodeHandle childExpHandle = InterCodeGenerate_Exp(GET_CHILD(nodeIndex, 1), &instruction);
        int retVarID = INVALID_VAR_ID;
        if(superInstruction->specialRequest != REQ_NORETURN)
        {
            retVarID = SymbolTable_getNextVarID(symbolTable_IC);
            InterCodeHandle_newCode(childExpHandle, IC_ASSIGN, 2,
                                    ICP_VAR, retVarID,
                                    ICP_INT, 1);
        }
        InterCodeHandle_newCode(childExpHandle, IC_EQ_GOTO, 3,
                                childExpHandle->returnType, childExpHandle->returnID,
                                ICP_INT, 0,
                                ICP_LABEL, trueLabel);
        if(superInstruction->specialRequest != REQ_NORETURN)
        {
            InterCodeHandle_newCode(childExpHandle, IC_ASSIGN, 2,
                                    ICP_VAR, retVarID,
                                    ICP_INT, 0);
        }

        if(bNeedDefineLabel){
            InterCodeHandle_newCode(childExpHandle, IC_LABEL, 1,
                                    ICP_LABEL, falseLabel);
        }else {
            InterCodeHandle_newCode(childExpHandle, IC_GOTO, 1,
                                    ICP_LABEL, falseLabel);
        }

        childExpHandle->returnID = retVarID;
        childExpHandle->returnType = ICP_VAR;

        return childExpHandle;
    }
    else if(isChildrenMatchRule(nodeIndex, 3, ID, LP, RP)){
        // void function call
        // just call function
        // codes:
        // ret := CALL [function name]
        InterCodeHandle functionCallHandle = InterCodeHandle_create();
        int retVarID = SymbolTable_getNextVarID(symbolTable_IC);
        InterCodeHandle_newCode(functionCallHandle, IC_CALL, 2,
                                ICP_VAR, retVarID,
                                ICP_LABEL, GET_NODE(GET_CHILD(nodeIndex, 0))->ID);
        functionCallHandle->returnID = retVarID;
        functionCallHandle->returnType = ICP_VAR;
        return functionCallHandle;
    }
    else if(isChildrenMatchRule(nodeIndex, 4, ID, LP, ARGS, RP)){
        // a function call
        // directly extract the varID of args and call ARG&function name
        // codes:
        // [Args' code]
        // ret := CALL [function name]
        InterCodeHandle childArgsHandle = InterCodeGenerate_Args(GET_CHILD(nodeIndex, 2));
        int retVarID = SymbolTable_getNextVarID(symbolTable_IC);
        InterCodeHandle_newCode(childArgsHandle, IC_CALL, 2,
                                ICP_VAR, retVarID,
                                ICP_LABEL, GET_NODE(GET_CHILD(nodeIndex, 0))->ID);
        childArgsHandle->returnID = retVarID;
        childArgsHandle->returnType = ICP_VAR;
        return childArgsHandle;
    }
    else if(isChildrenMatchRule(nodeIndex, 4, EXP, LB, EXP, RB)){
        // another offset calculation
        // just like the struct case
        SymbolInfo_Array_t arrayInfo = GET_CHILD_NODE(nodeIndex, 0)->semanticInfo->valueInfo;
        // we need the address of the array variable to get the member
        // construct a special request REQ_ADDRESS
        InterCodeInstruction instruction = {NULL, NULL, REQ_ADDRESS};
        InterCodeHandle childExpHandle_Array = InterCodeGenerate_Exp(GET_CHILD(nodeIndex, 0), &instruction);
        int addrVarID = INVALID_VAR_ID;
        InterCodeParam_Type addrVarType = ICP_VAR;
        if (childExpHandle_Array->specialReply == REP_IS_ADDRESS) {
            // below layer returns address
            // directly use that
            addrVarID = childExpHandle_Array->returnID;
            addrVarType = childExpHandle_Array->returnType;
        } else {
            // below layer ignored the special request
            // means that it's a normal variable
            // get the address manually.
            addrVarID = SymbolTable_getNextVarID(symbolTable_IC);
            addrVarType = ICP_VAR;
            InterCodeHandle_newCode(childExpHandle_Array, IC_ADDR, 2,
                                    addrVarType, addrVarID,
                                    childExpHandle_Array->returnType, childExpHandle_Array->returnID);
        }
        // get the member's address
        InterCodeHandle childExpHandle_Index = InterCodeGenerate_Exp(GET_CHILD(nodeIndex, 2), NULL);
        int offsetVarID = SymbolTable_getNextVarID(symbolTable_IC);
        int elementSize = SymbolValue_getSize(arrayInfo->elementType, arrayInfo->elementMeta);
        InterCodeHandle_newCode(childExpHandle_Index, IC_MUL, 3,
                                ICP_VAR, offsetVarID,
                                childExpHandle_Index->returnType, childExpHandle_Index->returnID,
                                ICP_INT, elementSize);
        int elementAddrVarID = SymbolTable_getNextVarID(symbolTable_IC);
        InterCodeHandle_newCode(childExpHandle_Index, IC_ADD, 3,
                                ICP_VAR, elementAddrVarID,
                                addrVarType, addrVarID,
                                ICP_VAR, offsetVarID);
        if(superInstruction->specialRequest == REQ_ADDRESS) {
            // this will be needed by nested struct or assign to member
            childExpHandle_Index->returnID = elementAddrVarID;
            childExpHandle_Index->returnType = ICP_VAR;
            childExpHandle_Index->specialReply = REP_IS_ADDRESS;
            return childExpHandle_Index;
        }else{
            // this will be needed by normal use
            int elementVarID = SymbolTable_getNextVarID(symbolTable_IC);
            InterCodeHandle_newCode(childExpHandle_Index, IC_ASSIGN_RDEREF, 2,
                                    ICP_VAR, elementVarID,
                                    ICP_VAR, elementAddrVarID);
            childExpHandle_Index->returnID = elementVarID;
            childExpHandle_Index->returnType = ICP_VAR;
            childExpHandle_Index->specialReply = REP_NO;
            return childExpHandle_Index;
        }
    }
    else if(isChildrenMatchRule(nodeIndex, 4, EXP, DOT, ID)){
        // get struct info from semantic info
        // hmmm seems we can directly get the isDefined from semantic analyze.
        // wait seems we should calculate the size of struct and its member when we
        // analyze that.
        // codes:
        // [Exp's code]
        // [AddrVar] := &[Exp's retval]  (if below layer did not return the address)
        // [MemberVar] := [AddrVar] + [Member's offset]
        // [retVal] := *[MemberVar]

        SymbolInfo_Struct_t structInfo = GET_CHILD_NODE(nodeIndex, 0)->semanticInfo->valueInfo;
        // we need the address of the struct variable to get the member
        // construct a special request REQ_ADDRESS
        InterCodeInstruction instruction = {NULL, NULL, REQ_ADDRESS};
        InterCodeHandle childExpHandle = InterCodeGenerate_Exp(GET_CHILD(nodeIndex, 0), &instruction);
        int addrVarID = INVALID_VAR_ID;
        InterCodeParam_Type addrVarType = ICP_VAR;
        if (childExpHandle->specialReply == REP_IS_ADDRESS) {
            // below layer returns address
            // directly use that
            addrVarID = childExpHandle->returnID;
            addrVarType = childExpHandle->returnType;
        } else {
            // below layer ignored the special request
            // means that it's a normal variable
            // get the address manually.
            addrVarID = SymbolTable_getNextVarID(symbolTable_IC);
            addrVarType = ICP_VAR;
            InterCodeHandle_newCode(childExpHandle, IC_ADDR, 2,
                                    addrVarType, addrVarID,
                                    childExpHandle->returnType, childExpHandle->returnID);
        }
        // get the member's address
        SymbolInfo_Member_t member = SemanticInfo_getMemberInfo(GET_CHILD_NODE(nodeIndex, 0)->semanticInfo,
                                                                GET_NODE(GET_CHILD(nodeIndex, 2))->ID);
        int memberAddrVarID = SymbolTable_getNextVarID(symbolTable_IC);
        InterCodeHandle_newCode(childExpHandle, IC_ADD, 3,
                                ICP_VAR, memberAddrVarID,
                                addrVarType, addrVarID,
                                ICP_INT, member->offset);
        if(superInstruction->specialRequest == REQ_ADDRESS){
            // this will be needed by nested struct or assign to member
            childExpHandle->returnID = memberAddrVarID;
            childExpHandle->returnType = ICP_VAR;
            childExpHandle->specialReply = REP_IS_ADDRESS;
            return childExpHandle;
        }else{
            // this will be needed by normal use
            int memberVarID = SymbolTable_getNextVarID(symbolTable_IC);
            InterCodeHandle_newCode(childExpHandle, IC_ASSIGN_RDEREF, 2,
                                    ICP_VAR, memberVarID,
                                    ICP_VAR, memberAddrVarID);
            childExpHandle->returnID = memberVarID;
            childExpHandle->returnType = ICP_VAR;
            childExpHandle->specialReply = REP_NO;
            return childExpHandle;
        }
    }
    else if(isChildrenMatchRule(nodeIndex, 1, ID)){
        // we always return the value of the variable when it's an ID
        // there's more complex situation for param
        // the struct and array param will be referenced by address

        SymbolInfo_Variable_t variableInfo = GET_CHILD_NODE(nodeIndex, 0)->semanticInfo->variableInfo;
        if(variableInfo->bIsParam){
            InterCodeHandle handle = InterCodeHandle_create();
            handle->returnType = ICP_PARAM;
            handle->returnID = variableInfo->varID;
            // get current FunctionInfo to check if it's a struct or array
            // if it is,
            // handle->specialReply = REP_IS_ADDRESS;
            if(isParamAddressReferenced[variableInfo->varID-1]){
                handle->specialReply = REP_IS_ADDRESS;
            }
            return handle;
        }
        else{
            InterCodeHandle handle = InterCodeHandle_create();
            handle->returnType = ICP_VAR;
            handle->returnID = variableInfo->varID;
            return handle;
        }
    }
    else if(isChildrenMatchRule(nodeIndex, 1, INT)){
        InterCodeHandle handle = InterCodeHandle_create();
        handle->returnType = ICP_INT;
        handle->returnID = GET_CHILD_NODE(nodeIndex, 0)->intVal;
    }
    else if(isChildrenMatchRule(nodeIndex, 1, FLOAT)){
        reportErrorFormat(GET_NODE(nodeIndex)->lineNum, UNDEF_SEMANTIC_ERROR, "Float is not supported in intermediate code.");
        exit(-1);
    }
    return InterCodeHandle_create();
}

InterCodeHandle InterCodeGenerate_Args(ParserNode_I nodeIndex){
    if(isChildrenMatchRule(nodeIndex, 1, EXP))
    {
        // code:
        // [Exp's code]
        // ARG [Exp's retval]

        // for array and struct, we need to get the address
        // in semantic analyze we have got the type/type meta of Exp, which was stored in the semantic info
        // remember that we need the address ONLY WHEN the arg is an array or struct
        // for nested struct, we will need the struct typed member's address, the plain member's value
        // for array, we will need the array's address, the element's value
        // if array has more than one dimension, we will need the address of the element
        Symbol_Value_Type valueType = GET_CHILD_NODE(nodeIndex, 0)->semanticInfo->valueType;
        InterCodeInstruction instruction = {NULL, NULL, REQ_NO};
        if(valueType == SVT_Array || valueType == SVT_Struct){
            instruction.specialRequest = REQ_ADDRESS;
        }

        InterCodeHandle childExpHandle = InterCodeGenerate_Exp(GET_CHILD(nodeIndex, 0), &instruction);

        if(valueType == SVT_Array || valueType == SVT_Struct && childExpHandle->specialReply != REP_IS_ADDRESS){
            // when the EXP is an ID, the reply will be the variable itself
            // we will get the address of the variable
            // avoid polluting the variable we use a new variable to store the address
            int addrVarID = SymbolTable_getNextVarID(symbolTable_IC);
            InterCodeHandle_newCode(childExpHandle, IC_ADDR, 2,
                                    ICP_VAR, addrVarID,
                                    childExpHandle->returnType, childExpHandle->returnID);
            InterCodeHandle_newCode(childExpHandle, IC_ARG, 1,
                                    ICP_VAR, addrVarID);
        }else{
            // when the Exp is a member or array access, the reply will be the address
            InterCodeHandle_newCode(childExpHandle, IC_ARG, 1,
                                    childExpHandle->returnType, childExpHandle->returnID);
        }
        // in other situations, the reply will be the value
        return childExpHandle;
    }
    else if(isChildrenMatchRule(nodeIndex, 3, EXP, COMMA, ARGS))
    {
        // code:
        // [Args's code]
        // [Exp's code]
        // ARG [Exp's retval]

        // for array and struct, we need to get the address
        // in semantic analyze we have got the type/type meta of Exp, which was stored in the semantic info
        // remember that we need the address ONLY WHEN the arg is an array or struct
        // for nested struct, we will need the struct typed member's address, the plain member's value
        // for array, we will need the array's address, the element's value
        // if array has more than one dimension, we will need the address of the element
        Symbol_Value_Type valueType = GET_CHILD_NODE(nodeIndex, 0)->semanticInfo->valueType;
        InterCodeInstruction instruction = {NULL, NULL, REQ_NO};
        if(valueType == SVT_Array || valueType == SVT_Struct){
            instruction.specialRequest = REQ_ADDRESS;
        }

        InterCodeHandle childExpHandle = InterCodeGenerate_Exp(GET_CHILD(nodeIndex, 0), &instruction);

        if(valueType == SVT_Array || valueType == SVT_Struct && childExpHandle->specialReply != REP_IS_ADDRESS){
            // when the EXP is an ID, the reply will be the variable itself
            // we will get the address of the variable
            // avoid polluting the variable we use a new variable to store the address
            int addrVarID = SymbolTable_getNextVarID(symbolTable_IC);
            InterCodeHandle_newCode(childExpHandle, IC_ADDR, 2,
                                    ICP_VAR, addrVarID,
                                    childExpHandle->returnType, childExpHandle->returnID);
            InterCodeHandle_newCode(childExpHandle, IC_ARG, 1,
                                    ICP_VAR, addrVarID);
        }else{
            // when the Exp is a member or array access, the reply will be the address
            InterCodeHandle_newCode(childExpHandle, IC_ARG, 1,
                                    childExpHandle->returnType, childExpHandle->returnID);
        }
        // in other situations, the reply will be the value

        InterCodeHandle childArgsHandle = InterCodeGenerate_Args(GET_CHILD(nodeIndex, 2));
        return InterCodeHandle_merge(childArgsHandle,childExpHandle);
    }
    return INVALID_INTERCODE_HANDLE;
}