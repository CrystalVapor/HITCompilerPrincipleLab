#pragma clang diagnostic push
#pragma ide diagnostic ignored "misc-no-recursion"
//
// Created by Crystal on 2024/3/19.
//

#include "Structure/SymbolTable.h"

#include "Structure/SemanticInfo.h"

int SymbolInfo_isVariableTypeMatched(SymbolInfo_Variable_t a, SymbolInfo_Variable_t b);
int SymbolInfo_isFunctionTypeMatched(SymbolInfo_Function_t a, SymbolInfo_Function_t b);
int SymbolInfo_isStructTypeMatched(SymbolInfo_Struct_t a, SymbolInfo_Struct_t b);
int SymbolInfo_isArrayTypeMatched(SymbolInfo_Array_t a, SymbolInfo_Array_t b);
int SymbolInfo_Helper_isTypeMatched(Symbol_Value_Type aType, SymbolInfo_t aMeta, Symbol_Value_Type bType, SymbolInfo_t bMeta);

SemanticInfo_t SemanticInfo_create(int scope, SymbolInfo_t symbolInfo) {
    SemanticInfo_t semanticInfo = (SemanticInfo_t)malloc(sizeof(SemanticInfo));
    semanticInfo->scope = scope;
    semanticInfo->symbolInfo = symbolInfo;
    return semanticInfo;
}

void SemanticInfo_destroy(void *semanticInfoToDestroy) {
    free(semanticInfoToDestroy);
}

int SemanticInfo_isTypeMatched(SemanticInfo_t a, SemanticInfo_t b) {
    if(a->type != b->type) {
        return 0;
    }
    switch (a->type) {
        case ST_Variable:
            return SymbolInfo_isVariableTypeMatched((SymbolInfo_Variable_t)a->symbolInfo, (SymbolInfo_Variable_t)b->symbolInfo);
        case ST_Function:
            return SymbolInfo_isFunctionTypeMatched((SymbolInfo_Function_t)a->symbolInfo, (SymbolInfo_Function_t)b->symbolInfo);
        case ST_Struct:
            return SymbolInfo_isStructTypeMatched((SymbolInfo_Struct_t)a->symbolInfo, (SymbolInfo_Struct_t)b->symbolInfo);
        default:
            return 0;
    }
}

int SemanticInfo_isReturnTypeMatched(SymbolInfo_Function_t functionInfo, SemanticInfo_t returnVariable) {
    if(returnVariable->type != ST_Variable)
    {
        return 0;
    }
    SymbolInfo_Variable_t variableInfo = (SymbolInfo_Variable_t)returnVariable->symbolInfo;
    return SymbolInfo_Helper_isTypeMatched(variableInfo->type, variableInfo->meta, functionInfo->returnType, functionInfo->returnTypeMeta);
}

int SemanticInfo_isParameterListMatched(SymbolInfo_Function_t functionInfo, SemanticInfo_t *parameterList,
                                        int parameterCount) {
    if(functionInfo->parameterCount == parameterCount) {
        for(int i = 0; i < parameterCount; i++) {

            if(parameterList[i]->type != ST_Variable) {
                return 0;
            }
            SymbolInfo_Variable_t variableInfo = (SymbolInfo_Variable_t)parameterList[i]->symbolInfo;
            SymbolInfo_Parameter_t parameter = functionInfo->parameters[i];
            if(!SymbolInfo_Helper_isTypeMatched(variableInfo->type,
                                                variableInfo->meta,
                                                parameter->parameterType,
                                                parameter->parameterMeta)) {
                return 0;
            }
        }
        return 1;
    }
    return 0;
}

int SemanticInfo_checkSymbolType(SemanticInfo_t semanticInfo, SymbolType type) {
    return semanticInfo->type == type;
}

int SemanticInfo_checkVariableType(SemanticInfo_t semanticInfo, Symbol_Value_Type type) {
    if(semanticInfo->type != ST_Variable) {
        return 0;
    }
    SymbolInfo_Variable_t variableInfo = (SymbolInfo_Variable_t)semanticInfo->symbolInfo;
    return variableInfo->type == type;
}

int SemanticInfo_hasMember(SemanticInfo_t semanticInfo, const char *memberName) {
    if(!SemanticInfo_checkVariableType(semanticInfo, SVT_Struct)) {
        return 0;
    }
    SymbolInfo_Variable_t variableInfo = (SymbolInfo_Variable_t)semanticInfo->symbolInfo;
    SymbolInfo_Struct_t structInfo = (SymbolInfo_Struct_t)variableInfo->meta;
    for(int i = 0; i < structInfo->memberCount; i++) {
        SymbolInfo_Member_t member = structInfo->members[i];
        if(strcmp(member->memberName, memberName) == 0) {
            return 1;
        }
    }
    return 0;
}

int SymbolInfo_isVariableTypeMatched(SymbolInfo_Variable_t a, SymbolInfo_Variable_t b){
    return SymbolInfo_Helper_isTypeMatched(a->type, a->meta, b->type, b->meta);
}
int SymbolInfo_isFunctionTypeMatched(SymbolInfo_Function_t a, SymbolInfo_Function_t b){
    if(SymbolInfo_Helper_isTypeMatched(a->returnType,
                                       a->returnTypeMeta,
                                       b->returnType,
                                       b->returnTypeMeta)) {
        if(a->parameterCount == b->parameterCount)
        {
            for(int i = 0; i < a->parameterCount; i++)
            {
                SymbolInfo_Parameter_t aParam = a->parameters[i];
                SymbolInfo_Parameter_t bParam = b->parameters[i];
                if(!SymbolInfo_Helper_isTypeMatched(aParam->parameterType,
                                                    aParam->parameterMeta,
                                                    bParam->parameterType,
                                                    bParam->parameterMeta))
                {
                    return 0;
                }
            }
            return 1;
        }
    }
    return 0;
}
int SymbolInfo_isStructTypeMatched(SymbolInfo_Struct_t a, SymbolInfo_Struct_t b){
    if(a->memberCount == b->memberCount)
    {
        for(int i = 0; i < a->memberCount; i++)
        {
            SymbolInfo_Member_t aMember = a->members[i];
            SymbolInfo_Member_t bMember = b->members[i];
            if(!SymbolInfo_Helper_isTypeMatched(aMember->memberType,
                                                aMember->memberMeta,
                                                bMember->memberType,
                                                bMember->memberMeta))
            {
                return 0;
            }
        }
        return 1;
    }
    return 0;
}

int SymbolInfo_isArrayTypeMatched(SymbolInfo_Array_t a, SymbolInfo_Array_t b) {
    if(a->dimensionCount == b->dimensionCount)
    {
        if(SymbolInfo_Helper_isTypeMatched(a->elementType,
                                           a->elementStructInfo,
                                           b->elementType,
                                           b->elementStructInfo))
        {
            return 1;
        }
    }
    return 0;
}

int SymbolInfo_Helper_isTypeMatched(Symbol_Value_Type aType, SymbolInfo_t aMeta, Symbol_Value_Type bType,
                                    SymbolInfo_t bMeta) {
    if(aType == bType)
    {
        switch (aType) {
            case SVT_Int:
            case SVT_Float:
            case SVT_Void:
                return 1;
            case SVT_Struct:
                return SymbolInfo_isStructTypeMatched((SymbolInfo_Struct_t)aMeta, (SymbolInfo_Struct_t)bMeta);
            case SVT_Array:
                return SymbolInfo_isArrayTypeMatched((SymbolInfo_Array_t)aMeta, (SymbolInfo_Array_t)bMeta);
            default:
                return 0;
        }
    }
    return 0;
}

#pragma clang diagnostic pop