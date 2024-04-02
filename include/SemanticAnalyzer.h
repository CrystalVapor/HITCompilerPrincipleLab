//
// Created by Crystal on 2024/3/20.
//

#ifndef LAB1_SEMANTICANALYZER_H
#define LAB1_SEMANTICANALYZER_H

/**
 * Analyze the semantic of the parser tree.
 * @return the number of semantic errors.
 */
int semanticAnalyze(ParserNode_I rootNodeIndex);

/**
 * End the semantic analyze, free the memory used by the semantic analyzer.
 */
void semanticAnalyze_End();

/**
 * Get the symbol table after the semantic analyze.
 * Only valid after the semantic analyze.
 * @return the symbol table.
 */
SymbolTable_t semanticAnalyze_getSymbolTable();

#endif //LAB1_SEMANTICANALYZER_H
