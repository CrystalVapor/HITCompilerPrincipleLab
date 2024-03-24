//
// Created by Crystal on 2024/3/19.
//

#include <string.h>
#include <stdlib.h>
#include <assert.h>

#include "Structure/SymbolTable.h"

#define SYMBOL_TABLE_HASH_TABLE_SIZE 10007

////////////////////////////////////////
/// SymbolTable
////////////////////////////////////////


SymbolTable_t SymbolTable_createSymbolTable() {
    SymbolTable_t table = (SymbolTable_t)malloc(sizeof(SymbolTable));
    table->table = SimpleHashTable_createWithSize(sizeof(SymbolRecord), NULL, NULL, SYMBOL_TABLE_HASH_TABLE_SIZE);
    table->scope = 0;
    table->scopeStack = SimpleArray_create(sizeof(int));
    memset(table->scopePrefix, 0, sizeof(table->scopePrefix));
    strcpy(table->scopePrefix, "+0_");
    return table;
}

void SymbolTable_destroy(void* tableToDestroy){
    SymbolTable_t table = (SymbolTable_t)tableToDestroy;
    SimpleHashTable_destroy(table->table, NULL, NULL);
    SimpleArray_destroy(table->scopeStack, NULL);
    free(table);
}

void SymbolTable_enterScope(SymbolTable_t table) {
    table->scope++;
    SimpleArray_pushBack(table->scopeStack, &table->scope);
    int currentScope = *(int*)SimpleArray_back(table->scopeStack);
    sprintf(table->scopePrefix, "+%d_", currentScope);
}

void SymbolTable_leaveScope(SymbolTable_t table) {
    assert(table->scopeStack->num > 0);
    table->scope--;
    SimpleArray_popBack(table->scopeStack, NULL);
    int currentScope = *(int *) SimpleArray_back(table->scopeStack);
    sprintf(table->scopePrefix, "+%d_", currentScope);
}

////////////////////////////////////////
/// SymbolInfo
////////////////////////////////////////


SymbolInfo_Variable_Raw SymbolInfo_Variable_create(Symbol_Value_Type type, void *meta) {
    SymbolInfo_Variable_Raw rawInfo = NULL;
    switch(type){
        case SVT_Int:
            rawInfo = (SymbolInfo_Variable_Raw)malloc(sizeof(SymbolInfo_Variable));
            ((SymbolInfo_Variable_Raw)rawInfo)->type = SVT_Int;
            ((SymbolInfo_Variable_Raw)rawInfo)->meta = NULL;
            return rawInfo;
            break;
        case SVT_Float:
            rawInfo = (SymbolInfo_Variable_Raw)malloc(sizeof(SymbolInfo_Variable));
            ((SymbolInfo_Variable_Raw)rawInfo)->type = SVT_Float;
            ((SymbolInfo_Variable_Raw)rawInfo)->meta = NULL;
            return rawInfo;
            break;
        case SVT_Struct:
            rawInfo = (SymbolInfo_Variable_Raw)malloc(sizeof(SymbolInfo_Variable));
            ((SymbolInfo_Variable_Raw)rawInfo)->type = SVT_Struct;
            ((SymbolInfo_Variable_Raw)rawInfo)->meta = strdup((char*)meta);
            return rawInfo;
            break;
        case SVT_Array:
            rawInfo = (SymbolInfo_Variable_Raw)malloc(sizeof(SymbolInfo_Variable));
            ((SymbolInfo_Variable_Raw)rawInfo)->type = SVT_Array;
            ((SymbolInfo_Variable_Raw)rawInfo)->meta = (SymbolInfo_Array_Raw)meta;
            return rawInfo;
            break;
        default:
            return NULL;
    }
}

int SymbolInfo_Variable_bake(SymbolTable_t table, SymbolInfo_Variable_Raw rawInfo) {
    if (rawInfo == NULL)
        return -1;
    switch (rawInfo->type) {
        case SVT_Int:
        case SVT_Float:
            return 0;
            break;
        case SVT_Struct:
        {
            SymbolInfo_Struct_t structInfo = NULL;
            int bakeResult = SymbolInfo_bakeStructName(table, rawInfo->meta, &structInfo);
            rawInfo->meta = structInfo;
            return bakeResult;
        }
        case SVT_Array:
        {
            SymbolInfo_Array_t arrayInfo = rawInfo->meta;
            return SymbolInfo_Array_bake(table, arrayInfo);
        }
        default:
            return -1;
    }
}

void SymbolInfo_Variable_destroyRaw(SymbolInfo_Variable_Raw info) {
    if(info == NULL)
        return;
    if(info->type == SVT_Struct){
        if(info->meta != NULL)
            free(info->meta);
    }
    else if(info->type == SVT_Array){
        SymbolInfo_Array_destroyRaw(info->meta);
    }
    free(info);
}

void SymbolInfo_Variable_destroy(SymbolInfo_Variable_t info) {
    if(info == NULL)
        return;
    else if(info->type == SVT_Array){
        SymbolInfo_Array_destroy(info->meta);
    }
    free(info);
}

SymbolInfo_Array_Raw
SymbolInfo_Array_create(Symbol_Value_Type elementType, int *dimensions, int dimensionCount, char *structName) {
    if(elementType == SVT_Array)
        return NULL;
    SymbolInfo_Array_Raw rawInfo = (SymbolInfo_Array_Raw)malloc(sizeof(SymbolInfo_Array));
    rawInfo->elementType = elementType;
    memcpy(rawInfo->dimensions, dimensions, sizeof(int) * dimensionCount);
    rawInfo->dimensionCount = dimensionCount;
    rawInfo->elementStructInfo = strdup(structName);
    return rawInfo;
}

int SymbolInfo_Array_bake(SymbolTable_t table, SymbolInfo_Array_Raw rawInfo) {
    if(rawInfo->elementType == SVT_Struct){
        SymbolInfo_Struct_t structInfo = NULL;
        int bakeResult = SymbolInfo_bakeStructName(table, rawInfo->elementStructInfo, &structInfo);
        rawInfo->elementStructInfo = structInfo;
        return bakeResult;
    }
    return 0;
}

void SymbolInfo_Array_destroyRaw(SymbolInfo_Array_Raw info) {
    if(info == NULL)
        return;
    if(info->elementType == SVT_Struct){
        if(info->elementStructInfo != NULL)
            free(info->elementStructInfo);
    }
    free(info);
}

void SymbolInfo_Array_destroy(SymbolInfo_Array_t info) {
    if(info == NULL)
        return;
    free(info);
}

SymbolInfo_Function_Raw
SymbolInfo_Function_create(Symbol_Value_Type returnType, void *returnTypeMeta, Symbol_Value_Type parameterTypes[],
                           char *parameterNames[], void *parametersMeta[], int parameterCount) {
    SymbolInfo_Function_Raw rawInfo = (SymbolInfo_Function_Raw)malloc(sizeof(SymbolInfo_Function));
    rawInfo->returnType = returnType;
    rawInfo->returnTypeMeta = returnTypeMeta;
    rawInfo->parameterCount = parameterCount;
    rawInfo->parameters = (SymbolInfo_Parameter_Raw*)malloc(sizeof(SymbolInfo_Parameter_Raw) * parameterCount);
    for(int i = 0; i < parameterCount; i++){
        rawInfo->parameters[i] = SymbolInfo_Parameter_create(parameterTypes[i], parameterNames[i], parametersMeta[i]);
    }
}

int SymbolInfo_Function_bakeReturnType(SymbolTable_t table, SymbolInfo_Function_Raw rawInfo) {
    if(rawInfo == NULL)
        return -1;
    if(rawInfo->returnType == SVT_Struct){
        SymbolInfo_Struct_t structInfo = NULL;
        int bakeResult = SymbolInfo_bakeStructName(table, rawInfo->returnTypeMeta, &structInfo);
        rawInfo->returnTypeMeta = structInfo;
        if(bakeResult != 0)
            return bakeResult;
    }
    if(rawInfo->returnType == SVT_Array){
        return SymbolInfo_Array_bake(table, rawInfo->returnTypeMeta);
    }
    return 0;
}

int SymbolInfo_Function_bakeParameters(SymbolTable_t table, SymbolInfo_Function_Raw rawInfo, int* errorParameterIndex) {
    if(rawInfo == NULL)
        return -1;
    int i = 0;
    for(; i < rawInfo->parameterCount; i++){
        SymbolInfo_Parameter_Raw parameter = rawInfo->parameters[i];
        int bakeResult = SymbolInfo_Parameter_bake(table, parameter);
        if(bakeResult != 0){
            *errorParameterIndex = i;
            return bakeResult;
        }
    }
    return 0;
}

void SymbolInfo_Function_destroyRaw(SymbolInfo_Function_Raw info, int retvalBakeResult, int bakedParameterCount) {
    if(info == NULL)
        return;
    if(retvalBakeResult == 0){
        if(info->returnType == SVT_Struct){
            if(info->returnTypeMeta != NULL)
                free(info->returnTypeMeta);
        }
        else if(info->returnType == SVT_Array){
            SymbolInfo_Array_destroyRaw(info->returnTypeMeta);
        }
    }
    if(bakedParameterCount == 0)
        return;
    // destroy the baked parameters if we have baked them
    for(int i = 0; i < bakedParameterCount; i++){
        SymbolInfo_Parameter_Raw parameter = info->parameters[i];
        SymbolInfo_Parameter_destroy(parameter);
    }
    // now destroy the raw parameters
    for(int i = bakedParameterCount; i < info->parameterCount; i++){
        SymbolInfo_Parameter_Raw parameter = info->parameters[i];
        SymbolInfo_Parameter_destroyRaw(parameter);
    }
    free(info->parameters);
    free(info);
}

void SymbolInfo_Function_destroy(SymbolInfo_Function_t info) {
    if(info == NULL)
        return;
    if(info->returnType == SVT_Array){
        SymbolInfo_Array_destroy(info->returnTypeMeta);
    }
    for(int i = 0; i < info->parameterCount; i++){
        SymbolInfo_Parameter_t parameter = info->parameters[i];
        if(parameter->parameterName != NULL)
            free(parameter->parameterName);
        if(parameter->parameterType == SVT_Array){
            SymbolInfo_Array_destroy(parameter->parameterMeta);
        }
        free(parameter);
    }
    free(info->parameters);
    free(info);
}

SymbolInfo_Parameter_Raw SymbolInfo_Parameter_create(Symbol_Value_Type type, char* parameterName, void *meta) {
    SymbolInfo_Parameter_Raw rawInfo = (SymbolInfo_Parameter_Raw)malloc(sizeof(SymbolInfo_Parameter));
    rawInfo->parameterType = type;
    rawInfo->parameterName = parameterName == NULL ? NULL : strdup(parameterName);
    rawInfo->parameterMeta = meta;
    return rawInfo;
}

int SymbolInfo_Parameter_bake(SymbolTable_t table, SymbolInfo_Parameter_Raw rawInfo) {
    if(rawInfo == NULL)
        return -1;
    SymbolInfo_Parameter_t parameter = (SymbolInfo_Parameter_t)rawInfo;
    if(parameter->parameterType == SVT_Struct){
        SymbolInfo_Struct_t structInfo = NULL;
        int bakeResult = SymbolInfo_bakeStructName(table, parameter->parameterMeta, &structInfo);
        parameter->parameterMeta = structInfo;
        if(bakeResult != 0){
            return bakeResult;
        }
    }
    if(parameter->parameterType == SVT_Array){
        int bakeResult = SymbolInfo_Array_bake(table, parameter->parameterMeta);
        if(bakeResult != 0){
            return bakeResult;
        }
    }
    return 0;
}

void SymbolInfo_Parameter_destroyRaw(SymbolInfo_Parameter_Raw info) {
    if(info == NULL)
        return;
    SymbolInfo_Parameter_Raw parameter = info;
    if(parameter->parameterName != NULL)
        free(parameter->parameterName);
    if(parameter->parameterType == SVT_Struct){
        if(parameter->parameterMeta != NULL)
            free(parameter->parameterMeta);
    }
    else if(parameter->parameterType == SVT_Array){
        SymbolInfo_Array_destroyRaw(parameter->parameterMeta);
    }
    free(parameter);
}

void SymbolInfo_Parameter_destroy(SymbolInfo_Parameter_t info) {
    if(info == NULL)
        return;
    SymbolInfo_Parameter_t parameter = info;
    if(parameter->parameterName != NULL)
        free(parameter->parameterName);
    if(parameter->parameterType == SVT_Array){
        SymbolInfo_Array_destroy(parameter->parameterMeta);
    }
    free(parameter);
}

SymbolInfo_Struct_Raw SymbolInfo_Struct_create(Symbol_Value_Type *memberTypes, void **memberMeta, int memberCount) {
    SymbolInfo_Struct_Raw rawInfo = (SymbolInfo_Struct_Raw)malloc(sizeof(SymbolInfo_Struct));
    rawInfo->memberCount = memberCount;
    rawInfo->members = (SymbolInfo_Member_Raw*)malloc(sizeof(SymbolInfo_Member_Raw) * memberCount);
    for(int i = 0; i < memberCount; i++){
        rawInfo->members[i] = SymbolInfo_Member_create(memberTypes[i], NULL, memberMeta[i]);
    }
    return rawInfo;
}

int SymbolInfo_Struct_bake(SymbolTable_t table, SymbolInfo_Struct_Raw rawInfo, int* errorMemberIndex) {
    if(rawInfo == NULL)
        return -1;
    int i = 0;
    for(; i < rawInfo->memberCount; i++){
        SymbolInfo_Member_Raw member = rawInfo->members[i];
        int bakeResult = SymbolInfo_Member_bake(table, member);
        if(bakeResult != 0){
            *errorMemberIndex = i;
            return bakeResult;
        }
    }
    return 0;
}

void SymbolInfo_Struct_destroyRaw(SymbolInfo_Struct_Raw info, int bakedMemberCount) {
    if(info == NULL)
        return;
    if(bakedMemberCount == 0)
        return;
    for(int i = 0; i < bakedMemberCount; i++){
        SymbolInfo_Member_Raw member = info->members[i];
        SymbolInfo_Member_destroy(member);
    }
    for(int i = bakedMemberCount; i < info->memberCount; i++){
        SymbolInfo_Member_Raw member = info->members[i];
        SymbolInfo_Member_destroyRaw(member);
    }
    free(info->members);
    free(info);
}


void SymbolInfo_Struct_destroy(SymbolInfo_Struct_t info) {
    if(info == NULL)
        return;
    if(info->memberCount == 0)
        return;
    for(int i = 0; i < info->memberCount; i++){
        SymbolInfo_Member_t member = info->members[i];
        SymbolInfo_Member_destroy(member);
    }
    free(info->members);
    free(info);
}

SymbolInfo_Member_Raw SymbolInfo_Member_create(Symbol_Value_Type memberType, char* memberName, void *memberMeta) {
    SymbolInfo_Member_Raw rawInfo = (SymbolInfo_Member_Raw)malloc(sizeof(SymbolInfo_Member));
    rawInfo->memberType = memberType;
    rawInfo->memberName = memberName == NULL ? NULL : strdup(memberName);
    rawInfo->memberMeta = memberMeta;
    return rawInfo;
}

int SymbolInfo_Member_bake(SymbolTable_t table, SymbolInfo_Member_Raw rawInfo) {
    if(rawInfo == NULL)
        return -1;
    SymbolInfo_Member_t member = (SymbolInfo_Member_t)rawInfo;
    if(member->memberType == SVT_Struct){
        SymbolInfo_Struct_t structInfo = NULL;
        int bakeResult = SymbolInfo_bakeStructName(table, member->memberMeta, &structInfo);
        member->memberMeta = structInfo;
        if(bakeResult != 0){
            return bakeResult;
        }
    }
    if(member->memberType == SVT_Array){
        int bakeResult = SymbolInfo_Array_bake(table, member->memberMeta);
        if(bakeResult != 0){
            return bakeResult;
        }
    }
    return 0;
}

void SymbolInfo_Member_destroyRaw(SymbolInfo_Member_Raw info) {
    if(info == NULL)
        return;
    SymbolInfo_Member_Raw member = info;
    if(member->memberName != NULL)
        free(member->memberName);
    if(member->memberType == SVT_Struct){
        if(member->memberMeta != NULL)
            free(member->memberMeta);
    }
    else if(member->memberType == SVT_Array){
        SymbolInfo_Array_destroyRaw(member->memberMeta);
    }
    free(member);
}

void SymbolInfo_Member_destroy(SymbolInfo_Member_t info) {
    if(info == NULL)
        return;
    SymbolInfo_Member_t member = info;
    if(member->memberName != NULL)
        free(member->memberName);
    if(member->memberType == SVT_Array){
        SymbolInfo_Array_destroy(member->memberMeta);
    }
    free(member);
}



