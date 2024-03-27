//
// Created by Crystal on 2024/3/19.
//

#ifndef LAB1_SEMANTICINFO_H
#define LAB1_SEMANTICINFO_H

#include "Structure/SemanticInfo.h"
#include "Structure/SymbolTable.h"
#include "SimpleArray.h"
#include "SymbolTable.h"

////////////////////////////////////////
// SemanticInfo
////////////////////////////////////////

typedef struct SemanticInfo_s{
    // Rvalue members, following members are only valid when isLValue is false
    Symbol_Value_Type valueType;
    SymbolInfo_t valueInfo;

    // Lvalue members, following members are only valid when isLValue is true
    int scope;

    // Semantic information
    int isLValue;
}SemanticInfo;
typedef SemanticInfo* SemanticInfo_t;

/**
 * Create a new Lvalue SemanticInfo object
 * @note IN Cmm, ALL Lvalue should be Variable
 * @param valueType the value type of the LValue
 * @param valueInfo the value information of the LValue
 * @param scope the scope of the SemanticInfo object
 * @param semanticInfoList the list to collect recently created semanticInfo, used for garbage collection
 * @return a new SemanticInfo object
 */
SemanticInfo_t SemanticInfo_createLvalue(Symbol_Value_Type valueType, SymbolInfo_t valueInfo, int scope, SimpleArray_t semanticInfoList);

/**
 * Create a new Rvalue SemanticInfo object
 * @note IN Cmm, ALL Rvalue act like a variable
 * @param valueType the value type of the RValue
 * @param valueInfo the valueInfo information of the RValue
 * @param semanticInfoList the list to collect recently created semanticInfo, used for garbage collection
 * @return a new SemanticInfo object
 */
SemanticInfo_t SemanticInfo_createRvalue(Symbol_Value_Type valueType, SymbolInfo_t valueInfo, SimpleArray_t semanticInfoList);

/**
 * Make a semantic variable to a RValue object whether it is a LValue or RValue
 * @param lvalue the LValue object
 * @param semanticInfoList the list to collect recently created semanticInfo, used for garbage collection
 * @return a new RValue object
 */
SemanticInfo_t SemanticInfo_makeRvalue(SemanticInfo_t semanticInfo, SimpleArray_t semanticInfoList);

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
 * Check if the given two FunctionInfo have the same return type
 * @param a
 * @param b
 * @return
 */
int SymbolInfo_Function_isReturnTypeMatched(SymbolInfo_Function_t a, SymbolInfo_Function_t b);

/**
 * Check if the given two FunctionInfo have the same parameter list
 * @param a
 * @param b
 * @return
 */
int SymbolInfo_Function_isParameterListMatched(SymbolInfo_Function_t a, SymbolInfo_Function_t b);

/**
 * Check if the given semanticInfo is the same as the given type(whether it is a RValue or LValue)
 * @param semanticInfo the semanticInfo to be checked
 * @param type the type to be checked
 * @return 1 if the semanticInfo is the same as the given type, 0 otherwise
 */
int SemanticInfo_checkValueType(SemanticInfo_t semanticInfo, Symbol_Value_Type type);

int SemanticInfo_checkReturnType(SymbolInfo_Function_t functionInfo, SemanticInfo_t semanticInfo);

int SemanticInfo_checkParameterList(SymbolInfo_Function_t functionInfo, SemanticInfo_t* semanticInfos, int paramCount);

/**
 * Try to get the memberInfo from the given semanticInfo
 * @param semanticInfo the semanticInfo to get from
 * @param memberName the member name
 * @return the memberInfo, NULL if failed
 */
SymbolInfo_Member_t SemanticInfo_getMemberInfo(SemanticInfo_t semanticInfo, const char* memberName);

int SymbolInfo_Helper_isTypeMatched(Symbol_Value_Type aType, SymbolInfo_t aMeta, Symbol_Value_Type bType, SymbolInfo_t bMeta);

#endif //LAB1_SEMANTICINFO_H
