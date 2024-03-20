//
// Created by Crystal on 2024/3/19.
//

#ifndef LAB1_SEMANTICNODES_H
#define LAB1_SEMANTICNODES_H

#include "SimpleArray.h"
#include "ParserNodes.h"

typedef struct SemanticNode_s{
    ParserNode_I parserNodeIndex;
    int symbol;
}SemanticNode;
typedef SemanticNode* SemanticNode_t;
typedef int SemanticNode_I;

typedef enum SemanticError_e{
    UndefinedVariable = 1,
    UndefinedFunctionCalled = 2,
    VariableRedefinition = 3,
    FunctionRedefinition = 4,
    TypeMismatch_Assignment = 5,
    RvalueAssignment = 6,
    TypeMismatch_Operator = 7,
    TypeMismatch_Return = 8,
    ArgListMismatch = 9,
    ArrayAccessOnNonArray = 10,
    FunctionCalledOnNonFunction = 11,
    NonIntegerIndex = 12,
    StructMemberAccessOnNonStruct = 13,
    UndefinedStructMember = 14,
    StructMemberRedefinition = 15,
    StructRedefinition = 16,
    UndefinedExternalFunction = 17,
    ImplicitFunctionDeclaration = 18,
}SemanticError;

int initSemanticTree(ParserNode_I parserTreeRoot);
void freeSemanticTree();

void semanticAnalyze();

void reportSemanticError(SemanticError error, int lineNum, const char** msgs);

#endif //LAB1_SEMANTICNODES_H
