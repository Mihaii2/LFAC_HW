#ifndef USEFUL_FUNCTIONS_H
#define USEFUL_FUNCTIONS_H

#include <string>
#include <vector>
#include "userType.h"
#include "varInfo.h"
#include "functionInfo.h"
using namespace std;

VarInfo* createVarInfo(std::string type, std::string name, std::string scope, const std::vector<UserType>& userTypes, int arraySize = 0, void* memoryLocation = nullptr);
FunctionInfo* createFunctionInfo(std::string type, std::string name, std::string scope, std::vector<VarInfo> params);

#endif // USEFUL_FUNCTIONS_H

extern vector<UserType> userTypes;

VarInfo* createVarInfo(string type, string name, string scope, int arraySize = 0, void* memoryLocation = nullptr) {
    VarInfo* var = new VarInfo();
    var->type = type;
    var->name = name;
    var->scope = scope;
    // Deduct the size from the type
    if (type == "int") {
        var->size = 4;
    } else if (type == "float") {
        var->size = 4;
    } else if (type == "char") {
        var->size = 1;
    } else if (type == "bool") {
        var->size = 1;
    } else if (type == "string") {
        var->size = 1;
    } else {
        // User defined type
        for (const UserType& userType : userTypes) {
            if (userType.name == type) {
                var->size = 0;
                for (const VarInfo& v : userType.vars) {
                    var->size += v.size;
                }
                break;
            }
        }
    }
    // Allocate memory for the variable
    if (arraySize == 0) {
        var->memoryLocation = malloc(var->size);
    }
    else {
        var->memoryLocation = malloc(var->size * arraySize);
        var->size = var->size * arraySize;
    }
    return var;
}

FunctionInfo* createFunctionInfo(string type, string name, string scope, vector<VarInfo> params) {
    FunctionInfo* func = new FunctionInfo();
    func->type = type;
    func->name = name;
    func->scope = scope;
    func->params = params;
    return func;
}