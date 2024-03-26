//
// Created by Crystal on 2024/3/20.
//

#ifndef LAB1_ERRORREPORTER_H
#define LAB1_ERRORREPORTER_H

#include <stdio.h>

typedef enum ErrorType_e{
    LEXICAL_ERROR_BASE = 0,

    UnrecognizedCharacter,
    InvalidIdentifier,
    InvalidNumber,
    InvalidFloat,

    UNDEF_LEXICAL_ERROR = 49,

    SYNTAX_ERROR_BASE = 50,

    UnexpectedStatement,
    UnexpectedDeclaration,
    MissingSemicolon,
    MissingRightBracket,
    MissingRightParenthesis,
    MissingComma,
    MissingSpecifier,
    UnterminatedComment,
    UnexpectedExpression,

    UNDEF_SYNTAX_ERROR = 99,

    SEMANTIC_ERROR_BASE = 100,

    UndefinedVariable,          // Error 1
    UndefinedFunctionCalled,    // Error 2
    VariableRedefinition,       // Error 3
    FunctionRedefinition,       // Error 4
    AssignmentTypeMismatch,     // Error 5
    AssignToRvalue,             // Error 6
    OperatorTypeMismatch,       // Error 7
    ReturnTypeMismatch,         // Error 8
    ParameterListMismatch,      // Error 9
    ArrayAccessOnNonArray,      // Error 10
    FunctionCalledOnNonFunction,// Error 11
    ArrayIndexTypeMismatch,     // Error 12
    MemberAccessOnNonStruct,    // Error 13
    UndefinedStructMember,      // Error 14
    InvalidMemberDefinition,    // Error 15
    ConflictStructDefinition,   // Error 16
    UndefinedStruct,            // Error 17
    UndefinedExternalFunction,  // Error 18
    ImplicitFunctionDeclaration,// Error 19

    UNDEF_SEMANTIC_ERROR = 149,
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

void yyerror(const char* msg);

#endif //LAB1_ERRORREPORTER_H
