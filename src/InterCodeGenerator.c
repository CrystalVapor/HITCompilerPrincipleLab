//
// Created by Crystal on 2024/3/31.
//

#include <stdarg.h>

#include "InterCodeGenerator.h"

/**
 * InterCodeGenerator
 */


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