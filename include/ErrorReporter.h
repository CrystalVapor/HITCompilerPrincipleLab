//
// Created by m1504 on 2024/3/20.
//

#ifndef LAB1_ERRORREPORTER_H
#define LAB1_ERRORREPORTER_H

#include <stdio.h>

typedef enum ErrorType_e{
    LEXICAL_ERROR_BASE = 0,
    UnrecognizedCharacter = 1,
    InvalidIdentifier = 2,
    InvalidNumber = 3,
    InvalidFloat = 4,

    SYNTAX_ERROR_BASE = 10,
    UnexpectedStatement = 11,
    UnexpectedExternalDefinition = 12,
    UnterminatedComment = 13,

    SEMANTIC_ERROR_BASE = 100,
    UndefinedVariable = 101,
    UndefinedFunctionCalled = 102,
    VariableRedefinition = 103,
    FunctionRedefinition = 104,
    TypeMismatch_Assignment = 105,
    RvalueAssignment = 106,
    TypeMismatch_Operator = 107,
    TypeMismatch_Return = 108,
    ArgListMismatch = 109,
    ArrayAccessOnNonArray = 110,
    FunctionCalledOnNonFunction = 111,
    NonIntegerIndex = 112,
    StructMemberAccessOnNonStruct = 113,
    UndefinedStructMember = 114,
    StructMemberRedefinition = 115,
    StructRedefinition = 116,
    UndefinedExternalFunction = 117,
    ImplicitFunctionDeclaration = 118,
}ErrorType;

// register an error to reporter, content of externalMessage will be malloc copied
// if there's already an error on the same line, the new one will be ignored
void reportError(int line, int errorType, char* externalMessage);

// register an error to reporter, content of externalMessage will be malloc copied and formatted
// if there's already an error on the same line, the new one will be ignored
void reportErrorFormat(int line, int errorType, const char* format, ...);

// print all errors to the file
void printError(FILE* file);

// reset the error reporter, clear all errors, and free all memory
void resetErrorReporter();

// return 0 if no error, otherwise return the number of errors
// just check if reportError is called, do not check the content of the error
int hasError();

#endif //LAB1_ERRORREPORTER_H
