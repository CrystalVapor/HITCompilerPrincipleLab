//
// Created by Crystal on 2024/3/31.
//

#include <stdarg.h>
#include "Structure/ParserNodes.h"
#include "Structure/SymbolTable.h"

#include "InterCodeGenerator.h"

char tempBuffer[100];

int currentScope = 0;

/**
 * Helper functions
 */

int SymbolTable_generateTempName(SymbolTable_t symbolTable ,InterCodeTempType type, char* buffer, int bufferSize, char* externalSuffix){
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

InterCodeHandle InterCodeGenerate_ExtDecList(ParserNode_I nodeIndex);

InterCodeHandle InterCodeGenerate_Specifier(ParserNode_I nodeIndex);

InterCodeHandle InterCodeGenerate_StructSpecifier(ParserNode_I nodeIndex);

InterCodeHandle InterCodeGenerate_OptTag(ParserNode_I nodeIndex);

InterCodeHandle InterCodeGenerate_Tag(ParserNode_I nodeIndex);

InterCodeHandle InterCodeGenerate_VarDec(ParserNode_I nodeIndex);

InterCodeHandle InterCodeGenerate_FunDec(ParserNode_I nodeIndex);

InterCodeHandle InterCodeGenerate_VarList(ParserNode_I nodeIndex);

InterCodeHandle InterCodeGenerate_ParamDec(ParserNode_I nodeIndex);

InterCodeHandle InterCodeGenerate_CompSt(ParserNode_I nodeIndex);

InterCodeHandle InterCodeGenerate_StmtList(ParserNode_I nodeIndex);

InterCodeHandle InterCodeGenerate_Stmt(ParserNode_I nodeIndex);

InterCodeHandle InterCodeGenerate_DefList(ParserNode_I nodeIndex);

InterCodeHandle InterCodeGenerate_Def(ParserNode_I nodeIndex);

InterCodeHandle InterCodeGenerate_DecList(ParserNode_I nodeIndex);

InterCodeHandle InterCodeGenerate_Dec(ParserNode_I nodeIndex);

InterCodeHandle InterCodeGenerate_Exp(ParserNode_I nodeIndex, InterCodeInstruction instruction);

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
    interCodeInfo->paramNum = paramNum;
    va_list args;
    va_start(args, paramNum);
    for(int i = 0; i < paramNum; i++){
        interCodeInfo->params[i] = va_arg(args, InterCodeParam);
    }
    va_end(args);
    return interCodeInfo;
}

int InterCodeParam_printToBuffer(InterCodeParam *param, char *buffer, int bufferSize) {
    switch(param->type){
        case ICP_INT:
            return snprintf(buffer, bufferSize, "#%d", INTERCODEPARAM_GETINT(param));
        case ICP_VAR:
            return snprintf(buffer, bufferSize, "%s", INTERCODEPARAM_GETVAR(param));
        case ICP_LABEL:
            return snprintf(buffer, bufferSize, "%s", INTERCODEPARAM_GETLABEL(param));
    }
    return 0;
}

/**
 * Implementations for InterCodeHandle
 */

InterCodeHandle InterCodeHandle_create() {
    InterCodeHandle handle = (InterCodeHandle)malloc(sizeof(InterCodeContainer));
    handle->codes = SimpleList_create();
    handle->returnVar = NULL;
    return handle;
}

void InterCodeHandle_destroy(InterCodeHandle handle) {
    SimpleList_destroy(handle->codes, free);
    free(handle);
}

InterCodeHandle InterCodeHandle_merge(InterCodeHandle handle1, InterCodeHandle handle2) {
    if(handle1 == INVALID_INTERCODE_HANDLE){
        return handle2;
    }
    if(handle2 == INVALID_INTERCODE_HANDLE){
        return handle1;
    }
    handle1->codes = SimpleList_append(handle1->codes, handle2->codes);
    handle1->returnVar = handle1->returnVar == NULL ? handle2->returnVar : handle1->returnVar;
    free(handle2);
    return handle1;
}

/**
 * Implementations for InterCodeGenerator
 */

void generateInterCode(ParserNode_I rootNodeIndex, FILE* file){

    InterCodeHandle handle = InterCodeGenerate_Program(rootNodeIndex);

    // add some extra intermediate code to the head of the list
    // this is for supporting the Predefined functions: [write] and [read]

    SimpleList_t codes = handle->codes;
    SimpleListNode_t node = codes->head;
    while(node != NULL){
        InterCodeInfo_t interCodeInfo = (InterCodeInfo_t)node->data;
        interCodeInfo->vptr->generateInterCode(interCodeInfo, file);
        node = node->next;
    }
    //InterCodeHandle_destroy(handle);
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
        return INVALID_INTERCODE_HANDLE;
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
        // [CompSt's code]
    }
    else if(isChildrenMatchRule(nodeIndex, 3, SPECIFIER, FUN_DEC, SEMI)){
        // a forward declaration
        // make no sense in intermediate code
        return INVALID_INTERCODE_HANDLE;
    }
    return INVALID_INTERCODE_HANDLE;
}

InterCodeHandle InterCodeGenerate_ExtDecList(ParserNode_I nodeIndex){
    if(isChildrenMatchRule(nodeIndex, 1, VAR_DEC))
    {
        // this make no sense in intermediate code
        return INVALID_INTERCODE_HANDLE;
    }
    else if(isChildrenMatchRule(nodeIndex, 3, VAR_DEC, COMMA, EXT_DEC_LIST))
    {
        // this make no sense in intermediate code
        return INVALID_INTERCODE_HANDLE;
    }
    return INVALID_INTERCODE_HANDLE;
}

InterCodeHandle InterCodeGenerate_Specifier(ParserNode_I nodeIndex){
    if(isChildrenMatchRule(nodeIndex, 1, TYPE))
    {
        // this make no sense in intermediate code
        return INVALID_INTERCODE_HANDLE;
    }
    else if(isChildrenMatchRule(nodeIndex, 1, STRUCT_SPECIFIER))
    {
        // this make no sense in intermediate code
        return INVALID_INTERCODE_HANDLE;
    }
    return INVALID_INTERCODE_HANDLE;
}

InterCodeHandle InterCodeGenerate_StructSpecifier(ParserNode_I nodeIndex){
    if(isChildrenMatchRule(nodeIndex, 2, STRUCT, OPT_TAG))
    {
        // this make no sense in intermediate code
        return INVALID_INTERCODE_HANDLE;
    }
    else if(isChildrenMatchRule(nodeIndex, 5, STRUCT, TAG, LC, DEF_LIST, RC))
    {
        // this make no sense in intermediate code
        return INVALID_INTERCODE_HANDLE;
    }
    return INVALID_INTERCODE_HANDLE;
}

InterCodeHandle InterCodeGenerate_OptTag(ParserNode_I nodeIndex){
    if(isChildrenMatchRule(nodeIndex, 1, ID))
    {
        // this make no sense in intermediate code
        return INVALID_INTERCODE_HANDLE;
    }
    else if(isChildrenMatchRule(nodeIndex, 0))
    {
        // this make no sense in intermediate code
        return INVALID_INTERCODE_HANDLE;
    }
    return INVALID_INTERCODE_HANDLE;
}

InterCodeHandle InterCodeGenerate_Tag(ParserNode_I nodeIndex){
    if(isChildrenMatchRule(nodeIndex, 1, ID))
    {
        // this make no sense in intermediate code
        return INVALID_INTERCODE_HANDLE;
    }
    return INVALID_INTERCODE_HANDLE;
}

InterCodeHandle InterCodeGenerate_VarDec(ParserNode_I nodeIndex){
    if(isChildrenMatchRule(nodeIndex, 1, ID))
    {
        // this make no sense in intermediate code
        return INVALID_INTERCODE_HANDLE;
    }
    else if(isChildrenMatchRule(nodeIndex, 4, VAR_DEC, LB, INT, RB))
    {
        // this make no sense in intermediate code
        return INVALID_INTERCODE_HANDLE;
    }
    return INVALID_INTERCODE_HANDLE;
}

InterCodeHandle InterCodeGenerate_FunDec(ParserNode_I nodeIndex){
    if(isChildrenMatchRule(nodeIndex, 3, ID, LP, RP))
    {
        // this make no sense in intermediate code
        return INVALID_INTERCODE_HANDLE;
    }
    else if(isChildrenMatchRule(nodeIndex, 4, ID, LP, VAR_LIST, RP))
    {
        // this make no sense in intermediate code
        return INVALID_INTERCODE_HANDLE;
    }
    return INVALID_INTERCODE_HANDLE;
}

InterCodeHandle InterCodeGenerate_VarList(ParserNode_I nodeIndex){
    if(isChildrenMatchRule(nodeIndex, 3, PARAM_DEC, COMMA, VAR_LIST))
    {
        // this make no sense in intermediate code
        return INVALID_INTERCODE_HANDLE;
    }
    else if(isChildrenMatchRule(nodeIndex, 1, PARAM_DEC))
    {
        // this make no sense in intermediate code
        return INVALID_INTERCODE_HANDLE;
    }
    return INVALID_INTERCODE_HANDLE;
}

InterCodeHandle InterCodeGenerate_ParamDec(ParserNode_I nodeIndex){
    if(isChildrenMatchRule(nodeIndex, 2, SPECIFIER, VAR_DEC))
    {
        // this make no sense in intermediate code
        return INVALID_INTERCODE_HANDLE;
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
        // RETURN [Exp's retval]
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
        InterCodeHandle childDecListHandle = InterCodeGenerate_DecList(GET_CHILD(nodeIndex, 1));
        return childDecListHandle;
    }
    return INVALID_INTERCODE_HANDLE;
}

InterCodeHandle InterCodeGenerate_DecList(ParserNode_I nodeIndex){
    if(isChildrenMatchRule(nodeIndex, 1, DEC))
    {
        InterCodeHandle childDecHandle = InterCodeGenerate_Dec(GET_CHILD(nodeIndex, 0));
        return childDecHandle;
    }
    else if(isChildrenMatchRule(nodeIndex, 3, DEC, COMMA, DEC_LIST))
    {
        InterCodeHandle childDecHandle = InterCodeGenerate_Dec(GET_CHILD(nodeIndex, 0));
        InterCodeHandle childDecListHandle = InterCodeGenerate_DecList(GET_CHILD(nodeIndex, 2));
        return InterCodeHandle_merge(childDecHandle, childDecListHandle);
    }
    return INVALID_INTERCODE_HANDLE;
}

InterCodeHandle InterCodeGenerate_Dec(ParserNode_I nodeIndex){
    if(isChildrenMatchRule(nodeIndex, 1, VAR_DEC))
    {
        // allocate new variable
        // make no sense in intermediate code
        return INVALID_INTERCODE_HANDLE;
    }
    else if(isChildrenMatchRule(nodeIndex, 3, VAR_DEC, ASSIGNOP, EXP))
    {
        // allocate new variable and assign value
        // just like the case in EXP
    }
    return INVALID_INTERCODE_HANDLE;
}

InterCodeHandle InterCodeGenerate_Exp(ParserNode_I nodeIndex, InterCodeInstruction instruction) {
    if(isChildrenMatchRule(nodeIndex, 3, EXP, ASSIGNOP, EXP)){
        // there's two cases
        // case1: assign to a normal variable(include param)
        // we just have the retval of exp1 and assign exp2 to it

        // case2: assign to a struct member or array element
        // we need to use the offset info from semantic analyze

        // different from case1, we will need to get the address of the left value
        // intermediate code will be more complicated
    }
    else if(isChildrenMatchRule(nodeIndex, 2, EXP, AND, EXP)){
        // we need to implement the short-circuit evaluation
        // code is like:
        // Exp1 := [Analyze left]
        // [retVal] := 0
        // if Exp1 == 0 GOTO falseLabel
        // Exp2 := [Analyze right]
        // if Exp2 == 0 GOTO falseLabel
        // [retVal] := 1
        // GOTO trueLabel
    }
    else if(isChildrenMatchRule(nodeIndex, 2, EXP, OR, EXP)){
        // we need to implement the short-circuit evaluation
        // code is like:
        // Exp1 := [Analyze left]
        // [retVal] := 1
        // if Exp1 != 0 GOTO trueLabel
        // Exp2 := [Analyze right]
        // if Exp2 != 0 GOTO trueLabel
        // [retVal] := 0
        // GOTO falseLabel

    }
    else if(isChildrenMatchRule(nodeIndex, 3, EXP, EQ, EXP)){

    }
    else if(isChildrenMatchRule(nodeIndex, 3, EXP, NEQ, EXP)){

    }
    else if(isChildrenMatchRule(nodeIndex, 3, EXP, GE, EXP)){

    }
    else if(isChildrenMatchRule(nodeIndex, 3, EXP, GT, EXP)){

    }
    else if(isChildrenMatchRule(nodeIndex, 3, EXP, LE, EXP)){

    }
    else if(isChildrenMatchRule(nodeIndex, 3, EXP, LT, EXP)){
        // need an inherit attribute to tell us if we need a return value
        // if a retVal is needed, we need to generate a temp var
        // basic operation for this translate action is:
        // 1. analyze the left and right exp
        // 2. IF left.retVal [relop] right.retVal GOTO trueLabel
        // 3. GOTO falseLabel
        // 4. if we need a return value, generate a temp var
        // the code is like:
        // Exp1 := [Analyze left]
        // Exp2 := [Analyze right]
        // [retVal] := 1
        // if Exp1 [relop] Exp2 GOTO trueLabel
        // [retVal] := 0
        // GOTO falseLabel
    }
    else if(isChildrenMatchRule(nodeIndex, 3, EXP, PLUS, EXP)){
        // easy
    }
    else if(isChildrenMatchRule(nodeIndex, 3, EXP, MINUS, EXP)){
        // easy
    }
    else if(isChildrenMatchRule(nodeIndex, 3, EXP, STAR, EXP)){
        // easy
    }
    else if(isChildrenMatchRule(nodeIndex, 3, EXP, DIV, EXP)){
        // easy
    }
    else if(isChildrenMatchRule(nodeIndex, 3, LP, EXP, RP)){
        // easy
    }
    else if(isChildrenMatchRule(nodeIndex, 2, MINUS, EXP)){
        // easy
    }
    else if(isChildrenMatchRule(nodeIndex, 2, NOT, EXP)){
        // seems a relop-like sentence
    }
    else if(isChildrenMatchRule(nodeIndex, 3, ID, LP, RP)){
        // void function call
        // just call function
    }
    else if(isChildrenMatchRule(nodeIndex, 4, ID, LP, ARGS, RP)){
        // a function call
        // directly extract the temp N.O of args and call ARG&function name
    }
    else if(isChildrenMatchRule(nodeIndex, 4, EXP, LB, EXP, RB)){
        // another offset question
        // need offset info from semantic analyze
    }
    else if(isChildrenMatchRule(nodeIndex, 4, EXP, DOT, ID)){
        // get struct info from semantic info
        // hmmm seems we can directly get the offset from semantic analyze.
        // wait seems we should calculate the size of struct and its member when we
        // analyze that.
    }
    else if(isChildrenMatchRule(nodeIndex, 1, ID)){
        // check if ID's a param
        // can also do this in semantic analyze
        // but how???
        // we can give a special mark to variable that it is a param.
        // and reuse the temp N.O. used by variable to mark which parm it is.

        // if is, use paramname

        // if not, try finding a relative temp var.
        // we can support this in semantic analyze
        // by giving a temp name to variable symbol
        // and save that in semantic info.
    }
    else if(isChildrenMatchRule(nodeIndex, 1, INT)){
        InterCodeParam_t newVar = InterCodeParam_createInt(GET_NODE(ID)->intVal);
        InterCodeHandle newHandle = InterCodeHandle_create();
        newHandle->returnVar = newVar;
        return newHandle;
    }
    else if(isChildrenMatchRule(nodeIndex, 1, FLOAT)){
        // consider an error, float is not supported
        exit(-1);
    }
    return INVALID_INTERCODE_HANDLE;
}

InterCodeHandle InterCodeGenerate_Args(ParserNode_I nodeIndex){
    if(isChildrenMatchRule(nodeIndex, 1, EXP))
    {

    }
    else if(isChildrenMatchRule(nodeIndex, 3, EXP, COMMA, ARGS))
    {

    }
    return INVALID_INTERCODE_HANDLE;
}

void InterCodeHandle_newCode(InterCodeHandle handle, InterCodeType codeType, int paramNum, ...) {
    SimpleList_t codes = handle->codes;
    va_list args;
    va_start(args, paramNum);
    InterCodeInfo_t codeInfo = InterCodeInfo_create(codeType, paramNum, args);
    SimpleList_push_back(codes, codeInfo);
    va_end(args);
}