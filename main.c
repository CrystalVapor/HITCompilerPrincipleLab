#include <stdio.h>
#include "main.h"
#include "C_Parser_Types.h"
#include "SimpleArray.h"
#include "string.h"
#include "stdlib.h"

//#define DEBUG_PARSER_TREE

SimpleArray_t parserNodes = NULL;
ParserNode_I rootIndex = INVALID_NODE_INDEX;
int hasError = 0;

extern char* yytext;
extern int yylineno;

extern void yyrestart(FILE* input_file);

int main(int argc, char** argv){
    if(argc<2)
    {
        fprintf(stderr, "Usage: %s <input file>\n", argv[0]);
        return 1;
    }
    FILE* file = fopen(argv[1], "r");
    if(file == NULL)
    {
        fprintf(stderr, "Error: Cannot open file %s\n", argv[1]);
        return 1;
    }
    yyrestart(file);
    yyparse();
    if(!hasError)
    {
        printParserTree_PreOrder(rootIndex, 0);
    }

#ifdef DEBUG_PARSER_TREE
    for(int i = 0;i<parserNodes->num;i++)
    {
        printParserNode(i, 0);
    }
#endif

    freeParserNodes();
    return 0;
}

void setParserTreeRoot(ParserNode_I InRootIndex){
    rootIndex = InRootIndex;
}

ParserNode_I newParserNode(int symbol, int lineNum, int childNum, ParserNode_I *children, ParserNode_I fatherNodeIndex) {
    if(parserNodes == NULL)
    {
        parserNodes = SimpleArray_newArray(sizeof(ParserNode));
    }
    ParserNode node;
    node.symbol = symbol;
    node.lineNum = lineNum;
    node.children = NULL;
    switch (symbol) {
        case ID:
        case TYPE:
            node.ID = malloc(strlen(yytext) + 1);
            strcpy(node.ID, yytext);
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
    return (ParserNode_t)SimpleArray_getElement(parserNodes, index);
}

void freeParserNodeContent(ParserNode_I index) {
    ParserNode_t node = getParserNode(index);
    if(node->children != NULL)
    {
        SimpleArray_freeSimpleArray(node->children);
    }
    if(node->symbol == ID || node->symbol == TYPE)
    {
        free(node->ID);
    }
}

void freeParserNodes(){
    if(parserNodes != NULL)
    {
        for(int i = 0; i < parserNodes->num; i++)
        {
            freeParserNodeContent(i);
        }
        SimpleArray_freeSimpleArray(parserNodes);
    }
}

ParserNodeIndexContainer_t ParserNodeIndexContainer_createContainer(){
    return SimpleArray_newArray(sizeof(ParserNode_I));
}

ParserNode_t ParserNodeIndexContainer_getNode(ParserNodeIndexContainer_t container, int index){
    ParserNode_I* indexPtr = (ParserNode_I*)SimpleArray_getElement(container, index);
    return getParserNode(*indexPtr);
}

int ParserNodeContainer_addNodeIndex(ParserNodeIndexContainer_t container, ParserNode_I index){
    return SimpleArray_addElement(container, &index);
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
        ParserNodeContainer_addNodeIndex(node->children, children[i]);
    }
}

void addChildToNode(ParserNode_I nodeIndex, ParserNode_I childIndex){
    ParserNode_t node = getParserNode(nodeIndex);
    if(node->children == NULL)
    {
        node->children = ParserNodeIndexContainer_createContainer();
        node->lineNum = getParserNode(childIndex)->lineNum;
    }
    ParserNodeContainer_addNodeIndex(node->children, childIndex);
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

#pragma clang diagnostic push
#pragma ide diagnostic ignored "misc-no-recursion"
void printParserTree_PreOrder(ParserNode_I nodeIndex, int depth) {
    if(rootIndex == INVALID_NODE_INDEX)
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

void printParserNode(ParserNode_I nodeIndex, int depth) {
    if(nodeIndex == INVALID_NODE_INDEX)
    {
        return;
    }
    ParserNode_t node = getParserNode(nodeIndex);
    if(node->symbol>=PROGRAM && node->symbol<=ARGS)
    {
        if(node->children!=NULL)
        {
            for(int i = 0; i < depth; i++)
            {
                printf("  ");
            }
            printf("%s (%d)\n", getGrammarSymbolName(node->symbol), node->lineNum);
        }

    }
    else if(node->symbol>=YYEMPTY && node->symbol<=WHILE)
    {
        for(int i = 0; i < depth; i++)
        {
            printf("  ");
        }
        switch(node->symbol)
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
            default:
                printf("%s\n", getTokenName(node->symbol));
                break;
        }
    }
}

ParserNode_I ParserNodeIndexContainer_getNodeIndex(ParserNodeIndexContainer_t container, int index) {
    return *((ParserNode_I *) SimpleArray_getElement(container, index));
}

void reportSyntaxError(int lineNum, const char *msg) {
    hasError = 1;
    fprintf(stderr, "Error type B at Line %d: %s\n", lineNum, msg);
}

void yyerror(const char *msg) {

}



