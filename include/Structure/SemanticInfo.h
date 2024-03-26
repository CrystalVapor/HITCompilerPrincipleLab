//
// Created by Crystal on 2024/3/19.
//

#ifndef LAB1_SEMANTICINFO_H
#define LAB1_SEMANTICINFO_H

#include "SimpleArray.h"
#include "ParserNodes.h"
#include "SymbolTable.h"

////////////////////////////////////////
// SemanticInfo
////////////////////////////////////////

typedef struct{
    SymbolType type;
    int scope;
    SymbolInfo_t symbolInfo;
}SemanticInfo;
typedef SemanticInfo* SemanticInfo_t;

/**
 * Create a new SemanticInfo object
 * @param scope scope where the symbol is defined
 * @param symbolInfo symbol information
 * @return a new SemanticInfo object
 */
SemanticInfo_t SemanticInfo_create(int scope, SymbolInfo_t symbolInfo);

/**
 * Destroy a SemanticInfo object
 * @param semanticInfoToDestroy the SemanticInfo object to be destroyed
 */
void SemanticInfo_destroy(void* semanticInfoToDestroy);

/**
 * Compare two SemanticInfo objects' types
 * int => int, float => float
 * for struct, if their members are matched(order and type), they are matched
 * for array, if their element type and dimension count are matched, they are matched
 * @param a the first SemanticInfo object
 * @param b the second SemanticInfo object
 * @return 1 if the two objects are matched, 0 otherwise
 */
int SemanticInfo_isTypeMatched(SemanticInfo_t a, SemanticInfo_t b);

/**
 * Check if the return type of a function is matched with the return variable
 * @param functionInfo the function information stored in the symbol table
 * @param returnVariable the return variable to be checked
 * @return 1 if the return type is matched, 0 otherwise
 */
int SemanticInfo_isReturnTypeMatched(SymbolInfo_Function_t functionInfo, SemanticInfo_t returnVariable);

/**
 * Check if the parameter list is matched with the function's parameter list
 * @param functionInfo the function information stored in the symbol table
 * @param parameterList the parameter list to be checked
 * @param parameterCount the number of parameters to be checked
 * @return 1 if the parameter list is matched, 0 otherwise
 */
int SemanticInfo_isParameterListMatched(SymbolInfo_Function_t functionInfo, SemanticInfo_t parameterList[], int parameterCount);

/**
 * Check if the symbol type is matched with the given type
 * @param semanticInfo the symbol to be checked
 * @param type the type used to check
 * @return 1 if the symbol type is matched, 0 otherwise
 */
int SemanticInfo_checkSymbolType(SemanticInfo_t semanticInfo, SymbolType type);

/**
 * Check if the variable type is matched with the given type
 * only check the variable type, will not check array or struct info
 * @param semanticInfo the variable to be checked
 * @param type the type used to check
 * @return 1 if the variable type is matched, 0 otherwise
 */
int SemanticInfo_checkVariableType(SemanticInfo_t semanticInfo, Symbol_Value_Type type);

/**
 * Check if the variable is a struct variable and has the member
 * @param semanticInfo the variable to be checked
 * @param memberName the member name to be checked
 * @return 1 if the variable is a struct and has the member, 0 otherwise
 */
int SemanticInfo_hasMember(SemanticInfo_t semanticInfo, const char* memberName);
#endif //LAB1_SEMANTICINFO_H
