//
// Created by Crystal on 2024/3/31.
//

#include <stdarg.h>

#include "InterCodeGenerator.h"

/**
 * Virtual function for generating intermediate code.
 * No need to copy this to your project, just for fun.
 */

void InterCodeInfo_generate_Label(struct InterCodeInfo* interCodeInfo, FILE* file){
}

void InterCodeInfo_generate_Func(struct InterCodeInfo* interCodeInfo, FILE* file){
}

void InterCodeInfo_generate_Assign(struct InterCodeInfo* interCodeInfo, FILE* file){
}

void InterCodeInfo_generate_Add(struct InterCodeInfo* interCodeInfo, FILE* file){
}

void InterCodeInfo_generate_Sub(struct InterCodeInfo* interCodeInfo, FILE* file){
}

void InterCodeInfo_generate_Mul(struct InterCodeInfo* interCodeInfo, FILE* file){
}

void InterCodeInfo_generate_Div(struct InterCodeInfo* interCodeInfo, FILE* file){
}

void InterCodeInfo_generate_Addr(struct InterCodeInfo* interCodeInfo, FILE* file){
}

void InterCodeInfo_generate_Deref_Get(struct InterCodeInfo* interCodeInfo, FILE* file){
}

void InterCodeInfo_generate_Deref_Set(struct InterCodeInfo* interCodeInfo, FILE* file){
}

void InterCodeInfo_generate_Goto(struct InterCodeInfo* interCodeInfo, FILE* file){
}

void InterCodeInfo_generate_Cond_Goto(struct InterCodeInfo* interCodeInfo, FILE* file){
}

void InterCodeInfo_generate_Return(struct InterCodeInfo* interCodeInfo, FILE* file){
}

void InterCodeInfo_generate_Dec(struct InterCodeInfo* interCodeInfo, FILE* file){
}

void InterCodeInfo_generate_Arg(struct InterCodeInfo* interCodeInfo, FILE* file){
}

void InterCodeInfo_generate_Call(struct InterCodeInfo* interCodeInfo, FILE* file){
}

void InterCodeInfo_generate_Param(struct InterCodeInfo* interCodeInfo, FILE* file){
}

void InterCodeInfo_generate_Read(struct InterCodeInfo* interCodeInfo, FILE* file){
}

void InterCodeInfo_generate_Write(struct InterCodeInfo* interCodeInfo, FILE* file){
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
        {InterCodeInfo_generate_Cond_Goto},

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
