//
// Created by Crystal on 2024/3/31.
//

#ifndef LAB1_INTERCODEGENERATOR_H
#define LAB1_INTERCODEGENERATOR_H

#include "CmmParserTypes.h"

#define MAX_INTERCODE_PARAM 5

struct InterCodeInfo;

typedef struct {
    void (*generateInterCode) (struct InterCodeInfo* interCodeInfo, FILE* file);
}InterCodeInfo_VT;
typedef InterCodeInfo_VT* InterCodeInfo_VT_t;

typedef enum {
    IC_LABEL = 0,
    IC_FUNC,
    IC_ASSIGN,
    IC_ADD,
    IC_SUB,
    IC_MUL,
    IC_DIV,

    IC_ADDR,
    IC_DEREF_GET,
    IC_DEREF_SET,

    IC_GOTO,
    IC_COND_GOTO,

    IC_RETURN,

    IC_DEC,
    IC_ARG,
    IC_CALL,
    IC_PARAM,
    IC_READ,
    IC_WRITE
}InterCodeType;

typedef enum{
    ICP_INT,
    ICP_VAR,
    ICP_LABEL,
}InterCodeParam_Type;

typedef struct {
    InterCodeParam_Type type;
    union{
        int intVal;
        char* varName;
        char* labelName;
    };
}InterCodeParam;

typedef struct{
    InterCodeInfo_VT_t vptr;
    InterCodeType type;
    int paramNum;
    InterCodeParam params[MAX_INTERCODE_PARAM];
}InterCodeInfo;
typedef InterCodeInfo* InterCodeInfo_t;

/**
 * Generate intermediate code for the given syntax tree.
 * tree must be valid and has no error.
 * @param rootNodeIndex the index of the root node of the syntax tree.
 * @param file output file of InterCode.
 */
void generateInterCode(ParserNode_I rootNodeIndex, FILE* file);

/**
 * End the generation of intermediate code.
 * Will clear the memory used for generating intermediate code.
 */
void generateInterCode_End();

/**
 * Create a new InterCodeInfo.
 * @param type the type of the intermediate code.
 * @param paramNum the number of parameters.
 * @param ... the parameters.
 * @return the new InterCodeInfo.
 */
InterCodeInfo_t InterCodeInfo_create(InterCodeType type, int paramNum, ...);

#endif //LAB1_INTERCODEGENERATOR_H
