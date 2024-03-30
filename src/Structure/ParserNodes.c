//
// Created by m1504 on 2024/3/19.
//

#include "Lab1.h"
#include <stdio.h>
#include "stdlib.h"
#include "string.h"
#include "Structure/SimpleArray.h"
#include "CmmParserTypes.h"
#include "Structure/SemanticInfo.h"

#include "Structure/ParserNodes.h"

SimpleArray_t parserNodes = NULL;
ParserNode_I rootIndex = INVALID_NODE_INDEX;
extern char* yytext;

void setParserTreeRoot(ParserNode_I InRootIndex){
    rootIndex = InRootIndex;
}

ParserNode_I newParserNode(int symbol, int lineNum, int childNum, ParserNode_I *children, ParserNode_I fatherNodeIndex) {
    if(parserNodes == NULL)
    {
        parserNodes = SimpleArray_create(sizeof(ParserNode));
    }
    ParserNode node;
    node.token = symbol;
    node.lineNum = lineNum;
    node.children = NULL;
    node.semanticInfo = NULL;
    switch (symbol) {
        case ID:
        case TYPE:
            node.ID = strdup(yytext);
            break;
        case INT:
            node.intVal = stoi(yytext);
            break;
        case FLOAT:
            node.floatVal = strtof(yytext, NULL);
            break;
        default:
            break;
    }
    int nodeIndex = SimpleArray_addElement(parserNodes, &node);

    addChildrenToNode(nodeIndex, childNum, children);
    if(fatherNodeIndex != INVALID_NODE_INDEX)
    {
        addChildToNode(fatherNodeIndex, nodeIndex);
    }

    return nodeIndex;
}

ParserNode_t getParserNode(ParserNode_I index){
    return (ParserNode_t) SimpleArray_at(parserNodes, index);
}

void freeParserNode(void *nodeToFree) {
    ParserNode_t node = (ParserNode_t)nodeToFree;
    if(node->children != NULL)
    {
        SimpleArray_destroy(node->children, NULL);
    }
    if(node->token == ID || node->token == TYPE)
    {
        free(node->ID);
    }
}

void freeParserNodes(){
    SimpleArray_destroy(parserNodes, freeParserNode);
}

int ParserNodeIndexContainer_addNodeIndex(ParserNodeIndexContainer_t container, ParserNode_I index){
    return SimpleArray_addElement(container, &index);
}

ParserNodeIndexContainer_t ParserNodeIndexContainer_createContainer(){
    return SimpleArray_newArrayWithCapacity(sizeof(ParserNode_I), 10);
}

ParserNode_t ParserNodeIndexContainer_getNode(ParserNodeIndexContainer_t container, int index){
    ParserNode_I* indexPtr = (ParserNode_I*) SimpleArray_at(container, index);
    return getParserNode(*indexPtr);
}

void addChildrenToNode(ParserNode_I nodeIndex, int childNum, ParserNode_I* children) {
    if(childNum == 0)
    {
        return;
    }
    ParserNode_t node = getParserNode(nodeIndex);
    if(node->children == NULL) {
        node->children = ParserNodeIndexContainer_createContainer();
        node->lineNum = getParserNode(children[0])->lineNum;
    }
    for(int i = 0; i < childNum; i++) {
        ParserNodeIndexContainer_addNodeIndex(node->children, children[i]);
    }
}

void addChildToNode(ParserNode_I nodeIndex, ParserNode_I childIndex){
    ParserNode_t node = getParserNode(nodeIndex);
    if(node->children == NULL)
    {
        node->children = ParserNodeIndexContainer_createContainer();
        node->lineNum = getParserNode(childIndex)->lineNum;
    }
    ParserNodeIndexContainer_addNodeIndex(node->children, childIndex);
}

int stoi(const char* str){
    int base = 10;
    int result = 0;
    int sign = 1;
    //处理符号和基数
    entry:
    switch(str[0]) {
        case '-':
            sign = -1;
            ++str;
            goto entry;
        case '+':
            ++str;
            goto entry;
        case '0':
            switch (str[1]) {
                case 'x':
                case 'X':
                    base = 16;
                    str+=2;
                    break;
                case '\0':
                    return 0;
                default:
                    base = 8;
                    ++str;
                    break;
            }
        default:
        break;
    }
    //此处已确保str指向真正的数字串
    //不关心无符号溢出，不可能炸，这里强转避免编译警告
    int len = (int)strlen(str);
    for(int i =0;i<len;i++)
    {
        int digit = 0;
        if(str[i]>='0' && str[i]<='9')
        {
            digit = str[i] - '0';
        }
        else if(str[i]>='a' && str[i]<='z')
        {
            digit = str[i] - 'a' + 10;
        }
        else if(str[i]>='A' && str[i]<='Z')
        {
            digit = str[i] - 'A' + 10;
        }
        result = result * base + digit;
    }
    return result * sign;
}

ParserNode_I ParserNodeIndexContainer_getNodeIndex(ParserNodeIndexContainer_t container, int index) {
    return *((ParserNode_I *) SimpleArray_at(container, index));
}

ParserNode_I getParserTreeRoot() {
    return rootIndex;
}

#pragma clang diagnostic push
#pragma ide diagnostic ignored "misc-no-recursion"
void printParserTree_PreOrder(ParserNode_I nodeIndex, int depth) {
    if(nodeIndex == INVALID_NODE_INDEX)
    {
        return;
    }
    printParserNode(nodeIndex, depth);
    ParserNode_t node = getParserNode(nodeIndex);
    if(node->children == NULL)
    {
        return;
    }
    for(int i = 0; i < node->children->num; i++)
    {
        printParserTree_PreOrder(ParserNodeIndexContainer_getNodeIndex(node->children, i), depth + 1);
    }
}
#pragma clang diagnostic pop

void printAllNodes() {
    for(int i = 0;i<parserNodes->num;i++)
    {
        printParserNode(i, 0);
    }
}

void printParserNode(ParserNode_I nodeIndex, int depth) {
    if(nodeIndex == INVALID_NODE_INDEX)
    {
        return;
    }
    ParserNode_t node = getParserNode(nodeIndex);
    if(IS_SYNTAX_TOKEN(node->token))
    {
        if(node->children!=NULL)
        {
            for(int i = 0; i < depth; i++)
            {
                printf("  ");
            }
            printf("%s (%d)\n", getGrammarSymbolName(node->token), node->lineNum);
        }

    }
    else if(IS_TERMINAL_TOKEN(node->token))
    {
        for(int i = 0; i < depth; i++)
        {
            printf("  ");
        }
        switch(node->token)
        {
            case ID:
                printf("ID: %s\n", node->ID);
                break;
            case TYPE:
                printf("TYPE: %s\n", node->ID);
                break;
            case INT:
                printf("INT: %d\n", node->intVal);
                break;
            case FLOAT:
                printf("FLOAT: %f\n", node->floatVal);
                break;
            case EQ:
            case NEQ:
            case LT:
            case GT:
            case LE:
            case GE:
                printf("RELOP\n" );
                break;
            default:
                printf("%s\n", getTokenName(node->token));
                break;
        }
    }
}

void yyerror(const char *msg) {

}

ParserNode_t getParserNodeChildNode(ParserNode_I index, int childIndex) {
    return getParserNode(getParserNodeChild(index, childIndex));
}

ParserNode_I getParserNodeChild(ParserNode_I index, int childIndex) {
    ParserNodeIndexContainer_t children = getParserNode(index)->children;
    return ParserNodeIndexContainer_getNodeIndex(children, childIndex);
}

int getParserNodeChildNum(ParserNode_I index) {
    ParserNodeIndexContainer_t children = getParserNode(index)->children;
    return children->num;
}
