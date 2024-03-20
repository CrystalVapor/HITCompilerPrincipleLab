//
// Created by Crystal on 2024/3/19.
//

#include "Structure/SymbolTable.h"

#include "Structure/SemanticNodes.h"

SimpleArray_t semanticNodes;
SemanticNode_I rootIndex;

SymbolTableStack_t symbolTableStack;

int initSemanticTree(ParserNode_I parserTreeRoot) {
    rootIndex = parserTreeRoot;
}

void freeSemanticTree() {
}
