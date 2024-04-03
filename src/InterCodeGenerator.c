//
// Created by Crystal on 2024/3/31.
//

#include <stdarg.h>
#include "Structure/ParserNodes.h"

#include "InterCodeGenerator.h"

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

InterCodeHandle InterCodeGenerate_Exp(ParserNode_I nodeIndex);

InterCodeHandle InterCodeGenerate_Args(ParserNode_I nodeIndex);

/**
 * Virtual function for generating intermediate code.
 * No need to copy this to your project, just for fun.
 */

void InterCodeInfo_generate_Label(struct InterCodeInfo_s* interCodeInfo, FILE* file){
    char buffer[100];
    InterCodeParam_printToBuffer(&interCodeInfo->params[0], buffer, 100);
    fprintf(file, "LABEL %s :\n", buffer);
}

void InterCodeInfo_generate_Func(struct InterCodeInfo_s*  interCodeInfo, FILE* file){
    char buffer[100];
    InterCodeParam_printToBuffer(&interCodeInfo->params[0], buffer, 100);
    fprintf(file, "FUNCTION %s :\n", buffer);
}

void InterCodeInfo_generate_Assign(struct InterCodeInfo_s*  interCodeInfo, FILE* file){
    char buffer[100];
    InterCodeParam_printToBuffer(&interCodeInfo->params[0], buffer, 100);
    fprintf(file, "%s := ", buffer);
    InterCodeParam_printToBuffer(&interCodeInfo->params[1], buffer, 100);
    fprintf(file, "%s\n", buffer);
}

void InterCodeInfo_generate_Add(struct InterCodeInfo_s*  interCodeInfo, FILE* file){
    char buffer[100];
    InterCodeParam_printToBuffer(&interCodeInfo->params[0], buffer, 100);
    fprintf(file, "%s := ", buffer);
    InterCodeParam_printToBuffer(&interCodeInfo->params[1], buffer, 100);
    fprintf(file, "%s + ", buffer);
    InterCodeParam_printToBuffer(&interCodeInfo->params[2], buffer, 100);
    fprintf(file, "%s\n", buffer);
}

void InterCodeInfo_generate_Sub(struct InterCodeInfo_s*  interCodeInfo, FILE* file){
    char buffer[100];
    InterCodeParam_printToBuffer(&interCodeInfo->params[0], buffer, 100);
    fprintf(file, "%s := ", buffer);
    InterCodeParam_printToBuffer(&interCodeInfo->params[1], buffer, 100);
    fprintf(file, "%s - ", buffer);
    InterCodeParam_printToBuffer(&interCodeInfo->params[2], buffer, 100);
    fprintf(file, "%s\n", buffer);
}

void InterCodeInfo_generate_Mul(struct InterCodeInfo_s*  interCodeInfo, FILE* file){
    char buffer[100];
    InterCodeParam_printToBuffer(&interCodeInfo->params[0], buffer, 100);
    fprintf(file, "%s := ", buffer);
    InterCodeParam_printToBuffer(&interCodeInfo->params[1], buffer, 100);
    fprintf(file, "%s * ", buffer);
    InterCodeParam_printToBuffer(&interCodeInfo->params[2], buffer, 100);
    fprintf(file, "%s\n", buffer);
}

void InterCodeInfo_generate_Div(struct InterCodeInfo_s*  interCodeInfo, FILE* file){
    char buffer[100];
    InterCodeParam_printToBuffer(&interCodeInfo->params[0], buffer, 100);
    fprintf(file, "%s := ", buffer);
    InterCodeParam_printToBuffer(&interCodeInfo->params[1], buffer, 100);
    fprintf(file, "%s / ", buffer);
    InterCodeParam_printToBuffer(&interCodeInfo->params[2], buffer, 100);
    fprintf(file, "%s\n", buffer);
}

void InterCodeInfo_generate_Addr(struct InterCodeInfo_s*  interCodeInfo, FILE* file){
    char buffer[100];
    InterCodeParam_printToBuffer(&interCodeInfo->params[0], buffer, 100);
    fprintf(file, "%s := &", buffer);
    InterCodeParam_printToBuffer(&interCodeInfo->params[1], buffer, 100);
    fprintf(file, "%s\n", buffer);
}

void InterCodeInfo_generate_Deref_Get(struct InterCodeInfo_s*  interCodeInfo, FILE* file){
    char buffer[100];
    InterCodeParam_printToBuffer(&interCodeInfo->params[0], buffer, 100);
    fprintf(file, "%s := *", buffer);
    InterCodeParam_printToBuffer(&interCodeInfo->params[1], buffer, 100);
    fprintf(file, "%s\n", buffer);
}

void InterCodeInfo_generate_Deref_Set(struct InterCodeInfo_s*  interCodeInfo, FILE* file){
    char buffer[100];
    fprintf(file, "*");
    InterCodeParam_printToBuffer(&interCodeInfo->params[0], buffer, 100);
    fprintf(file, "%s := ", buffer);
    InterCodeParam_printToBuffer(&interCodeInfo->params[1], buffer, 100);
    fprintf(file, "%s\n", buffer);
}

void InterCodeInfo_generate_Goto(struct InterCodeInfo_s*  interCodeInfo, FILE* file){
    char buffer[100];
    InterCodeParam_printToBuffer(&interCodeInfo->params[0], buffer, 100);
    fprintf(file, "GOTO %s\n", buffer);
}

void InterCodeInfo_generate_EQ_Goto(struct InterCodeInfo_s*  interCodeInfo, FILE* file){
    char buffer[100];
    InterCodeParam_printToBuffer(&interCodeInfo->params[0], buffer, 100);
    fprintf(file, "IF ");
    InterCodeParam_printToBuffer(&interCodeInfo->params[1], buffer, 100);
    fprintf(file, "%s = ", buffer);
    InterCodeParam_printToBuffer(&interCodeInfo->params[2], buffer, 100);
    fprintf(file, "%s GOTO ", buffer);
    InterCodeParam_printToBuffer(&interCodeInfo->params[3], buffer, 100);
    fprintf(file, "%s\n", buffer);
}

void InterCodeInfo_generate_NE_Goto(struct InterCodeInfo_s*  interCodeInfo, FILE* file){
    char buffer[100];
    InterCodeParam_printToBuffer(&interCodeInfo->params[0], buffer, 100);
    fprintf(file, "IF ");
    InterCodeParam_printToBuffer(&interCodeInfo->params[1], buffer, 100);
    fprintf(file, "%s != ", buffer);
    InterCodeParam_printToBuffer(&interCodeInfo->params[2], buffer, 100);
    fprintf(file, "%s GOTO ", buffer);
    InterCodeParam_printToBuffer(&interCodeInfo->params[3], buffer, 100);
    fprintf(file, "%s\n", buffer);
}

void InterCodeInfo_generate_GE_Goto(struct InterCodeInfo_s*  interCodeInfo, FILE* file){
    char buffer[100];
    InterCodeParam_printToBuffer(&interCodeInfo->params[0], buffer, 100);
    fprintf(file, "IF ");
    InterCodeParam_printToBuffer(&interCodeInfo->params[1], buffer, 100);
    fprintf(file, "%s >= ", buffer);
    InterCodeParam_printToBuffer(&interCodeInfo->params[2], buffer, 100);
    fprintf(file, "%s GOTO ", buffer);
    InterCodeParam_printToBuffer(&interCodeInfo->params[3], buffer, 100);
    fprintf(file, "%s\n", buffer);
}

void InterCodeInfo_generate_GT_Goto(struct InterCodeInfo_s*  interCodeInfo, FILE* file){
    char buffer[100];
    InterCodeParam_printToBuffer(&interCodeInfo->params[0], buffer, 100);
    fprintf(file, "IF ");
    InterCodeParam_printToBuffer(&interCodeInfo->params[1], buffer, 100);
    fprintf(file, "%s > ", buffer);
    InterCodeParam_printToBuffer(&interCodeInfo->params[2], buffer, 100);
    fprintf(file, "%s GOTO ", buffer);
    InterCodeParam_printToBuffer(&interCodeInfo->params[3], buffer, 100);
    fprintf(file, "%s\n", buffer);
}

void InterCodeInfo_generate_LE_Goto(struct InterCodeInfo_s*  interCodeInfo, FILE* file){
    char buffer[100];
    InterCodeParam_printToBuffer(&interCodeInfo->params[0], buffer, 100);
    fprintf(file, "IF ");
    InterCodeParam_printToBuffer(&interCodeInfo->params[1], buffer, 100);
    fprintf(file, "%s <= ", buffer);
    InterCodeParam_printToBuffer(&interCodeInfo->params[2], buffer, 100);
    fprintf(file, "%s GOTO ", buffer);
    InterCodeParam_printToBuffer(&interCodeInfo->params[3], buffer, 100);
    fprintf(file, "%s\n", buffer);
}

void InterCodeInfo_generate_LT_Goto(struct InterCodeInfo_s*  interCodeInfo, FILE* file){
    char buffer[100];
    InterCodeParam_printToBuffer(&interCodeInfo->params[0], buffer, 100);
    fprintf(file, "IF ");
    InterCodeParam_printToBuffer(&interCodeInfo->params[1], buffer, 100);
    fprintf(file, "%s < ", buffer);
    InterCodeParam_printToBuffer(&interCodeInfo->params[2], buffer, 100);
    fprintf(file, "%s GOTO ", buffer);
    InterCodeParam_printToBuffer(&interCodeInfo->params[3], buffer, 100);
    fprintf(file, "%s\n", buffer);
}

void InterCodeInfo_generate_Return(struct InterCodeInfo_s*  interCodeInfo, FILE* file){
    char buffer[100];
    fprintf(file, "RETURN ");
    InterCodeParam_printToBuffer(&interCodeInfo->params[0], buffer, 100);
    fprintf(file, "%s\n", buffer);
}

void InterCodeInfo_generate_Dec(struct InterCodeInfo_s*  interCodeInfo, FILE* file){
    char buffer[100];
    fprintf(file, "DEC ");
    InterCodeParam_printToBuffer(&interCodeInfo->params[0], buffer, 100);
    fprintf(file, "%s \n", buffer);
    snprintf(buffer, 100, "%d", INTERCODEPARAM_GETINT(&interCodeInfo->params[1]));
    fprintf(file, "%s\n", buffer);
}

void InterCodeInfo_generate_Arg(struct InterCodeInfo_s*  interCodeInfo, FILE* file){
    char buffer[100];
    fprintf(file, "ARG ");
    InterCodeParam_printToBuffer(&interCodeInfo->params[0], buffer, 100);
    fprintf(file, "%s\n", buffer);
}

void InterCodeInfo_generate_Call(struct InterCodeInfo_s*  interCodeInfo, FILE* file){
    char buffer[100];
    InterCodeParam_printToBuffer(&interCodeInfo->params[0], buffer, 100);
    fprintf(file, "%s := CALL ", buffer);
    InterCodeParam_printToBuffer(&interCodeInfo->params[1], buffer, 100);
    fprintf(file, "%s\n", buffer);
}

void InterCodeInfo_generate_Param(struct InterCodeInfo_s*  interCodeInfo, FILE* file){
    char buffer[100];
    fprintf(file, "PARAM ");
    InterCodeParam_printToBuffer(&interCodeInfo->params[0], buffer, 100);
    fprintf(file, "%s\n", buffer);
}

void InterCodeInfo_generate_Read(struct InterCodeInfo_s*  interCodeInfo, FILE* file){
    char buffer[100];
    fprintf(file, "READ ");
    InterCodeParam_printToBuffer(&interCodeInfo->params[0], buffer, 100);
    fprintf(file, "%s\n", buffer);
}

void InterCodeInfo_generate_Write(struct InterCodeInfo_s*  interCodeInfo, FILE* file){
    char buffer[100];
    fprintf(file, "WRITE ");
    InterCodeParam_printToBuffer(&interCodeInfo->params[0], buffer, 100);
    fprintf(file, "%s\n", buffer);
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
 * Implementations for InterCodeGenerator
 */

void generateInterCode(ParserNode_I rootNodeIndex, FILE* file){

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
        /*InterCodeHandle handle = InterCodeGenerate_ExtDef(GET_CHILD(nodeIndex, 0));
        InterCodeHandle handle2 = InterCodeGenerate_ExtDefList(GET_CHILD(nodeIndex, 1));
         //TODO: A Function to Merge the two handles
        return handle;*/
    }
    else if(isChildrenMatchRule(nodeIndex, 0))
    {
        return INVALID_INTERCODE_HANDLE;
    }
    return INVALID_INTERCODE_HANDLE;
}

InterCodeHandle InterCodeGenerate_ExtDef(ParserNode_I nodeIndex){
    if(isChildrenMatchRule(nodeIndex, 3, SPECIFIER, EXT_DEC_LIST, COMP_STM)){

    }
    else if(isChildrenMatchRule(nodeIndex, 2, SPECIFIER, SEMI)){

    }
    else if(isChildrenMatchRule(nodeIndex, 3, SPECIFIER, FUN_DEC, COMP_STM)){

    }
    else if(isChildrenMatchRule(nodeIndex, 3, SPECIFIER, FUN_DEC, SEMI)){

    }
    return INVALID_INTERCODE_HANDLE;
}

InterCodeHandle InterCodeGenerate_ExtDecList(ParserNode_I nodeIndex){
    if(isChildrenMatchRule(nodeIndex, 1, VAR_DEC))
    {

    }
    else if(isChildrenMatchRule(nodeIndex, 3, VAR_DEC, COMMA, EXT_DEC_LIST))
    {

    }
    return INVALID_INTERCODE_HANDLE;
}

InterCodeHandle InterCodeGenerate_Specifier(ParserNode_I nodeIndex){
    if(isChildrenMatchRule(nodeIndex, 1, TYPE))
    {

    }
    else if(isChildrenMatchRule(nodeIndex, 1, STRUCT_SPECIFIER))
    {

    }
    return INVALID_INTERCODE_HANDLE;
}

InterCodeHandle InterCodeGenerate_StructSpecifier(ParserNode_I nodeIndex){
    if(isChildrenMatchRule(nodeIndex, 2, STRUCT, OPT_TAG))
    {

    }
    else if(isChildrenMatchRule(nodeIndex, 5, STRUCT, TAG, LC, DEF_LIST, RC))
    {

    }
    return INVALID_INTERCODE_HANDLE;
}

InterCodeHandle InterCodeGenerate_OptTag(ParserNode_I nodeIndex){
    if(isChildrenMatchRule(nodeIndex, 1, ID))
    {

    }
    else if(isChildrenMatchRule(nodeIndex, 0))
    {

    }
    return INVALID_INTERCODE_HANDLE;
}

InterCodeHandle InterCodeGenerate_Tag(ParserNode_I nodeIndex){
    if(isChildrenMatchRule(nodeIndex, 1, ID))
    {

    }
    return INVALID_INTERCODE_HANDLE;
}

InterCodeHandle InterCodeGenerate_VarDec(ParserNode_I nodeIndex){
    if(isChildrenMatchRule(nodeIndex, 1, ID))
    {

    }
    else if(isChildrenMatchRule(nodeIndex, 4, VAR_DEC, LB, INT, RB))
    {

    }
    return INVALID_INTERCODE_HANDLE;
}

InterCodeHandle InterCodeGenerate_FunDec(ParserNode_I nodeIndex){
    if(isChildrenMatchRule(nodeIndex, 3, ID, LP, RP))
    {

    }
    else if(isChildrenMatchRule(nodeIndex, 4, ID, LP, VAR_LIST, RP))
    {

    }
    return INVALID_INTERCODE_HANDLE;
}

InterCodeHandle InterCodeGenerate_VarList(ParserNode_I nodeIndex){
    if(isChildrenMatchRule(nodeIndex, 3, PARAM_DEC, COMMA, VAR_LIST))
    {

    }
    else if(isChildrenMatchRule(nodeIndex, 1, PARAM_DEC))
    {

    }
    return INVALID_INTERCODE_HANDLE;
}

InterCodeHandle InterCodeGenerate_ParamDec(ParserNode_I nodeIndex){
    if(isChildrenMatchRule(nodeIndex, 2, SPECIFIER, VAR_DEC))
    {

    }
    return INVALID_INTERCODE_HANDLE;
}

InterCodeHandle InterCodeGenerate_CompSt(ParserNode_I nodeIndex){
    if(isChildrenMatchRule(nodeIndex, 4, LC, DEF_LIST, STMT_LIST, RC))
    {

    }
    return INVALID_INTERCODE_HANDLE;
}

InterCodeHandle InterCodeGenerate_StmtList(ParserNode_I nodeIndex){
    if(isChildrenMatchRule(nodeIndex, 2, STMT, STMT_LIST))
    {

    }
    else if(isChildrenMatchRule(nodeIndex, 0))
    {

    }
    return INVALID_INTERCODE_HANDLE;
}

InterCodeHandle InterCodeGenerate_Stmt(ParserNode_I nodeIndex){
    if(isChildrenMatchRule(nodeIndex, 2, EXP, SEMI))
    {

    }
    else if(isChildrenMatchRule(nodeIndex, 1, COMP_STM))
    {

    }
    else if(isChildrenMatchRule(nodeIndex, 3, RETURN, EXP, SEMI))
    {

    }
    else if(isChildrenMatchRule(nodeIndex, 5, IF, LP, EXP, RP, STMT))
    {

    }
    else if(isChildrenMatchRule(nodeIndex, 7, IF, LP, EXP, RP, STMT, ELSE, STMT))
    {

    }
    else if(isChildrenMatchRule(nodeIndex, 5, WHILE, LP, EXP, RP, STMT))
    {

    }
    return INVALID_INTERCODE_HANDLE;
}

InterCodeHandle InterCodeGenerate_DefList(ParserNode_I nodeIndex){
    if(isChildrenMatchRule(nodeIndex, 2, DEF, DEF_LIST))
    {

    }
    else if(isChildrenMatchRule(nodeIndex, 0))
    {

    }
    return INVALID_INTERCODE_HANDLE;
}

InterCodeHandle InterCodeGenerate_Def(ParserNode_I nodeIndex){
    if(isChildrenMatchRule(nodeIndex, 3, SPECIFIER, DEC_LIST, SEMI))
    {

    }
    return INVALID_INTERCODE_HANDLE;
}

InterCodeHandle InterCodeGenerate_DecList(ParserNode_I nodeIndex){
    if(isChildrenMatchRule(nodeIndex, 1, DEC))
    {

    }
    else if(isChildrenMatchRule(nodeIndex, 3, DEC, COMMA, DEC_LIST))
    {

    }
    return INVALID_INTERCODE_HANDLE;
}

InterCodeHandle InterCodeGenerate_Dec(ParserNode_I nodeIndex){
    if(isChildrenMatchRule(nodeIndex, 1, VAR_DEC))
    {

    }
    else if(isChildrenMatchRule(nodeIndex, 3, VAR_DEC, ASSIGNOP, EXP))
    {

    }
    return INVALID_INTERCODE_HANDLE;
}

InterCodeHandle InterCodeGenerate_Exp(ParserNode_I nodeIndex){
    if(isChildrenMatchRule(nodeIndex, 3, EXP, ASSIGNOP, EXP)){

    }
    else if(isChildrenMatchRule(nodeIndex, 2, EXP, AND, EXP)){

    }
    else if(isChildrenMatchRule(nodeIndex, 2, EXP, OR, EXP)){

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

    }
    else if(isChildrenMatchRule(nodeIndex, 3, EXP, PLUS, EXP)){

    }
    else if(isChildrenMatchRule(nodeIndex, 3, EXP, MINUS, EXP)){

    }
    else if(isChildrenMatchRule(nodeIndex, 3, EXP, STAR, EXP)){

    }
    else if(isChildrenMatchRule(nodeIndex, 3, EXP, DIV, EXP)){

    }
    else if(isChildrenMatchRule(nodeIndex, 3, LP, EXP, RP)){

    }
    else if(isChildrenMatchRule(nodeIndex, 2, MINUS, EXP)){

    }
    else if(isChildrenMatchRule(nodeIndex, 2, NOT, EXP)){

    }
    else if(isChildrenMatchRule(nodeIndex, 3, ID, LP, RP)){

    }
    else if(isChildrenMatchRule(nodeIndex, 4, ID, LP, ARGS, RP)){

    }
    else if(isChildrenMatchRule(nodeIndex, 4, EXP, LB, EXP, RB)){

    }
    else if(isChildrenMatchRule(nodeIndex, 4, EXP, DOT, ID)){

    }
    else if(isChildrenMatchRule(nodeIndex, 1, ID)){

    }
    else if(isChildrenMatchRule(nodeIndex, 1, INT)){

    }
    else if(isChildrenMatchRule(nodeIndex, 1, FLOAT)){

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