//
// Created by Crystal on 2024/3/19.
//

/** 碎碎念：
 * 我是个傻逼
 * 符号创建流程中设计了一套从raw到baked的转换，也就是从拿到struct名称到拿到struct信息的转换
 * 我以为这样能方便struct变量、struct数组、嵌套struct的创建
 * 然而tmd到了现在我才发现，这个设计是多余的
 * 在创建相关符号的时候一定是先查表拿到了struct信息才能创建的
 * 根本不需要脱裤子放屁地先创建一个raw再bake
 * 就算是前置声明也肯定是先创建一个空的baked丢进符号表，这个流程里完全没有structname的事
 * 艹！这个b流程从设计到编写到debug花了我两天
 * 我是个傻逼
 * 现在还得回头再搭一套基于全程bakedmeta的流程
 * 虽说不改也不是不能用，可以直接从struct那里提一个rawmeta出来，但性能浪费我就不说了
 * 还是码吧，但我tm现在已经不想玩了
 * 艹
 * 我是个傻逼
 * Crystal 2024/3/27 11:50
 */

/*
 * 为了后续翻找方便，相关弃用方法已移除。
 * Crystal 2024/4/6 12:00
 */

#ifndef LAB1_SYMBOLTABLE_H
#define LAB1_SYMBOLTABLE_H

#include "SimpleArray.h"
#include "SimpleHashTable.h"

#define INVALID_VAR_ID (-1)
#define INVALID_LABEL_ID (-1)

////////////////////////////////////////
// Enums for SymbolRecord
////////////////////////////////////////

/**
 * The status of the symbol.
 */
typedef enum SymbolDefineStatus_e {
    SDS_Undefined = -1,     // A symbol is not declared
    SDS_Declared = 0,     // A symbol is declared but not defined
    SDS_ExternalDeclared = 1,       // A symbol is declared and defined in other nextScopeID
    SDS_ExternalDefined = 2,      // A symbol is defined and usable in current nextScopeID
    SDS_Defined = 3,      // A symbol is declared in other nextScopeID
} SymbolDefineStatus;

/**
 * The type of the symbol.
 */
typedef enum SymbolType_e {
    ST_Variable = 0b00,
    ST_Function = 0b01,
    ST_Struct = 0b10,
} SymbolType;

////////////////////////////////////////
// Types for Symbol's value
////////////////////////////////////////

/**
 * The type of the symbol value.
 */
typedef enum Symbol_Value_Type_e {
    SVT_Int = 0b00,
    SVT_Float = 0b01,
    SVT_Struct = 0b10,
    SVT_Array = 0b11,
    SVT_Void = 0b100,
} Symbol_Value_Type;

/**
 * The size of the symbol value.
 */
int SymbolValue_getSize(Symbol_Value_Type type, void *meta);

////////////////////////////////////////
///SymbolRecord
////////////////////////////////////////

typedef void* SymbolInfo_t;

typedef struct {
    SymbolType type;
    SymbolInfo_t info;
    int scope;
} SymbolRecord;
typedef SymbolRecord* SymbolRecord_t;

void SymbolRecord_destroy(void* record);
void SymbolRecord_printDebug(SymbolRecord_t record, char* buffer, int bufferSize);

////////////////////////////////////////
/// SymbolTable
////////////////////////////////////////

#define INVALID_SCOPE (-1)

typedef struct SymbolTable_s {
    SimpleHashTable_t table;    // hash table for symbol records, key is full name of symbol, records stored as flat struct SymbolRecord
    int nextScopeID;            // next scope ID that will be used
    SimpleArray_t scopeStack;   // stack of scope IDs
    int currentScope;     // current scopeID that is being used
    int nextVarID;        // next variable ID that will be used
    int nextLabelID;      // next label ID that will be used
} SymbolTable;
typedef SymbolTable* SymbolTable_t;

/**
 * Create a symbol table.
 * @return The symbol table.
 */
SymbolTable_t SymbolTable_create();

/**
 * Destroy a symbol table.
 * @param table The symbol table.
 */
void SymbolTable_destroy(void* table);

/**
 * Enter a new scope, will get a new scope ID and update prefix.
 * prefix is always same as the top of the scope stack.
 * @param table The symbol table.
 */
void SymbolTable_enterScope(SymbolTable_t table);

/**
 * Leave current scope, will pop an ID from ID stack and update prefix.
 * prefix is always same as the top of the scope stack.
 * @param table The symbol table.
 */
void SymbolTable_leaveScope(SymbolTable_t table);

/**
 * Get the current scope.
 * @param table The symbol table.
 * @return The current scope.
 */
int SymbolTable_getScope(SymbolTable_t table);

/**
 * Generate a new name with the current nextScopeID prefix in input buffer.
 * @param table The symbol table.
 * @param name The name.
 * @return The name without the nextScopeID prefix(a pointer to the middle of buffer).
 */
void SymbolTable_generateName(SymbolTable_t table, char* name, char* buffer, int bufferSize);

/**
 * Lookup a symbol in the symbol table.
 * @param table The symbol table.
 * @param name The name of the symbol.
 * @param outRecord The output record.
 * @return The status of the symbol.
 */
SymbolDefineStatus SymbolTable_lookupRecord(SymbolTable_t table, char* name, SymbolRecord_t* outRecord);

/**
 * Lookup a symbol in the symbol table.
 * @param table The symbol table.
 * @param name The name of the symbol.
 * @param outRecord The output record.
 * @return index of the nextScopeID where the symbol is found, -1 if not found.
 */
int SymbolTable_internalLookupRecord(SymbolTable_t table, char* name, SymbolRecord_t* outRecord);

/**
 * Lookup a symbol in the symbol table in the specific scope.
 * @param table The symbol table.
 * @param name The name of the symbol.
 * @param scope The scope to search.
 * @param outRecord The output record.
 * @return The status of the symbol.
 */
SymbolDefineStatus SymbolTable_lookupRecordInScope(SymbolTable_t table, char* name, int scope, SymbolRecord_t* outRecord);

/**
 * Insert a symbol into the symbol table, content will be copied.
 * @param table The symbol table.
 * @param name The name of the symbol, will be duplicated.
 * @param record The record.
 * @return 0 if success, -1 if failed.
 */
int SymbolTable_insertRecord(SymbolTable_t table, char* name, SymbolRecord_t record);

/**
 * Creates a blank variable record with valid function info, the meta need to be well-baked.
 * will also allocate a new variable ID for the variable.
 * ID can be accessed by SymbolRecord->info->varID
 * @param table     The symbol table
 * @param outRecord The output record, should be a pointer to valid memory of SymbolRecord
 * @param info      The meta data of the variable
 * @return SE_Success if success, failed otherwise
 */
void SymbolTable_createVariableByInfo(SymbolTable_t table, SymbolRecord *outRecord, SymbolInfo_t info);

/**
 * Creates a blank function record with valid function info, the meta need to be well-baked.
 * @param table     The symbol table
 * @param outRecord The output record, should be a pointer to valid memory of SymbolRecord
 * @param info      The meta data of the function
 * @return SE_Success if success, failed otherwise
 */
void SymbolTable_createFunctionByInfo(SymbolTable_t table, SymbolRecord *outRecord, SymbolInfo_t info);

/**
 * Creates a blank struct record with valid struct info, the meta need to be well-baked.
 * @param table     The symbol table
 * @param outRecord The output record, should be a pointer to valid memory of SymbolRecord
 * @param info      The meta data of the struct
 * @return SE_Success if success, failed otherwise
 */
void SymbolTable_createStructByInfo(SymbolTable_t table, SymbolRecord *outRecord, SymbolInfo_t info);

int SymbolTable_getCurrentVarID(SymbolTable_t table);

int SymbolTable_getCurrentLabelID(SymbolTable_t table);

int SymbolTable_getNextVarID(SymbolTable_t table);

char* SymbolTable_generateNextLabelName(SymbolTable_t table);

int SymbolTable_generateTempVariable(SymbolTable_t table, char* buffer, int bufferSize);

int SymbolTable_generateParamVariable(SymbolTable_t table, int paramID, char* buffer, int bufferSize);

int SymbolTable_generateLabel(SymbolTable_t table, char* buffer, int bufferSize);

////////////////////////////////////////
/// SymbolInfo
////////////////////////////////////////

typedef struct {
    Symbol_Value_Type type;
    SymbolInfo_t meta;
    char isParam;
    int varID;
} SymbolInfo_Variable;
typedef SymbolInfo_Variable* SymbolInfo_Variable_t;
typedef SymbolInfo_Variable* SymbolInfo_Variable_Raw;

/**
 * Create a new baked SymbolInfo_Variable with baked meta info.
 * @param type The type of the variable.
 * @param meta The baked meta data of the variable.
 * @return The baked SymbolInfo_Variable.
 */
SymbolInfo_Variable_t SymbolInfo_Variable_createBaked(Symbol_Value_Type type, SymbolInfo_t meta);

/**
 * Destroy the baked SymbolInfo_Variable.
 * @param info The baked SymbolInfo_Variable.
 */
void SymbolInfo_Variable_destroy(SymbolInfo_Variable_t info);

        typedef struct {
            Symbol_Value_Type elementType;
            SymbolInfo_t elementMeta;
            int dimensionCount;
            int dimension;
        } SymbolInfo_Array;
        typedef SymbolInfo_Array* SymbolInfo_Array_t;
        typedef SymbolInfo_Array* SymbolInfo_Array_Raw;

        /**
         * Create a new baked SymbolInfo_Array with baked element struct info.
         * @param elementType The type of the elements in the array.
         * @param elementStructInfo The struct info of the elements in the array.
         * @param dimensions The dimensions and its length of the array, -1 if it is not fixed.
         * @param dimensionCount The count of the dimensions.
         * @return The raw SymbolInfo_Array.
         */
        SymbolInfo_Array_t SymbolInfo_Array_createBaked(Symbol_Value_Type elementType, SymbolInfo_t elementStructInfo, int dimensions[], int dimensionCount);

        /**
         * Destroy the baked SymbolInfo_Array.
         * @param info The baked SymbolInfo_Array.
         */
        void SymbolInfo_Array_destroy(SymbolInfo_Array_t info);

typedef struct {
    Symbol_Value_Type returnType;
    SymbolInfo_t returnTypeMeta;
    char* functionName;
    int parameterCount;
    SymbolInfo_t* parameters;
    int isDefined;
    int firstDeclaredLine;
} SymbolInfo_Function;
typedef SymbolInfo_Function* SymbolInfo_Function_t;
typedef SymbolInfo_Function* SymbolInfo_Function_Raw;

/**
 * Create a new baked SymbolInfo_Function with baked meta info.
 * @param returnType     The return type of the function, SVT_Void for void.
 * @param returnTypeMeta The baked meta data of the return type.
 * @param parameterTypes An array of parameter types, length must match the parameterCount.
 * @param parameterNames An array of parameter names, length must match the parameterCount, all content will be duplicated.
 * @param parametersMeta An array of baked parameter metadata, length must match the parameterCount.
 *                       <code>NULL</code> if the parameter is not a struct or an array.
 *                       baked SymbolInfo_Struct_t if the parameter is a struct.
 *                       baked SymbolInfo_Array_t if the parameter is an array.
 * @param parameterCount
 * @return
 */
SymbolInfo_Function_t
SymbolInfo_Function_createBaked(Symbol_Value_Type returnType, SymbolInfo_t returnTypeMeta, Symbol_Value_Type parameterTypes[],
                                char *parameterNames[], void *parametersMeta[], int parameterCount);

/**
 * Destroy the baked SymbolInfo_Function.
 * @param info The baked SymbolInfo_Function.
 */
void SymbolInfo_Function_destroy(SymbolInfo_Function_t info);

int SymbolInfo_Function_hasParameterName(SymbolInfo_Function_t functionInfo, char* parameterName);

void SymbolInfo_Function_addParameter(SymbolInfo_Function_t functionInfo, SymbolInfo_t parameter);
/**
 * Get the name of the function.
 * @param info The baked SymbolInfo_Function.
 * @return The name of the function.
 */
char* SymbolInfo_Function_getName(SymbolInfo_Function_t info);

/**
 * Set the name of the function.
 * @param info The baked SymbolInfo_Function.
 * @param name The name of the function, will be duplicated.
 */
void SymbolInfo_Function_setName(SymbolInfo_Function_t info, char* name);

        typedef struct {
            Symbol_Value_Type parameterType;
            char* parameterName;
            SymbolInfo_t parameterMeta;
        } SymbolInfo_Parameter;
        typedef SymbolInfo_Parameter* SymbolInfo_Parameter_t;
        typedef SymbolInfo_Parameter* SymbolInfo_Parameter_Raw;

        /**
         * Create a new baked SymbolInfo_Parameter with baked meta info.
         * @param type The type of the parameter.
         * @param parameterName The name of the parameter, will be duplicated if not NULL.
         * @param meta The baked meta data of the parameter.
         *             <code>NULL</code> if the parameter is not a struct or an array.
         *             baked SymbolInfo_Struct_t if the parameter is a struct.
         *             baked SymbolInfo_Array_t if the parameter is an array.
         * @return The baked SymbolInfo_Parameter.
         */
        SymbolInfo_Parameter_t SymbolInfo_Parameter_createBaked(Symbol_Value_Type type, char* parameterName, SymbolInfo_t meta);

typedef struct {
#ifdef SYMBOL_TABLE_STRUCT_NAME
    char* structName;
#endif
    int memberCount;
    SymbolInfo_t* members;
    int size;
} SymbolInfo_Struct;
typedef SymbolInfo_Struct* SymbolInfo_Struct_t;
typedef SymbolInfo_Struct* SymbolInfo_Struct_Raw;

/**
 * Create a new baked SymbolInfo_Struct with baked meta info.
 * @param memberTypes   An array of member types, length must match the memberCount.
 * @param memberNames   An array of member names, length must match the memberCount, all content will be duplicated, memberName cannot be NULL.
 * @param memberMeta    An array of member metadata.
 *                      <code>NULL</code> if the member is not a struct or an array.
 *                      baked SymbolInfo_Struct_t if the member is a struct.
 *                      baked SymbolInfo_Array_t if the member is an array.
 * @param memberCount   The count of the members.
 * @return baked SymbolInfo_Struct_t if success, NULL if failed.
 */
SymbolInfo_Struct_t
SymbolInfo_Struct_createBaked(Symbol_Value_Type *memberTypes, char **memberNames, void **memberMeta, int memberCount);

/** Destroy the baked SymbolInfo_Struct.
 * @param info The baked SymbolInfo_Struct.
 */
void SymbolInfo_Struct_destroy(SymbolInfo_Struct_t info);

int SymbolInfo_Struct_checkMemberName(SymbolInfo_Struct_t info, char* memberName);

/**
 * Insert a member into the struct.
 * @param info The baked SymbolInfo_Struct.
 * @param memberInfo The member info.
 */
void SymbolInfo_Struct_insertMember(SymbolInfo_Struct_t info, SymbolInfo_t memberInfo);

#ifdef SYMBOL_TABLE_STRUCT_NAME
/**
 * Get the name of the struct.
 * @param info The baked SymbolInfo_Struct.
 * @return The name of the struct.
 */
char* SymbolInfo_Struct_getName(SymbolInfo_Struct_t info);
/**
 * Set the name of the struct.
 * @param info The baked SymbolInfo_Struct.
 * @param name The name of the struct, will be duplicated.
 */
void SymbolInfo_Struct_setName(SymbolInfo_Struct_t info, char* name);
#endif

        typedef struct {
            Symbol_Value_Type memberType;
            SymbolInfo_t memberMeta;
            char* memberName;
            int offset;
        } SymbolInfo_Member;
        typedef SymbolInfo_Member* SymbolInfo_Member_t;
        typedef SymbolInfo_Member* SymbolInfo_Member_Raw;
        /**
         * Create a new SymbolInfo_Member.
         * @param memberType The type of the member.
         * @param memberName The name of the member, will be duplicated.
         * @param memberMeta The meta data of the member.
         *                   <code>NULL</code> if the member is not a struct or an array.
         *                   <code>char[]</code> if the member is a struct, represent the name of the struct without the nextScopeID prefix.
         *                   <code>SymbolInfo_Array_t</code> (create by <code>SymbolInfo_Array_create</code>, **need to be raw**) if the member is an array.
         * @return The raw SymbolInfo_Member.
         * @see SymbolInfo_Array_create
         */
        SymbolInfo_Member_Raw SymbolInfo_Member_create(Symbol_Value_Type memberType, char* memberName, void* memberMeta);

        /**
         * Create a new baked SymbolInfo_Member with baked meta info.
         * @param memberType The type of the member.
         * @param memberName The name of the member, will be duplicated.
         * @param memberMeta The baked meta data of the member.
         *                  <code>NULL</code> if the member is not a struct or an array.
         *                  baked SymbolInfo_Struct_t if the member is a struct.
         *                  baked SymbolInfo_Array_t if the member is an array.
         * @return
         */
        SymbolInfo_Member_t SymbolInfo_Member_createBaked(Symbol_Value_Type memberType, char* memberName, SymbolInfo_t memberMeta);

        /**
         * Destroy the baked SymbolInfo_Member.
         * @param info The baked SymbolInfo_Member.
         */
        void SymbolInfo_Member_destroy(SymbolInfo_Member_t info);

/**
 * Check if the symbol is defined.
 * @param info The symbol info.
 * @return 1 if defined, 0 if not defined.
 */
int SymbolRecord_isSymbolDefined(SymbolRecord_t record);




#endif //LAB1_SYMBOLTABLE_H
