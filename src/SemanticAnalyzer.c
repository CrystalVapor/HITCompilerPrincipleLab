//
// Created by m1504 on 2024/3/20.
//

#include "SemanticAnalyzer.h"

int semanticErrors = 0;

int semanticAnalyze() {
    semanticErrors = 0;
    semanticAnalyzeNode(getParserTreeRoot());
    return semanticErrors;
}

int semanticAnalyzeNode(ParserNode_I nodeIndex) {
    return 0;
}
