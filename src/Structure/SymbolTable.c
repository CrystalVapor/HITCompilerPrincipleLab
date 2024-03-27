//
// Created by Crystal on 2024/3/19.
//

#include <string.h>
#include <assert.h>

#include "Structure/SymbolTable.h"

#define SYMBOL_TABLE_HASH_TABLE_SIZE 10007

////////////////////////////////////////
/// debug
////////////////////////////////////////

void SymbolInfo_Struct_printDebug(SymbolInfo_t structInfo, char *buffer, int size);

void SymbolInfo_Function_printDebug(SymbolInfo_t functionInfo, char *buffer, int size);

void SymbolInfo_Variable_printDebug(SymbolInfo_t variableInfo, char *buffer, int size);

void SymbolInfo_DebugHelper_getTypeString(Symbol_Value_Type e, void* meta, char buffer[], int bufferSize);

////////////////////////////////////////
/// SymbolTable
////////////////////////////////////////

SymbolTable_t SymbolTable_create() {
    SymbolTable_t table = (SymbolTable_t)malloc(sizeof(SymbolTable));
    table->table = SimpleHashTable_createWithSize(sizeof(SymbolRecord), NULL, NULL, SYMBOL_TABLE_HASH_TABLE_SIZE);
    table->nextScopeID = 0;
    table->scopeStack = SimpleArray_create(sizeof(int));
    memset(table->scopePrefix, 0, sizeof(table->scopePrefix));
    SymbolTable_enterScope(table);
    return table;
}

void SymbolTable_destroy(void* tableToDestroy){
    SymbolTable_t table = (SymbolTable_t)tableToDestroy;
    SimpleHashTable_destroy(table->table, NULL, SymbolRecord_destroy);
    SimpleArray_destroy(table->scopeStack, NULL);
    free(table);
}

void SymbolTable_enterScope(SymbolTable_t table) {
    int currentScope = table->nextScopeID;
    SimpleArray_pushBack(table->scopeStack, &table->nextScopeID);
    sprintf(table->scopePrefix, "+%d_", currentScope);
    table->nextScopeID++;
}

void SymbolTable_leaveScope(SymbolTable_t table) {
    assert(table->scopeStack->num > 0);
    SimpleArray_popBack(table->scopeStack, NULL);
    int currentScope = *(int *) SimpleArray_back(table->scopeStack);
    sprintf(table->scopePrefix, "+%d_", currentScope);
}

int SymbolTable_getScope(SymbolTable_t table) {
    return *(int *) SimpleArray_back(table->scopeStack);
}

char *SymbolTable_generateName(SymbolTable_t table, char *name, char *buffer, int bufferSize) {
    snprintf(buffer, bufferSize, "%s%s", table->scopePrefix, name);
    return buffer + strlen(table->scopePrefix);
}

SymbolDefineStatus SymbolTable_lookupRecord(SymbolTable_t table, char *name, SymbolRecord_t *outRecord) {
    int scopeIndex = SymbolTable_internalLookupRecord(table, name, outRecord);
    if(scopeIndex == -1)
    {
        return SDS_Undefined;
    }
    if(scopeIndex==table->scopeStack->num-1)
    {
        if(SymbolRecord_isSymbolDefined(*outRecord))
            return SDS_Defined;
        else
            return SDS_Declared;
    }
    else
    {
        if(SymbolRecord_isSymbolDefined(*outRecord))
            return SDS_ExternalDefined;
        else
            return SDS_ExternalDeclared;
    }
}

int SymbolTable_internalLookupRecord(SymbolTable_t table, char *name, SymbolRecord_t *outRecord) {
    for(int i = table->scopeStack->num - 1; i >= 0; i--){
        int scope = *(int*) SimpleArray_at(table->scopeStack, i);
        char buffer[256];
        snprintf(buffer, sizeof(buffer), "+%d_%s", scope, name);
#ifdef SYMBOL_TABLE_DEBUG
        printf("Looking up \"%s\"\n", buffer);
#endif
        SymbolRecord_t record = SimpleHashTable_find(table->table, buffer, (int)strlen(buffer)+1);
        if(record != NULL){
            *outRecord = record;
            return i;
        }
    }
#ifdef SYMBOL_TABLE_DEBUG
    printf("Failed to find \"%s\"\n", name);
#endif
    *outRecord = NULL;
    return -1;
}

int SymbolTable_insertRecord(SymbolTable_t table, char *name, SymbolRecord_t record) {
    record->scope = SymbolTable_getScope(table);
    char fullNameBuffer[256];
    SymbolTable_generateName(table, name, fullNameBuffer, sizeof(fullNameBuffer));
#ifdef SYMBOL_TABLE_STRUCT_NAME
    if(record->type == ST_Struct){
        SymbolInfo_Struct_setName(record->info, name);
    }
#endif
#ifdef SYMBOL_TABLE_FUNCTION_NAME
    if(record->type == ST_Function){
        SymbolInfo_Function_setName(record->info, name);
    }
#endif
#ifndef SYMBOL_TABLE_DEBUG
    return SimpleHashTable_insert(table->table, fullNameBuffer, (int)strlen(fullNameBuffer)+1, record);
#else
    char debugBuffer[1024];
    int result = SimpleHashTable_insert(table->table, fullNameBuffer, (int)strlen(fullNameBuffer) + 1, record);
    if(result == 0){
        SymbolRecord_printDebug(record, debugBuffer, 1024);
        printf("Inserted record \"%s\": %s\n", fullNameBuffer, debugBuffer);
    }
    else
    {
        printf("Failed to insert record \"%s\": %s\n", fullNameBuffer, debugBuffer);
    }
    return result;
#endif
}

SymbolTable_Error
SymbolTable_createVariable(SymbolTable_t table, SymbolRecord *outRecord, Symbol_Value_Type type, void* meta){
    SymbolInfo_Variable_t info = SymbolInfo_Variable_createBaked(type, meta);
    outRecord->type = ST_Variable;
    outRecord->info = info;
    return SE_Success;
}

SymbolTable_Error
SymbolTable_createFunction(SymbolTable_t table, SymbolRecord *outRecord,
                           Symbol_Value_Type returnType, void* returnTypeMeta,
                           Symbol_Value_Type *parameterTypes, char **parameterNames, void **parametersMeta, int parameterCount){
    SymbolInfo_Function_t info = SymbolInfo_Function_createBaked(returnType, returnTypeMeta, parameterTypes, parameterNames, parametersMeta, parameterCount);
    outRecord->type = ST_Function;
    outRecord->info = info;
    return SE_Success;
}

SymbolTable_Error
SymbolTable_createStruct(SymbolTable_t table, SymbolRecord *outRecord,
                         Symbol_Value_Type *memberTypes, char **memberNames, void **memberMetas, int memberCount){
    SymbolInfo_Struct_t info = SymbolInfo_Struct_create(memberTypes, memberNames, memberMetas, memberCount);
    outRecord->type = ST_Struct;
    outRecord->info = info;
    return SE_Success;
}

SymbolTable_Error
SymbolTable_createVariableByRawMeta(SymbolTable_t table, SymbolRecord *outRecord, Symbol_Value_Type type, void *meta) {
    SymbolInfo_Variable_Raw rawInfo = SymbolInfo_Variable_create(type, meta);
    SymbolTable_Error bakeResult = SymbolInfo_Variable_bake(table, rawInfo);
    if(bakeResult != SE_Success){
        SymbolInfo_Variable_destroyRaw(rawInfo);
        outRecord->info = NULL;
        return bakeResult;
    }
    SymbolInfo_Variable_t info = (SymbolInfo_Variable_t)rawInfo;
    outRecord->type = ST_Variable;
    outRecord->info = info;
    return SE_Success;
}

SymbolTable_Error
SymbolTable_createFunctionByRawMeta(SymbolTable_t table, SymbolRecord *outRecord, Symbol_Value_Type returnType,
                                    void *returnTypeMeta, Symbol_Value_Type *parameterTypes,
                                    char **parameterNames, void **parametersMeta, int parameterCount) {
    SymbolInfo_Function_Raw rawInfo = SymbolInfo_Function_create(returnType, returnTypeMeta, parameterTypes, parameterNames, parametersMeta, parameterCount);
    SymbolTable_Error bakeResult = SymbolInfo_Function_bakeReturnType(table, rawInfo);
    if(bakeResult != SE_Success){
        SymbolInfo_Function_destroyRaw(rawInfo, 0, 0);
        outRecord->info = NULL;
        return bakeResult;
    }
    int errorParameterIndex = 0;
    bakeResult = SymbolInfo_Function_bakeParameters(table, rawInfo, &errorParameterIndex);
    if(bakeResult != SE_Success){
        SymbolInfo_Function_destroyRaw(rawInfo, 0, errorParameterIndex);
        outRecord->info = NULL;
        return bakeResult;
    }
    SymbolInfo_Function_t info = (SymbolInfo_Function_t)rawInfo;
    outRecord->type = ST_Function;
    outRecord->info = info;
    return SE_Success;
}

SymbolTable_Error
SymbolTable_createStructByRawMeta(SymbolTable_t table, SymbolRecord *outRecord, Symbol_Value_Type *memberTypes,
                                  char **memberNames, void **memberMetas, int memberCount) {
    SymbolInfo_Struct_Raw rawInfo = SymbolInfo_Struct_create(memberTypes, memberNames, memberMetas, memberCount);
    int errorMemberIndex = 0;
    SymbolTable_Error bakeResult = SymbolInfo_Struct_bake(table, rawInfo, &errorMemberIndex);
    if(bakeResult != SE_Success){
        SymbolInfo_Struct_destroyRaw(rawInfo, errorMemberIndex);
        outRecord->info = NULL;
        return bakeResult;
    }
    SymbolInfo_Struct_t info = (SymbolInfo_Struct_t)rawInfo;
    outRecord->type = ST_Struct;
    outRecord->info = info;
    return SE_Success;
}

SymbolTable_Error SymbolTable_createVariableByInfo(SymbolTable_t table, SymbolRecord *outRecord, SymbolInfo_t info)
{
    outRecord->type = ST_Variable;
    outRecord->info = info;
    return SE_Success;
}

SymbolTable_Error SymbolTable_createFunctionByInfo(SymbolTable_t table, SymbolRecord *outRecord, SymbolInfo_t info) {
    outRecord->type = ST_Function;
    outRecord->info = info;
    return SE_Success;
}

SymbolTable_Error SymbolTable_createStructByInfo(SymbolTable_t table, SymbolRecord *outRecord, SymbolInfo_t info) {
    outRecord->type = ST_Struct;
    outRecord->info = info;
    return SE_Success;
}

////////////////////////////////////////
/// SymbolRecord
////////////////////////////////////////

SymbolRecord_t SymbolRecord_create(SymbolType type, SymbolInfo_t info) {
    SymbolRecord_t record = (SymbolRecord_t)malloc(sizeof(SymbolRecord));
    record->type = type;
    record->info = info;
    return record;
}
void SymbolRecord_destroy(void* recordToDestroy){
    SymbolRecord_t record = (SymbolRecord_t)recordToDestroy;
    switch(record->type)
    {
        case ST_Variable:
            SymbolInfo_Variable_destroy(record->info);
            break;
        case ST_Function:
            SymbolInfo_Function_destroy(record->info);
            break;
        case ST_Struct:
            SymbolInfo_Struct_destroy(record->info);
            break;
        default:
            break;
    }
    free(record);
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
        case SVT_Float:
            rawInfo = (SymbolInfo_Variable_Raw)malloc(sizeof(SymbolInfo_Variable));
            ((SymbolInfo_Variable_Raw)rawInfo)->type = SVT_Float;
            ((SymbolInfo_Variable_Raw)rawInfo)->meta = NULL;
            return rawInfo;
        case SVT_Struct:
            rawInfo = (SymbolInfo_Variable_Raw)malloc(sizeof(SymbolInfo_Variable));
            ((SymbolInfo_Variable_Raw)rawInfo)->type = SVT_Struct;
            ((SymbolInfo_Variable_Raw)rawInfo)->meta = strdup((char*)meta);
            return rawInfo;
        case SVT_Array:
            rawInfo = (SymbolInfo_Variable_Raw)malloc(sizeof(SymbolInfo_Variable));
            ((SymbolInfo_Variable_Raw)rawInfo)->type = SVT_Array;
            ((SymbolInfo_Variable_Raw)rawInfo)->meta = (SymbolInfo_Array_Raw)meta;
            return rawInfo;
        default:
            return NULL;
    }
}

SymbolTable_Error SymbolInfo_Variable_bake(SymbolTable_t table, SymbolInfo_Variable_Raw rawInfo) {
    if (rawInfo == NULL)
        return SE_UnexpectedNullPointer;
    switch (rawInfo->type) {
        case SVT_Int:
        case SVT_Float:
            return SE_Success;
        case SVT_Struct:
        {
            SymbolInfo_Struct_t structInfo = NULL;
            SymbolTable_Error bakeResult = SymbolInfo_bakeStructName(table, rawInfo->meta, &structInfo);
            rawInfo->meta = structInfo;
            return bakeResult;
        }
        case SVT_Array:
        {
            SymbolInfo_Array_t arrayInfo = rawInfo->meta;
            return SymbolInfo_Array_bake(table, arrayInfo);
        }
        default:
            return SE_UnexpectedSymbolValueType;
    }
}

SymbolInfo_Variable_t SymbolInfo_Variable_createBaked(Symbol_Value_Type type, SymbolInfo_t meta){
    SymbolInfo_Variable_Raw info = NULL;
    switch(type){
        case SVT_Int:
            info = (SymbolInfo_Variable_Raw)malloc(sizeof(SymbolInfo_Variable));
            ((SymbolInfo_Variable_Raw)info)->type = SVT_Int;
            ((SymbolInfo_Variable_Raw)info)->meta = NULL;
            return info;
        case SVT_Float:
            info = (SymbolInfo_Variable_Raw)malloc(sizeof(SymbolInfo_Variable));
            ((SymbolInfo_Variable_Raw)info)->type = SVT_Float;
            ((SymbolInfo_Variable_Raw)info)->meta = NULL;
            return info;
        case SVT_Struct:
            info = (SymbolInfo_Variable_Raw)malloc(sizeof(SymbolInfo_Variable));
            ((SymbolInfo_Variable_Raw)info)->type = SVT_Struct;
            ((SymbolInfo_Variable_Raw)info)->meta = meta;
            return info;
        case SVT_Array:
            info = (SymbolInfo_Variable_Raw)malloc(sizeof(SymbolInfo_Variable));
            ((SymbolInfo_Variable_Raw)info)->type = SVT_Array;
            ((SymbolInfo_Variable_Raw)info)->meta = meta;
            return info;
        default:
            return NULL;
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
    rawInfo->elementStructInfo = structName == NULL ? NULL : strdup(structName);
    return rawInfo;
}

SymbolInfo_Array_t SymbolInfo_Array_createBaked(Symbol_Value_Type elementType, SymbolInfo_t elementStructInfo, int dimensions[], int dimensionCount){
    if(elementType == SVT_Array)
        return NULL;
    SymbolInfo_Array_Raw info = (SymbolInfo_Array_Raw)malloc(sizeof(SymbolInfo_Array));
    info->elementType = elementType;
    memcpy(info->dimensions, dimensions, sizeof(int) * dimensionCount);
    info->dimensionCount = dimensionCount;
    info->elementStructInfo = elementStructInfo;
    return info;
}

SymbolTable_Error SymbolInfo_Array_bake(SymbolTable_t table, SymbolInfo_Array_Raw rawInfo) {
    if(rawInfo->elementType == SVT_Struct){
        SymbolInfo_Struct_t structInfo = NULL;
        SymbolTable_Error bakeResult = SymbolInfo_bakeStructName(table, rawInfo->elementStructInfo, &structInfo);
        rawInfo->elementStructInfo = structInfo;
        return bakeResult;
    }
    return SE_Success;
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
    // cast to void* to make clang-tidy happy
    rawInfo->parameters = (void*)(SymbolInfo_Parameter_Raw*)malloc(sizeof(SymbolInfo_Parameter_Raw) * parameterCount);
    for(int i = 0; i < parameterCount; i++){
        rawInfo->parameters[i] = SymbolInfo_Parameter_create(parameterTypes[i], parameterNames[i], parametersMeta[i]);
    }
    rawInfo->offset = INVALID_OFFSET;
    return rawInfo;
}

SymbolTable_Error SymbolInfo_Function_bakeReturnType(SymbolTable_t table, SymbolInfo_Function_Raw rawInfo) {
    if(rawInfo == NULL)
        return SE_UnexpectedNullPointer;
    if(rawInfo->returnType == SVT_Struct){
        SymbolInfo_Struct_t structInfo = NULL;
        SymbolTable_Error bakeResult = SymbolInfo_bakeStructName(table, rawInfo->returnTypeMeta, &structInfo);
        rawInfo->returnTypeMeta = structInfo;
        if(bakeResult != SE_Success)
            return bakeResult;
    }
    if(rawInfo->returnType == SVT_Array){
        return SymbolInfo_Array_bake(table, rawInfo->returnTypeMeta);
    }
    return SE_Success;
}

SymbolTable_Error SymbolInfo_Function_bakeParameters(SymbolTable_t table, SymbolInfo_Function_Raw rawInfo, int* errorParameterIndex) {
    if(rawInfo == NULL)
        return SE_UnexpectedNullPointer;
    int i = 0;
    for(; i < rawInfo->parameterCount; i++){
        SymbolInfo_Parameter_Raw parameter = rawInfo->parameters[i];
        SymbolTable_Error bakeResult = SymbolInfo_Parameter_bake(table, parameter);
        if(bakeResult != SE_Success){
            *errorParameterIndex = i;
            return bakeResult;
        }
    }
    return SE_Success;
}

SymbolInfo_Function_t
SymbolInfo_Function_createBaked(Symbol_Value_Type returnType, SymbolInfo_t returnTypeMeta, Symbol_Value_Type parameterTypes[],
                                char *parameterNames[], void *parametersMeta[], int parameterCount){
    SymbolInfo_Function_Raw rawInfo = (SymbolInfo_Function_Raw)malloc(sizeof(SymbolInfo_Function));
    rawInfo->returnType = returnType;
    rawInfo->returnTypeMeta = returnTypeMeta;
    rawInfo->parameterCount = parameterCount;
    // cast to void* to make clang-tidy happy
    rawInfo->parameters = (void*)(SymbolInfo_Parameter_Raw*)malloc(sizeof(SymbolInfo_Parameter_Raw) * parameterCount);
    for(int i = 0; i < parameterCount; i++){
        rawInfo->parameters[i] = SymbolInfo_Parameter_createBaked(parameterTypes[i], parameterNames[i], parametersMeta[i]);
    }
    rawInfo->offset = INVALID_OFFSET;
    return rawInfo;
}

void SymbolInfo_Function_destroyRaw(SymbolInfo_Function_Raw info, int retvalBakeResult, int bakedParameterCount) {
    if(info == NULL)
        return;
#ifdef SYMBOL_TABLE_FUNCTION_NAME
    if(info->functionName != NULL)
        free(info->functionName);
#endif
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
#ifdef SYMBOL_TABLE_FUNCTION_NAME
    if(info->functionName != NULL)
        free(info->functionName);
#endif
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

int SymbolInfo_Function_hasParameterName(SymbolInfo_Function_t functionInfo, char* parameterName){
    if(parameterName == NULL)
    {
        return 0;
    }
    for(int i = 0; i < functionInfo->parameterCount; i++)
    {
        SymbolInfo_Parameter_t parameter = functionInfo->parameters[i];
        if(parameter->parameterName != NULL && strcmp(parameter->parameterName, parameterName) == 0)
        {
            return 1;
        }
    }
    return 0;
}

void SymbolInfo_Function_addParameter(SymbolInfo_Function_t functionInfo, SymbolInfo_t parameter){
    functionInfo->parameters[functionInfo->parameterCount] = parameter;
    functionInfo->parameterCount++;
}
#ifdef SYMBOL_TABLE_FUNCTION_NAME
/**
 * Get the name of the function.
 * @param info The baked SymbolInfo_Function.
 * @return The name of the function.
 */
char* SymbolInfo_Function_getName(SymbolInfo_Function_t info){
    return info->functionName;
}

/**
 * Set the name of the function.
 * @param info The baked SymbolInfo_Function.
 * @param name The name of the function, will be duplicated.
 */
void SymbolInfo_Function_setName(SymbolInfo_Function_t info, char* name){
    info->functionName = name == NULL ? NULL : strdup(name);
}
#endif

SymbolInfo_Parameter_Raw SymbolInfo_Parameter_create(Symbol_Value_Type type, char* parameterName, void *meta) {
    SymbolInfo_Parameter_Raw rawInfo = (SymbolInfo_Parameter_Raw)malloc(sizeof(SymbolInfo_Parameter));
    rawInfo->parameterType = type;
    rawInfo->parameterName = parameterName == NULL ? NULL : strdup(parameterName);
    rawInfo->parameterMeta = meta;
    return rawInfo;
}

SymbolTable_Error SymbolInfo_Parameter_bake(SymbolTable_t table, SymbolInfo_Parameter_Raw rawInfo) {
    if(rawInfo == NULL)
        return SE_UnexpectedNullPointer;
    SymbolInfo_Parameter_t parameter = (SymbolInfo_Parameter_t)rawInfo;
    if(parameter->parameterType == SVT_Struct){
        SymbolInfo_Struct_t structInfo = NULL;
        SymbolTable_Error bakeResult = SymbolInfo_bakeStructName(table, parameter->parameterMeta, &structInfo);
        parameter->parameterMeta = structInfo;
        if(bakeResult != SE_Success){
            return bakeResult;
        }
    }
    if(parameter->parameterType == SVT_Array){
        SymbolTable_Error bakeResult = SymbolInfo_Array_bake(table, parameter->parameterMeta);
        if(bakeResult != SE_Success){
            return bakeResult;
        }
    }
    return SE_Success;
}

SymbolInfo_Parameter_t SymbolInfo_Parameter_createBaked(Symbol_Value_Type type, char* parameterName, SymbolInfo_t meta){
    SymbolInfo_Parameter_Raw info = (SymbolInfo_Parameter_Raw)malloc(sizeof(SymbolInfo_Parameter));
    info->parameterType = type;
    info->parameterName = parameterName == NULL ? NULL : strdup(parameterName);
    info->parameterMeta = meta;
    return info;
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

SymbolInfo_Struct_Raw
SymbolInfo_Struct_create(Symbol_Value_Type *memberTypes, char **memberNames, void **memberMeta, int memberCount) {
    SymbolInfo_Struct_Raw rawInfo = (SymbolInfo_Struct_Raw)malloc(sizeof(SymbolInfo_Struct));
    rawInfo->memberCount = memberCount;
    // cast to void* to make clang-tidy happy
    rawInfo->members = (void*)(SymbolInfo_Member_Raw*)malloc(sizeof(SymbolInfo_Member_Raw) * memberCount);
    for(int i = 0; i < memberCount; i++){
        rawInfo->members[i] = SymbolInfo_Member_create(memberTypes[i], memberNames[i], memberMeta[i]);
    }
    return rawInfo;
}

SymbolTable_Error SymbolInfo_Struct_bake(SymbolTable_t table, SymbolInfo_Struct_Raw rawInfo, int* errorMemberIndex) {
    if(rawInfo == NULL)
        return SE_UnexpectedNullPointer;
    int i = 0;
    for(; i < rawInfo->memberCount; i++){
        SymbolInfo_Member_Raw member = rawInfo->members[i];
        SymbolTable_Error bakeResult = SymbolInfo_Member_bake(table, member);
        if(bakeResult != SE_Success){
            *errorMemberIndex = i;
            return bakeResult;
        }
    }
    return SE_Success;
}

SymbolInfo_Struct_t
SymbolInfo_Struct_createBaked(Symbol_Value_Type *memberTypes, char **memberNames, void **memberMeta, int memberCount) {
    SymbolInfo_Struct_Raw info = (SymbolInfo_Struct_Raw)malloc(sizeof(SymbolInfo_Struct));
    info->memberCount = memberCount;
    // cast to void* to make clang-tidy happy
    info->members = (void*)(SymbolInfo_Member_Raw*)malloc(sizeof(SymbolInfo_Member_Raw) * memberCount);
    for(int i = 0; i < memberCount; i++){
        info->members[i] = SymbolInfo_Member_create(memberTypes[i], memberNames[i], memberMeta[i]);
    }
    return info;
}

void SymbolInfo_Struct_destroyRaw(SymbolInfo_Struct_Raw info, int bakedMemberCount) {
    if(info == NULL)
        return;
#ifdef SYMBOL_TABLE_STRUCT_NAME
    if(info->structName != NULL)
        free(info->structName);
#endif
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
#ifdef SYMBOL_TABLE_STRUCT_NAME
    if(info->structName != NULL)
        free(info->structName);
#endif
    if(info->memberCount == 0)
        return;
    for(int i = 0; i < info->memberCount; i++){
        SymbolInfo_Member_t member = info->members[i];
        SymbolInfo_Member_destroy(member);
    }
    free(info->members);
    free(info);
}

int SymbolInfo_Struct_checkMemberName(SymbolInfo_Struct_t info, char* memberName){
    for(int i = 0; i < info->memberCount; i++){
        SymbolInfo_Member_t member = info->members[i];
        if(strcmp(member->memberName, memberName) == 0){
            return 1;
        }
    }
    return 0;
}


void SymbolInfo_Struct_insertMember(SymbolInfo_Struct_t info, SymbolInfo_t memberInfo){
    info->members[info->memberCount] = memberInfo;
    info->memberCount++;
}


#ifdef SYMBOL_TABLE_STRUCT_NAME
char* SymbolInfo_Struct_getName(SymbolInfo_Struct_t info)
{
    if(info == NULL)
        return NULL;
    return info->structName;
}

void SymbolInfo_Struct_setName(SymbolInfo_Struct_t info, char* name)
{
    info->structName = name == NULL ? NULL : strdup(name);
}
#endif

SymbolInfo_Member_Raw SymbolInfo_Member_create(Symbol_Value_Type memberType, char* memberName, void *memberMeta) {
    SymbolInfo_Member_Raw rawInfo = (SymbolInfo_Member_Raw)malloc(sizeof(SymbolInfo_Member));
    rawInfo->memberType = memberType;
    rawInfo->memberName = memberName == NULL ? NULL : strdup(memberName);
    rawInfo->memberMeta = memberMeta;
    return rawInfo;
}

SymbolTable_Error SymbolInfo_Member_bake(SymbolTable_t table, SymbolInfo_Member_Raw rawInfo) {
    if(rawInfo == NULL)
        return SE_UnexpectedNullPointer;
    SymbolInfo_Member_t member = (SymbolInfo_Member_t)rawInfo;
    if(member->memberType == SVT_Struct){
        SymbolInfo_Struct_t structInfo = NULL;
        SymbolTable_Error bakeResult = SymbolInfo_bakeStructName(table, member->memberMeta, &structInfo);
        member->memberMeta = structInfo;
        if(bakeResult != SE_Success){
            return bakeResult;
        }
    }
    if(member->memberType == SVT_Array){
        SymbolTable_Error bakeResult = SymbolInfo_Array_bake(table, member->memberMeta);
        if(bakeResult != SE_Success){
            return bakeResult;
        }
    }
    return SE_Success;
}

SymbolInfo_Member_t SymbolInfo_Member_createBaked(Symbol_Value_Type memberType, char* memberName, SymbolInfo_t memberMeta){
    SymbolInfo_Member_Raw info = (SymbolInfo_Member_Raw)malloc(sizeof(SymbolInfo_Member));
    info->memberType = memberType;
    info->memberName = memberName == NULL ? NULL : strdup(memberName);
    info->memberMeta = memberMeta;
    return info;
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

void SymbolRecord_printDebug(SymbolRecord_t record, char *buffer, int bufferSize) {
    if(record == NULL){
        snprintf(buffer, bufferSize, "NULL SymbolRecord");
        return;
    }
    switch (record->type) {
        case ST_Variable:
            SymbolInfo_Variable_printDebug(record->info, buffer, bufferSize);
            break;
        case ST_Function:
            SymbolInfo_Function_printDebug(record->info, buffer, bufferSize);
            break;
        case ST_Struct:
            SymbolInfo_Struct_printDebug(record->info, buffer, bufferSize);
            break;
        default:
            snprintf(buffer, bufferSize, "Unknown SymbolRecord type");
            break;

    }
}

SymbolTable_Error SymbolInfo_bakeStructName(SymbolTable_t table, char *structName, SymbolInfo_Struct_t *foundStruct) {
    SymbolRecord_t record = NULL;
    SymbolDefineStatus status = SymbolTable_lookupRecord(table, structName, &record);
    if(status == SDS_Undefined){
        *foundStruct = NULL;
        free(structName); // free the strdup-ed name
        return SE_StructNotFound;
    }
    if(status != SDS_Defined){
        *foundStruct = NULL;
        free(structName); // free the strdup-ed name
        return SE_StructNotDefined;
    }
    if(record->type != ST_Struct){
        *foundStruct = NULL;
        free(structName); // free the strdup-ed name
        return SE_UnexpectedSymbolValueType;
    }
    *foundStruct = (SymbolInfo_Struct_t)record->info;
    return SE_Success;
}



int SymbolRecord_isSymbolDefined(SymbolRecord_t record) {
    switch(record->type){
        case ST_Variable:
            return 1;
        case ST_Function: {
            SymbolInfo_Function_t functionInfo = (SymbolInfo_Function_t) record->info;
            return functionInfo->offset != INVALID_OFFSET;
        }
        case ST_Struct:
            return 1;
        default:
            return 0;
    }
}



void SymbolInfo_Variable_printDebug(SymbolInfo_t variableInfo, char *buffer, int size) {
    SymbolInfo_Variable_t info = (SymbolInfo_Variable_t)variableInfo;
    SymbolInfo_DebugHelper_getTypeString(info->type, info->meta, buffer, size);
    if(info->type == SVT_Struct){
        char structDefBuffer[256];
        SymbolInfo_Struct_printDebug(info->meta, structDefBuffer, sizeof(structDefBuffer));
        snprintf(buffer+strlen(buffer), size-strlen(buffer), "\n\tVariable %s", structDefBuffer);
    }
    if(info->type == SVT_Array)
    {
        SymbolInfo_Array_t arrayInfo = info->meta;
        if(arrayInfo->elementType == SVT_Struct){
            char structDefBuffer[256];
            SymbolInfo_Struct_printDebug(arrayInfo->elementStructInfo, structDefBuffer, sizeof(structDefBuffer));
            snprintf(buffer+strlen(buffer), size-strlen(buffer), "\n\tArray %s", structDefBuffer);
        }
    }
}

void SymbolInfo_Function_printDebug(SymbolInfo_t functionInfo, char *buffer, int size) {
    SymbolInfo_Function_t info = (SymbolInfo_Function_t)functionInfo;
    char returnTypeBuffer[256];
    SymbolInfo_DebugHelper_getTypeString(info->returnType, info->returnTypeMeta, returnTypeBuffer, sizeof(returnTypeBuffer));
#ifndef SYMBOL_TABLE_FUNCTION_NAME
    snprintf(buffer, size, "Function: %s(", returnTypeBuffer);
#else
    snprintf(buffer, size, "Function: %s %s(", returnTypeBuffer, info->functionName == NULL ? "NULL" : info->functionName);
#endif
    int offset = (int)strlen(buffer);
    for(int i = 0; i < info->parameterCount; i++){
        char parameterTypeBuffer[256];
        SymbolInfo_Parameter_t paraInfo = info->parameters[i];
        SymbolInfo_DebugHelper_getTypeString(paraInfo->parameterType, paraInfo->parameterMeta, parameterTypeBuffer, sizeof(parameterTypeBuffer));
        offset += snprintf(buffer+offset, size-offset, "%s %s", parameterTypeBuffer, paraInfo->parameterName == NULL ? "NULL" : paraInfo->parameterName);
        if(i != info->parameterCount - 1){
            offset += snprintf(buffer+offset, size-offset, ", ");
        }
    }
    snprintf(buffer+offset, size-offset, ")");
    if(info->returnType== SVT_Struct){
        char structDefBuffer[256];
        SymbolInfo_Struct_printDebug(info->returnTypeMeta, structDefBuffer, sizeof(structDefBuffer));
        snprintf(buffer+strlen(buffer), size-strlen(buffer), "\n\tReturn %s", structDefBuffer);
    }
    for(int i = 0; i < info->parameterCount; i++) {
        SymbolInfo_Parameter_t param = info->parameters[i];
        if(param->parameterType == SVT_Struct){
            char structDefBuffer[256];
            SymbolInfo_Struct_printDebug(param->parameterMeta, structDefBuffer, sizeof(structDefBuffer));
            snprintf(buffer+strlen(buffer), size-strlen(buffer), "\n\tParam [%d] %s", i, structDefBuffer);
        }
    }
}

void SymbolInfo_Struct_printDebug(SymbolInfo_t structInfo, char *buffer, int size) {
    SymbolInfo_Struct_t info = (SymbolInfo_Struct_t)structInfo;
#ifndef SYMBOL_TABLE_STRUCT_NAME
    snprintf(buffer, size, "Struct: {");
#else
    snprintf(buffer, size, "Struct \"%s\": {", info->structName == NULL ? "NULL" : info->structName);
#endif
    int offset = (int)strlen(buffer);
    for(int i = 0; i < info->memberCount; i++){
        char memberTypeBuffer[256];
        SymbolInfo_Member_t memberInfo = info->members[i];
        SymbolInfo_DebugHelper_getTypeString(memberInfo->memberType, memberInfo->memberMeta, memberTypeBuffer, sizeof(memberTypeBuffer));
        offset += snprintf(buffer+offset, size-offset, "%s %s", memberTypeBuffer, memberInfo->memberName == NULL ? "NULL" : memberInfo->memberName);
        if(i != info->memberCount - 1){
            offset += snprintf(buffer+offset, size-offset, ", ");
        }
    }
    snprintf(buffer+offset, size-offset, "}");
    for(int i = 0; i < info->memberCount; i++) {
        SymbolInfo_Member_t member = info->members[i];
        if(member->memberType == SVT_Struct){
            char structDefBuffer[256];
            SymbolInfo_Struct_printDebug(member->memberMeta, structDefBuffer, sizeof(structDefBuffer));
            snprintf(buffer+strlen(buffer), size-strlen(buffer), "\n\tMember [%s] %s", member->memberName, structDefBuffer);
        }
    }
}

void SymbolInfo_DebugHelper_getTypeString(Symbol_Value_Type e, void* meta, char *buffer, int bufferSize) {
    switch (e) {
        case SVT_Int:
            snprintf(buffer, bufferSize, "int");
            break;
        case SVT_Float:
            snprintf(buffer, bufferSize, "float");
            break;
        case SVT_Struct:
#ifndef SYMBOL_TABLE_STRUCT_NAME
            snprintf(buffer, bufferSize, "struct");
#else
            snprintf(buffer, bufferSize, "struct \"%s\"", SymbolInfo_Struct_getName((SymbolInfo_Struct_t)meta));
#endif
            break;
        case SVT_Array: {
            SymbolInfo_Array_t arrayInfo = (SymbolInfo_Array_t) meta;
            char dimBuffer[256];
            char dimListBuffer[256];
            snprintf(dimBuffer, sizeof(dimBuffer), "[%d]", arrayInfo->dimensions[0]);
            for (int i = 1; i < arrayInfo->dimensionCount ; i++) {
                snprintf(dimListBuffer, sizeof(dimListBuffer) - strlen(dimBuffer), "%s[%d]", dimBuffer , arrayInfo->dimensions[i]);
                strcpy(dimBuffer, dimListBuffer);
            }
            char elementTypeBuffer[256];
            SymbolInfo_DebugHelper_getTypeString(arrayInfo->elementType, arrayInfo->elementStructInfo, elementTypeBuffer, sizeof(elementTypeBuffer));
            snprintf(buffer, bufferSize, "%s %s", elementTypeBuffer , dimBuffer);
            break;
        }
        case SVT_Void:
            snprintf(buffer, bufferSize, "void");
            break;
        default:
            snprintf(buffer, bufferSize, "Unknown_Type");
            break;
    }
}


