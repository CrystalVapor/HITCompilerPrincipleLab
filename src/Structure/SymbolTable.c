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
/// SymbolValue
////////////////////////////////////////

int SymbolValue_getSize(Symbol_Value_Type type, SymbolInfo_t meta) {
    switch (type) {
        case SVT_Int:
        case SVT_Float:
            return 4;
        case SVT_Struct:
            return ((SymbolInfo_Struct_t)meta)->size;
        case SVT_Array:
            return ((SymbolInfo_Array_t)meta)->dimension * SymbolValue_getSize(((SymbolInfo_Array_t)meta)->elementType,
                                                                               ((SymbolInfo_Array_t)meta)->elementMeta);
        default:
            return 0;
    }
    return 0;
}

////////////////////////////////////////
/// SymbolTable
////////////////////////////////////////

SymbolTable_t SymbolTable_create() {
    SymbolTable_t table = (SymbolTable_t)malloc(sizeof(SymbolTable));
    table->table = SimpleHashTable_createWithSize(sizeof(SymbolRecord), NULL, NULL, SYMBOL_TABLE_HASH_TABLE_SIZE);
    table->nextScopeID = 0;
    table->scopeStack = SimpleArray_create(sizeof(int));
    table->currentScope = 0;
    table->nextVarID = 0;
    table->nextLabelID = 0;
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
    table->currentScope = table->nextScopeID;
    SimpleArray_pushBack(table->scopeStack, &table->nextScopeID);
    table->nextScopeID++;
}

void SymbolTable_leaveScope(SymbolTable_t table) {
    assert(table->scopeStack->num > 0);
    SimpleArray_popBack(table->scopeStack, NULL);
    table->currentScope = *(int *) SimpleArray_back(table->scopeStack);
}

int SymbolTable_getScope(SymbolTable_t table) {
    return *(int *) SimpleArray_back(table->scopeStack);
}

void SymbolTable_generateName(SymbolTable_t table, char *name, char *buffer, int bufferSize) {
    snprintf(buffer, bufferSize, "+%d_%s", table->currentScope, name);
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


SymbolDefineStatus
SymbolTable_lookupRecordInScope(SymbolTable_t table, char *name, int scope, SymbolRecord_t *outRecord) {
    char buffer[256];
    snprintf(buffer, sizeof(buffer), "+%d_%s", scope, name);
    SymbolRecord_t record = SimpleHashTable_find(table->table, buffer, (int)strlen(buffer)+1);
    if(record == NULL) {
        *outRecord = NULL;
        return SDS_Undefined;
    }
    *outRecord = record;
    if(SymbolRecord_isSymbolDefined(record))
        return SDS_Defined;
    else
        return SDS_Declared;
}

int SymbolTable_insertRecord(SymbolTable_t table, char *name, SymbolRecord_t record) {
    char fullNameBuffer[256];
    SymbolTable_generateName(table, name, fullNameBuffer, sizeof(fullNameBuffer));
#ifdef SYMBOL_TABLE_STRUCT_NAME
    if(record->type == ST_Struct){
        SymbolInfo_Struct_setName(record->info, name);
    }
#endif
    if(record->type == ST_Function){
        SymbolInfo_Function_setName(record->info, name);
    }
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

void SymbolTable_createVariableByInfo(SymbolTable_t table, SymbolRecord *outRecord, SymbolInfo_t info)
{
    outRecord->type = ST_Variable;
    outRecord->info = info;
    ((SymbolInfo_Variable_t)info)->varID = SymbolTable_getNextVarID(table);
}

void SymbolTable_createFunctionByInfo(SymbolTable_t table, SymbolRecord *outRecord, SymbolInfo_t info) {
    outRecord->type = ST_Function;
    outRecord->info = info;
}

void SymbolTable_createStructByInfo(SymbolTable_t table, SymbolRecord *outRecord, SymbolInfo_t info) {
    outRecord->type = ST_Struct;
    outRecord->info = info;
}

////////////////////////////////////////
/// SymbolRecord
////////////////////////////////////////

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


SymbolInfo_Variable_t SymbolInfo_Variable_createBaked(Symbol_Value_Type type, SymbolInfo_t meta){
    SymbolInfo_Variable_Raw info = NULL;
    switch(type){
        case SVT_Int:
            info = (SymbolInfo_Variable_Raw)malloc(sizeof(SymbolInfo_Variable));
            ((SymbolInfo_Variable_Raw)info)->type = SVT_Int;
            ((SymbolInfo_Variable_Raw)info)->meta = NULL;
            ((SymbolInfo_Variable_Raw)info)->bIsParam = 0;
            ((SymbolInfo_Variable_Raw)info)->varID = -1;
            return info;
        case SVT_Float:
            info = (SymbolInfo_Variable_Raw)malloc(sizeof(SymbolInfo_Variable));
            ((SymbolInfo_Variable_Raw)info)->type = SVT_Float;
            ((SymbolInfo_Variable_Raw)info)->meta = NULL;
            ((SymbolInfo_Variable_Raw)info)->bIsParam = 0;
            ((SymbolInfo_Variable_Raw)info)->varID = -1;
            return info;
        case SVT_Struct:
            info = (SymbolInfo_Variable_Raw)malloc(sizeof(SymbolInfo_Variable));
            ((SymbolInfo_Variable_Raw)info)->type = SVT_Struct;
            ((SymbolInfo_Variable_Raw)info)->meta = meta;
            ((SymbolInfo_Variable_Raw)info)->bIsParam = 0;
            ((SymbolInfo_Variable_Raw)info)->varID = -1;
            return info;
        case SVT_Array:
            info = (SymbolInfo_Variable_Raw)malloc(sizeof(SymbolInfo_Variable));
            ((SymbolInfo_Variable_Raw)info)->type = SVT_Array;
            ((SymbolInfo_Variable_Raw)info)->meta = meta;
            ((SymbolInfo_Variable_Raw)info)->bIsParam = 0;
            ((SymbolInfo_Variable_Raw)info)->varID = -1;
            return info;
        default:
            return NULL;
    }
}

void SymbolInfo_Variable_destroy(SymbolInfo_Variable_t info) {
    if(info == NULL)
        return;
    else if(info->type == SVT_Array){
        SymbolInfo_Array_destroy(info->meta);
    }
    free(info);
}

SymbolInfo_Array_t SymbolInfo_Array_createBaked(Symbol_Value_Type elementType, SymbolInfo_t elementStructInfo, int dimensions[], int dimensionCount){
    SymbolInfo_Array_Raw info = (SymbolInfo_Array_Raw)malloc(sizeof(SymbolInfo_Array));
    info->dimensionCount = dimensionCount;
    info->dimension = dimensions[0];
    if(dimensionCount > 1){
        info->elementType = SVT_Array;
        info->elementMeta = SymbolInfo_Array_createBaked(elementType, elementStructInfo, dimensions+1, dimensionCount-1);
    }else{
        info->elementType = elementType;
        info->elementMeta = elementStructInfo;
    }
    return info;
}

void SymbolInfo_Array_destroy(SymbolInfo_Array_t info) {
    if(info == NULL)
        return;
    if(info->elementType == SVT_Array){
        SymbolInfo_Array_destroy(info->elementMeta);
    }
    free(info);
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
    rawInfo->isDefined = 0;
    return rawInfo;
}

void SymbolInfo_Function_destroy(SymbolInfo_Function_t info) {
    if(info == NULL)
        return;
    if(info->functionName != NULL)
        free(info->functionName);
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

SymbolInfo_Parameter_t SymbolInfo_Parameter_createBaked(Symbol_Value_Type type, char* parameterName, SymbolInfo_t meta){
    SymbolInfo_Parameter_Raw info = (SymbolInfo_Parameter_Raw)malloc(sizeof(SymbolInfo_Parameter));
    info->parameterType = type;
    info->parameterName = parameterName == NULL ? NULL : strdup(parameterName);
    info->parameterMeta = meta;
    return info;
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
    ((SymbolInfo_Member_t) memberInfo)->offset = info->size;
    info->size += SymbolValue_getSize(((SymbolInfo_Member_t) memberInfo)->memberType, ((SymbolInfo_Member_t) memberInfo)->memberMeta);
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

SymbolInfo_Member_t SymbolInfo_Member_createBaked(Symbol_Value_Type memberType, char* memberName, SymbolInfo_t memberMeta){
    SymbolInfo_Member_Raw info = (SymbolInfo_Member_Raw)malloc(sizeof(SymbolInfo_Member));
    info->memberType = memberType;
    info->memberName = memberName == NULL ? NULL : strdup(memberName);
    info->memberMeta = memberMeta;
    return info;
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


int SymbolRecord_isSymbolDefined(SymbolRecord_t record) {
    switch(record->type){
        case ST_Variable:
            return 1;
        case ST_Function: {
            SymbolInfo_Function_t functionInfo = (SymbolInfo_Function_t) record->info;
            return functionInfo->isDefined;
        }
        case ST_Struct:
            return 1;
        default:
            return 0;
    }
}

int SymbolTable_getNextVarID(SymbolTable_t table) {
    return table->nextVarID++;
}

void SymbolTable_generateNextLabelName(SymbolTable_t table, char* buffer, int bufferSize){
    SymbolTable_generateNextLabelNameWithSuffix(table, buffer, bufferSize, "");
}

void SymbolTable_generateNextLabelNameWithSuffix(SymbolTable_t table, char* buffer, int bufferSize, char* suffix){
    snprintf(buffer, bufferSize, "label#%d%s", table->nextLabelID++, suffix);
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
            SymbolInfo_Struct_printDebug(arrayInfo->elementMeta, structDefBuffer, sizeof(structDefBuffer));
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
            snprintf(dimBuffer, sizeof(dimBuffer), "[%d]", arrayInfo->dimension);
            while(arrayInfo->dimensionCount > 1){
                arrayInfo = arrayInfo->elementMeta;
                snprintf(dimBuffer, sizeof(dimBuffer), "[%d]", arrayInfo->dimension);
                snprintf(dimListBuffer+strlen(dimListBuffer), sizeof(dimListBuffer)-strlen(dimListBuffer), "%s", dimBuffer);
            }
            char elementTypeBuffer[256];
            SymbolInfo_DebugHelper_getTypeString(arrayInfo->elementType, arrayInfo->elementMeta, elementTypeBuffer, sizeof(elementTypeBuffer));
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


