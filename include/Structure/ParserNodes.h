//
// Created by m1504 on 2024/3/19.
//

#ifndef LAB1_PARSERNODES_H
#define LAB1_PARSERNODES_H

#include "CmmParserTypes.h"

#define INVALID_NODE_INDEX (-1)

void setParserTreeRoot(ParserNode_I InRootIndex);

ParserNode_I getParserTreeRoot();

// Create a new parser node in the global node container, will return the index of the new node
ParserNode_I newParserNode(int symbol, int lineNum, int childNum, ParserNode_I *children, ParserNode_I fatherNodeIndex);

// Add the parser node to the container
int ParserNodeIndexContainer_addNodeIndex(ParserNodeIndexContainer_t container, ParserNode_I index);

// Get the parser node from the global node container
ParserNode_t getParserNode(ParserNode_I index);

// free the parser node's content, will free the memory of the node's content
void freeParserNodeContent(ParserNode_I index);

// Free the global node container
void freeParserNodes();

// Create a new parser node container
ParserNodeIndexContainer_t ParserNodeIndexContainer_createContainer();

// Get the parser node from the container
ParserNode_t ParserNodeIndexContainer_getNode(ParserNodeIndexContainer_t container, int index);

// Add children to the parser node, parameter children will not be freed
void addChildrenToNode(ParserNode_I nodeIndex, int childNum, ParserNode_I* children);

// Add single child to the parser node
void addChildToNode(ParserNode_I nodeIndex, ParserNode_I childIndex);

int stoi(const char* str);

// Get the parser node index from the container
ParserNode_I ParserNodeIndexContainer_getNodeIndex(ParserNodeIndexContainer_t container, int index);

void printParserTree_PreOrder(ParserNode_I nodeIndex, int depth);

void printAllNodes();

void printParserNode(ParserNode_I nodeIndex, int depth);

void yyerror(const char* msg);

#endif //LAB1_PARSERNODES_H
