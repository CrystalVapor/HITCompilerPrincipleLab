//
// Created by CrystalVapor on 2024/3/9.
//

#ifndef LAB1_MAIN_H
#define LAB1_MAIN_H

#include "C_Parser_Types.h"

#define YYSTYPE_IS_DECLARED 1

#define INVALID_NODE_INDEX (-1)

extern YYSTYPE yylval;
extern int yylex();

void setParserTreeRoot(ParserNode_I InRootIndex);
// Create a new parser node in the global node container, will return the index of the new node
ParserNode_I newParserNode(int symbol, int lineNum, int childNum, ParserNode_I *children, ParserNode_I fatherNodeIndex);
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
// Get the parser node index from the container
ParserNode_I ParserNodeIndexContainer_getNodeIndex(ParserNodeIndexContainer_t container, int index);
// Add the parser node to the container
int ParserNodeIndexContainer_addNodeIndex(ParserNodeIndexContainer_t container, ParserNode_I index);
// Add children to the parser node, parameter children will not be freed
void addChildrenToNode(ParserNode_I nodeIndex, int childNum, ParserNode_I* children);
// Add single child to the parser node
void addChildToNode(ParserNode_I nodeIndex, ParserNode_I childIndex);

int stoi(const char* str);
void printParserTree_PreOrder(ParserNode_I nodeIndex, int depth);
void printParserNode(ParserNode_I nodeIndex, int depth);

void reportSyntaxError(int lineNum, const char* msg);
void yyerror(const char* msg);

#endif //LAB1_MAIN_H
