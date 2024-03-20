//
// Created by m1504 on 2024/3/20.
//

#ifndef LAB1_SEMANTICANALYZER_H
#define LAB1_SEMANTICANALYZER_H

#include "Structure/ParserNodes.h"

// Start the semantic analysis on the root of the parser tree
// return 0 if no error, otherwise return the number of errors
int semanticAnalyze();

int semanticAnalyzeNode(ParserNode_I nodeIndex);

#endif //LAB1_SEMANTICANALYZER_H
