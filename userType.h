#ifndef USER_TYPE_H
#define USER_TYPE_H

#include "varInfo.h"
#include "functionInfo.h"
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class UserType {
public:
    std::string name;
    std::vector<VarInfo> vars;
    std::vector<FunctionInfo> methods;

    void addVar(const char* type, const char* name, const char* scope);
    void addMethod(const char* type, const char* name, const char* scope);
    void printMembers();
};

#endif // USER_TYPE_H

void UserType::addVar(const char* type, const char* name, const char* scope) {
    VarInfo var;
    var.type = type;
    var.name = name;
    var.scope = scope;
    vars.push_back(var);
}

void UserType::addMethod(const char* type, const char* name, const char* scope) {
    FunctionInfo method;
    method.type = type;
    method.name = name;
    method.scope = scope;
    methods.push_back(method);
}

void UserType::printMembers() {
    cout << "User type name: " << name << endl;
    cout << "Variables: " << endl;
    for (const VarInfo& v : vars) {
        cout << "name: " << v.name << " type:" << v.type << endl;
    }
    cout << "Methods: " << endl;
    for (const FunctionInfo& m : methods) {
        cout << "name: " << m.name << " type:" << m.type << endl;
    }
}

