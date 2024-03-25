//
// Created by Crystal on 2024/3/19.
//

#ifndef LAB1_SYMBOLTABLE_H
#define LAB1_SYMBOLTABLE_H

#include "SimpleArray.h"
#include "SimpleHashTable.h"

#define SYMBOL_TABLE_DEBUG

#ifdef SYMBOL_TABLE_DEBUG
#define SYMBOL_TABLE_STRUCT_NAME
#define SYMBOL_TABLE_FUNCTION_NAME
#endif

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
    SDS_Initialized = 4   // A symbol is defined and initialized
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
// Error Enum for SymbolTable Actions
////////////////////////////////////////

/**
 * The error code of the symbol table.
 */
typedef enum {
    SE_Success = 0,                            // No error
    SE_NameExists = -1,                  // The name already exists
    SE_NameNotFound = -2,                // The name not found
    SE_TypeMismatch = -3,                // The type mismatch
    SE_UnexpectedNullPointer = -4,       // Unexpected error, always means a NULL SymbolInfo is baked
    SE_UnexpectedSymbolValueType = -5,   // Unexpected error, always means a VariableInfo with unexpected value type(e.g. SVT_Void) is baked
    SE_StructNotFound = -6,              // The struct not found
    SE_StructNotDefined = -7,            // The struct is not defined
}SymbolTable_Error;


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

////////////////////////////////////////
///SymbolRecord
////////////////////////////////////////

typedef void* SymbolInfo_t;

typedef struct {
    SymbolType type;
    SymbolInfo_t info;
} SymbolRecord;
typedef SymbolRecord* SymbolRecord_t;

SymbolRecord_t SymbolRecord_create(SymbolType type, SymbolInfo_t info);
void SymbolRecord_destroy(void* record);
void SymbolRecord_printDebug(SymbolRecord_t record, char* buffer, int bufferSize);

////////////////////////////////////////
/// SymbolTable
////////////////////////////////////////

typedef struct SymbolTable_s {
    SimpleHashTable_t table;    // hash table for symbol records, key is full name of symbol, records stored as flat struct SymbolRecord
    int nextScopeID;            // next scope ID that will be used
    SimpleArray_t scopeStack;   // stack of scope IDs
    char scopePrefix[64];       // prefix of the current scope
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
 * Generate a new name with the current nextScopeID prefix in input buffer.
 * @param table The symbol table.
 * @param name The name.
 * @return The name without the nextScopeID prefix(a pointer to the middle of buffer).
 */
char* SymbolTable_generateName(SymbolTable_t table, char* name, char* buffer, int bufferSize);

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
 * Insert a symbol into the symbol table, content will be copied.
 * @param table The symbol table.
 * @param name The name of the symbol, will be duplicated.
 * @param record The record.
 * @return 0 if success, -1 if failed.
 */
int SymbolTable_insertRecord(SymbolTable_t table, char* name, SymbolRecord_t record);

/**
 * Creates a blank variable record with valid variable info, will auto bake all the metadata in the given symbol table.
 *
 * @param table The symbol table.
 * @param outRecord The output record.
 * @param type  The type of the variable.
 * @param meta  The meta data of the variable.
 *              <code>NULL</code> if the variable is not a struct or an array.
 *              <code>char[]</code> if the variable is a struct, represent the name of the struct without the nextScopeID prefix.
 *              <code>SymbolInfo_Array_t</code> (create by <code>SymbolInfo_Array_create()</code>, **need to be raw**) if the variable is an array.
 * @return SE_Success if success, failed otherwise.
 * @see SymbolInfo_Array_create
 */
SymbolTable_Error
SymbolTable_createVariable(SymbolTable_t table, SymbolRecord *outRecord, Symbol_Value_Type type, void *meta);

/**
 * Creates a blank function record with valid function info, will auto bake all the metadata in the given symbol table.
 * @param table             the symbol table
 * @param outRecord         the output record
 * @param returnType        the return type of the function
 * @param parameterTypes    an array of parameter types, length must match the parameterCount
 * @param parametersMeta    an array of parameter metadata, length must match the parameterCount
 *                          <code>NULL</code> if the parameter is not a struct or an array
 *                          <code>char[]</code> if the parameter is a struct, represent the name of the struct without the nextScopeID prefix
 *                          <code>SymbolInfo_Array_t</code> (create by SymbolInfo_Array_create, need to be raw) if the parameter is an array
 * @param parameterCount    the count of the parameters
 * @return SE_Success if success, failed otherwise
 * @see SymbolInfo_Array_create
 */
SymbolTable_Error
SymbolTable_createFunction(SymbolTable_t table, SymbolRecord *outRecord, Symbol_Value_Type returnType,
                           void *returnTypeMeta, Symbol_Value_Type *parameterTypes,
                           char **parameterNames, void **parametersMeta, int parameterCount);

/** Create a blank struct record with valid struct info, will auto bake all the metadata in the given symbol table.
 * @param table The symbol table.
 * @param outRecord The output record.
 * @param memberTypes An array of member types.
 * @param memberMeta An array of member metadata.
 *                    <code>NULL</code> if the member is not a struct or an array.
 *                    <code>char[]</code> if the member is a struct, represent the name of the struct without the nextScopeID prefix.
 *                    <code>SymbolInfo_Array_t</code> (create by <code>SymbolInfo_Array_create</code>, **need to be raw**) if the member is an array.
 * @param memberCount The count of the members.
 * @return SE_Success if success, failed otherwise.
 * @see SymbolInfo_Array_create
 */
SymbolTable_Error
SymbolTable_createStruct(SymbolTable_t table, SymbolRecord *outRecord, Symbol_Value_Type *memberTypes,
                         char **memberNames, void **memberMeta, int memberCount);

////////////////////////////////////////
/// SymbolInfo
////////////////////////////////////////

typedef struct {
    Symbol_Value_Type type;
    SymbolInfo_t meta;
} SymbolInfo_Variable;
typedef SymbolInfo_Variable* SymbolInfo_Variable_t;
typedef SymbolInfo_Variable* SymbolInfo_Variable_Raw;
/**
 * Create a new SymbolInfo_Variable.
 * @param type The type of the variable.
 * @param meta The meta data of the variable.
 *             <code>NULL</code> if the variable is not a struct or an array.
 *             <code>char[]</code> if the variable is a struct, represent the name of the struct without the nextScopeID prefix.
 *             <code>SymbolInfo_Array_t</code> (create by <code>SymbolInfo_Array_create</code>, **need to be raw**) if the variable is an array.
 * @return The raw SymbolInfo_Variable.
 * @see SymbolInfo_Array_create
 */
SymbolInfo_Variable_Raw SymbolInfo_Variable_create(Symbol_Value_Type type, void* meta);
/**
 * Bake the SymbolInfo_Variable, will try to find the struct info or bake array info in the symbol table.
 * @param table The symbol table.
 * @param rawInfo The raw SymbolInfo_Variable.
 * @return 0 if success, -1 if failed.
 */
SymbolTable_Error SymbolInfo_Variable_bake(SymbolTable_t table, SymbolInfo_Variable_Raw rawInfo);
/**
 * Destroy the raw SymbolInfo_Variable.
 * @param info The raw SymbolInfo_Variable.
 */
void SymbolInfo_Variable_destroyRaw(SymbolInfo_Variable_Raw info);
/**
 * Destroy the baked SymbolInfo_Variable.
 * @param info The baked SymbolInfo_Variable.
 */
void SymbolInfo_Variable_destroy(SymbolInfo_Variable_t info);

        typedef struct {
            Symbol_Value_Type elementType;
            int dimensionCount;
            int dimensions[16];
            SymbolInfo_t elementStructInfo;
        } SymbolInfo_Array;
        typedef SymbolInfo_Array* SymbolInfo_Array_t;
        typedef SymbolInfo_Array* SymbolInfo_Array_Raw;
        /**
         * Create a new SymbolInfo_Array.
         * @param elementType The type of the elements in the array.
         * @param dimensions The dimensions and its length of the array, -1 if it is not fixed.
         * @param dimensionCount The count of the dimensions.
         * @param structName The name of the struct if the element type is SVT_Struct, <code>NULL</code> otherwise.
         * @return The raw SymbolInfo_Array.
         */
        SymbolInfo_Array_Raw SymbolInfo_Array_create(Symbol_Value_Type elementType, int dimensions[], int dimensionCount, char structName[]);
        /**
         * Bake the SymbolInfo_Array, will try to find the struct info in the symbol table.
         * @param table The symbol table.
         * @param rawInfo The raw SymbolInfo_Array.
         * @return 0 if success, -1 if failed.
         */
        SymbolTable_Error SymbolInfo_Array_bake(SymbolTable_t table, SymbolInfo_Array_Raw rawInfo);
        /**
         * Destroy the raw SymbolInfo_Array.
         * @param info The raw SymbolInfo_Array.
         */
        void SymbolInfo_Array_destroyRaw(SymbolInfo_Array_Raw info);
        /**
         * Destroy the baked SymbolInfo_Array.
         * @param info The baked SymbolInfo_Array.
         */
        void SymbolInfo_Array_destroy(SymbolInfo_Array_t info);

typedef struct {
#ifdef SYMBOL_TABLE_FUNCTION_NAME
    char* functionName;
#endif
    Symbol_Value_Type returnType;
    SymbolInfo_t returnTypeMeta;
    int parameterCount;
    SymbolInfo_t* parameters;
} SymbolInfo_Function;
typedef SymbolInfo_Function* SymbolInfo_Function_t;
typedef SymbolInfo_Function* SymbolInfo_Function_Raw;

/**
 * Create a new SymbolInfo_Function.
 * @param returnType The return type of the function, SVT_Void for void.
 * @param returnTypeMeta The meta data of the return type.
 * @param parameterTypes An array of parameter types, length must match the parameterCount.
 * @param parametersMeta An array of parameter metadata, length must match the parameterCount.
 *                       <code>NULL</code> if the parameter is not a struct or an array.
 *                       <code>char[]</code> if the parameter is a struct, represent the name of the struct without the nextScopeID prefix.
 *                       <code>SymbolInfo_Array_t</code> (create by <code>SymbolInfo_Array_create</code>, **need to be raw**) if the parameter is an array.
 * @param parameterCount The count of the parameters.
 * @return The raw SymbolInfo_Function.
 * @see SymbolInfo_Array_create
 */
SymbolInfo_Function_Raw
SymbolInfo_Function_create(Symbol_Value_Type returnType, void *returnTypeMeta, Symbol_Value_Type parameterTypes[],
                           char *parameterNames[], void *parametersMeta[], int parameterCount);
/**
 * Bake the SymbolInfo_Function's return type, will try to find the struct info or bake array info in the symbol table.
 * @param table The symbol table.
 * @param rawInfo The raw SymbolInfo_Function.
 * @return 0 if success, -1 if failed.
 */
SymbolTable_Error SymbolInfo_Function_bakeReturnType(SymbolTable_t table, SymbolInfo_Function_Raw rawInfo);

/**
 * Bake the SymbolInfo_Function's parameters, will try to find the struct info or bake array info in the symbol table.
 * @param table The symbol table.
 * @param rawInfo The raw SymbolInfo_Function.
 * @param errorParameterIndex The index of the parameter if failed to bake, equal to ParameterCount if success.
 * @return 0 if success, -1 if failed.
 */
SymbolTable_Error SymbolInfo_Function_bakeParameters(SymbolTable_t table, SymbolInfo_Function_Raw rawInfo, int* errorParameterIndex);

/**
 * Destroy the raw SymbolInfo_Function.
 * @param info The raw SymbolInfo_Function.
 * @param retvalBakeResult Bake result of retval, use 0 if successfully baked, otherwise not.
 * @param bakedParameterCount The count of the baked parameters, used if the baking failed, use 0 to destroy all as raw.
 */
void SymbolInfo_Function_destroyRaw(SymbolInfo_Function_Raw info, int retvalBakeResult, int bakedParameterCount);
/**
 * Destroy the baked SymbolInfo_Function.
 * @param info The baked SymbolInfo_Function.
 */
void SymbolInfo_Function_destroy(SymbolInfo_Function_t info);

#ifdef SYMBOL_TABLE_FUNCTION_NAME
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
#endif

        typedef struct {
            Symbol_Value_Type parameterType;
            char* parameterName;
            SymbolInfo_t parameterMeta;
        } SymbolInfo_Parameter;
        typedef SymbolInfo_Parameter* SymbolInfo_Parameter_t;
        typedef SymbolInfo_Parameter* SymbolInfo_Parameter_Raw;
        /**
         * Create a new SymbolInfo_Parameter.
         * @param type The type of the parameter.
         * @param parameterName The name of the parameter, will be duplicated if not NULL.
         * @param meta The meta data of the parameter.
         *             <code>NULL</code> if the parameter is not a struct or an array.
         *             <code>char[]</code> if the parameter is a struct, represent the name of the struct without the nextScopeID prefix.
         *             <code>SymbolInfo_Array_t</code> (create by <code>SymbolInfo_Array_create</code>, **need to be raw**) if the parameter is an array.
         * @return The raw SymbolInfo_Parameter.
         * @see SymbolInfo_Array_create
         */
        SymbolInfo_Parameter_Raw SymbolInfo_Parameter_create(Symbol_Value_Type type, char* parameterName,void* meta);
        /**
         * Bake the SymbolInfo_Parameter, will try to find the struct info or bake array info in the symbol table.
         * @param table The symbol table.
         * @param rawInfo The raw SymbolInfo_Parameter.
         * @return 0 if success, -1 if failed.
         */
        SymbolTable_Error SymbolInfo_Parameter_bake(SymbolTable_t table, SymbolInfo_Parameter_Raw rawInfo);
        /**
         * Destroy the raw SymbolInfo_Parameter.
         * @param info The raw SymbolInfo_Parameter.
         */
        void SymbolInfo_Parameter_destroyRaw(SymbolInfo_Parameter_Raw info);
        /**
         * Destroy the baked SymbolInfo_Parameter.
         * @param info The baked SymbolInfo_Parameter.
         */
        void SymbolInfo_Parameter_destroy(SymbolInfo_Parameter_t info);

typedef struct {
#ifdef SYMBOL_TABLE_STRUCT_NAME
    char* structName;
#endif
    int memberCount;
    SymbolInfo_t* members;
} SymbolInfo_Struct;
typedef SymbolInfo_Struct* SymbolInfo_Struct_t;
typedef SymbolInfo_Struct* SymbolInfo_Struct_Raw;
/**
 * Create a new SymbolInfo_Struct.
 * @param memberTypes An array of member types.
 * @param memberMeta An array of member metadata.
 *                   <code>NULL</code> if the member is not a struct or an array.
 *                   <code>char[]</code> if the member is a struct, represent the name of the struct without the nextScopeID prefix.
 *                   <code>SymbolInfo_Array_t</code> (create by <code>SymbolInfo_Array_create</code>, **need to be raw**) if the member is an array.
 * @param memberCount The count of the members.
 * @return The raw SymbolInfo_Struct.
 * @see SymbolInfo_Array_create
 */
SymbolInfo_Struct_Raw
SymbolInfo_Struct_create(Symbol_Value_Type *memberTypes, char **memberNames, void **memberMeta, int memberCount);
/** Bake the SymbolInfo_Struct, will try to find the struct info or bake array info in the symbol table.
 * @param table The symbol table.
 * @param rawInfo The raw SymbolInfo_Struct.
 * @param errorMemberIndex The index of the member if failed to bake, equal to MemberCount if success.
 * @return 0 if success, -1 if failed.
 */
SymbolTable_Error SymbolInfo_Struct_bake(SymbolTable_t table, SymbolInfo_Struct_Raw rawInfo, int* errorMemberIndex);
/** Destroy the raw SymbolInfo_Struct.
 * @param info The raw SymbolInfo_Struct.
 */
void SymbolInfo_Struct_destroyRaw(SymbolInfo_Struct_Raw info, int bakedMemberCount);
/** Destroy the baked SymbolInfo_Struct.
 * @param info The baked SymbolInfo_Struct.
 */
void SymbolInfo_Struct_destroy(SymbolInfo_Struct_t info);

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
            char* memberName;
            SymbolInfo_t memberMeta;
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
         * Bake the SymbolInfo_Member, will try to find the struct info or bake array info in the symbol table.
         * @param table The symbol table.
         * @param rawInfo The raw SymbolInfo_Member.
         * @return SE_Success if success, failed otherwise.
         */
        SymbolTable_Error SymbolInfo_Member_bake(SymbolTable_t table, SymbolInfo_Member_Raw rawInfo);
        /**
         * Destroy the raw SymbolInfo_Member.
         * @param info The raw SymbolInfo_Member.
         */
        void SymbolInfo_Member_destroyRaw(SymbolInfo_Member_Raw info);
        /**
         * Destroy the baked SymbolInfo_Member.
         * @param info The baked SymbolInfo_Member.
         */
        void SymbolInfo_Member_destroy(SymbolInfo_Member_t info);

/**
 * Bake the SymbolInfo with the struct name.
 * Whenever it was called it will always free the structName.
 * @param table The symbol table.
 * @param structName The name of the struct.
 * @param foundStruct The found structInfo ptr, will be NULL if failed to find the struct.
 * @return SE_Success if success, failed otherwise.
 */
SymbolTable_Error SymbolInfo_bakeStructName(SymbolTable_t table, char* structName, SymbolInfo_Struct_t* foundStruct);

/**
 * Check if the symbol is defined.
 * @param info The symbol info.
 * @return 1 if defined, 0 if not defined.
 */
int SymbolRecord_isSymbolDefined(SymbolRecord_t record);




#endif //LAB1_SYMBOLTABLE_H
