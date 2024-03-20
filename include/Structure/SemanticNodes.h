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


int initSemanticTree(ParserNode_I parserTreeRoot);
void freeSemanticTree();

void semanticAnalyze();

#endif //LAB1_SEMANTICNODES_H
