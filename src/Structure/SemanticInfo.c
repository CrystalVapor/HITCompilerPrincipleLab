#pragma clang diagnostic push
#pragma ide diagnostic ignored "misc-no-recursion"
//
// Created by Crystal on 2024/3/19.
//

#include "Structure/SymbolTable.h"

#include "Structure/SemanticInfo.h"

int SymbolInfo_isStructTypeMatched(SymbolInfo_Struct_t a, SymbolInfo_Struct_t b);
int SymbolInfo_isArrayTypeMatched(SymbolInfo_Array_t a, SymbolInfo_Array_t b);

SemanticInfo_t
SemanticInfo_createLvalue(Symbol_Value_Type valueType, SymbolInfo_t valueInfo, SimpleArray_t semanticInfoList) {
    SemanticInfo_t semanticInfo = (SemanticInfo_t)malloc(sizeof(SemanticInfo));
    semanticInfo->isLValue = 1;
    semanticInfo->valueType = valueType;
    semanticInfo->valueTypeMeta = valueInfo;
    SimpleArray_pushBack(semanticInfoList, &semanticInfo);
    return semanticInfo;
}

SemanticInfo_t SemanticInfo_createRvalue(Symbol_Value_Type valueType, SymbolInfo_t valueInfo, SimpleArray_t semanticInfoList) {
    SemanticInfo_t semanticInfo = (SemanticInfo_t)malloc(sizeof(SemanticInfo));
    semanticInfo->isLValue = 0;
    semanticInfo->valueType = valueType;
    semanticInfo->valueTypeMeta = valueInfo;
    SimpleArray_pushBack(semanticInfoList, &semanticInfo);
    return semanticInfo;
}

SemanticInfo_t SemanticInfo_makeRvalue(SemanticInfo_t semanticInfo, SimpleArray_t semanticInfoList){
    if(semanticInfo->isLValue)
    {
        return SemanticInfo_createRvalue(semanticInfo->valueType, semanticInfo->valueTypeMeta, semanticInfoList);
    }
    return semanticInfo;
}

void SemanticInfo_destroy(void *semanticInfoToDestroy) {
    SemanticInfo_t* semanticInfo = (SemanticInfo_t*)semanticInfoToDestroy;
    free(*semanticInfo);
}

int SemanticInfo_isTypeMatched(SemanticInfo_t a, SemanticInfo_t b) {
    if(a==NULL || b==NULL)
    {
        return 0;
    }
    return SymbolInfo_Helper_isTypeMatched(a->valueType, a->valueTypeMeta, b->valueType, b->valueTypeMeta);
}

int SymbolInfo_Function_isReturnTypeMatched(SymbolInfo_Function_t a, SymbolInfo_Function_t b){
    return SymbolInfo_Helper_isTypeMatched(a->returnType, a->returnTypeMeta, b->returnType, b->returnTypeMeta);
}

int SymbolInfo_Function_isParameterListMatched(SymbolInfo_Function_t a, SymbolInfo_Function_t b){
    if(a->parameterCount != b->parameterCount)
    {
        return 0;
    }
    for(int i = 0; i < a->parameterCount; i++)
    {
        SymbolInfo_Parameter_t aParameter = a->parameters[i];
        SymbolInfo_Parameter_t bParameter = b->parameters[i];
        if(!SymbolInfo_Helper_isTypeMatched(aParameter->parameterType,
                                            aParameter->parameterMeta,
                                            bParameter->parameterType,
                                            bParameter->parameterMeta))
        {
            return 0;
        }
    }
    return 1;
}


int SemanticInfo_checkValueType(SemanticInfo_t semanticInfo, Symbol_Value_Type type){
    return semanticInfo->valueType == type;
}

int SemanticInfo_checkReturnType(SymbolInfo_Function_t functionInfo, SemanticInfo_t semanticInfo){
    return SymbolInfo_Helper_isTypeMatched(semanticInfo->valueType, semanticInfo->valueTypeMeta,
                                           functionInfo->returnType, functionInfo->returnTypeMeta);
}

int SemanticInfo_checkParameterList(SymbolInfo_Function_t functionInfo, SemanticInfo_t* semanticInfos, int paramCount){
    if(functionInfo->parameterCount != paramCount)
    {
        return 0;
    }
    for(int i = 0; i < paramCount; i++)
    {
        SymbolInfo_Parameter_t parameter = functionInfo->parameters[i];
        if(!SymbolInfo_Helper_isTypeMatched(parameter->parameterType, parameter->parameterMeta,
                                            semanticInfos[i]->valueType, semanticInfos[i]->valueTypeMeta))
        {
            return 0;
        }
    }
    return 1;
}


SymbolInfo_Member_t SemanticInfo_getMemberInfo(SemanticInfo_t semanticInfo, const char *memberName) {
    if(!SemanticInfo_checkValueType(semanticInfo, SVT_Struct)) {
        return NULL;
    }
    SymbolInfo_Struct_t structInfo = (SymbolInfo_Struct_t)semanticInfo->valueTypeMeta;
    for(int i = 0; i < structInfo->memberCount; i++) {
        SymbolInfo_Member_t member = structInfo->members[i];
        if(strcmp(member->memberName, memberName) == 0) {
            return member;
        }
    }
    return NULL;
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
    return a->dimensionCount == b->dimensionCount
        && SymbolInfo_Helper_isTypeMatched(a->elementType, a->elementMeta,
                                           b->elementType, b->elementMeta);
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