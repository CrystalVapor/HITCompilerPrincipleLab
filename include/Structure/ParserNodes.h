//
// Created by m1504 on 2024/3/19.
//

/*
 * 碎碎念：
 * 这里是一开始编写的地方，当时过于迷恋动态内存管理，所以将ParserNode的管理写得很复杂。
 * 实际上这里parsernode应该使用保存在数组中的指针而非保存数组索引（不直接保存数组内指针的原因是因为可能realloc后失效）
 * (再注：不过由于没有移除节点的需求，似乎可以使用块状链表以避免不断少量申请内存产生的内存碎片，同样也可以安全地保存指针)
 * 另外就算如此，parsernode的子节点也应该使用一个C数组而非动态数组。
 * 不过懒得改了，将就着用吧（
 */

#ifndef LAB1_PARSERNODES_H
#define LAB1_PARSERNODES_H

#include "CmmParserTypes.h"

#define INVALID_NODE_INDEX (-1)

#define GET_NODE(nodeIndex)  (getParserNode(nodeIndex))
#define GET_CHILD(nodeIndex, i)  (getParserNodeChild(nodeIndex, i))
#define GET_CHILD_NODE(nodeIndex, i)  (GET_NODE(GET_CHILD(nodeIndex, i)))
#define GET_CHILD_NUM(nodeIndex)  (getParserNodeChildNum(nodeIndex))

void setParserTreeRoot(ParserNode_I InRootIndex);

ParserNode_I getParserTreeRoot();

/**
 * Create a new parser node in the global node container, will return the index of the new node
 * @param symbol the symbol of the node
 * @param lineNum the line number of the node
 * @param childNum the number of children of the node
 * @param children the children of the node
 * @param fatherNodeIndex the father node of the node
 * @return the index of the new node
 */
ParserNode_I newParserNode(int symbol, int lineNum, int childNum, ParserNode_I *children, ParserNode_I fatherNodeIndex);

/**
 * Add the parser node to the global node container
 * @param node the parser node to be added
 * @return the index of the new node
 */
int ParserNodeIndexContainer_addNodeIndex(ParserNodeIndexContainer_t container, ParserNode_I index);

/**
 * Get the parser node from the global node container
 * @param index the index of the node
 * @return the parser node
 */
ParserNode_t getParserNode(ParserNode_I index);

/**
 * Get the child's node index of the parser node
 * @param index     the index of the father node
 * @param childIndex the index of the child(in the children array)
 * @return the index of the child's node(in the global node container)
 */
ParserNode_I getParserNodeChild(ParserNode_I index, int childIndex);

/**
 * Get the child's node of the parser node
 * @param index the index of the father node
 * @param childIndex the index of the child(in the children array)
 * @return the child's node
 */
ParserNode_t getParserNodeChildNode(ParserNode_I index, int childIndex);

/**
 * Get the number of children of the parser node
 * @param index the index of the node
 * @return the number of children
 */
int getParserNodeChildNum(ParserNode_I index);

/**
 * Free the global node container
 */
void freeParserNodes();

/**
 * Create a new parser node index container
 * @return the new parser node index container
 */
ParserNodeIndexContainer_t ParserNodeIndexContainer_createContainer();

/**
 * Get the parser node from the container
 * @param container the container
 * @param index the index of the node
 * @return the parser node
 */
ParserNode_t ParserNodeIndexContainer_getNode(ParserNodeIndexContainer_t container, int index);

/**
 * Add children to the parser node
 * @param nodeIndex the index of the node
 * @param childNum the number of children
 * @param children the children
 */
void addChildrenToNode(ParserNode_I nodeIndex, int childNum, ParserNode_I* children);

/**
 * Add a child to the parser node
 * @param nodeIndex the index of the node
 * @param childIndex the index of the child
 */
void addChildToNode(ParserNode_I nodeIndex, ParserNode_I childIndex);

/**
 * Convert a string(HEX,DEC,OCT) to an integer
 * @param str the string to be converted
 * @return integer converted from the string
 */
int stoi(const char* str);

/**
 * Get the parser node index from the container
 * @param container the container
 * @param index the index of the node
 * @return the parser node index
 */
ParserNode_I ParserNodeIndexContainer_getNodeIndex(ParserNodeIndexContainer_t container, int index);

/**
 * Traverse the parser tree in pre-order and print the tree
 * @param nodeIndex the index of the root node
 * @param depth the depth of the root node(used for printing)
 */
void printParserTree_PreOrder(ParserNode_I nodeIndex, int depth);

/**
 * Print all the nodes in the global node container linearly
 */
void printAllNodes();

/**
 * Print the parser node
 * @param nodeIndex the index of the node
 * @param depth the depth of the node(used for printing)
 */
void printParserNode(ParserNode_I nodeIndex, int depth);

/**
 * do not use.
 */
void yyerror(const char* msg);

/**
 * Check if the children of the node match the rule
 * @param nodeIndex the node to be checked
 * @param ruleSize the size of rule
 * @param ... rule, should be a list of token(Lexical or Syntax)
 * @return 1 if match, 0 if not match
 */
int isChildrenMatchRule(ParserNode_I nodeIndex, int ruleSize, ...);

#endif //LAB1_PARSERNODES_H
